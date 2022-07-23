#define GL_SILENCE_DEPRECATION

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>
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
    GLfloat sizes[2];       // Store supported point size range
    GLfloat step;           // Store supported point size increments
    GLfloat currentSize;        // Store current point size



    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    //Save matrix stat and do the rotation
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    


    // Get supported point size range and step size
    glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);

    // Set the initial point size
    currentSize = sizes[0];

    // Set beggining z coordinate
    z = -50.0f;

    // Loop around in a circle three times
    for(angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f) {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

        // Specify the point size before the primitive is specified
        glPointSize(currentSize);
        
        glBegin(GL_POINTS);
            glVertex3f(x, y, z);
        glEnd();
        // Bump up the z value and the point size
        z += 0.5f;
        currentSize += (step * 1000);
    }


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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Points Size Example");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
