// The code to get screen information and take screenshots is based on
// a post on https://stackoverflow.com/questions/3291167/how-can-i-take-a-screenshot-in-a-windows-application
// by Woody.
// The code to write to a bitmap file is from a post on
// https://stackoverflow.com/questions/24720451/save-hbitmap-to-bmp-file-using-only-win32
// by Dmitry.
// The code to copy a string to a char[] is from
// https://www.geeksforgeeks.org/convert-string-char-array-cpp/#:~:text=A%20way%20to%20do%20this,current%20value%20of%20the%20string.

#ifndef OBJECT_ROTATION_SCREENSHOTS_SCREENSHOTTAKER_H
#define OBJECT_ROTATION_SCREENSHOTS_SCREENSHOTTAKER_H

#include <string>
#include <assert.h>
#include <stdio.h>
#include "graphics.h"

class ScreenshotTaker
{
private:
    std::string directory;       // where the files get saved to
    std::string imageNameBase;   // a unique string (like current date/time) to name the files
    int currentIndex;            // how many screenshots have been taken

    // How many pixels to cut off from the edges of the screen
    int leftIgnore, topIgnore, bottomIgnore, rightIgnore;
    int imageWidth, imageHeight; // dimensions of the screenshots
public:
    ScreenshotTaker();
    ScreenshotTaker(std::string inputDirectory, std::string inputImageNameBase,
            int inputLeftIgnore, int inputRightIgnore,
            int inputTopIgnore, int inputBottomIgnore);

    // Helper functions to write to a bmp file
    PBITMAPINFO CreateBitmapInfoStruct(HBITMAP);
    void CreateBMPFile(LPTSTR pszFile, HBITMAP hBMP);

    // What actually gets called
    void takeScreenShot();
};

#endif //OBJECT_ROTATION_SCREENSHOTS_SCREENSHOTTAKER_H
