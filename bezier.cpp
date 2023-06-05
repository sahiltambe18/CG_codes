#include <iostream>

#include <GL/glut.h>

#include <math.h>

using namespace std;



int xpt[10];

int ypt[10];

int count = 0;



void bez(){

	float dx ,dy;

	glBegin(GL_POINTS);

	glColor3f(1.0,0.0,0.0);

	for(float i = 0 ; i <= 1 ; i+=0.001){

	   dx = (float)( pow(1-i,3)*xpt[0] + 3*pow(1-i,2)*i*xpt[1] + 3*(1-i)*pow(i,2)*xpt[2] + 3*pow(i,3)*xpt[3] );

	   dy = (float)( pow(1-i,3)*ypt[0] + 3*pow(1-i,2)*i*ypt[1] + 3*(1-i)*pow(i,2)*ypt[2] + 3*pow(i,3)*ypt[3] );

	   glVertex2f(dx,dy);

	}

	glEnd();

	glFlush();

}



void myMouse(int button , int state , int mx , int my){

	my = 600 - my;

	cout<<"enter "<<count<<endl;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

	    if(count<4){

	         xpt[count] = mx;

	         ypt[count++] = my;

	    }else{

		bez();

		count = 0;

	    }

	}

}





int main(int argc,char** argv){



	

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_SINGLE||GLUT_RGB);

	glutInitWindowSize(600,600);

	glutInitWindowPosition(700,200);

	glutCreateWindow("bezier");

	

	glClearColor(1.0,1.0,1.0,1.0);

	glColor3f(1.0,0.0,0.0);

	gluOrtho2D(0,1400,0,900);

	

	glutMouseFunc(myMouse);

	glutMainLoop();

	return 0;

}
