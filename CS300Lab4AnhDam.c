// Anh Dam - Lab 4

#include <stdlib.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

//global variables
GLuint teapotL;
GLfloat lightpx = 0.0;
GLfloat lightpy = 2.0;
GLfloat angle1 = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
int moving, startx, starty = 0;

GLfloat light_position[] = {1.0, 1.0, 2.0, 1.0};

void init(void)
/*
 Initializes OpenGL
 */
{
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glLoadIdentity();
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    teapotL = glGenLists(1);
    glNewList (teapotL, GL_COMPILE);
    glutSolidTeapot(1.0);
    glEndList();
}

void drawTeapot(GLfloat x, GLfloat y, GLfloat emr, GLfloat emg, GLfloat emb,
                GLfloat ambr, GLfloat ambg, GLfloat ambb,
                GLfloat difr, GLfloat difg, GLfloat difb,
                GLfloat specr, GLfloat specg, GLfloat specb,
                GLfloat shine)
/*
 Render a list of teapots
 */
{
    GLfloat mat[3];
    
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle1, 0.0, 1.0, 0.0);
    // emission
    mat[0] = emr;
    mat[1] = emg;
    mat[2] = emb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat);
    
    // ambient
    mat[0] = ambr;
    mat[1] = ambg;
    mat[2] = ambb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat);
    
    // diffuse
    mat[0] = difr;
    mat[1] = difg;
    mat[2] = difb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat);
    
    // specular
    mat[0] = specr;
    mat[1] = specg;
    mat[2] = specb;
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat);
    
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine * 128.0);
    glCallList(teapotL);
    glPopMatrix();
}

void display(void)
/*
 Display the lighting models
 */
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    light_position[0] = lightpx;
    light_position[1] = lightpy;
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPushMatrix();
    
    // First row - emissive reflection
    glPushMatrix();
    drawTeapot(2.0, 17.0,  0.135, 0.2225, 0.1575,        // jade
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(6.0, 17.0, 0.25, 0.20725, 0.20725,       // pearl
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(10.0, 17.0, 0.1745, 0.01175, 0.01175,      // ruby
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(14.0, 17.0, 0.1, 0.18725, 0.1745,     // turquoise
               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    glPopMatrix();

    // Second row - ambient reflection
    glPushMatrix();

    drawTeapot(2.0, 12.0, 0.0215, 0.1745, 0.0215, 0.7, 0.7, 0.7,    // emerald
               0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0);
    drawTeapot(6.0, 12.0, 0.2125, 0.1275, 0.054, 0.7, 0.7, 0.7,      // bronze
               0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0);
    drawTeapot(10.0, 12.0, 0.24725, 0.1995, 0.0745, 0.7, 0.7, 0.7,       // gold
               0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0);
    drawTeapot(14.0, 12.0, 0.329412, 0.223529, 0.027451, 0.7, 0.7, 0.7, // brass
               0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 1.0);
    
    glPopMatrix();
    
    //Third row rubber - ambient, and diffuse reflection
    glPushMatrix();
    drawTeapot(2.0, 7.0, 0.0, 0.0, 0.0, 0.0, 0.05, 0.05,      // cyan
               0.4, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(6.0, 7.0, 0.0, 0.0, 0.0, 0.05, 0.0, 0.0,       // red
               0.5, 0.4, 0.4, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(10.0, 7.0, 0.0, 0.0, 0.0, 0.05, 0.05, 0.05,   // white
               0.5, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0);
    drawTeapot(14.0, 7.0, 0.0, 0.0, 0.0, 0.05, 0.05, 0.0,     // yellow
               0.5, 0.5, 0.4, 0.0, 0.0, 0.0, 0.0);
    glPopMatrix();
    
    //Fourth row plastic - ambient, diffuse, specular reflection
    glPushMatrix();
    drawTeapot(2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.06,       // cyan
               0.0, 0.509804, 0.509804, 0.501961, 0.501961, 0.501961, 0.25);
    drawTeapot(6.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,        // red
               0.5, 0.0, 0.0, 0.7, 0.6, 0.6, 0.5);
    drawTeapot(10.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,       // white
               0.55, 0.55, 0.55, 0.70, 0.70, 0.70, 0.75);
    drawTeapot(14.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,       // yellow
               0.5, 0.5, 0.0, 0.60, 0.60, 0.50, 1.0);
    glPopMatrix();
    
    glPopMatrix();
    glFlush();
}

void reshape(int w, int h)
/*
 GLUT calls this routine when the window is resized
 */
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w,
                -10.0, 10.0);
    else
        glOrtho(0.0, 16.0*(GLfloat)w/(GLfloat)h, 0.0, 16.0,
                -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

static void motion(int x, int y)
/*
 Rotate the object with mouse
 */
{
    if (moving) {
        angle1 = (angle1 + (x - startx));
        angle2 = (angle2 + (y - starty));
        lightpx = (lightpx + (x - startx));
        lightpy = (lightpy + (y - starty));
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}


void mouse(int button, int state, int x, int y)
/*
 GLUT calls this when mouse is clicked
 */
{
    /* Rotate the scene with the left mouse button. */
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

void keyboard(GLubyte key, GLint x, GLint y)
/*
 GLUT calls this routine when a key is pressed
 */
{
    switch(key) {
        case 'q':
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
/*
 Executes the main() function to display window.
 */
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 600);
    glutInitWindowPosition(500,600);
    glutCreateWindow("Lab 4");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
