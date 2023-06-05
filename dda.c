#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<GL/glut.h>
#include<math.h>


bool fpt = true;
float X , Y;

////////////////////////////////////////////////////////////////////////
int invertX(int x){
    return (x-300);
}
int invertY(int y){
    return (300-y);
}

//////////////////////////////////////////////////////////////////////////////////////

void ddaline(float x1 , float y1 , float x2 , float y2 ,int type){
      float dx ,dy,xi,yi,x,y;
      int steps;
      printf("x1: %f y1: %f x2: %f , y2: %f \n",x1,y1,x2,y2);
      dx = x2-x1;
      dy = y2-y1;
      
      if(abs(dx)> abs(dy)){
           steps = (int)(abs(dx));
      }else{
           steps = (int)(abs(dy));
      }
      
      xi = dx/ (float)(steps);
      yi = dy/ (float)(steps);
      
      x = x1;
      y = y1;
      
      glColor3f(0.0,1.0,0.0);
      glBegin(GL_POINTS);
        glVertex2f(x,y);
      for(int i = 0 ; i< steps ; i++){
          
          x = x+ xi;
          y = y+ yi;
          
          if(type == 1){
             
             glVertex2f(x,y);
          }else if(type == 2 && (i%2==0)){
             
             glVertex2f(x,y);
          }else if (type == 3 && (i%4!=0)){
               glVertex2f(x,y);
          }else if (type == 4 ){
               glPointSize(3.0);
               glVertex2f(x,y);
          }
      }
      glEnd();
      glFlush();
      
}

void myMouse(int button ,int state , int mx , int my){
    
    if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN){
         if(fpt){
            X = invertX(mx);
            Y = invertY(my);
            fpt = false;
         }else{
        printf("x1: %f y1: %f x2: %d , y2: %d \n",X,Y,invertX(mx),invertY(my));
            ddaline(X,Y ,invertX(mx),invertY(my) ,3);
            fpt = true;
         }
    }
    
}

void myInit(){
   glClearColor(1.0,1.0,1.0,0.0);
   gluOrtho2D(-300,300,-300,300);
}

int main(int argc ,char**argv){
       
       glutInit(&argc,argv);
       glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
       glutInitWindowPosition(700,200);
       glutInitWindowSize(600,600);
       glutCreateWindow("dda line");
       
       glutMouseFunc(myMouse);
       myInit();
       glutMainLoop();
       
       
   return 0;
}
