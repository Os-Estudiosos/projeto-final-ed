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


def group_by_and_average(chunks: Iterator[pd.DataFrame], wich: str, group_column: str, queue):
    registered_comparisions = None
    registered_times = None
    registered_lines = None

    for chunk in chunks:
        grouped_chunk = chunk.groupby(group_column)

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


def group_to_boxplot(chunks: Iterator[pd.DataFrame], column, queue, wich):
    column_series = None
    for chunk in chunks:
        if column_series is None:
            column_series = chunk[column]
        else:
            column_series = pd.concat([column_series, chunk[column]])

    algorithm_series = pd.Series([wich for _ in range(len(column_series))])

    df = pd.DataFrame({
        "algorithm": algorithm_series,
        column: column_series
    })

    queue.put(df)

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
            avl_mean_time.value,
            bst_mean_time.value,
            rbt_mean_time.value
        ],
        "mean_comparisions": [
            avl_mean_comparisions.value,
            bst_mean_comparisions.value,
            rbt_mean_comparisions.value
        ],
        "tree": ["AVL", "BST", "RBT"]
    })

    colors = {
        "AVL": "#90B8D0",
        "BST": "#66BB88",
        "RBT": "#E57373"
    }
    
    plt.title("Média do Tempo de Inserção em Nanosegundos por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="median_time",
        palette=colors,
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
        palette=colors,
        x="tree",
        legend=False
    )
    plt.ylabel("Média de Comparações")
    plt.xlabel("Tipo de Árvore")
    plt.savefig(os.path.join(graphics_path, "Insertion_Comparisions_Mean.png"))
    plt.close()


@execution_time
def generate_insert_group_treeheight_graphics(
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
            "treeHeight",
            queue
        )
    )

    avl_grouping_process = mp.Process(
        target=group_by_and_average,
        args=(
            avl_insert,
            "avl",
            "treeHeight",
            queue
        )
    )

    rbt_grouping_process = mp.Process(
        target=group_by_and_average,
        args=(
            rbt_insert,
            "rbt",
            "treeHeight",
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
    
    colors = {
        "avl": "#90B8D0",
        "bst": "#66BB88",
        "rbt": "#E57373"
    }

    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    fig.suptitle("Média de Comparações em Função da Altura da Árvore")

    sizes = [len(info[1]) for info in infos_to_plot]

    infos_to_plot = sorted(infos_to_plot, key=lambda i: i[0])

    for j, info in enumerate(infos_to_plot):
        axes[j].plot(info[1].index, info[1], "--o", linewidth=1, markersize=4, color=colors[info[0]])
        axes[j].set_title(info[0].upper())

    for ax in axes:
        ax.set_axisbelow(True)
        ax.set_facecolor("#eeeeee")
        maximum_series = max(infos_to_plot, key=lambda i: i[1].max())[1]
        ax.set_ylim(bottom=0, top=maximum_series.max())
        ax.set_xlim(left=0, right=max(sizes))
        for spine in ax.spines.values():
            spine.set_visible(False)
        ax.tick_params(axis="both", labelsize=8)
        ax.set_xlabel("Altura")
        ax.set_ylabel("Média de Comparações")
        ax.grid(color="white")
    
    plt.savefig(os.path.join(graphics_path, "Mean_Comparisions_per_Height.png"))
    plt.close()


    sizes = [len(info[2]) for info in infos_to_plot]

    fig, axes = plt.subplots(1, 3, figsize=(15, 5))
    fig.suptitle("Média de Performance em Função da Altura da Árvore")

    infos_to_plot = sorted(infos_to_plot, key=lambda i: i[0])

    for i, info in enumerate(infos_to_plot):
        axes[i].plot(info[2].index, info[2], "--o", linewidth=1, markersize=4, color=colors[info[0]])
        axes[i].set_title(info[0].upper())
    
    for ax in axes:
        ax.set_axisbelow(True)
        ax.set_facecolor("#eeeeee")
        maximum_series = max(infos_to_plot, key=lambda i: i[2].max())[2]
        ax.set_ylim(bottom=0, top=maximum_series.max())
        ax.set_xlim(left=0, right=max(sizes))
        for spine in ax.spines.values():
            spine.set_visible(False)
        ax.tick_params(axis="both", labelsize=8)
        ax.set_xlabel("Altura")
        ax.set_ylabel("Média de Comparações")
        ax.grid(color="white")
    
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
            avl_mean_time.value,
            bst_mean_time.value,
            rbt_mean_time.value
        ],
        "mean_comparisions": [
            avl_mean_comparisions.value,
            bst_mean_comparisions.value,
            rbt_mean_comparisions.value
        ],
        "tree": ["AVL", "BST", "RBT"]
    })

    colors = {
        "AVL": "#90B8D0",
        "BST": "#66BB88",
        "RBT": "#E57373"
    }

    plt.title("Média do Tempo de Busca em Nanosegundos por Árvore")
    sns.barplot(
        data=plot_df,
        hue="tree",
        y="median_time",
        palette=colors,
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
        palette=colors,
        x="tree",
        legend=False
    )
    plt.ylabel("Média de Comparações")
    plt.xlabel("Tipo de Árvore")

    plt.savefig(os.path.join(graphics_path, "Search_Comparisions_Median.png"))
    plt.close()


