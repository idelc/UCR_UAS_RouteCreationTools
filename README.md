# UCR_UAS_RouteCreationTools

This repository will contain the programs that fetch, create and upload the route the uav will fly.

These tools will work from and the command line and represent routes and waypoints as simple textfiles.
This will make it simpler to break the tasks up into small easy to test segments.

## Overview

* Route file format: text file containing a full route as used in [MavProxy](https://github.com/ArduPilot/MAVProxy/blob/master/MAVProxy/modules/mavproxy_wp.py). Its not documented well any one place so its is helpfull to RE the format from the code.

* Obstacle file format: text file storing the obsticals that must be avoided.
         
* `combine in0.txt in1.txt out.txt`: Take in two routes and merges them into one valid route.

* `safeRoute Obst.txt route.txt out.txt`: Takes a list of obsticals and a route. It creates from these a route that still hits all waypoints in `route.txt` but no longer collides with any obstical in `Obst.txt`.

* Upload: MavProxy will be used to upload the finished route file to the UAV.
