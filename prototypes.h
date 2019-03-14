#include <list>
#include <vector>

struct point{               //specifies a point in space in decimal degrees
	double lat;
	double log;
};

struct waypoint : public point{
    int sequenceNumber;     //what number are we along route
};

struct obstacle : public point{
    double radius;
    double height;
};

struct collision {          //is the object that defines a detected collision
    obstacle    danger;     //the object that will be hit in a direct route
    waypoint       first;   //from the point first
    waypoint       last;    //to the point last
};


std::list<point> subdivideCircle(obstacle, int numPoints);

std::vector<collision> detect(std::list<waypoint> originalRoute, std::vector<obstacle> obstacles);

vector<obstacle> readObstacles(string filename);
