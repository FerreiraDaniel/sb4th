#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

// Define a constant for the value of PI
#define GL_PI 3.1415f

static GLint windowId;

// Keep track of windwos changing width and height
GLfloat windowWidth;
GLfloat windowHeight;

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

// Called to draw scene
void RenderScene(void)
{
    // Clear blue window
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Now set scissor to smaller red sub region
    glClearColor(1.0f, 0.0, 0.0f, 0.0f);
    glScissor(100, 100, 600, 400);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    // Finally, an even smaller green rectangle
    glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    glScissor(200, 200, 400, 200);
    glClear(GL_COLOR_BUFFER_BIT);

    // Turn scissor back off for next render
    glDisable(GL_SCISSOR_TEST);

    glutSwapBuffers();
}

// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei width, GLsizei height)
{
    GLfloat nRange = 100.0f;

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
    windowWidth = width;
    windowHeight = height;
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    windowId = glutCreateWindow("OpenGL Scissor");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
