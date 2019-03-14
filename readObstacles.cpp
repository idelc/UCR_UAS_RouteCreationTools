#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include "prototypes.h"

vector<obstacle> readObstacles(string filename) {
   obstacle temp; 
   vector<obstacle> temps;
   ifstream read(filename.c_str());

   double la;//reads in lattitude val
   double lo;//reads in longitude val
   int   rad;//reads in radius
   char  com;//will trash commas
   
   while(read >> la >> com >> lo >> com >> rad) {//uses inherent boolean
      temp.lat    = la;
      temp.log    = lo; //reads in val
      temp.radius = rad; 
      temps.push_back(temp); //adds to vector
   }
   return temps;
}