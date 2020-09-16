// Much of the code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.
// The code to switch to 2D drawing mode is from https://www.youtube.com/watch?v=i1mp4zflkYo,
// a video by The Pentamollis Project
// The code to enable alpha is from https://www.opengl.org/archives/resources/faq/technical/transparency.htm

#include "graphics.h"
#include "manager.h"

GLdouble width, height;
int wd;
Manager manager;
// Mouse variables
int prevMouseX, prevMouseY;
bool justClicked;

void init()
{
    //width = 1024;
    HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
    width = GetDeviceCaps(hScreenDC, HORZRES);
    //height = 512;
    height =  GetDeviceCaps(hScreenDC, VERTRES);
    prevMouseX = width/2;
    prevMouseY = height/2;
    justClicked = false;
}

/* Initialize OpenGL Graphics */
void initGL()
{
    // Enable alpha transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Point camLoc = manager.getCameraLoc();
    Point camLook = manager.getCameraLook();
    Point camUp = manager.getCameraUp();
    gluLookAt(camLoc.x, camLoc.y, camLoc.z,  // eye position
              camLook.x, camLook.y, camLook.z,  // center position (not gaze direction)
              camUp.x, camUp.y, camUp.z); // up vector
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display()
{

    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-width/2, width/2, -height/2, height/2, -width, width);
    gluPerspective(45, width/height, 1, 4096);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);

    // Update where the camera is
    Point camLoc = manager.getCameraLoc();
    Point camLook = manager.getCameraLook();
    Point camUp = manager.getCameraUp();
    gluLookAt(camLoc.x, camLoc.y, camLoc.z,  // eye position
              camLook.x, camLook.y, camLook.z,  // center position (not gaze direction)
              camUp.x, camUp.y, camUp.z); // up vector

    // Draw in 3d
    glLineWidth(2.0);
    manager.draw();


    // Switch to 2d mode
    // Code from https://www.youtube.com/watch?v=i1mp4zflkYo
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0,width,0.0,height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //manager.drawUI();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27)
    {
        glutDestroyWindow(wd);
        exit(0);
    }
    glutPostRedisplay();
}


void kbu(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void kbdS(int key, int x, int y)
{
    glutPostRedisplay();
}

void cursor(int x, int y)
{
    prevMouseX = x;
    prevMouseY = y;

    // if the cursor gets close to the edge, put it back in the middle
    if(x < 120 || x > width - 120 || y < 120 || y > height - 120)
    {
        glutWarpPointer(width/2,height/2);
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void timer(int dummy)
{
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
    manager.tick();
    if(manager.getIsDone())
    {
        glutDestroyWindow(wd);
        exit(0);
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
    manager = Manager(15);
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Object Rotation." /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // Make the cursor invisible
    glutSetCursor(GLUT_CURSOR_NONE);

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    glutKeyboardUpFunc(kbu);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

void drawPoint(const Point &p)
{
    glVertex3f(p.x, p.y, p.z);
}
void setGLColor(RGBAcolor color)
{
    glColor4f(color.r, color.g, color.b, color.a);
}
