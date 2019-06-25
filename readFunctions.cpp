#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

#include "prototypes.h"

vector<obstacle> readObstacles(string filename) {
   obstacle temp; 
   vector<obstacle> temps;
   ifstream read(filename);

   if(!read.is_open()){
      cout << "Error opening file" << endl;
      exit(1); 
   }

   // double la;//reads in lattitude val
   // double lo;//reads in longitude val
   // int   rad;//reads in radius
   // char  com;//will trash commas
   
   // while(read >> la >> com >> lo >> com >> rad) {//uses inherent boolean
   //    temp.lat    = la;
   //    temp.log    = lo; //reads in val
   //    temp.radius = rad; 
   //    temps.push_back(temp); //adds to vector
   // }
   // return temps;

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

