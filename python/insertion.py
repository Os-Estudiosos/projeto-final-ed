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


@execution_time
def generate_insert_graphics(
    bst_insert: Iterator[pd.DataFrame],
    avl_insert: Iterator[pd.DataFrame],
    rbt_insert: Iterator[pd.DataFrame],
    graphics_path: str
):
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

    fig, axes = plt.subplots(1, 2, figsize=(15, 5))

    fig.suptitle("Informações para Comparação de Desempenho por tipo de Árvore")

    sns.barplot(
        data=plot_df,
        hue="tree",
        y="median_time",
        ax=axes[0],
        palette="pastel",
        x="tree",
        legend=False
    )
    axes[0].set_title("Média do Tempo de Inserção em Nanosegundos por Árvore")
    axes[0].set_ylabel("Média do Tempo de Inserção (Nanosegundos)")
    axes[0].set_xlabel("Tipo de Árvore")

    sns.barplot(
        data=plot_df,
        hue="tree",
        y="mean_comparisions",
        ax=axes[1],
        palette="pastel",
        x="tree",
        legend=False
    )
    axes[1].set_title("Média de Comparações na Inserção por Árvore")
    axes[1].set_ylabel("Média de Comparações")
    axes[1].set_xlabel("Tipo de Árvore")

    plt.savefig(os.path.join(graphics_path, "Insertion_Time_Median.png"))
    plt.close()


# @execution_time
# def generate_bst_search_graphics(path: str, graphics_path: str):
#     """Generates the graphics about the BST searching statistics

#     Args:
#         path (str): Statistics path
#         graphics_path (str): Graphics directory path
#     """
#     search_infos = pd.read_csv(path, sep=";")
#     print(search_infos)
