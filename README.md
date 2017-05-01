# Fluxo de Matérias do CiC - UnB

Segundo projeto da matéria de Teoria e Aplicação de Grafos (TAG) do semestre de 2017/1. O sistema coleta as matérias do curso de Ciência da Computação da Universidade de Brasília usando Webscraper no Matrícula Web e calcula o caminho crítico do grafo.

## Execução

Para executar este programa basta executar os seguintes comandos no terminal:

```
  $ bash run_all.sh
```

Este comando acima compila o programa utilizando o [Makefile](https://github.com/Dayof/college_path/blob/master/Makefile) e já o executa em seguida. Caso queira só executar o programa sem necessariamente compilar novamente, executar o seguinte comando:

```
  $ ./main
```

## Pré-requisitos do sistema

Este programa foi testado no sistema operacional ``macOS Sierra``, versão ``10.12``. A linguagem de programação utilizada para implementar todo o projeto foi ``C++11``.

## Detalhes sobre o projeto

Este programa utiliza o arquivo ``courses.txt`` para gerar um grafo das matérias do CiC (UnB). É gerado um estrutura abstrata de grafo direcionado e acíclico para representar as matérias do fluxo do curso e algumas optativas. Ao total são 214 créditos de matérias, sendo 146 obrigatórias e 68 matérias optativas.

### Funcionalidades

O programa realiza as seguintes funcionalidades a partir do menu principal:

- Opção 1 : Mostra a ordenação topológica do grafo do fluxo das matérias do CiC. Imprime na tela na ordenação que foi encontrado, exibindo somente o nome das matérias.

- Opção 2 : Mostra o caminho crítico do grafo do fluxo das matérias do CiC. Imprime na tela o maior caminho crítico encontrado, o nome de cada uma e no final o tamanho do peso total encontrado ao percorrer os vértices. Não está necessariamente ordenado de acordo como é para percorrer o caminho.

- Opção 3 : Imprime na tela todo o grafo direcionado acíclico e os adjacentes de cada matérias. É mostrado no seguinte formato ``ÍNDICE : MATÉRIA : MATÉRIAS QUE DEPENDEM DESTA``.

- Opção 4 : Imprime na tela todas as matérias obrigatórias e optativas que totalizam 214 créditos do curso do CiC. É mostrado no seguinte formato ``CODIGO | MATERIA | FATOR | MATERIAS DEPENDENTES``.

- Opção 5 : Mostra um menu de instrução ao usuário a respeito do sistema e seus desenvolvedores.

- Opção 6 : Permite sair do programa.

### Fluxo do programa

- Coleta dados do Matrícula Web sobre o fluxo do CiC UnB e persiste as informações úteis para este sistema em um arquivo denominado ``courses.txt``;
- Lê os seguintes dados de cada matéria do fluxo de CiC da UnB :
   - Código,
   - nome,
   - número de créditos,
   - fator de dificuldade,
   - matérias que se disponibilizam após a aprovação na matéria que está sendo processada.
- Calcula o peso de cada matéria a partir do seguinte cálculo : peso = número de créditos * fator de dificuldade da matéria;
- Insere os dados de código, nome e peso das matérias nos vértices do grafo;
- Processa e insere no grafo cada vértice adjacente das matérias do fluxo;
- Faz a ordenação topológica usando o algoritmo de Kahn;
- Calcula o caminho crítico do fluxo do curso;
- Mostra a interface de usuário na tela do terminal;
- Espera receber alguma ação do usuário;
- Executa a ação requisitada e volta para o menu inicial até que o usuário não queira mais utilizar o sistema (pressionando o número 6 do teclado na tela principal para sair do programa).

## Autoria

- Dayanne Fernandes da Cunha
  - Matrícula: 13/0107191
  - E-mail: dayannefernandesc@gmail.com
  - GitHub: [Dayof](https://github.com/Dayof)

- Renato Avellar Nobre
  - Matrícula: 15/0146698
  - E-mail: rekanobre@gmail.com
  - GitHub: [Skalwalker](https://github.com/Skalwalker)
