#include "SoundUtil.h"
#include <GL/freeglut.h>
#include "ofbx.h"

void initializeWindow(int argc, char** argv);
void display();
void keyboard(unsigned char key, int x, int y);
void reshape (int w, int h);

int main(int argc, char** argv) {
    bool running = true;

    initializeWindow(argc, argv);
    // initializeSound();
    // initializeBackgroundMusic();

    do {
        
    } while(running);

    return 0;
}

void initializeWindow(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

   glutInitWindowSize (1280, 600); 
//    glutFullScreen();
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);

   glutMainLoop();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

void display() {
   const ofbx::Object* castle = scene.getRoot();

}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}