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
 * Main function. Read and load basic data, then execute all main
 *  functionalities of the program.
 *
 * @return int 0 represents good exit, -1 represents bad exit
 */
int main()
{
  FILE *pF = fopen("courses.txt", "r");

  if(pF == NULL)
  {
    cout << "Error on open the file." << endl;
    return -1;
  }

  // while (fscanf(pF, "%s | %[^|] | %[^\n]", reg, name, links) != EOF)
  // {
  //
  // }

  fclose(pF);

  return 0;
}
