#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

#define nRange 100.0f

// Initial square position and size
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat rsize = 25;

// Step size in x and y directions
//  (number of pixels to move each time)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;


// Set up the rendering state
void SetupRC(void)
{
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set current drawing color to green
    //          R     G      B
    glColor3f(0.0f, 1.0f, 0.0f);

    // Set color shading model to flat
    glShadeModel(GL_FLAT);

    // Clockwise-wound polygon are front facing; this is reversed
    // because we are using triangle fans
    glFrontFace(GL_CW);
}

void DrawWhiteSpiral()
{
    GLdouble dRadius = 0.1; // Initial radius of spiral
    GLdouble dAngle;        // Looping variable

    glColor3d(1.0, 1.0, 1.0f);

    glBegin(GL_LINE_STRIP);
    for (dAngle = 0; dAngle < 400.0; dAngle += 0.1)
    {
        glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
        dRadius *= 1.002;
    }
    glEnd();
}

// Called to draw scene
void RenderScene(void)
{

    // Clear blue window
    glClearColor(0.0, 0.0, 1.0, 0.0);

    // Use 0 for clear stencil
    glClearStencil(0.0f);

    // enable stencil
    glEnable(GL_STENCIL_TEST);

    // Clear color and stencil buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // All draing commands fail the stencil test, and are not
    //  drawn, but increment the value in the stencil buffer.
    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    // spiral pattern will create stencil pattern
    // Draw the spiral pattern with white lines.
    // We make the lines white to demonstrate that the
    // stancil function prevents them from being drawn
    DrawWhiteSpiral();

    //Now, allow drawing, except where the stencil pattern is 0x1
    //and do not make any further change to the stencil buffer
    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // Now draw red bounding square
    // (x and y) are modifier by a timer function
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x, y, x + rsize, y - rsize);

    // All done, do the buffer swap
    glutSwapBuffers();
}

// Called by GLUT library when idle (window not being resized or moved)
void TimerFunction(int value)
{
    // Reverse direction when you reach left or right edge
    if (x > nRange - rsize || x < -nRange)
        xstep = -xstep;

    // Reverse direction when you reach top or botton edge
    if (y > nRange || y < -nRange + rsize)
        ystep = -ystep;

    // Actually move the square
    x += xstep;
    y += ystep;

    // Check bounds. This is in case the window is made
    // smaller while the rectangle is bouncing and the
    // rectangle suddenly finds itself outside the new
    // clipping volume
    if (x > (nRange - rsize + xstep))
        x = nRange - rsize - 1;
    else if (x < -(nRange + xstep))
        x = -nRange - 1;

    if (y > (nRange + ystep))
        y = nRange - 1;
    else if (y < -(nRange - rsize + ystep))
        y = -nRange + rsize - 1;

    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei width, GLsizei height)
{
    

    // Prevent a divide by zero
    if (height == 0)
        height = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    if (width <= height)
        glOrtho(-nRange, nRange, -nRange * height / width, nRange * height / width, -nRange, nRange);
    else
        glOrtho(-nRange * width / height, nRange * width / height, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 800);
    glutCreateWindow("OpenGL Stencil test");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);
    SetupRC();

    glutMainLoop();

    return 0;
}