@execution_time
def boxplots_performance(
    bst_search_path: Iterator[pd.DataFrame],
    avl_search_path: Iterator[pd.DataFrame],
    rbt_search_path: Iterator[pd.DataFrame],
    graphics_path: str
):
    bst_search = pd.read_csv(bst_search_path, chunksize=100000, sep=";")
    avl_search = pd.read_csv(avl_search_path, chunksize=100000, sep=";")
    rbt_search = pd.read_csv(rbt_search_path, chunksize=100000, sep=";")

    queue = mp.Queue()

    bst_search_process = mp.Process(
        target=group_to_boxplot,
        args=(
            bst_search,
            "time",
            queue,
            'BST'
        )
    )
    avl_insert_process = mp.Process(
        target=group_to_boxplot,
        args=(
            avl_search,
            "time",
            queue,
            'AVL'
        )
    )
    rbt_insert_process = mp.Process(
        target=group_to_boxplot,
        args=(
            rbt_search,
            "time",
            queue,
            'RBT'
        )
    )

    bst_search_process.start()
    avl_insert_process.start()
    rbt_insert_process.start()
    
    dataframes = []
    for _ in range(3):
        dataframes.append(queue.get())
    
    dataframes = pd.concat(dataframes)

    bst_search_process.join()
    avl_insert_process.join()
    rbt_insert_process.join()

    plt.title("Boxplot dos Tempos de Execução na BUSCA")

    Q1 = dataframes["time"].quantile(.25)
    Q3 = dataframes["time"].quantile(.75)
    IQR = Q3 - Q1

    SUP = Q3 + 1.5*IQR
    INF = Q1 - 1.5*IQR

    dataframes = dataframes[ (dataframes["time"]>=INF) & (dataframes["time"]<=SUP) ]

    colors = {
        "AVL": "#90B8D0",
        "BST": "#66BB88",
        "RBT": "#E57373"
    }

    sns.boxplot(
        data=dataframes,
        legend=False,
        x="algorithm",
        y="time",
        hue="algorithm",
        palette=colors,
        order=["AVL", "BST", "RBT"]
    )

    plt.xlabel("Algoritmo")
    plt.ylabel("Tempo de Execução da Busca (Nanosegundos)")

    plt.savefig(os.path.join(graphics_path, 'Boxplot_Performance_Search'))
    plt.close()


@execution_time
def boxplots_comparisions(
    bst_search_path: Iterator[pd.DataFrame],
    avl_search_path: Iterator[pd.DataFrame],
    rbt_search_path: Iterator[pd.DataFrame],
    graphics_path: str
):
    bst_search = pd.read_csv(bst_search_path, chunksize=100000, sep=";")
    avl_search = pd.read_csv(avl_search_path, chunksize=100000, sep=";")
    rbt_search = pd.read_csv(rbt_search_path, chunksize=100000, sep=";")

    queue = mp.Queue()

    bst_search_process = mp.Process(
        target=group_to_boxplot,
        args=(
            bst_search,
            "comparisions",
            queue,
            'BST'
        )
    )
    avl_insert_process = mp.Process(
        target=group_to_boxplot,
        args=(
            avl_search,
            "comparisions",
            queue,
            'AVL'
        )
    )
    rbt_insert_process = mp.Process(
        target=group_to_boxplot,
        args=(
            rbt_search,
            "comparisions",
            queue,
            'RBT'
        )
    )

    bst_search_process.start()
    avl_insert_process.start()
    rbt_insert_process.start()
    
    dataframes = []
    for _ in range(3):
        dataframes.append(queue.get())
    
    dataframes = pd.concat(dataframes)

    bst_search_process.join()
    avl_insert_process.join()
    rbt_insert_process.join()

    plt.title("Boxplot das Comparações na BUSCA")

    Q1 = dataframes["comparisions"].quantile(.25)
    Q3 = dataframes["comparisions"].quantile(.75)
    IQR = Q3 - Q1

    SUP = Q3 + 1.5*IQR
    INF = Q1 - 1.5*IQR

    dataframes = dataframes[ (dataframes["comparisions"]>=INF) & (dataframes["comparisions"]<=SUP) ]

    colors = {
        "AVL": "#90B8D0",
        "BST": "#66BB88",
        "RBT": "#E57373"
    }

    sns.boxplot(
        data=dataframes,
        legend=False,
        x="algorithm",
        y="comparisions",
        hue="algorithm",
        palette=colors,
        order=["AVL", "BST", "RBT"]
    )

    plt.xlabel("Algoritmo")
    plt.ylabel("Comparações")

    plt.savefig(os.path.join(graphics_path, 'Boxplot_Comparisions_Search'))
    plt.close()
