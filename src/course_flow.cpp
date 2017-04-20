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
float calculateWeight(int cred, float f){
    return cred*f;
}

void insertAllOnGraph(string cod, string name, int cred, float f, int i){
    GRAPH[i].push_back(make_pair(make_pair(cod, name), calculateWeight(cred, f)));
    cout << GRAPH[i][0].first.first << GRAPH[i][0].first.second << GRAPH[i][0].second  << endl;

}
/**
 * Main function. Read and load basic data, then execute all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main(){

    char cod[15], name[50];
    string scod, sname;
    int cred, i = 0;
    float f;

    FILE *pF = fopen("courses.txt", "r");

    if(pF == NULL) {
        cout << "Error on open the file." << endl;
        return -1;
    }

    while (fscanf(pF, "%s | %[^|] | %d | %f", cod, name, &cred, &f) != EOF)
    {
        scod = cod;
        sname = name;
        insertAllOnGraph(scod, sname, cred, f, i);
        ++i;
    }

  fclose(pF);

  return 0;
}
