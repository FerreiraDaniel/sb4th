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
    GLfloat y;  //Storage for verying y coordinate
    GLint factor = 1;   // Stippling factor
    GLushort pattern = 0x55555;


    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    //Save matrix stat and do the rotation
    glPushMatrix();
    

    // Enable Stippling
    glEnable(GL_LINE_STIPPLE);

        // Step up Y axis 20 units at a time
        for(y = -90.0f; y < 90.0f; y += 20.0f )
        {
            //Reset the repeat factor and pattern
            glLineStipple(factor, pattern);

            glBegin(GL_LINES);
                glVertex2f(-80.0f, y);
                glVertex2f(80.0f, y);
            glEnd();
            factor++;
        }
    glDisable(GL_LINE_STIPPLE);

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
    glutCreateWindow("Line Stippled Example");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();

    glutMainLoop();

    return 0;
}
