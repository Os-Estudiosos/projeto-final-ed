import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from utils import execution_time
import os


@execution_time
def generate_bst_insert_graphics(path: str, graphics_path: str):
    """Generates the graphics about the BST insertion statistics

    Args:
        path (str): Statistics path
        graphics_path (str): Graphics directory path
    """
    insertion_infos = pd.read_csv(path, sep=";")

    plot_df = insertion_infos.groupby(by="word").median().tail(500)
    ordered_indexes = plot_df.sort_values(by="time").index

    plt.title("Histograma da Mediana do Tempo de Inserção (BST)")

    sns.barplot(
        data=plot_df,
        x="word",
        y="time",
        errorbar=None,
        order=ordered_indexes,
        width=1
    )

    plt.xlabel("Palavra")
    plt.ylabel("Tempo (Nanosegundo)")

    plt.xticks([])

    plt.savefig(os.path.join(graphics_path, "Insertion_Time_Median.png"))
    plt.close()


@execution_time
def generate_bst_search_graphics(path: str, graphics_path: str):
    """Generates the graphics about the BST searching statistics

    Args:
        path (str): Statistics path
        graphics_path (str): Graphics directory path
    """
    search_infos = pd.read_csv(path, sep=";")
    print(search_infos)
