/** @file course_flow.inl
 *  @brief File of libraries.
 *
 *  This file includes all general libraries
 *  of C++ as well as the signature of each funcion of the program.
 *  Also, all global variables are kept here.
 *
 *  @author Dayanne Fernandes da Cunha 13/0107191
 *  @author Renato Avellar Nobre 15/0146698
 *  @bug No bug known.
 */

#ifndef HEADERS_INL_INCLUDED
#define HEADERS_INL_INCLUDED

/* -- Basic libraries for the better functioning of the program -- */

#include <iostream>
#include <sstream>
#include <ostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

/* ----------- Definition of all functions of the program ----------- */
void processUIChoice();

/* -- Functions to show data on command terminal -- */
void displayHeaderUI();
void displayTopologicSortUI();
void displayCriticalPathUI();
void displayHelpUI();
void displayWrongChoiceUI();
void displayUI();
void printAllAdj();

/* -- Functions to create and populate the base graph -- */


/* -- Functions to create and populate the base graph -- */
void insertAllOnGraph(string, string, int, float, int);
void insertLinksOnGraph(vector<string>);
void processCodeLink(string, int);
float calculateWeight(int, float);

/* -- Global variables definitions -- */

#define GRAPHSIZE 4

#if defined POSIX || defined __APPLE__
  #define CLEARSCR() system("clear")
#elif defined MSDOS || defined WIN32
  #define CLEARSCR() system("cls")
#endif

#define ss pair<string, string>
#define ssf pair<ss, float>
#define ssfv pair <ssf, vector<int> >

vector<ssfv> GRAPH(GRAPHSIZE);

#endif // HEADERS_INL_INCLUDED
