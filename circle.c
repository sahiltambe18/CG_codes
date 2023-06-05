//SAHIL TAMBE SIB58
#include<stdio.h>
#include<math.h>
#include <stdbool.h>
#include <GL/glut.h>


int x  ,y ;
bool fpt = true;


void draw(){
       
       glBegin(GL_LINES);
          glColor3f(0.0,1.0,0.0);
          glVertex2f(-300.0,0.0);
          glVertex2f(300.0,0.0);
          
          glVertex2f(0.0,-300.0);
          glVertex2f(0.0,300.0);
       glEnd();
       glFlush();
}

int invertX(int X){
    return (x -300);
}

int invertY(int Y){
    return (300-Y);
}

void drawPoint(int X , int Y){
      glBegin(GL_POINTS);
         glColor3f(1.0,0.0,0.0);
         glPointSize(3);
         glVertex2f(X,Y);
      glEnd();
      glFlush();
}

////////////////////////////////////////////////////////


void allQuads(int x0 , int y0 , int xc , int yc ){
        
        //Q1
        drawPoint(x0+xc , y0+yc);
        drawPoint(y0+xc , x0+yc);
        //Q2
        drawPoint(-x0+xc , y0+yc);
        drawPoint(-y0+xc , x0+yc);
        //Q3
        drawPoint(-x0+xc , -y0+yc);
        drawPoint(-y0+xc , -x0+yc);
        //Q4
        drawPoint(x0+xc , -y0+yc);
        drawPoint(y0+xc , -x0+yc);
        
}


void drawCircle(int x1 ,int y1 , int x2 , int y2){
    int p , x0 ,y0;
    int r = sqrt( abs( pow(x1-x2,2) + pow(y2-y1,2) ) );
    x0 = 0;
    y0 = r;
    
    p = 3-2*r;
    
    while(y0>=x0){
       if(p < 0){
          x0++;
          p+= 4 * x0 + 6;
       }else{
          x0++;
          y0--;
          p+= 4*(x0-y0) + 10;
       }
       allQuads(x0,y0,x1,y1);
    }
    
}



/*void drawCircle(int x1 , int y1 ,int x2 ,int y2){
        
        int x0 , y0 , p;
        
        int radius = sqrt( pow( abs(x2-x1),2 ) + pow( abs(y2-y1),2 ) );
        
        x0 = 0;
        y0 = radius;
//        printf("%f \n",radius);
        
        p = 3 - 2*radius;
        
        while(x0<=y0){
           if(p<0){
              x++;
              p+= 4 * x0 + 6;
           }else{
              x0++;
              y0--;
              p+= 4*(x0-y0) + 10;  
           }
           
           //printf("%d , %d , %d \n",x0 , y0 , p);
           
           allQuads(x0 ,y0 , x1 , y1);
           
        }
}*/


void myMouse(int button ,int state , int mx , int my){
	mx = mx - 300;
	my = 300 - my ;

        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
             if(fpt){
                x = mx;
                y = my;
                fpt = false;
                printf("%d , %d  \n",x , y);
             }else{
                 drawCircle(x,y,mx,my);
                 printf("%d , %d  \n",mx , my);
                 fpt = true;
             }
        }

}

void init(){
	glClearColor(1.0,1.0,1.0,0);
     glColor3f(0.0,0.0,0.0);
     gluOrtho2D(-300, 300 , -300 , 300);
     glFlush();
}


int main(int argc,char ** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(700,100);
	glutCreateWindow("circle");


	glutDisplayFunc(draw);
	glutMouseFunc(myMouse);
	init();
	glutMainLoop();	
return 0;
}
