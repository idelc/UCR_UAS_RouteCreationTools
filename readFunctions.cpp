#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "prototypes.h"

vector<obstacle> readObstacles(string fileName) {
   obstacle temp; 
   vector<obstacle> temps;
   ifstream read(fileName);

   if(!read.is_open()){
      cout << "Error opening file" << endl;
      exit(1); 
   }

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

vector<obstacle> readObstacles2(string fileName){
   obstacle temp; 
   vector<obstacle> temps;
   ifstream read(fileName);

   if(!read.is_open()){
      cout << "Error opening file" << endl;
      exit(1); 
   }

   double deg;//reads in degrees
   double min;//reads in minutes
   double sec;//reads in 
   double rad;
   char   head;
   char   rand;//will trash commas
   bool   first = true;
   double tempNum = 0;
   
   while(read >> head >> deg >> rand >> min >> rand >> sec){ //uses inherent boolean
      if((head == 'S') || (head == 'W')){
         tempNum = (deg + (min/60) + (sec/3600)) * -1;
      }
      else{
         tempNum = (deg + (min/60) + (sec/3600));
      }
      if(first){
         temp.lat = tempNum;
         first = false;
      }
      else{
         temp.log = tempNum;
         first = true;
         read >> rad;
         temp.radius = rad;
         temps.push_back(temp);
      }
   }
   return temps;
}

vector<point> readPoints(string fileName){
   point temp; 
   vector<point> temps;
   ifstream read(fileName);

   if(!read.is_open()) {
      cout << "Error opening file" << endl;
      exit(1); 
   }

   double deg;//reads in degrees
   double min;//reads in minutes
   double sec;//reads in 
   char   head;
   char   rand;//will trash commas
   bool   first = true;
   double tempNum = 0;
   
   while(read >> head >> deg >> rand >> min >> rand >> sec){ //uses inherent boolean
      if((head == 'S') || (head == 'W')){
         tempNum = (deg + (min/60) + (sec/3600)) * -1;
      }
      else{
         tempNum = (deg + (min/60) + (sec/3600));
      }
      if(first){
         temp.lat = tempNum;
         first = false;
      }
      else{
         temp.log = tempNum;
         first = true;
         temps.push_back(temp);
      }
   }
   return temps;
}

bool colides(const point toCheck, vector<obstacle> obstacles){
   double x = 0, y = 0;
   x = toCheck.log;
   y = toCheck.lat;
   double h = 0, k = 0, r = 0;
   for(unsigned i = 0; i < obstacles.size(); ++i){
      h = obstacles.at(i).log;
      k = obstacles.at(i).lat;
      r = obstacles.at(i).radius;
      if(sqrt(x-h) + sqrt(y-k) == sqrt(r)){
         return true;
      }
   }
   return false; 
}