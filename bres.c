#include<stdio.h>
#include<stdbool.h>
#include <GL/glut.h>


bool fpt = true;
int x , y;




////////////////////////////////

void gline(int x1 , int y1 , int x2 , int y2){
	int dx = abs(x2 - x1);
	int dy = abs(y2 -y1);
	
	int DX , DY;
	DX = (x2 > x1) ? 1 : -1;
	DY = (y2 > y1 ) ? 1 : -1;
	
	int p = (2*dy) - dx ;
	int x0 = x1;
	int y0 = y1;
	
	for(int i = 0 ; i < dx ; i++){
		if(p<0){
			x0 += DX;
			p += 2*dy;
		}else{
			x0+=DX;
			y0+= DY;
			p+= 2*(dy - dx);
		}
		glBegin(GL_POINTS);
		  glColor3f(1.0,0.0,0.0);
		  glVertex2f(x0 , y0);
		glEnd();
		glFlush();
	}
	
}

void hline(int x1 , int y1 , int x2 , int y2){
	int dx = abs(x2 - x1);
	int dy = abs(y2 -y1);
	
	int DX , DY;
	DX = (x2 > x1) ? 1 : -1;
	DY = (y2 > y1 ) ? 1 : -1;
	
	int p = (2 * dx) - dy;
	int x0 = x1;
	int y0 = y1;
	
	for(int i = 0 ; i < dy ; i++){
		if(p<0){
			y0 += DY;
			p += 2*dx;
		}else{
			y0+= DY;
			x0+=DX;
			p+= 2* (dx-dy);
		}
		glBegin(GL_POINTS);
		  glColor3f(1.0,0.0,0.0);
		  glVertex2f(x0 , y0);
		glEnd();
		glFlush();
	}
	
}

void bres(int x1 , int y1 , int x2 , int y2){
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	
	dx > dy ? gline(x1 , y1 , x2 , y2) : hline(x1 , y1 , x2 ,y2) ;
	
}

void draw(){
	bres(-300,0,300,0);
	bres(0,300,0,-300);
	glFlush();
}

void mouse(int button , int state , int mx , int my){
	mx = mx - 300;
	my = 300 - my;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if(fpt){
			x = mx;
			y = my;
			fpt = false;
			printf("%d %d \n",mx,my);
		}else{
			printf("%d %d \n",mx,my);
			bres(x ,y , mx , my);
			fpt = true;
		}
	}
}



void init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
      	gluOrtho2D(-300,300,-300,300);
}


int main(int argc,char ** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("bresenham");
	init();
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();	
return 0;
}
