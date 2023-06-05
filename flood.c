#include<stdio.h>

#include<GL/glut.h>

#include <math.h>







int xpt[10];

int ypt[10];

int count = 0;

int v = 0;





struct Color{

   float r,g,b;

};



struct Color old ,neu;



void neuCol(){

    float R , G , B;

    printf("enter new color code : ");

    scanf("%f %f %f",&R ,&G ,&B);

    neu.r = R;

    neu.g = G;

    neu.b = B;

}



// draw polygon

void draw(){

    glBegin(GL_LINE_LOOP);

    glColor3f(1.0,0.0,0.0);

    for (int i = 0; i < count;i++){

        glVertex2f(xpt[i],ypt[i]);

    }

    glEnd();

    glFlush();

}







///////////////////////////////////////////////////////////////////////////





void floodfill(int x , int y , struct Color nc , struct Color oc){

      

      struct Color curr ;

      glReadPixels(x , y , 1 , 1 , GL_RGB , GL_FLOAT , &curr);

      

      if( curr.r==nc.r && curr.g== nc.g && curr.b==nc.b ){

           return;

      }

      if( curr.r==oc.r && curr.g== oc.g && curr.b==oc.b ){

           glBegin(GL_POINTS);

            glColor3f(nc.r,nc.g,nc.b);

             glVertex2f(x,y);

           glEnd();

           glFlush();

           

           floodfill(x+1 ,y , nc ,oc);

           floodfill(x ,y-1 , nc ,oc);

           floodfill(x-1 ,y , nc ,oc);

           floodfill(x ,y+1 , nc ,oc);

      }

      return;

} 



void mouse(int button ,int state , int mx , int my){

      my = 600- my;

      if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

           if(count < v){

              xpt[count] = mx;

              ypt[count++] = my;

              if(count>=v){

                 draw();

              }

           }else{

              

              neuCol();

              glReadPixels(mx,my,1,1,GL_RGB,GL_FLOAT,&old);

              floodfill(mx , my ,neu ,old);

              count = 0;

           }

      }



}





void myInit(){

     glClearColor(1.0,1.0,1.0,0);

     glColor3f(0.0,0.0,0.0);

     gluOrtho2D(0, 600 , 0 , 600);

}



int main(int argc , char**argv){



    printf("enter no of vertices : ");

    scanf("%d",&v);

     

     glutInit(&argc,argv);

     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

     glutInitWindowSize(600,600);

     glutInitWindowPosition(600,200);

     glutCreateWindow("flood fill");

     

     myInit();

   //  glutDisplayFunc(draw);

     glutMouseFunc(mouse);

     glutMainLoop();

     return 0;     

}
