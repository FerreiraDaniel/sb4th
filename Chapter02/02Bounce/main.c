#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

// Initial square position and size
GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLfloat rsize = 25;

// Step size in x and y directions
//  (number of pixels to move each time)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Keep track of windwos changing width and height
GLfloat windowWidth;
GLfloat windowHeight;

// Called to draw scene
void RenderScene(void)
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    // Set current drawing color to red
    //          R     G      B
    glColor3f(1.0f, 0.0f, 0.0f);

    // Draw a filled rectangle with current color
    glRectf(x1, y1, x1 + rsize, y1 - rsize);

    // Flush drawing commands and swap
    glutSwapBuffers();
}

// Called by GLUT library when idle (window not being resized or moved)
void TimerFunction(int value)
{
    // Reverse direction when you reach left or right edge
    char test = x1 > windowWidth - rsize || x1 < -windowWidth;
    printf("test: %d x1: %f \n", test, x1);
    if (x1 > windowWidth - rsize || x1 < -windowWidth)
        xstep = -xstep;

    // Reverse direction when you reach top or botton edge
    if (y1 > windowHeight || y1 < -windowHeight + rsize)
        ystep = -ystep;

    // Actually move the square
    x1 += xstep;
    y1 += ystep;

    // Check bounds. This is in case the window is made
    // smaller while the rectangle is bouncing and the
    // rectangle suddenly finds itself outside the new
    // clipping volume
    if (x1 > (windowWidth - rsize + xstep))
        x1 = windowWidth - rsize - 1;
    else if (x1 < -(windowWidth + xstep))
        x1 = -windowWidth - 1;

    if (y1 > (windowHeight + ystep))
        y1 = windowHeight - 1;
    else if (y1 < -(windowHeight - rsize + ystep))
        y1 = -windowHeight + rsize - 1;

    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

// Set up the rendering state
void SetupRC(void)
{
    // Set clear color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio;
    // Prevent a divide by zero
    if (height == 0)
        height = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);

    
    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Establish clipping volume (left, right, bottom, top, near, far)
    aspectRatio = (GLfloat)width / (GLfloat)height;
    if (width <= height)
        glOrtho(-width, width, -height / aspectRatio, height / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-width * aspectRatio, width * aspectRatio, -height, height, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    windowWidth = width;
    windowHeight = height;
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bounce");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);
    SetupRC();

    glutMainLoop();

    return 0;
}
