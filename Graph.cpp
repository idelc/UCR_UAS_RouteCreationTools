#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

#include "Graph.h"

Graph::Graph(ifstream& read){
    int numNames = 0;
    int numRelations = 0;
    read >> numNames >> numRelations;
    vertices.resize(numNames);
    string name1, name2;
    for(unsigned i = 0; i < vertices.size(); ++i){
        read >> name1;
        vertices.at(i).label = name1;
    }
    int save1 = -1, save2 = -1, weight = -1;

    while(read >> name1 >> name2 >> weight){
        for(unsigned j = 0; j < vertices.size(); j++){
            if(name1 == vertices.at(j).label){
                save1 = j;
            }
            if(name2 == vertices.at(j).label){
                save2 = j;
            }
        }
        if(save1 == -1 || save2 == -2){
            exit(1);
        }
        else{
            vertices.at(save1).neighbors.push_back(pair<int,int>(save2,weight));
        }
    }
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