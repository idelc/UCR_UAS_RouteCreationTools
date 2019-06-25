#include <list>
#include <vector>
#include <string>

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


std::list<point> subdivideCircle(const obstacle, int numPoints);

std::vector<collision> detect(std::list<waypoint> originalRoute, std::vector<obstacle> obstacles);

std::vector<obstacle> readObstacles(std::string filename);

std::vector<point> readPoints(std::string fileName);
