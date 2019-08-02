#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

#include "Graph.h"
#include "prototypes.h"

Graph::Graph(list<point> points){
    vector<point> easyAcc;
    int numNames = points.size();
    int numRelations = ((points.size() - 2) * 4) + 4;
    vertices.resize(numNames);
    int cntr = 0;
    string name1, name2;
    for(unsigned i = 0; i < vertices.size(); ++i){
        vertices.at(i).label = cntr++;
    }
    for (list<point>::iterator it = points.begin(); it != points.end(); ++it){
        easyAcc.push_back(*it);
    }
    vertices.at(1).neighbors.push_back(pair<int,int>(points.size() - 2, distanceFt(easyAcc.at(1),easyAcc.at(points.size() - 2))));
    vertices.at(points.size() - 2).neighbors.push_back(pair<int,int>(1, distanceFt(easyAcc.at(1),easyAcc.at(points.size() - 2))));
    for(unsigned i = 1; i < (points.size() - 2); ++i){ 
        vertices.at(i).neighbors.push_back(pair<int,int>(i+1, distanceFt(easyAcc.at(i),easyAcc.at(i+1))));
        vertices.at(i+1).neighbors.push_back(pair<int,int>(i, distanceFt(easyAcc.at(i),easyAcc.at(i+1))));        
    }
    unsigned min1 = 0, min2 = 0;
    double minVal1 = INT_MAX, minVal2 = INT_MAX, temp;
    for(unsigned i = 1; i < (points.size() - 2); ++i){
        temp = distanceFt(easyAcc.at(0), easyAcc.at(i));
        if(temp < minVal1){
            min1 = i;
            
        }
        temp = distanceFt(easyAcc.at(easyAcc.size()-1),easyAcc.at(i));
        if(temp < minVal2){
            min2 = i;
        }
    }
    vertices.at(0).neighbors.push_back(pair<int,int>(min1, distanceFt(easyAcc.at(0), easyAcc.at(min1))));
    vertices.at(easyAcc.size()-1).neighbors.push_back(pair<int,int>(min2, distanceFt(easyAcc.at(easyAcc.size()-1),easyAcc.at(min2))));
    vertices.at(min1).neighbors.push_back(pair<int,int>(0, distanceFt(easyAcc.at(0), easyAcc.at(min1))));
    vertices.at(min2).neighbors.push_back(pair<int,int>(easyAcc.size()-1, distanceFt(easyAcc.at(easyAcc.size()-1),easyAcc.at(min2))));
}

void Graph::output_graph(const string & nameOfFile){
    ofstream write(nameOfFile);
    write << "digraph G {" << endl;
    for(unsigned i = 0; i < vertices.size(); ++i){
        write << "\t" << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"];" << endl;
        for (list<pair<int,double>>::iterator it = vertices.at(i).neighbors.begin();
        it != vertices.at(i).neighbors.end(); ++it){
            write << "\t" << vertices.at(i).label << " -> ";
            write << vertices.at(it->first).label << endl;
        }
    }
    write << "}";
    write.close();
    string jpgFilename = nameOfFile.substr(0,nameOfFile.size()-4)+".jpg";
    string command = "dot -Tjpg " + nameOfFile + " -o " + jpgFilename;
    system(command.c_str());
}
 
void Graph::bfs(){
    queue<Vertex> nodes;
    vertices.at(0).distance = 0;
    vertices.at(0).color = "GREY";
    nodes.push(vertices.at(0));
    while(!nodes.empty()){ 
        Vertex u = nodes.front();
        nodes.pop();
        for (list<pair<int,double>>::iterator it = u.neighbors.begin();
        it != u.neighbors.end(); ++it){
           if(vertices.at(it->first).color == "WHITE"){
               vertices.at(it->first).color = "GREY"; // (Gray means discovered, but not expanded)
               vertices.at(it->first).distance = u.distance + 1;
               vertices.at(it->first).prev = &u;
               nodes.push(vertices.at(it->first));
           }
        }
        u.color = "BLACK";
    }
}

Graph::~Graph(){

} // No need to input anything here

list<point> Graph::customShortestPath(){
    double initialVal = this->vertices.at(0).neighbors.front().second; // distance from point before to connecting point
    int initialPoint = this->vertices.at(0).neighbors.front().first, nextVal = 0;
    // int exitPoint = this ->vertices
    double totalDistance1 = initialVal, totalDistance2 = initialVal;
    bool found = false;
    list<int> path1;
    list<int> path2;
    path1.push_back(0);
    path1.push_back(initialPoint);
    path2.push_back(0);
    path2.push_back(initialPoint);
    for(unsigned i = initialPoint; (this->vertices.at(i).neighbors.size() != 3) && (i != 0);){ // while a point does not have three connections (the third being the exit point)
        // nextVal = max(this->vertices.at(i).neighbors.front().first, this->vertices.at(i).neighbors.back().first); // next in line // TODO: Figure out how to find next in line based on connection
        path1.push_back(nextVal);
        for(list<pair<int,double>>::iterator it = this->vertices.at(i).neighbors.begin(); (it != this->vertices.at(i).neighbors.end()) && (!found); ++it){
            if(it->first == nextVal){
                totalDistance1 += it->second;
                found = true;
            }
        }
        found = false;
        i = nextVal;
    }
}