import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import os

DATA_PATH = os.path.join(os.getcwd(), 'build', 'stats')

if not os.path.exists(DATA_PATH):
    print("\033[31mVocê ainda não gerou as estatísticas sobre as árvores, por favor, gere-as primeiro e depois execute o programa\033[m")
    exit()

# Gerando os gráficos da BST

