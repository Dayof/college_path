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

// void insertArcsOnGraph(){
//
// }


void processCodeLink(string links, int origin_index){
    string token;
    size_t pos = 0;
    while((pos = links.find(' ')) != (string::npos)){
        token = links.substr(0, pos);
        cout << token << endl;
        links.erase(0, pos+1);
    }
    cout << links << endl;
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
    cout << GRAPH[i].first.first.first << GRAPH[i].first.first.second << GRAPH[i].first.second << endl;
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

    //insertLinksOnGraph(link);

  fclose(pF);

  return 0;
}
