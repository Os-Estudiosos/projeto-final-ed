import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from utils import execution_time
import os
from typing import Iterator
import multiprocessing as mp


def get_mean_time_and_mean_comparisons(chunks: Iterator[pd.DataFrame], time_mean, comparision_mean):
    total_lines = 0
    total_time_sum = 0
    total_comparisions = 0
    for i, df in enumerate(chunks):
        total_lines += len(df)
        time_sum = df["time"].sum()
        comparisions_sum = df["comparisions"].sum()
        
        total_comparisions += comparisions_sum
        total_time_sum += time_sum
    
    mean_time = total_time_sum / total_lines
    mean_comparisions = total_comparisions / total_lines

    time_mean.value = mean_time
    comparision_mean.value = mean_comparisions


def group_by_and_average(chunks: Iterator[pd.DataFrame], wich: str, queue):
    registered_comparisions = None
    registered_times = None
    registered_lines = None

    for chunk in chunks:
        grouped_chunk = chunk.groupby("treeHeight")

        comparisions_sum_result = grouped_chunk["comparisions"].sum().copy()
        if registered_comparisions is None:
            registered_comparisions = comparisions_sum_result
        else:
            partial_sum = registered_comparisions + comparisions_sum_result
            registered_comparisions = partial_sum.combine_first(comparisions_sum_result).combine_first(registered_comparisions)
        
        times_sum_result = grouped_chunk["time"].sum().copy()
        if registered_times is None:
            registered_times = times_sum_result
        else:
            partial_sum = registered_times + times_sum_result
            registered_times = partial_sum.combine_first(times_sum_result).combine_first(registered_times)

        number_of_lines_per_treeHeight = grouped_chunk.size().copy()
        if registered_lines is None:
            registered_lines = number_of_lines_per_treeHeight
        else:
            partial_sum = registered_lines + number_of_lines_per_treeHeight
            registered_lines = partial_sum.combine_first(number_of_lines_per_treeHeight).combine_first(registered_lines)
    
    average_comparisions = registered_comparisions / registered_lines
    average_performance = registered_times / registered_lines

    
    queue.put((wich, average_comparisions, average_performance))


@execution_time
def generate_insert_graphics(
    bst_insert_path: Iterator[pd.DataFrame],
    avl_insert_path: Iterator[pd.DataFrame],
    rbt_insert_path: Iterator[pd.DataFrame],
    graphics_path: str
):
    bst_insert = pd.read_csv(bst_insert_path, chunksize=100000, sep=";")
    avl_insert = pd.read_csv(avl_insert_path, chunksize=100000, sep=";")
    rbt_insert = pd.read_csv(rbt_insert_path, chunksize=100000, sep=";")

    bst_mean_time = mp.Value('d', 0.0)
    bst_mean_comparisions = mp.Value('d', 0.0)

    avl_mean_time = mp.Value('d', 0.0)
    avl_mean_comparisions = mp.Value('d', 0.0)

    rbt_mean_time = mp.Value('d', 0.0)
    rbt_mean_comparisions = mp.Value('d', 0.0)

    # Tratando os dataframes passados
    bst_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(bst_insert, bst_mean_time, bst_mean_comparisions)
    )

    avl_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(avl_insert, avl_mean_time, avl_mean_comparisions)
    )

    rbt_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(rbt_insert, rbt_mean_time, rbt_mean_comparisions)
    )

    bst_cleaning_process.start()
    avl_cleaning_process.start()
    rbt_cleaning_process.start()

    bst_cleaning_process.join()
    avl_cleaning_process.join()
    rbt_cleaning_process.join()

    plot_df = pd.DataFrame({
        "median_time": [
            bst_mean_time.value,
            avl_mean_time.value,
            rbt_mean_time.value
        ],
        "mean_comparisions": [
            bst_mean_comparisions.value,
            avl_mean_comparisions.value,
            rbt_mean_comparisions.value
        ],
        "tree": ["BST", "AVL", "RBT"]
    })

    
    plt.title("Média do Tempo de Inserção em Nanosegundos por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="median_time",
        palette="pastel",
        x="tree",
        legend=False
    )
    plt.ylabel("Média do Tempo de Inserção (Nanosegundos)")
    plt.xlabel("Tipo de Árvore")
    plt.savefig(os.path.join(graphics_path, "Insertion_Time_Mean.png"))
    plt.close()

    plt.title("Média de Comparações na Inserção por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="mean_comparisions",
        palette="pastel",
        x="tree",
        legend=False
    )
    plt.ylabel("Média de Comparações")
    plt.xlabel("Tipo de Árvore")
    plt.savefig(os.path.join(graphics_path, "Insertion_Comparisions_Mean.png"))
    plt.close()


