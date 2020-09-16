#ifndef OBJECT_ROTATION_SCREENSHOTS_CUBE_H
#define OBJECT_ROTATION_SCREENSHOTS_CUBE_H

#include "graphics.h"
#include <vector>

class Cube
{
private:
    std::vector<Point> corners;
    Point center;
    double sideLength;
    RGBAcolor faceColor;
    RGBAcolor lineColor;
public:
    Cube();
    Cube(Point inputCenter, double inputSideLength, RGBAcolor inputFaceColor, RGBAcolor inputLineColor);

    void initializeCorners();

    void rotate(double thetaX, double thetaY, double thetaZ);
    void move(double deltaX, double deltaY, double deltaZ);
    void rotateAroundPoint(const Point &pBase, double thetaX, double thetaY, double thetaZ);

    void draw() const;
    void drawFaces() const;
    void drawLines() const;
};

#endif //OBJECT_ROTATION_SCREENSHOTS_CUBE_H
