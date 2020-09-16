#ifndef OBJECT_ROTATION_SCREENSHOTS_MANAGER_H
#define OBJECT_ROTATION_SCREENSHOTS_MANAGER_H

#include "screenshotTaker.h"
#include "cube.h"

class Manager
{
private:
    Cube cube;
    ScreenshotTaker photographer;

    int frameNumber;
    int totalNumScreenshots;
    bool isDone;

    std::string directory = R"(C:\Users\Marcus\CLionProjects\object-rotation-screenshots\screenshots\)";
    std::string imageNameBase = "rotatedCube";
public:
    Manager();
    Manager(int inputTotalNumScreenshots);

    Point getCameraLoc() const;
    Point getCameraLook() const;
    Point getCameraUp() const;

    bool getIsDone() const;

    void tick();

    void draw() const;
};

#endif //OBJECT_ROTATION_SCREENSHOTS_MANAGER_H
