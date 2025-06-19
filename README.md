# Projeto final estrutura de dados - Implementação de índices invertidos

Este projeto, desenvolvido para a disciplina de Estrutura de Dados, foca na implementação e análise de três tipos de árvores binárias de busca: Árvore Binária de Busca (BST), Árvore AVL e Árvore Rubro-Negra (RBT).\
O objetivo principal é a implementação do índice invertido usando os 3 diferentes tipos de árvores aprendidos em sala, coletando dados para análise
---
## Sumário
[1- Sobre as árvores](#sobre-as-arvores)\
[2- Estrutura do repositório](#estrutura-do-repositório)\
[3- Resquisitos](#requisitos)\
[4- Compilação](#compilação)\
[5- Como usar](#como-usar)\
[6- Modos de uso](#modos)\
[7- Testes](#testes)\
[8- Integrantes](#integrantes)

## Sobre as árvores
1. **BST**\
A árvore mais simples, com apenas uma propriedade, definida a sua raiz, todo valor a ser inserido passa por uma comparação, caso seja maior vai para um nó a direita, caso seja menor vai para um nó a esquerda, seguindo assim até em que após uma comparação não haja nó na direção que o valor deve ir, sendo assim, ela será a posição do nó referente ao novo valor
2. **AVL**\
Essa árvore, diferente da BST sem mantém balanceada, sua inserção é semelhante a BST, porém realiza rotações para manter o balanceamento, seguindo que sendo l a altura à esquerda e r a altura à direitra, a arvore rotaciona de forma em que $-1 \leq r - l \geq 1$
3. **Rbt**\
Se assemelha a AVL, porém nela os nós tem cores (pretos e vermelhos), mantém uma estrutura em que não há duas cores consecultivas e as folhas não podem ser vermelhas, também nela há menos rotações que a AVL


## Estrutura do Repositório

O projeto está organizado da seguinte forma para facilitar a navegação, compilação e execução:

```
projeto_final_ed/
|-- .gitignore
|-- Makefile                      # Script para compilar os arquivos necessŕios das arvores
|-- src/                          # Pasta com os códigos do projeto
|   |-- modules/                  
|   |   |-- avl/                  
|   |   |   |-- avl.cpp           # Implementação do algoritmo da arvore avl
|   |   |   |-- avl.h
|   |   |-- bst/
|   |   |   |-- bst.cpp           # Implementação do algoritmo da arvore bst
|   |   |   |-- bst.h
|   |   |-- rbt/
|   |   |   |-- rbt.cpp           # Implementação do algoritmo da arvore rbt
|   |   |   |-- rbt.h
|   |   |-- data.cpp              # Implementação de funções de leitura dos arquivos
|   |   |-- data.h
|   |-- tests/                    # Pasta com os testes unitários dos 3 algoritmos
|   |   |-- test_avl.cpp        
|   |   |-- test_bst.cpp
|   |   |-- test_rbt.cpp
|   |-- utils/
|   |   |-- tree_utils.cpp        # Funções comuns as 3 arvores
|   |   |-- tree_utils.h
|   |   |-- utils.cpp             # Funções relacionadas ao CLI
|   |   |-- utils.h
|   |-- main_avl.cpp              # Arquivo que implementa a interação do usuário com a arvore avl
|   |-- main_bst.cpp              # Arquivo que implementa a interação do usuário com a arvore bst
|   |-- main_rbt.cpp              # Arquivo que implementa a interação do usuário com a arvore rbt
|-- data/                         # Diretório com os arquivos utilizados para gerar estatísiticas 
|-- python/                       # Diretório com códigos em python para gerar estatísticas, gráficos e manipulação de dados
    |-- generate_graphs.py        
    |-- graphics.py
    |-- utils.py
|-- docs/                         # Diretório com as estatísticas coletadas e relatório
|   |-- report.pdf
|   |-- graficos/                 # Diretório com os graficos gerados
|-- requirements.txt
|-- README.md                     # Este mesmo que vos fala
```

## Requisitos
Para execultar o programa, é necessário ter instalado:
* **g++** Para compilar os arquivos 
* **Make:** Para organizar as compilação em build/
* **python3** Para geração dos graficos

## Compilação

1. **Clone o repositório:**

   Com chave sh:
   ```bash
   git clone git@github.com:Os-Estudiosos/projeto-final-ed.git
   cd projeto-final-ed
   ```
   via Https:
   ```bash
   git clone https://github.com/Os-Estudiosos/projeto-final-ed.git
   cd projeto-final-ed
   ```
   

2. **Execute o Makefile:**

   * **Para compilar tudo:**
     ```bash
     make
     ```
     ou
     ```bash
     make all
     ```

   * **Para compilar apenas uma arvore:**
     ```bash
     make avl
     make bst
     make rbt
     ```
será gerado uma pasta seguindo a seguinte distribuição:
```
projeto-final-ed/build/
|-- avl*
|-- bst*
|-- rbt*
|-- testsAvl*
|-- testsBst*
|-- testsRbt*
```

3. Instale as depêndencias python para geração dos gráficos
    * (Opcional) Gere um virtual enviroment

      Para Linux:
      ```bash
      python3 -m venv venv
      ```
      
      Para Windows:
      ```bash
      python -m venv venv
      ```
    
    * (Opcional) Ative o virtual enviroment

      Para Linux:
      ```
      source <caminho até a venv>/venv/bin/activate
      ```

      Para Windows (CMD):
      ```
      <caminho até venv>\venv\Scripts\activate
      ```

      Para Windows (PowerShell):
      ```
      .\venv\Scripts\Activate.ps1
      ```
    
    * Instalar as dependências especificadas no `requirements.txt`
      ```
      pip install -r requirements.txt
      ```

## Como Usar
Os programas podem ser execultados no modo search de qualque local do computador, e no modo stats podem ser execultados da raiz do repositório projeto-final-ed/ ou na basta build/
 
* `<tipo_arvore>`: `avl`, `bst` ou `rbt`
* `<n_docs>`: O número de documentos documentos que serão lidos
* `<path_para_data>`: O caminho para o diretório com os documentos numerados de 0 a n

### Modos

1. **search**
```bash
./build/<tipo_arvore> search <n_docs> <path_para_data>
```
ou 
```bash
./<tipo_arvore> search <n_docs> <path_para_data>
```
Cria a arvore selecionada e monta seu indice invertido, de modo interativo o programa espera receber uma a uma, palavras que serão buscadas na arvore
```bash
======================== PESQUISA COM INDICE INVERTIDO ========================
(Se quiser sair, digite . e de enter)
Digite a palavra que gostaria de procurar:
--> 

```

Para cada palavra recebida será retornado uma lista com todos os índices dos documentos em que há ocorrencia de palavras, para continuar pesquisando basta pressionar enter

```bash
======================== PESQUISA COM INDICE INVERTIDO ========================
(Se quiser sair, digite . e de enter)
Digite a palavra que gostaria de procurar:
--> arvore

Sua palavra foi ENCONTRADA!
Ela se localiza nos documentos: 155, 2008, 2141, 2350, 3015, 4367, 4586, 5577, 5589, 6710, 7123, 7268, 7441, 7491, 7952, 9169, 9733
Aperte Enter para procurar outra palavra
```
Após a pesquisa, o programa volta a mensagem inical para realizar nova busca ou encerrar o programa buscando "."
```bash
======================== PESQUISA COM INDICE INVERTIDO ========================
(Se quiser sair, digite . e de enter)
Digite a palavra que gostaria de procurar:
--> .

Encerrando o programa
```


Exemplo:
```bash
./build/avl search 10 ./data
```

2. **stats**
```bash
./build/<tipo_arvore> stats <n_docs> <path_para_data>
```
ou 
```bash
./<tipo_arvore> stats <n_docs> <path_para_data>
```
cria a arvore e monta ela guardando as estatísticas, encerra o programa logo após gerar as estatísticas\
guarda os dados coletados em `./build/stats/<arvore>` em arquivos no formato csv (explicar melhor sobre como é montado)
as estatísticas impressas são:
- média de tempo de inserção
- média de comparações por inserção
- quantidade de palavras inseridas
- quantidade de palavras unicas
- quantidade de rotações (para avl)

Exemplo:
```bash
./build/bst stats 9999 ./data
```
saida:
```bash
Dependendo de quantos documentos você está fazendo a leitura, isso pode levar um tempinho
Calculando as estatísticas de Inserção
=====================ESTATÍSTICAS DE INSERÇÃO=====================
Tempo de Inserção: 1.14215 segundos
Total de palavras inseridas: 4361997
Palavras unicas: 20274
Total de comparacoes: 54642515
Media de comparacoes: 12.5269
Altura: 37
Menor altura: 6

Calculando as estatísticas de Busca
=====================ESTATÍSTICAS DE BUSCA=====================
Media tempo de busca: 5.17807e-07 segundos
Media de comparacoes de busca: 17.8586
```

## Testes

O projeto inclui testes para cada estrutura de árvore. A compilação dos testes já é feita juntamente com os executáveis principais

Para executar um dos testes:
```bash
./build/testsBst
./build/testsAvl
./build/testsRbt
```

exemplo: 
```bash
./buid/testsRbt
```
saida:
```bash
======================= TESTES ESTRUTURAIS DA ARVORE =======================
Testando insercao numa ÁRVORE NULA... CONCLUiDO
Testando insercao numa arvore com raiz NULA... CONCLUIDO
Testando insercao e busca na arvore CONCLUIDO

======================= TESTANDO O RETORNO DA ARVORE =======================
Testando insercao de palavra duplicada no mesmo documento CONCLUIDO
Testando insercao de palavra duplicada em documento diferente CONCLUIDO
Testando insercao de palavras vazias CONCLUIDO

====================== TESTANDO PROPRIEDADES DA RBT ======================
Testando propriedades RBT com insercao crescente (a, b, c, d, e)... CONCLUIDO
Testando propriedades RBT com insercao decrescente (e, d, c, b, a)... CONCLUIDO
Testando propriedades RBT com rotacao dupla (Dir-Esq)... CONCLUIDO
Testando propriedades RBT com recoloracao... CONCLUIDO
Testando propriedades RBT com numero de rotacoes... CONCLUIDO

Todos os testes foram concluídos.

```

## Documentação
Em `projeto-final-ed/docs/` há um arquivo `relatorio.pdf` com o relatório feito pelo grupo, nele encontra-se:
- Divisão das tarefa
- Analise de dados
- Dificuldades encontradas

## Integrantes
Alex Júnio Maia de Oliveira\
João Pedro Jerônimo de Oliveira\
Lucas Batista Pereira\
Matheus Villarino Pinto\
Thalis Ambrosim Falqueto
