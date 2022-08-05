#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>


static GLint windowId;


// Bitmap of campfire
GLubyte fire[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0xf0,
                  0x00, 0x00, 0x07, 0xf0, 0x0f, 0x00, 0x1f, 0xe0,
                  0x1f, 0x80, 0x1f, 0xc0, 0x0f, 0xc0, 0x3f, 0x80,
                  0x07, 0xe0, 0x7e, 0x00, 0x03, 0xf0, 0xff, 0x80,
                  0x03, 0xf5, 0xff, 0xe0, 0x07, 0xfd, 0xff, 0xf8,
                  0x1f, 0xfc, 0xff, 0xe8, 0xff, 0xe3, 0xbf, 0x70,
                  0xde, 0x80, 0xb7, 0x00, 0x71, 0x10, 0x4a, 0x80,
                  0x03, 0x10, 0x4e, 0x40, 0x02, 0x88, 0x8c, 0x20,
                  0x05, 0x05, 0x04, 0x40, 0x02, 0x82, 0x14, 0x40,
                  0x02, 0x40, 0x10, 0x80, 0x02, 0x64, 0x1a, 0x80,
                  0x00, 0x92, 0x29, 0x00, 0x00, 0xb0, 0x48, 0x00,
                  0x00, 0xc8, 0x90, 0x00, 0x00, 0x85, 0x10, 0x00,
                  0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00};

// Set up the rendering state
void SetupRC(void)
{
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set current drawing color to red
    //          R     G      B
    glColor3f(1.0f, 0.0f, 0.0f);

    // Enable polygon stippling
    glEnable(GL_POLYGON_STIPPLE);

    // Specify a specific stipple pattern
    glPolygonStipple(fire);
}

// Called to draw scene
void RenderScene(void)
{
    GLfloat x, y, angle; // Storage for coordinates and angles

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Save matrix state and to the rotation
    glPushMatrix();


    glBegin(GL_POLYGON);
    glVertex2f(-20.0f, 50.0f);
    glVertex2f(20.0f, 50.0f);
    glVertex2f(50.0f, 20.0f);
    glVertex2f(50.0f, -20.0f);
    glVertex2f(20.0f, -50.0f);
    glVertex2f(-20.0f, -50.0f);
    glVertex2f(-50.0f, -20.0f);
    glVertex2f(-50.0f, 20.0f);
    glEnd();

    // Restore transformations
    glPopMatrix();

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
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    windowId = glutCreateWindow("Polygon Stippling");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