@execution_time
def generate_insert_difference_graphics(
    bst_insert_path: Iterator[pd.DataFrame],
    avl_insert_path: Iterator[pd.DataFrame],
    rbt_insert_path: Iterator[pd.DataFrame],
    graphics_path: str
):
    queue = mp.Queue()
    processes = []

    bst_insert = pd.read_csv(bst_insert_path, chunksize=100000, sep=";")
    avl_insert = pd.read_csv(avl_insert_path, chunksize=100000, sep=";")
    rbt_insert = pd.read_csv(rbt_insert_path, chunksize=100000, sep=";")

    bst_grouping_process = mp.Process(
        target=group_by_and_average,
        args=(
            bst_insert,
            "bst",
            queue
        )
    )

    avl_grouping_process = mp.Process(
        target=group_by_and_average,
        args=(
            avl_insert,
            "avl",
            queue
        )
    )

    rbt_grouping_process = mp.Process(
        target=group_by_and_average,
        args=(
            rbt_insert,
            "rbt",
            queue
        )
    )

    processes.append(bst_grouping_process)
    processes.append(avl_grouping_process)
    processes.append(rbt_grouping_process)

    for process in processes:
        process.start()

    infos_to_plot = []

    for _ in range(len(processes)):
        infos_to_plot.append(queue.get())
    
    for process in processes:
        process.join()
    

    plt.title("Boxplot da Média de Comparações por Inserção na Árvore")
    algorithm_series = None
    insertion = None

    for info in infos_to_plot:
        if algorithm_series is None:
            algorithm_series = pd.Series([ info[0] for _ in range(len(info[1])) ])
        else:
            algorithm_series = pd.concat([ algorithm_series, pd.Series([ info[0] for _ in range(len(info[1])) ]) ]).reset_index(drop=True)
        
        if insertion is None:
            insertion = info[1]
        else:
            insertion = pd.concat([insertion, info[1]]).reset_index(drop=True)
    
    means_plot_df = pd.DataFrame({
        "algorithm": algorithm_series,
        "comparisions": insertion
    })

    sns.boxplot(
        data=means_plot_df,
        x="algorithm",
        y="comparisions",
        legend=False,
        palette="pastel",
        hue="algorithm"
    )

    plt.ylabel("Média de Comparações")
    plt.xlabel("Algoritmo")

    plt.savefig(os.path.join(graphics_path, "Mean_Comparisisons_Boxplot.png"))
    plt.close()


    plt.title("Boxplot da Média de Performance (Nanosegundo) por Inserção na Árvore")
    algorithm_series = None
    insertion = None

    for info in infos_to_plot:
        if algorithm_series is None:
            algorithm_series = pd.Series([ info[0] for _ in range(len(info[2])) ])
        else:
            algorithm_series = pd.concat([ algorithm_series, pd.Series([ info[0] for _ in range(len(info[2])) ]) ]).reset_index(drop=True)
        
        if insertion is None:
            insertion = info[2]
        else:
            insertion = pd.concat([insertion, info[2]]).reset_index(drop=True)
    
    means_plot_df = pd.DataFrame({
        "algorithm": algorithm_series,
        "times": insertion
    })

    sns.boxplot(
        data=means_plot_df,
        x="algorithm",
        y="times",
        legend=False,
        palette="pastel",
        hue="algorithm"
    )

    plt.ylabel("Tempo Médio de Desempenho (Nanosegundos)")
    plt.xlabel("Algoritmo")

    plt.savefig(os.path.join(graphics_path, "Mean_Performance_Boxplot.png"))
    plt.close()
    
    colors = {
        "avl": "#90B8D0",
        "rbt": "#66BB88",
        "bst": "#E57373"
    }

    plt.title("Média de Comparações em Função da Altura da Árvore")
    ax = plt.gca()
    ax.set_axisbelow(True)
    ax.set_facecolor("#eeeeee")
    for spine in ax.spines.values():
        spine.set_visible(False)
    ax.tick_params(axis="both", labelsize=8)
    for info in infos_to_plot:
        plt.plot(info[1].index, info[1], "--o", label=info[0], linewidth=1, markersize=4, color=colors[info[0]])
    plt.xlabel("Altura")
    plt.ylabel("Média de Comparações")
    plt.legend()
    plt.grid(color="white")
    plt.savefig(os.path.join(graphics_path, "Mean_Comparisions_per_Height.png"))
    plt.close()

    plt.title("Média de Performance em Função da Altura da Árvore")
    ax = plt.gca()
    ax.set_axisbelow(True)
    ax.set_facecolor("#eeeeee")
    for spine in ax.spines.values():
        spine.set_visible(False)
    ax.tick_params(axis="both", labelsize=8)
    for info in infos_to_plot:
        plt.plot(info[2].index, info[2], "--o", label=info[0], linewidth=1, markersize=4, color=colors[info[0]])
    plt.xlabel("Altura")
    plt.ylabel("Média de Performance (Nanosegundos)")
    plt.grid(color="white")
    plt.legend()
    plt.savefig(os.path.join(graphics_path, "Mean_Performance_per_Height.png"))
    plt.close()


