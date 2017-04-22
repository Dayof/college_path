_/** @file course_flow.cpp
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

void processUIChoice(){
    int a;

    

}

void displayUI(){
    cout << "--------------------COLLEGE PATH--------------------" << endl;
    cout << "-                                                  -" << endl;
    cout << "- 1. Topological Sort (Ordenacao Topologica)       -" << endl;
    cout << "- 2. Critical Path (Caminho Critico)               -" << endl;
    cout << "- 3. Help (Ajuda)                                  -" << endl;
    cout << "- 4. Exit (Sair)                                   -" << endl;
    cout << "-                                                  -" << endl;
    cout << "----------------------------------------------------" << endl;
}

void printAllAdj(){
    for(int i = 0; i < GRAPHSIZE; i++){
        for(int j = 0; j < GRAPH[i].second.size();++j){
            cout << GRAPH[i].second[j] << endl;
        }
    }
}

int findIndexFromCode(string code){
    int result = -1;

    for(int i = 0; i < GRAPHSIZE; i++){
        cout << "it:-" << GRAPH[i].first.first.first << "-" << code << "-" << endl;
        if(code == GRAPH[i].first.first.first){
            result = i;
            cout << code << ": " << result << endl;
            break;
        }
    }
    return result;
}

void processCodeLink(string links, int origin_index){
    string token;
    size_t pos = 0;
    vector<int> adj;
    int index;

    while((pos = links.find(' ')) != (string::npos)){
        token = links.substr(0, pos);
        cout << "Token: " << token << endl;
        index = findIndexFromCode(token);
        if(index != -1){
            adj.push_back(index);
        }
        // cout << adj << endl;
        links.erase(0, pos+1);
    }
    index = findIndexFromCode(token);
    if(index != -1){
        adj.push_back(index);
    }

    GRAPH[origin_index].second = adj;
}

void insertLinksOnGraph(vector<string> links){
    for(int i = 0; i < GRAPHSIZE; ++i)
    {
        processCodeLink(links[i], i);
    }

}

float calculateWeight(int cred, float f){
    return cred*f;
}

void insertAllOnGraph(string cod, string name, int cred, float f, int i){
    pair<string, string> inner_node = make_pair(cod, name);
    pair<pair<string, string>, float> node = make_pair(inner_node, calculateWeight(cred, f));
    pair<pair<pair<string, string>, float>, vector<int> > node_list = make_pair(node, vector<int>());

    GRAPH[i] = node_list;
    // cout << GRAPH[i].first.first.first << GRAPH[i].first.first.second << GRAPH[i].first.second << endl;
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

    printAllAdj();
    fclose(pF);

    return 0;
}
