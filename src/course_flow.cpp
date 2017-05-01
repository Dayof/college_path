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

/**
 * Displays the whole university program.
 *
 * @return void
 */
void displayProgram(){
  displayHeaderUI();

  cout << endl << endl << "\t- CODIGO | MATERIA | FATOR | MATERIAS DEPENDENTES \n" << endl;

  for(int i = 0; i < GRAPHSIZE; i++){
      cout << "\t- " << GRAPH[i].first.first.first << " | " << GRAPH[i].first.first.second << " | " << GRAPH[i].first.second << " | ";
      for(int j = 0; j < GRAPH[i].second.size();++j)
          cout << GRAPH[i].second[j] << " ";
      cout << endl;
  }

  pressToContinue();
}

/**
 * Displays the directed acyclic graph of the university program.
 *
 * @return void
 */
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

/**
 * Displays the critical path found on the graph.
 *
 * @return void
 */
void displayCriticalPath(){
  cout << endl;
  for(int i = 0; i < CPM.first.size(); ++i)
    cout << "\t- " << GRAPH[CPM.first[i]].first.first.second << endl;

  cout << "\t- Total weight: " << CPM.second << endl;
}

/**
 * Displays the topological sort found on the graph.
 *
 * @return void
 */
void displayTopologicSort(){
  cout << endl;
    for(int k = 0; k < ORD_GRAPH.size(); k++)
        cout << "\t- " << ORD_GRAPH[k].first.first.second << endl;
    cout << "\t" << endl;
}

/**
 * Calculates the critical path of the graph.
 *
 * @param cod string that represent the id of a course
 *
 * @return integer that represent the vertex index of the if of the parameter
 */
int findIndexFromCod(string cod){
  for(int i = 0; i < GRAPHSIZE; ++i)
    if(cod == GRAPH[i].first.first.first)
      return i;

  return -1;
}

/**
 * Calculates the critical path of the graph.
 *
 * @param origin_index integer that represent the index of the vertex that's
 *                     being analised, runs all the path from this index
 *
 * @return a pair of vector of integers and a integer represents the abstract
 *          structure of the critical path of the graph
 */
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

/**
 * Function responsable to do the topological sort on the graph.
 *  Also, call the CPM function to calculate the critical path of the ordered
 *  graph.
 *
 * @return void
 */
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

/**
 * Information message to guide the user to press any key to continue using the
 *  system.
 *
 * @return void
 */
void pressToContinue(){
    cout << endl << "\t    Aperte <QUALQUER TECLA> para voltar ao menu.    ";
    getchar();
    getchar();
}

/**
 * Displays the header with the name of the system and the university program
 *  name.
 *
 * @return void
 */
void displayHeaderUI(){
    cout << "\t------------------------COLLEGE PATH------------------------" << endl;
    cout << "\t- Curso: Ciencia da Computacao (Bacharelado)               -" << endl;
    cout << "\t------------------------------------------------------------" << endl;
}

/**
 * Displays the menu of topologial sort, show the graph ordered.
 *
 * @return void
 */
void displayTopologicSortUI(){
    displayHeaderUI();

    cout << endl << "\t>>> Ordenacao Topologica: " << endl;

    displayTopologicSort();

    pressToContinue();
}

/**
 * Displays the menu of critical path method, show the CPM of the graph.
 *
 * @return void
 */
void displayCriticalPathUI(){
    displayHeaderUI();

    cout << endl << "\t>>> Caminho Critico: " << endl;

    displayCriticalPath();
    pressToContinue();
}


/**
 * Displays a message when the user inputs a not valid choice for the
 *  processUIChoice.
 *
 * @return void
 */
void displayWrongChoiceUI(){
    displayUI();
    cout << "\tEscolha invalida, informe um valor de 1 a 5" << endl;
    cout << "\t>>> ";
}


/**
 * Displays the help screen.
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
 * Process what is the user's choice of the main user interface
 *  and call the respective method.
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
            displayCritical
