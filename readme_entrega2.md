# Projeto Final
## Entrega 2

Este repositório contém o código fonte de **três programas diferentes que implementam um índice invertido**, todos realizando a mesma tarefa com abordagens distintas. A tarefa consiste em ler uma quantidade especificada de documentos e montar um **índice invertido** a partir dos documentos.
Esta Branch contém as árvores BST e AVL implementadas.

## Modos de Operação

O programa possui dois modos funcionais:

- **search** — Permite buscar termos nos documentos indexados, mostra uma interface para iteragir e buscar as palavras. Se a palavra procurada está em algum documento, mostra em quais ela está, se não está em nenhum, também o informa.

- **stats** — Retorna dados estatísticos sobre a árvore em questão. A saída será da forma:
    - **Tempo de execucao**: Tempo que leva para criar toda a árvore
    - **Total de palavras inseridas**: total de palavras na árvore
    - **Palavras unicas**: Total de palavras únicas na árvore
    - **Total de comparacoes**: Total de comparações realizadas durante a criação da árvore 
    - **Media de comparacoes**: Média de comparações que cada palavra sofreu até receber uma posição na árvore
    - **Altura**: Altura final da árvore
    - **Menor altura**: Menor de um nó folha da árvore
    - **Media tempo de busca**: Média de tempo para buscar uma palavra na árvore
    - **Media de comparacoes de busca**: média de comparações feitas por busca na árvore até encontrar um resultado

## Compilação
Para compilar as dependencias do programa basta usar o comando 
```
make
```
que ele irá compilar o programa, gerando uma pasta ./build com dois executaveis
* **bst** , onde será criada a arvore e realizada a busca por palavras de forma interativa com o usuário
* **testsBst**, um arquivo que realiza os testes unitários referentes a bst
* **avl** , onde será criada a arvore e realizada a busca por palavras de forma interativa com o usuário
* **testsAvl**, um arquivo que realiza os testes unitários referentes a avl

## Como Usar
Para executar o programa basta usar um comando como abaixo, onde:
- n_docs deve ser uma quantidade valida de documentos presentes na pasta
- path deve ser um caminho relativo para a pasta, ou seja, deve ser descrito a partir de onde o porgrama estiver sendo executado
- Os arquivos são lidos em ordem crescente e continua, a partir de 0 à n (número de documentos na pasta)
- uma pasta valida tem estrutura: ./pasta/ (./pasta está incorreto)

```
# Para busca
/<arvore> search <n_docs> <path>
```

```
# Para gerar estatísticas
/<arvore> stats <n_docs> <path>
```

Para testes unitários, basta usar 
```
/tests<arvore>
```

