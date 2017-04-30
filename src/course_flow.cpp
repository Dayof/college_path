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

void displayDAG(){
  displayHeaderUI();

  for(int i = 0; i < GRAPHSIZE; i++){
      cout << "\t\t" << i << " - " << GRAPH[i].first.first.second << ": ";
      if(GRAPH[i].second.size() == 0)
        cout << "Esta matéria não é pré requisito de nenhuma outra.";
      else
        for(int j = 0; j < GRAPH[i].second.size();++j)
            cout << GRAPH[i].second[j] << " ";
      cout << endl;
  }

  pressToContinue();
}

void displayCriticalPath(){
  for(int i = 0; i < CPM.first.size(); ++i)
    cout << "\t\t- " << GRAPH[CPM.first[i]].first.first.second << endl;

  cout << "\t\t- Total weight: " << CPM.second << endl;
}

void displayTopologicSort(){
    for(int k = 0; k < ORD_GRAPH.size(); k++)
        cout << "\t\t" << ORD_GRAPH[k].first.first.second << " > "<< endl;
    cout << "\t\t" << endl;
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

  // cout << "ORIGIN VERTEX : " << GRAPH[origin_index].first.first.second << endl;

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
          // cout << dist[GRAPH[u].second[j]] << endl;
          path.push_back(GRAPH[u].second[j]);
        }
      }
    }
  }

  // for(int i = 0; i < dist.size(); ++i)
  //   (dist[i] == NINFINITY) ? cout << "NINFINITY " : cout << dist[i] << " ";
  // cout << endl;

  // for(int i = 0; i < path.size(); ++i)
  //   cout << GRAPH[path[i]].first.first.second << " | w: " << GRAPH[path[i]].first.second << " -> ";
  // cout << endl;
  //
  // cout << "Last Path: " << largest_path << endl;

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

    // cout << "Largest Path begin from index : " << GRAPH[CPM.first[0]].first.first.second << " with weight : " << CPM.second << endl;

    displayTopologicSort();
}

void pressToContinue(){
    cout << endl << "\t\t    Aperte <QUALQUER TECLA> para voltar ao menu.    ";
    getchar();
    getchar();
}

void displayHeaderUI(){
    cout << "\t\t--------------------COLLEGE PATH--------------------" << endl;
    cout << "\t\t- Curso: Ciencia da Computacao (Bacharelado)       -" << endl;
    cout << "\t\t----------------------------------------------------" << endl;
}

void displayTopologicSortUI(){
    displayHeaderUI();

    cout << endl << "\t\t>>> Ordenacao Topologica: " << endl;

    topologicSort();

    pressToContinue();
}

void displayCriticalPathUI(){
    displayHeaderUI();

    cout << endl << "\t\t>>> Caminho Critico: " << endl;

    displayCriticalPath();
    pressToContinue();
}

void displayWrongChoiceUI(){
    displayUI();
    cout << "\t\tEscolha invalida, informe um valor de 1 a 5" << endl;
    cout << "\t\t>>> ";
}

void displayHelpUI(){
    cout << "\t\t--------------------COLLEGE PATH--------------------" << endl;
    cout << "\t\t- Segundo projeto da materia de Teoria e Aplicacao -" << endl;
    cout << "\t\t- de Grafos (TAG) do semestre de 2017/1.           -" << endl;
    cout << "\t\t- Feito por Dayanne Fernandes e Renato Nobre       -" << endl;
    cout << "\t\t-                                                  -" << endl;
    cout << "\t\t- O trabalho implementa um grafo aciclico dirigido -" << endl;
    cout << "\t\t- das diciplinas do curso de Ciência da Computação -" << endl;
    cout << "\t\t- da UnB. As opcão 1 mostra o ordenamento          -" << endl;
    cout << "\t\t- topologico das materias, a opcao 2 mosta o       -" << endl;
    cout << "\t\t- caminho critico do curso, e por fim a opcao 3    -" << endl;
    cout << "\t\t- mostra o grafo completo                          -" << endl;
    cout << "\t\t----------------------------------------------------" << endl;

    pressToContinue();
}

void processUIChoice(){
    int choice = 0;

    cin >> choice;

    while(choice != 5){
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
            displayHelpUI();
            displayUI();
        } else {
            displayWrongChoiceUI();
        }

        cin >> choice;
    }

}

void displayUI(){
    CLEARSCR();

    cout << "\t\t--------------------COLLEGE PATH--------------------" << endl;
    cout << "\t\t-                                                  -" << endl;
    cout << "\t\t- 1. Ordenacao Topologica                          -" << endl;
    cout << "\t\t- 2. Caminho Critico                               -" << endl;
    cout << "\t\t- 3. DAG                                           -" << endl;
    cout << "\t\t- 4. Ajuda                                         -" << endl;
    cout << "\t\t- 5. Sair                                          -" << endl;
    cout << "\t\t-                                                  -" << endl;
    cout << "\t\t----------------------------------------------------" << endl;
    cout << endl << "\t\t>>> ";
}

void printAllAdj(){
    for(int i = 0; i < GRAPHSIZE; i++){
        for(int j = 0; j < GRAPH[i].second.size();++j)
            cout << GRAPH[i].second[j] << " ";
        cout << endl;
    }
}

void processCodeLink(string links, int origin_index){
    string token;
    size_t pos = 0, found ;
    vector<int> adj;
    int index;

    while((found = links.find_first_of(' ', pos)) != (string::npos)){
        token = links.substr(pos, found - pos);
        pos = found + 1;
        if(stoi(token) != -1)
            adj.push_back(stoi(token));
    }
    token = links.substr(pos);

    if(stoi(token) != -1)
        adj.push_back(stoi(token));

    GRAPH[origin_index].second = adj;
}

void insertLinksOnGraph(vector<string> links){
    for(int i = 0; i < GRAPHSIZE; ++i)
        processCodeLink(links[i], i);
}

float calculateWeight(int cred, float f){
    return (cred*f);
}

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

    displayUI();
    processUIChoice();

    fclose(pF);

    return 0;
}
