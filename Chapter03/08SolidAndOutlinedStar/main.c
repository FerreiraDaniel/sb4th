#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

// Define a constant for the value of PI
#define TRUE 1

static GLint windowId;

// Keep track of windwos changing width and height
GLfloat windowWidth;
GLfloat windowHeight;

GLbyte bCull = 0;
GLbyte bDepth = 0;
GLbyte bOutline = 0;
GLbyte bEdgeFlag = 0;

void menu(int num)
{
    if (num == 0)
    {
        glutDestroyWindow(windowId);
        exit(0);
    }
    else
    {
        switch (num)
        {
        case 2:
            bCull = 1;
            break;
        case 3:
            bCull = 0;
            break;
        case 4:
            bDepth = 1;
            break;
        case 5:
            bDepth = 0;
            break;
        case 6:
            bOutline = 1;
            break;
        case 7:
            bOutline = 0;
        case 8:
            bEdgeFlag = 1;
            break;
        case 9:
            bEdgeFlag = 0;
            break;

        default:
            break;
        }
    }
    glutPostRedisplay();
}

void createMenu(void)
{
    int turnCullingSubMenuId = glutCreateMenu(menu);
    glutAddMenuEntry("On", 2);
    glutAddMenuEntry("Off", 3);
    int enableDepthTestMenuId = glutCreateMenu(menu);
    glutAddMenuEntry("On", 4);
    glutAddMenuEntry("Off", 5);
    int outlineMenuId = glutCreateMenu(menu);
    glutAddMenuEntry("On", 6);
    glutAddMenuEntry("Off", 7);
    int edgeFlagMenuId = glutCreateMenu(menu);
    glutAddMenuEntry("On", 8);
    glutAddMenuEntry("Off", 9);

    // Main menu
    int menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Turn culling", turnCullingSubMenuId);
    glutAddSubMenu("Enable depth testing", enableDepthTestMenuId);
    glutAddSubMenu("Outline", outlineMenuId);
    glutAddSubMenu("Edge", edgeFlagMenuId);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

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
    GLfloat x, y, angle; // Storage for coordinates and angles
    int iPivot = 1;

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Turn culling on if flat is set
    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    // Enable depth testing if flat is set
    if (bDepth)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    // Draw the back side as a wireframe only, if flag is set
    if (bOutline)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);

    // Save matrix state and to the rotation
    glPushMatrix();

    // Begin the triangles
    glBegin(GL_TRIANGLES);

    glEdgeFlag(bEdgeFlag);
    glVertex2f(-20.0f, 0.0f);
    glEdgeFlag(TRUE);
    glVertex2f(20.0f, 0.0f);
    glVertex2f(0.0f, 40.0f);

    glVertex2f(-20.0f, 0.0f);
    glVertex2f(-60.0f, -20.0f);
    glEdgeFlag(bEdgeFlag);
    glVertex2f(-20.0f, -40.0f);

    glEdgeFlag(TRUE);
    glVertex2f(-20.0f, -40.0f);
    glVertex2f(0.0f, -80.0f);
    glEdgeFlag(bEdgeFlag);
    glVertex2f(20.0f, -40.0f);

    glEdgeFlag(TRUE);
    glVertex2f(20.0f, -40.0f);
    glVertex2f(60.0f, -20.0f);
    glEdgeFlag(bEdgeFlag);
    glVertex2f(20.0f, 0.0f);

    glEdgeFlag(TRUE);
    
    // Center square as two triangles
    glEdgeFlag(bEdgeFlag);
    glVertex2f(-20.0f, 0.0f);
    glVertex2f(-20.0f, -40.0f);
    glVertex2f(20.0f, 0.0f);

    glVertex2f(-20.0f, -40.0f);
    glVertex2f(20.0f, -40.0f);
    glVertex2f(20.0f, 0.0f);
    glEdgeFlag(TRUE);
    // Done drawing triangles
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
    windowWidth = width;
    windowHeight = height;
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    windowId = glutCreateWindow("Solid and outlined star");
    createMenu();
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
