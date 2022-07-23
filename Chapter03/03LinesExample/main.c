#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

//Define a constant for the value of PI
#define GL_PI 3.1415f

static GLfloat xRot = 250.0f;
static GLfloat yRot = 0.2f;

// Keep track of windwos changing width and height
GLfloat windowWidth;
GLfloat windowHeight;

// Called to draw scene
void RenderScene(void)
{
    GLfloat x,y,z, angle;   // Storage for coordinates and angles

    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    //Save matrix stat and do the rotation
    glPushMatrix();
    

    // Call only once for all remaining points
    glBegin(GL_LINES);

        // All the lines lie in the xy plane
        z = 0.0f;

        // Loop around in a circle three times
        for(angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += (GL_PI / 20.0f)) {
            
            // Top hal of the circle
            x = 50.0f * sin(angle);
            y = 50.0f * cos(angle);
            glVertex3f(x, y, z);    // First endpoint of line

            // Bottom half of the circle
            x = 50.0f * sin(angle + GL_PI);
            y = 50.0f * cos(angle + GL_PI);
            glVertex3f(x, y, z);    // Second endpoint of line
            
        }
    // Done drawing points
    glEnd();

    //Restore transformations
    glPopMatrix();

    // Flush drawing commands and swap
    glutSwapBuffers();
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
    GLfloat nRange = 100.0f;

    // Prevent a divide by zero
    if (height == 0)
    {
        height = 1;
    }

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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lines Example");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
