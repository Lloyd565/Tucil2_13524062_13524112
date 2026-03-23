#pragma once
#include "parser.hpp"
#include <bits/stdc++.h>
using namespace std;

class AABB
{
    public:
        static double maxPointX(const vector<Point>& objectMesh){
            double maxPointX = objectMesh[0].x;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].x > maxPointX) {
                    maxPointX = objectMesh[i].x;
                }
            }
            return maxPointX;
        }
        static double minPointX(const vector<Point>& objectMesh){
            double minPointX = objectMesh[0].x;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].x < minPointX) {
                    minPointX = objectMesh[i].x;
                }
            }
            return minPointX;
        }

        static double maxPointY(const vector<Point>& objectMesh){
            double maxPointY = objectMesh[0].y;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].y > maxPointY) {
                    maxPointY = objectMesh[i].y;
                }
            }
            return maxPointY;
        }

        static double minPointY(const vector<Point>& objectMesh){
            double minPointY = objectMesh[0].y;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].y < minPointY) {
                    minPointY = objectMesh[i].y;
                }
            }
            return minPointY;
        }
        static double maxPointZ(const vector<Point>& objectMesh){
            double maxPointZ = objectMesh[0].z;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].z > maxPointZ) {
                    maxPointZ = objectMesh[i].z;
                }
            }
            return maxPointZ;
        }
        static double minPointZ(const vector<Point>& objectMesh){
            double minPointZ = objectMesh[0].z;
            for (int i = 0; i<objectMesh.size(); i++){
                if (objectMesh[i].z < minPointZ) {
                    minPointZ = objectMesh[i].z;
                }
            }
            return minPointZ;
        }

        static bool computeAABBPoint(const vector<Point>& objectMesh, const Point& Point){
            double maxX = maxPointX(objectMesh);
            double minX = minPointX(objectMesh);
            double maxY = maxPointY(objectMesh);
            double minY = minPointY(objectMesh);
            double maxZ = maxPointZ(objectMesh);
            double minZ = minPointZ(objectMesh);
            return (Point.x >= minX && Point.x <= maxX) && (Point.y >= minY && Point.y <= maxY) && (Point.z >= minZ && Point.z <= maxZ);
        }

        static bool computeAABBAABB(const vector<Point>& objectMesh1, const vector<Point>& objectMesh2){
            double maxX1 = maxPointX(objectMesh1);
            double minX1 = minPointX(objectMesh1);
            double maxY1 = maxPointY(objectMesh1);
            double minY1 = minPointY(objectMesh1);
            double maxZ1 = maxPointZ(objectMesh1);
            double minZ1 = minPointZ(objectMesh1);

            double maxX2 = maxPointX(objectMesh2);
            double minX2 = minPointX(objectMesh2);
            double maxY2 = maxPointY(objectMesh2);
            double minY2 = minPointY(objectMesh2);
            double maxZ2 = maxPointZ(objectMesh2);
            double minZ2 = minPointZ(objectMesh2);

            return (maxX1 >= minX2 && minX1 <= maxX2) && (maxY1 >= minY2 && minY1 <= maxY2) && (maxZ1 >= minZ2 && minZ1 <= maxZ2);
        }

        
};