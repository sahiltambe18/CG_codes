#include <iostream>

#include <GL/glut.h>

#include <cmath>

#include <vector>



#define rad 0.017455556



using namespace std;



int count = 0;

char type;

vector<vector<float>> v(15,vector<float>(3));



void mul(vector<vector<float>> &a , vector<vector<float>> &b ,int c){

	

	vector<vector<float>> res(15 , vector<float>(3));

	

	for(int i = 0 ; i < c ; i++){

	   for(int j = 0 ; j < 3 ; j++){

	      res[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j];

	   }

	}

	

	///to ans

	for(int i = 0 ; i < c ; i++){

	   for(int j = 0 ; j < 3 ; j++){

	      a[i][j] = res[i][j];

	   }

	}

	

}



void draw(int c){

	glBegin(GL_LINE_LOOP);

	  glColor3f(1.0,0.0,0.0);

	  for(int i = 0 ; i < c ; i++){

	  	glVertex2f(v[i][0] , v[i][1]);

	  }

	glEnd();

	glFlush();

}



void draw2(int c){

	glBegin(GL_LINE_LOOP);

	  glColor3f(0.0,1.0,0.0);

	  for(int i = 0 ; i < c ; i++){

	  	glVertex2f(v[i][0] , v[i][1]);

	  }

	glEnd();

	glFlush();

}



void axes(){

	glPointSize(3.0);

	glBegin(GL_LINES);

  	 glVertex2f(-300,0);

	 glVertex2f(300,0);

	

	 glVertex2f(0,-300);

	 glVertex2f(0,300);

	glEnd();

	glFlush();

}





///////////////////////////////////////////////////



void rotation(int c){

	int theta;

	cout<<"enter rotation angle";

	cin>>theta;

	float nrad = (float)(theta * 0.017455556); 

	

	vector<vector<float>> rot = { { cos(nrad) , -sin(nrad) , 0 },

				       {sin(nrad) , cos(nrad) , 0},

				       { 0 , 0 , 1} };

	mul(v , rot , count);

	draw2(count);

	

}



void scalling(int c){

	float sx , sy;

	cout<<"enter scaling factors \n";

	cin>>sx>>sy;

	vector<vector<float>> sc = { {sx , 0 , 0},

				     {0 , sy , 0},

				     { v[0][0]*(1-sx) ,v[0][1]*(1-sy) , 1 } };

	mul(v , sc , c);

	draw2(count);

}



void reflectX(int c)

{

	vector<vector<float>> ref = {{1, 0, 0},

						   {0, -1, 0},

						   {0, 0, 1}};



	mul(v, ref , c);

	draw2(c);

}





void reflectY(int c)

{

	vector<vector<float>> ref = {{-1, 0, 0},

						   {0, 1, 0},

						   {0, 0, 1}};



	mul(v, ref , c);

	draw2(c);

}





/////////////////////////////////////////////////////////////////////



void myMouse(int button , int state , int mx , int my){

        mx = mx - 300;

	my =300 - my;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

		if(count <3){

		    v[count][0] = mx;

		    v[count][1] = my;

		    v[count++][2] = 1;

		    cout<<mx<<" "<<my<<endl;

		    

		    if(count == 3){

		    draw(count);

			cout<<type<<endl;

			if(type == 'o'){

			    rotation(count);

			    count = 0;

			}

			else if(type == 's'){

			    scalling(count);

			    count = 0;

			}

			else if(type == 'x'){

			    reflectX(count);

			    count = 0;

			}

			else if(type == 'y'){

			    reflectY(count);

			    count = 0;

			}

		    }

	         }

		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){

			count = 0;

		}

}



}



void keybord(unsigned char key , int x , int y){

	if(key == 's'){

		type = key;	

	}else if(key == 'r'){

		type = key;

	}else if(key == 'o'){

		type = key;

	}else if(key == 'x'){

		type = key;

	}else if(key == 'y'){

		type = key;

	}

}



void myInit(){

	glClearColor(1.0,1.0,1.0,0.0);

	gluOrtho2D(-300,300,-300,300);

}



int main(int argc ,char**argv)

{

    glutInit(&argc ,argv);

     glutInitWindowPosition(700,200);

     glutInitWindowSize(600,600);

     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

     glutCreateWindow("translation");



     glutDisplayFunc(axes);

     glutMouseFunc(myMouse);

     glutKeyboardFunc(keybord);

     myInit();

     glutMainLoop();

    return 0;



}
