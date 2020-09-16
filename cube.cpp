#include "cube.h"

Cube::Cube()
{
    center = {0, 0, 0};
    sideLength = 20;
    faceColor = {1, 0, 0, 1};
    lineColor = {1, 1, 1, 1};

    initializeCorners();
}
Cube::Cube(Point inputCenter, double inputSideLength, RGBAcolor inputFaceColor, RGBAcolor inputLineColor)
{
    center = inputCenter;
    sideLength = inputSideLength;
    faceColor = inputFaceColor;
    lineColor = inputLineColor;

    initializeCorners();
}

void Cube::initializeCorners()
{
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (sideLength / 2.0), center.y + (sideLength / 2.0), center.z + (sideLength / 2.0)};
    corners[1] = {center.x - (sideLength / 2.0), center.y + (sideLength / 2.0), center.z + (sideLength / 2.0)};
    corners[2] = {center.x + (sideLength / 2.0), center.y - (sideLength / 2.0), center.z + (sideLength / 2.0)};
    corners[3] = {center.x - (sideLength / 2.0), center.y - (sideLength / 2.0), center.z + (sideLength / 2.0)};
    corners[4] = {center.x + (sideLength / 2.0), center.y + (sideLength / 2.0), center.z - (sideLength / 2.0)};
    corners[5] = {center.x - (sideLength / 2.0), center.y + (sideLength / 2.0), center.z - (sideLength / 2.0)};
    corners[6] = {center.x + (sideLength / 2.0), center.y - (sideLength / 2.0), center.z - (sideLength / 2.0)};
    corners[7] = {center.x - (sideLength / 2.0), center.y - (sideLength / 2.0), center.z - (sideLength / 2.0)};
}

void Cube::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(Point &p : corners)
    {
        rotatePointAroundPoint(p, center, thetaX, thetaY, thetaZ);
    }
}
void Cube::move(double deltaX, double deltaY, double deltaZ)
{
    movePoint(center, deltaX, deltaY, deltaZ);
    for(Point &p : corners)
    {
       movePoint(p, deltaX, deltaY, deltaZ);
    }
}
void Cube::rotateAroundPoint(const Point &pBase, double thetaX, double thetaY, double thetaZ)
{
    rotatePointAroundPoint(center, pBase, thetaX, thetaY, thetaZ);
    for(Point &p : corners)
    {
        rotatePointAroundPoint(p, pBase, thetaX, thetaY, thetaZ);
    }
}

void Cube::draw() const
{
    drawLines();
    drawFaces();
}
void Cube::drawFaces() const
{
    setGLColor(faceColor);
    glBegin(GL_QUADS);

    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[5]);
    drawPoint(corners[4]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[2]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[6]);
    drawPoint(corners[2]);
    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[3]);
    drawPoint(corners[1]);
    drawPoint(corners[5]);
    drawPoint(corners[7]);
    glEnd();
}
void Cube::drawLines() const
{
    setGLColor(lineColor);
    glBegin(GL_LINES);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[1]);
    drawPoint(corners[3]);

    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[2]);
    drawPoint(corners[0]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);

    drawPoint(corners[5]);
    drawPoint(corners[7]);

    drawPoint(corners[7]);
    drawPoint(corners[6]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);

    drawPoint(corners[0]);
    drawPoint(corners[4]);

    drawPoint(corners[2]);
    drawPoint(corners[6]);

    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[1]);
    drawPoint(corners[5]);

    glEnd();
}