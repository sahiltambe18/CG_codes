#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include <stdbool.h>
#include <math.h>

#define SIN sin(1.047619048)
#define COS cos(1.047619048)

bool fristClick = true;
int x ,y ,itr;

int invertY(int y){
    return 600-y;
}

int nofitr(){
   printf("enter no of iterations \n");
   scanf("%d" , &itr);
   return itr;
}

void line(int x1 , int y1 , int x2 , int y2){
      glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
      glEnd();
      glFlush();
}

void koch(int x1 , int y1 , int x2 , int y2 , int n){
       float xc , yc , xd ,yd , xh , yh;
       
       xc = (float)(2*x1 + x2)/3.0;
       yc = (float)(2*y1 + y2)/3.0;
       xd = (float)(2*x2 + x1)/3.0;
       yd = (float)(2*y2 + y1)/3.0;
       
       xh = xc - ((xd-xc)*COS) + ((yd-yc)*SIN);
       yh = yc + ((xd-xc)*SIN) + ((yd-yc)*COS);
       
       if(n >0){
           koch(x1 , y1 , xc , yc , n-1);
           koch(xc , yc ,xh , yh , n-1);
           koch(xh , yh , xd , yd , n-1);
           koch(xd , yd , x2 , y2 , n-1);
       }
       else{
          
             glVertex2f(x1 , y1);
             glVertex2f(xc , yc);
             
             glVertex2f(xc , yc);
             glVertex2f(xh , yh);
             
             glVertex2f(xh , yh);
             glVertex2f(xd , yd);
             
             glVertex2f(xd , yd);
             glVertex2f(x2 , y2);
          
       }
       
}

void myMouse(int button , int state , int mx , int my){
       
       if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
             if(fristClick){
                  x = mx;
                  y = invertY(my);
                  fristClick = false;         
             }else{
                  itr = nofitr();
                 
                 glBegin(GL_LINES);
	            koch(x , y , mx , invertY(my) , itr);
	         glEnd();
	         glFlush();
                  fristClick = true;
             }
       }

}

void myInit(){
    
    glClearColor(0.0,0.0,0.0,0.0);
   glColor3f(1.0,1.0,1.0);
   gluOrtho2D(0,600,0,600);
}

int main(int argc ,char**argv){
    
    
    glutInit(&argc ,argv);
     glutInitWindowPosition(700,200);
     glutInitWindowSize(600,600);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutCreateWindow("KOCH");
     
     glutMouseFunc(myMouse);
     myInit();
     glutMainLoop();

  return 0;
}
