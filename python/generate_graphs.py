import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import os

DATA_PATH = os.path.join(os.getcwd(), 'build', 'stats')

if not os.path.exists(DATA_PATH):
    print("\033[31mVocê ainda não gerou as estatísticas sobre as árvores, por favor, gere-as primeiro e depois execute o programa\033[m")
    exit()

# Achando os arquivos na pasta e pegando seus nomes
directories = os.listdir(DATA_PATH)

# Definindo as variáveis que terão os nomes de cada arquivo
files = {
    "bst": {
        "insert": None,
        "search": None
    },
    "rbt": {
        "insert": None,
        "search": None
    },
    "avl": {
        "insert": None,
        "search": None
    },
}

for directory in directories:
    archives = os.listdir(os.path.join(DATA_PATH, directory))

    if len(archives) > 2:
        print("\033[31mAs pastas de estatísticas tem arquivos demais, elas devem conter apenas 1 arquivo com as informaçẽos de Inserção e outro com as de Busca\033[m")
        exit()

    for archive in archives:
        wich_tree = archive[:3]
        type_of_archive = "insert" if "Insert" in archive else "search"

        files[wich_tree][type_of_archive] = archive


# Gerando os gráficos da BST
if files["bst"]["search"] is not None and files["bst"]["insert"] is not None:
    insertion_infos = pd.read_csv(os.path.join(DATA_PATH, 'bst', files['bst']['insert']), sep=";")
    search_infos = pd.read_csv(os.path.join(DATA_PATH, 'bst', files['bst']['search']), sep=";")

    sns.barplot(data=insertion_infos, x="word", y="time", estimator="mean")
    plt.show()
