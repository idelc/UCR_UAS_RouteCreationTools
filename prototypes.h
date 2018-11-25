#include <list>
#include <vector>
#include <cmath>

struct point{               //specifies a point in space in decimal degrees
	double lat; //x
	double lng; //y
};

struct waypoint : public point{
    int sequenceNumber;     //what number are we along route
};

struct obstacle : public point{
    double radius;
    double height;
};

struct collision{           //is the object that defines a detected collision
    obstacle     danger;    //the object that will be hit in a direct route
    waypoint      first;    //from the point first
    waypoint       last;    //to the point last
};


std::list<point> subdivideCircle(obstacle, int numPoints);

std::vector<collision> detect(std::list<waypoint> originalRoute, std::vector<obstacle> obstacles){
    std::vector <collision> collisions;
    for(std::list<waypoint>::iterator it = originalRoute.begin() ; it != --originalRoute.end(); ++it){
        waypoint point1 = *it;
        waypoint point2 = *(++it);
        for(int i = 0; i < obstacles.size(); i++){ //iterate over all obstacles
            //calculate angle using cosine function cos(x) = u*v/||v||*||u||
            point vector1;
            point vector2;
            vector1.lat = point2.lat - point1.lat;
            vector2.lat = obstacles.at(i).lat - point1.lat;
            vector1.lng = point2.lng - point1.lng;
            vector2.lng = obstacles.at(i).lng - point1.lng;
            double angle = acos((vector1.lat * vector2.lat + vector1.lng * vector2.lng)/
                                (sqrt(pow(vector1.lat,2) + pow(vector1.lng,2)) * 
                                 sqrt(pow(vector2.lat,2) + pow(vector2.lng,2))));
            double side = sqrt(pow(vector2.lat,2) + pow(vector2.lng,2)) * sin(angle);
            
            if(side <= obstacles.at(i).radius){
                collision new_collision;
                new_collision.danger = obstacles.at(i);
                new_collision.first = point1;
                new_collision.last = point2;
                collisions.push_back(new_collision);
            }
        }
    }
    return collisions;
}
