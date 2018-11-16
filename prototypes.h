#include <list>
#include <vector>

struct point{               //specifies a point in space in decimal degrees
	double lat;
	double log;
};

struct waypoint : public point{
    int sequenceNumber;     //what number are we along route
};

struct obstical : public point{
    double radius;
    double height;
};

struct collision {          //is the object that defines a detected collision
    obstical    danger;     //the object that will be hit in a direct route
    waypoint       first;   //from the point first
    waypoint       last;    //to the point last
};


std::list<point> subdivideCircle(obstical, int numPoints);

std::vector<collision> detect(std::list<waypoint> originalRoute, std::vector<obstical> obsticals);


