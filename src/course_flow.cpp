/** @file course_flow.cpp
 *  @brief Main file.
 *
 *  This file contains all the functions and variables
 *  to fully execute the second project of TAG 2017/1.
 *
 *  @author Dayanne Fernandes da Cunha 13/0107191
 *  @author Renato Avellar Nobre 15/0146698
 *  @bug No bug known.
 */

#include "course_flow.inl"

void displayProgram(){
  displayHeaderUI();

  cout << endl;
  cout << '\n' << "\t- CODIGO | MATERIA | FATOR | MATERIAS DEPENDENTES \n" << endl;

  for(int i = 0; i < GRAPHSIZE; i++){
      cout << "\t- " << GRAPH[i].first.first.first << " | " << GRAPH[i].first.first.second << " | " << GRAPH[i].first.second << " | ";
      for(int j = 0; j < GRAPH[i].second.size();++j)
          cout << GRAPH[i].second[j] << " ";
      cout << endl;
  }

  pressToContinue();
}

void displayDAG(){
  displayHeaderUI();

  cout << '\n' << "\t- ÍNDICE : MATÉRIA : MATÉRIAS QUE DEPENDEM DESTA \n" << endl;

  for(int i = 0; i < GRAPHSIZE; i++){
      cout << "\t- " << i << " : " << GRAPH[i].first.first.second << ": ";
      if(GRAPH[i].second.size() == 0)
        cout << "NENHUMA";
      else
        for(int j = 0; j < GRAPH[i].second.size();++j)
            cout << GRAPH[i].second[j] << " ";
      cout << endl;
  }

  pressToContinue();
}

void displayCriticalPath(){
  cout << endl;
  for(int i = 0; i < CPM.first.size(); ++i)
    cout << "\t- " << GRAPH[CPM.first[i]].first.first.second << endl;

  cout << "\t- Total weight: " << CPM.second << endl;
}

void displayTopologicSort(){
  cout << endl;
    for(int k = 0; k < ORD_GRAPH.size(); k++)
        cout << "\t- " << ORD_GRAPH[k].first.first.second << endl;
    cout << "\t" << endl;
}

int findIndexFromCod(string cod){
  for(int i = 0; i < GRAPHSIZE; ++i)
    if(cod == GRAPH[i].first.first.first)
      return i;

  return -1;
}

pair<vector<int>, int> calculateCPM(int origin_index){
  pair<vector<int>, int> last_cpm;
  vector<int> dist(GRAPHSIZE), path;
  int u, largest_path = NINFINITY, k = 0;

  for(int i = 0; i < dist.size(); ++i)
    dist[i] = NINFINITY;

  dist[origin_index] = 0;
  path.push_back(origin_index);

  while(k < ORD_GRAPH.size())
  {
    u = findIndexFromCod(ORD_GRAPH[k].first.first.first);
    k++;

    if(u == -1){
      cout << "Error on CPM" << endl;
      break;
    }

    if(dist[u] != NINFINITY){
      for(int j = 0; j < GRAPH[u].second.size(); j++){
        if(dist[GRAPH[u].second[j]] < dist[u] + GRAPH[GRAPH[u].second[j]].first.second){
          dist[GRAPH[u].second[j]] = dist[u] + GRAPH[GRAPH[u].second[j]].first.second;
          if(largest_path < dist[GRAPH[u].second[j]])
            largest_path = dist[GRAPH[u].second[j]];
          path.push_back(GRAPH[u].second[j]);
        }
      }
    }
  }

  last_cpm = make_pair(path, largest_path);

  return last_cpm;
}

void topologicSort(){
    int j, degree, index, last_path, largest_path_index, largest_path = NINFINITY;
    vector<pair<ssfv, int> > auxGraph;
    vector<ssfv> queue;
    vector<ssfv> out;
    pair<vector<int>, int> largest_path_pair, last_largest_path_pair;
    ssfv n;

    for(int i = 0; i< GRAPH.size();i++){
        degree = 0;
        for(int j = 0; j < GRAPH.size();j++)
            for(int k = 0;k<GRAPH[j].second.size();k++)
                if(GRAPH[j].second[k] == i)
                    degree += 1;

        auxGraph.push_back(make_pair(GRAPH[i], degree));
    }

    for(int i = 0; i < auxGraph.size(); i++)
        if(auxGraph[i].second == 0)
            queue.push_back(auxGraph[i].first);

    while(!queue.empty()){
        n = queue.back();
        queue.pop_back();
        out.push_back(n);
        for(int i=0;i< n.second.size();i++){
            index = n.second[i];
            auxGraph[index].second -= 1;
            if(auxGraph[index].second == 0)
                queue.push_back(auxGraph[index].first);
        }
    }

    auxGraph.clear();
    queue.clear();

    ORD_GRAPH = out;

    for(int i = 0; i < GRAPHSIZE; ++i)
    {
      largest_path_pair = calculateCPM(i);
      if(largest_path_pair.second > largest_path && largest_path_pair.second > NINFINITY)
      {
        last_largest_path_pair = largest_path_pair;
        largest_path = largest_path_pair.second;
      }
    }

    CPM = last_largest_path_pair;

    displayTopologicSort();
}

void pressToContinue(){
    cout << endl << "\t    Aperte <QUALQUER TECLA> para voltar ao menu.    ";
    getchar();
    getchar();
}

void displayHeaderUI(){
    cout << "\t------------------------COLLEGE PATH------------------------" << endl;
    cout << "\t- Curso: Ciencia da Computacao (Bacharelado)               -" << endl;
    cout << "\t------------------------------------------------------------" << endl;
}

void displayTopologicSortUI(){
    displayHeaderUI();

    cout << endl << "\t>>> Ordenacao Topologica: " << endl;

    displayTopologicSort();

    pressToContinue();
}