@execution_time
def generate_read_graphics(
    bst_insert_path: Iterator[pd.DataFrame],
    avl_insert_path: Iterator[pd.DataFrame],
    rbt_insert_path: Iterator[pd.DataFrame],
    graphics_path: str
):
    bst_insert = pd.read_csv(bst_insert_path, chunksize=100000, sep=";")
    avl_insert = pd.read_csv(avl_insert_path, chunksize=100000, sep=";")
    rbt_insert = pd.read_csv(rbt_insert_path, chunksize=100000, sep=";")

    bst_mean_time = mp.Value('d', 0.0)
    bst_mean_comparisions = mp.Value('d', 0.0)

    avl_mean_time = mp.Value('d', 0.0)
    avl_mean_comparisions = mp.Value('d', 0.0)

    rbt_mean_time = mp.Value('d', 0.0)
    rbt_mean_comparisions = mp.Value('d', 0.0)

    # Tratando os dataframes passados
    bst_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(bst_insert, bst_mean_time, bst_mean_comparisions)
    )

    avl_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(avl_insert, avl_mean_time, avl_mean_comparisions)
    )

    rbt_cleaning_process = mp.Process(
        target=get_mean_time_and_mean_comparisons,
        args=(rbt_insert, rbt_mean_time, rbt_mean_comparisions)
    )

    bst_cleaning_process.start()
    avl_cleaning_process.start()
    rbt_cleaning_process.start()

    bst_cleaning_process.join()
    avl_cleaning_process.join()
    rbt_cleaning_process.join()

    plot_df = pd.DataFrame({
        "median_time": [
            bst_mean_time.value,
            avl_mean_time.value,
            rbt_mean_time.value
        ],
        "mean_comparisions": [
            bst_mean_comparisions.value,
            avl_mean_comparisions.value,
            rbt_mean_comparisions.value
        ],
        "tree": ["BST", "AVL", "RBT"]
    })

    plt.title("Média do Tempo de Busca em Nanosegundos por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="median_time",
        palette="pastel",
        x="tree",
        legend=False
    )
    plt.ylabel("Média do Tempo de Busca (Nanosegundos)")
    plt.xlabel("Tipo de Árvore")
    plt.savefig(os.path.join(graphics_path, "Search_Time_Median.png"))
    plt.close()

    plt.title("Média de Comparações na Busca por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="mean_comparisions",
        palette="pastel",
        x="tree",
        legend=False
    )
    plt.ylabel("Média de Comparações")
    plt.xlabel("Tipo de Árvore")

    plt.savefig(os.path.join(graphics_path, "Search_Comparisions_Median.png"))
    plt.close()
