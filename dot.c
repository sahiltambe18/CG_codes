#include<stdio.h>
#include<GL/glut.h>

int x,y;

void putPixel(float x ,float y){
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
       glVertex2i(x,y);
    glEnd();
    glFlush();
}

void dda(int x1 ,int y1 , int x2 ,int y2){
      int dx , dy ,steps ;
      float xi , yi ,xp,yp;
      
      dx = x2 -x1;
      dy = y2-y1;
      
      if(abs(dx) > abs(dy)){
          steps = abs(dx);
      }else{
         steps = abs(dy);
      }
      
      xi = dx /(float) steps;
      yi = dy /(float) steps;
      putPixel(x1,y1);
      xp =x1;
      yp = y1;
      for(int i = 0; i < steps ;i++){
          xp = xp +xi;
          yp = yp + yi;
          putPixel(xp,yp);
      }      
      glFlush();
}

void myMouse(int button , int state , int mx , int my){

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
             printf("x: %d ,y: %d",mx , my);
             x = mx;
             y = 600-my;
        }
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
             printf("x: %d ,y: %d",mx , my);
             
                dda(x ,y, mx, 600-my );
                
        }

}

void myInit(){
   glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(1.0,1.0,1.0);
   gluOrtho2D(0,600,0,600);
}

int main(int argc , char**argv){
     
     glutInit(&argc ,argv);
     glutInitWindowPosition(700,200);
     glutInitWindowSize(600,600);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutCreateWindow("dott");
     
     glutMouseFunc(myMouse);
     myInit();
     glutMainLoop();
     
     return 0;

}
