# Fluxo de Matérias do CiC - UnB

Segundo projeto da matéria de Teoria e Aplicação de Grafos (TAG) do semestre de 2017/1.

## Execução

Para executar este programa basta executar os seguintes comandos no terminal:

```
  $ bash run_all.sh
```

Este comando acima compila o programa utilizando o [Makefile](https://github.com/Dayof/college_path/blob/master/Makefile) e já o executa em seguida. Caso queira só executar o programa sem necessariamente compilar, executar o seguinte comando:

```
  $ ./main
```

## Pré-requisitos do sistema

Este programa foi testado no sistema operacional ``macOS Sierra``, versão ``10.12``. A linguagem de programação utilizada para implementar todo o projeto foi ``C++11``.

## Detalhes sobre o projeto

Fluxo de matérias do curso de Ciência da Computação da Universidade de Brasília.

### TODO

Todo o ciclo de desenvolvimento deverá conter a implementação, teste e documentação do código.

- Webscraper das matérias do CiC Bacharelado no Matrícula Web (courses.txt)
- Elaborar e colocar os fatores de dificuldade de cada matéria
- Algoritmo de ordenação topológica
- Algoritmo de cálculo do caminho crítico
- Menu com informações no terminal para o usurário escolher as ações do sistema

### Funcionalidades

<!-- O programa realiza as seguintes funcionalidades a partir do menu principal:

- Opção 1 : Calcula todos os graus dos vértices do grafo e imprime em ordem decrescente estes dados no seguinte formato ``MATRICULA has X friends``, ``X`` representa o número de grau do vértice vinculado aquela matrícula.

- Opção 2 : Calcula o maior clique do grafo e imprime no seguinte formato ``Existem X cliques máximos maximais de tamanho Y em cada clique. \n Clique 1.
Nome : Z``. Neste programa com a lista fornecida foi possível encontrar 3 cliques máximos com tamanhos iguais a 6, portanto será mostrado todos estes cliques encontrados.

- Opção 3 : Permite sair do programa. -->

### Fluxo do programa

- Lê os seguintes dados de cada matéria do fluxo de CiC da UnB :
 - Código,
 - nome,
 - número de créditos,
 - fator de dificuldade,
 - matérias que se disponibilizam após a aprovação na matéria que está sendo processada.
- Calcula o peso de cada matéria a partir do seguinte cálculo : peso = número de créditos * fator de dificuldade da matéria;
- Insere os dados de código, nome e peso da matéria nos vértices do grafo;
- Processa e insere no grafo cada vértice adjacente das matérias do fluxo;

## Autoria

- Dayanne Fernandes da Cunha
  - Matrícula: 13/0107191
  - E-mail: dayannefernandesc@gmail.com
  - GitHub: [Dayof](https://github.com/Dayof)

- Renato Avellar Nobre
  - Matrícula: 15/0146698
  - E-mail: rekanobre@gmail.com
  - GitHub: [Skalwalker](https://github.com/Skalwalker)
