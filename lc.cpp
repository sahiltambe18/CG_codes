#include<iostream>
#include<GL/glut.h>

using namespace std;


#define inside 0
#define left 1
#define right 2
#define bottom 4
#define top 8

int xmin , ymin , xmax , ymax;
int x1 , y1 , x2 ,y2 ;
bool fpt = true;


int invertY(int y){
	return 600 -y;
}



//window
void draw(){
	
   glBegin(GL_LINE_LOOP);
	glColor3f(1.0,0.0,0.0);
   	glPointSize(3);
     	glVertex2i(xmin,ymin);
	glVertex2i(xmin,ymax);
	glVertex2i(xmax,ymax);
	glVertex2i(xmax,ymin);
   glEnd();
	glFlush();
}

//find region
int computeCode(int x ,int y){
      int code = inside;
	
	if(x < xmin){
	   code |= left;
	}
	if(x > xmax){
	   code |= right;
	}
	if(y < ymin){
	   code |= bottom;
	}
	if(y> ymax){
	   code |= top;
	}
       return code;
}


/////////////////////////////////////////////////////////////////////


void drawline(int X1 ,int Y1 ,int X2 ,int Y2){
	glBegin(GL_LINES);
	  glColor3f(0.0,1.0,0.0);
	  glVertex2i(X1,Y1);
	  glVertex2i(X2,Y2);
	glEnd();
        glFlush();
}

void drawline2(int X1 ,int Y1 ,int X2 ,int Y2){
	glBegin(GL_LINES);
	  glColor3f(0.0,0.0,1.0);
	  glVertex2i(X1,Y1);
	  glVertex2i(X2,Y2);
	glEnd();
        glFlush();
}

void lineClip(int X1 ,int Y1 ,int X2 ,int Y2){
        int code1 = computeCode(X1 , Y1);
	int code2 = computeCode(X2 , Y2);
	
       while(true){
       if((code1 == 0) && (code2 == 0)){
	   cout<<"both points inside of window \n";
           break ;
           
	}else if((code1 != 0) && (code1==code2)){
	     cout<<"both points outside of window and same region \n";
	     //glClear(GL_COLOR_BUFFER_BIT);
	     x1 = 0;
	     x2 = 0;
	     y1 = 0;
	     y2 = 0;
	     return;
	}
	else{
             int resCode,xp ,yp ;
               if(code1 != 0){
                      resCode = code1;
	       }else{
		   resCode = code2;
	       }
///-------------------------------------------------------------------	   
	if(resCode & top){
              // in top region
              yp = ymax;
              if(resCode & left){//top left
                  xp = xmin;
              }else if(resCode & right){// top right
                xp = xmax;
             }else{
               xp =  X1 + (X2 - X1) * (ymax -Y1)/(Y2 - Y1);
            }
          }
///-------------------------------------------------------------------
 	if(resCode & bottom){
              // in bottom region
              yp = ymin;
              if(resCode & left){//bottom left
                  xp = xmin;
              }else if(resCode & right){// bottom right
                xp = xmax;
             }else{
               xp =  X1 + (X2 - X1) * (ymin -Y1)/(Y2 - Y1);
            }
          }
///-------------------------------------------------------------------

   	if(resCode & left){
	    //left rigion
            xp = xmin;
	    if(resCode & top){//top left
                  yp = xmax;
              }else if(resCode & bottom){// bottom left
                yp = xmin;
             }else{
               yp = Y1 + (Y2 -Y1) * (xmin - X1) /(X2 -X1);
            }
	}
///-------------------------------------------------------------------

   	if(resCode & right){
	    //right rigion
            xp = xmax;
	    if(resCode & top){//top right
                  yp = xmax;
              }else if(resCode & bottom){// bottom right
                yp = xmin;
             }else{
               yp = Y1 + (Y2 -Y1) * (xmax - X1) /(X2 -X1);
            }
	}
//--------------------------------------------------------------------------

  cout<<xp<<" "<<yp<<endl;
     if(resCode == code1){

	x1 = xp;
	y1 = yp;
        code1 = computeCode(x1,y1);
	}else{
	  x2 = xp;
          y2 = yp;
        code2 = computeCode(x2,y2);
	}

     }
   }
  glColor3f(0.0,0.0,1.0);
  drawline2(x1,y1,x2,y2);

}

void mymouse(int button , int state ,int mx ,int my){
 	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
	
	if(fpt){
			x1 = mx;
			y1 = invertY(my);
			fpt = false;	
	}else{
		x2 = mx;
		y2 = invertY(my);
   	   drawline(x1 , y1 ,mx , invertY(my));
	  lineClip(x1 ,y1 ,x2 ,y2);
	   fpt = true;
	     }
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0,0.0,0.0,0.0);
		draw();
		drawline2(x1,y1,x2,y2);
		 
	}
}



int main(int argc, char ** argv)
{
       
    cout<<"Enter the xmin and ymin of the window: ";
    cin>>xmin>>ymin;
    cout<<"Enter the xmax and ymax of the window: ";
    cin>>xmax>>ymax;
    


     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     glutInitWindowSize(600,600);
     glutInitWindowPosition(200,100);
     glutCreateWindow("Line clipping");
     
     glClear(GL_COLOR_BUFFER_BIT);
     glClearColor(0.0,0.0,0.0,0.0);
     gluOrtho2D(0,600,0,600);


     glutDisplayFunc(draw);
     glutMouseFunc(mymouse);
         
     glutMainLoop();
    return 0;

    
}
