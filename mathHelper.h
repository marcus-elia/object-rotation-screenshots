#ifndef OBJECT_ROTATION_SCREENSHOTS_MATHHELPER_H
#define OBJECT_ROTATION_SCREENSHOTS_MATHHELPER_H

#include <cmath>
#include "structs.h"

// This file contains general math helper functions

const double PI = 3.14159265358979323846;

// ============ Geometry =============
double distanceFormula(double x1, double y1, double x2, double y2);

// Returns the distance in the xz plane
double distance2d(Point p1, Point p2);

double distance3d(Point p1, Point p2);

// =============== Points ==============

// Translates Point p
void movePoint(Point &p, double deltaX, double deltaY, double deltaZ);

// Rotates p around pBase in 3D space
void rotatePointAroundPoint(Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ);

// Returns rotated copy of p, leaving p unchanged
Point getRotatedPointAroundPoint(const Point &p, const Point &pBase, double thetaX, double thetaY, double thetaZ);


#endif //OBJECT_ROTATION_SCREENSHOTS_MATHHELPER_H
