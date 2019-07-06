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
    for(unsigned i = 1; i < (points.size() - 1); ++i) // finish this loop
         
}

void Graph::output_graph(const string & nameOfFile){
    ofstream write(nameOfFile);
    write << "digraph G {" << endl;
    for(unsigned i = 0; i < vertices.size(); ++i){
        write << "\t" << vertices.at(i).label << "[label = \"" << vertices.at(i).label << ", " << vertices.at(i).distance << "\"];" << endl;
        for (list<pair<int,int>>::iterator it = vertices.at(i).neighbors.begin();
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
        for (list<pair<int,int>>::iterator it = u.neighbors.begin();
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