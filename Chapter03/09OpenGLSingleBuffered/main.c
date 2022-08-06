#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

// Define a constant for the value of PI
#define GL_PI 3.1415f

// Keep track of windwos changing width and height
GLfloat windowWidth;
GLfloat windowHeight;



// Called to draw scene
void RenderScene(void)
{

    static GLdouble dRadius = 0.1; 
    static GLdouble dAngle = 0.0;


    if (dAngle == 0.0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glBegin(GL_POINTS);
    glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
    glEnd();
    dRadius *= 1.01;
    dAngle += 0.1;

    if (dAngle > 30.0)
    {
        dRadius = 0.1;
        dAngle = 0.0;
    }

    glFlush();
}

// Set up the rendering state
void SetupRC(void)
{
    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Set current drawing color to green
    //          R     G      B
    glColor3f(0.0f, 1.0f, 0.0f);
}

// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei width, GLsizei height)
{
    GLfloat nRange = 5.0f;

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

void TimerFunction(int value)
{
    // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(16, TimerFunction, 1);
}

// Main program entry point
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Single Buffered");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);
    SetupRC();

    glutMainLoop();

    return 0;
}