void displayCriticalPathUI(){
    displayHeaderUI();

    cout << endl << "\t>>> Caminho Critico: " << endl;

    displayCriticalPath();
    pressToContinue();
}


/**
 * displayWrongChoiceUI function. Display a message when the
 * user inputs a not valid choice for the processUIChoice.
 *
 * @return void
 */
void displayWrongChoiceUI(){
    displayUI();
    cout << "\tEscolha invalida, informe um valor de 1 a 5" << endl;
    cout << "\t>>> ";
}


/**
 * displayHelpUI function. Display the help screen.
 *
 *
 * @return void
 */
void displayHelpUI(){
    cout << "\t------------------------COLLEGE PATH------------------------" << endl;
    cout << "\t- Segundo projeto da materia de Teoria e Aplicacao         -" << endl;
    cout << "\t- de Grafos (TAG) do semestre de 2017/1.                   -" << endl;
    cout << "\t- Feito por Dayanne Fernandes e Renato Nobre               -" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t- O trabalho implementa um grafo aciclico dirigido         -" << endl;
    cout << "\t- das diciplinas do curso de Ciência da Computação         -" << endl;
    cout << "\t- da UnB. As opcão 1 mostra o ordenamento                  -" << endl;
    cout << "\t- topologico das materias, a opcao 2 mosta o               -" << endl;
    cout << "\t- caminho critico do curso, e por fim a opcao 3            -" << endl;
    cout << "\t- mostra o grafo completo                                  -" << endl;
    cout << "\t------------------------------------------------------------" << endl;

    pressToContinue();
}


/**
 * processUIChoice function. Process what is the user choice
 * of the main user interface and call the respective method.
 *
 * @return void
 */
void processUIChoice(){
    int choice = 0;

    cin >> choice;

    while(choice != 6){
        CLEARSCR();

        if(choice == 1){
            displayTopologicSortUI();
            displayUI();
        } else if(choice == 2){
            displayCriticalPathUI();
            displayUI();
        } else if(choice == 3){
            displayDAG();
            displayUI();
        } else if(choice == 4){
            displayProgram();
            displayUI();
        } else if(choice == 5){
            displayHelpUI();
            displayUI();
        } else {
            displayWrongChoiceUI();
        }

        cin >> choice;
    }

}

/**
 * displayUI function. Display the main user interface
 * of the project
 *
 * @return void
 */
void displayUI(){
    CLEARSCR();

    cout << "\t------------------------COLLEGE PATH------------------------" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t- 1. Ordenacao Topologica                                  -" << endl;
    cout << "\t- 2. Caminho Critico                                       -" << endl;
    cout << "\t- 3. DAG                                                   -" << endl;
    cout << "\t- 4. Curso                                                 -" << endl;
    cout << "\t- 5. Ajuda                                                 -" << endl;
    cout << "\t- 6. Sair                                                  -" << endl;
    cout << "\t-                                                          -" << endl;
    cout << "\t------------------------------------------------------------" << endl;
    cout << endl << "\t>>> ";
}


/**
 * printAllAdj function. Print edges list of the graph
 *
 * @return void
 */
void printAllAdj(){
    for(int i = 0; i < GRAPHSIZE; i++){
        for(int j = 0; j < GRAPH[i].second.size();++j)
            cout << GRAPH[i].second[j] << " ";
        cout << endl;
    }
}


/**
 * processCodeLink function.
 *
 *
 * @return void
 */
void processCodeLink(string links, int origin_index){
    string token;
    size_t pos = 0, found ;
    vector<int> adj;
    int index;

    while((found = links.find_first_of(' ', pos)) != (string::npos)){
        token = links.substr(pos, found - pos);
        pos = found + 1;
        cout << token << endl;
        if(stoi(token) != -1)
            adj.push_back(stoi(token));
    }
    token = links.substr(pos);
      cout << token << endl;
    if(stoi(token) != -1)
        adj.push_back(stoi(token));

    GRAPH[origin_index].second = adj;
}


/**
 * insertLinksOnGraph function.
 *
 *
 * @return void
 */
void insertLinksOnGraph(vector<string> links){
    for(int i = 0; i < GRAPHSIZE; ++i)
        processCodeLink(links[i], i);
}

/**
 * calculateWeight function. Calculate the weight of an edge
 * given the credits and the dificulty of a course.
 *
 * @return float value that represents the edge weight
 */
float calculateWeight(int cred, float f){
    return (cred*f);
}

/**
 * insertAllOnGraph function. Insert inner node, node, and edges into the
 * Graph data structure.
 *
 *
 * @return void
 */
void insertAllOnGraph(string cod, string name, int cred, float f, int i){
    pair<string, string> inner_node = make_pair(cod, name);
    pair<pair<string, string>, float> node = make_pair(inner_node, calculateWeight(cred, f));
    pair<pair<pair<string, string>, float>, vector<int> > node_list = make_pair(node, vector<int>());

    GRAPH[i] = node_list;
}

/**
 * Main function. Read and load basic data, then execute all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main(){

    char cod[15], name[50], links[500];
    string scod, sname, slinks;
    int cred, i = 0;
    float f;
    vector<string> link;

    FILE *pF = fopen("courses.txt", "r");

    if(pF == NULL) {
        cout << "Error on open the file." << endl;
        return -1;
    }

    while (fscanf(pF, "%s | %[^|] | %d | %f | %[^\n] ", cod, name, &cred, &f, links) != EOF)
    {
        slinks = links;
        link.push_back(slinks);
        scod = cod;
        sname = name;
        insertAllOnGraph(scod, sname, cred, f, i);
        ++i;
    }

    insertLinksOnGraph(link);

    topologicSort();

    displayUI();
    processUIChoice();

    fclose(pF);

    return 0;
}
