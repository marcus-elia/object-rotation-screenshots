#include "manager.h"

Manager::Manager()
{
    cube = Cube({0, 0, -50}, 20, {0,0,1,1}, {1,1,1,1});
    photographer = ScreenshotTaker(directory, imageNameBase, 10, 0, 30, 40);

    totalNumScreenshots = 10;
    frameNumber = 0;
    isDone = false;
}

Manager::Manager(int inputTotalNumScreenshots)
{
    cube = Cube({0, 0, -50}, 20, {0,0,1,1}, {1,1,1,1});
    photographer = ScreenshotTaker(directory, imageNameBase, 10, 0, 30, 40);

    totalNumScreenshots = inputTotalNumScreenshots;
    frameNumber = 0;
    isDone = false;
}

Point Manager::getCameraLoc() const
{
    return {0, 10, 0};
}
Point Manager::getCameraLook() const
{
    return {0, 0, -50};
}
Point Manager::getCameraUp() const
{
    return {0, 1, 0};
}
bool Manager::getIsDone() const
{
    return isDone;
}

void Manager::tick()
{
    if(frameNumber >= delay)
    {
        photographer.takeScreenShot();
        cube.rotate(0, 0.2, 0);
    }
    frameNumber++;
    if(frameNumber == totalNumScreenshots + delay)
    {
        isDone = true;
    }
}

void Manager::draw() const
{
    cube.draw();
}