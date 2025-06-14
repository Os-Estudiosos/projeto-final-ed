import os
from bst import *
import multiprocessing as mp

if __name__ == "__main__":
    # Pegando o caminho dos arquivos
    DATA_PATH = os.path.join(os.getcwd(), 'build', 'stats')
    GRAPHICS_PATH = os.path.join(os.getcwd(), 'build', 'graphics')

    # Se o arquivo especificado não existir, eu levando um erro
    if not os.path.exists(DATA_PATH):
        print("\033[31mVocê ainda não gerou as estatísticas sobre as árvores, por favor, gere-as primeiro e depois execute o programa\033[m")
        exit()

    # Se o caminho dos gráficos não existir ainda, eu vou criar
    if not os.path.exists(GRAPHICS_PATH):
        os.mkdir(GRAPHICS_PATH)

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

    # Fazendo um for para pegar os nomes dos arquivos de acordo com o nome definido no código C++
    for directory in directories:
        archives = os.listdir(os.path.join(DATA_PATH, directory))

        if len(archives) > 2:
            print("\033[31mAs pastas de estatísticas tem arquivos demais, elas devem conter apenas 1 arquivo com as informaçẽos de Inserção e outro com as de Busca\033[m")
            exit()

        for archive in archives:
            wich_tree = archive[:3]
            type_of_archive = "insert" if "Insert" in archive else "search"

            files[wich_tree][type_of_archive] = archive

    if files["bst"]["search"] is not None and files["bst"]["insert"] is not None:
        # bst_insert_process = mp.Process(
        #    target=generate_bst_insert_graphics,
        #    args=(os.path.join(DATA_PATH, 'bst', files['bst']['insert']), GRAPHICS_PATH)
        # )
        generate_bst_insert_graphics(
            os.path.join(DATA_PATH, 'bst', files['bst']['insert']),
            GRAPHICS_PATH
        )
        # bst_search_process = mp.Process(
        #    target=generate_bst_search_graphics,
        #    args=(os.path.join(DATA_PATH, 'bst', files['bst']['search']), GRAPHICS_PATH)
        # )

        # bst_insert_process.start()
        # bst_search_process.start()

        # bst_insert_process.join()
        # bst_search_process.join()
