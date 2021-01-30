#define  _CRT_SECURE_NO_WARNINGS
#include<GL/glut.h>
#include<stdio.h>
#include <vector>
#include <math.h>
#include<locale.h>
#include<windows.h>
#include<fstream>
#include<iostream>

using namespace std;

int x = 100, y = 100, z = 100;
float Wide = 800;
float Lent = 800;
//int xPers = -Wide + 20;
//int yPers = -Lent + 20;
bool down = false;
float Fi = 5;
void init(void);//Задание цвета
void Skeyboard(int key, int x, int y);
int Editional = 1;
ofstream Map;
float dx = 0, dy = 0;
int xMap = -Wide, yMap = -Lent;
//карта
int reb = 250;
float radAngel(float x1, float y1, float x2, float y2);
float Modul(float xCoord, float yCoord);
void playerMove(int key, int x, int y);
class Point
{
public:
	float xPoint;
	float yPoint;

private:

};

class Lines
{
private:
	int lCollor1;
	int lCollor2;
	int lCollor3;

public:
	float x1Line;
	float y1Line;
	float x2Line;
	float y2Line;
	float Angle = 0;
	bool crossing = false;
	float normalDistance = Wide;
	//////////////////////////////////
	void build_new_line(int x1,int y1,int x2,int y2);
	void Init(int x1, int y1, int x2, int y2);
	float line_lentch();
	void change_size(bool change);
	void rotation(bool vector);
	void build_line();
	
	Point Line_center();
};


void Lines::build_new_line(int x1, int y1, int x2, int y2)
{
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2d(x1, y1);
	glVertex2d(x2 , y2);
	glEnd();
}
void Lines :: Init(int x1, int y1, int x2, int y2)
{
	
	x1Line = x1;
	y1Line = y1;
	x2Line = x2;
	y2Line = y2;
}

float Lines::line_lentch()
{
	float xCoord = x2Line - x1Line;
	float yCoord = y2Line - y1Line;
	float Mod;
	Mod = powf((powf(xCoord, 2) + powf(yCoord, 2)), 0.5);
	return Mod;

}
void Lines :: change_size(bool change)
{
	Point Center;
	Center = this->Line_center();
	float Pril = x2Line-x1Line;
	float Protiv = y2Line - y1Line;
	float Gipot = this->line_lentch();
	float cos = Pril/Gipot;
	float sin = Protiv/Gipot;
	int size = 2;
	if (change)
	{
		x1Line = Center.xPoint - ((x2Line - x1Line) / 2 + size * cos);
		y1Line = Center.yPoint - ((y2Line - y1Line) / 2 + size * sin);
		x2Line = Center.xPoint + ((x2Line - x1Line) / 2 + size * cos);
		y2Line = Center.yPoint + ((y2Line - y1Line) / 2 + size * sin);
	}
	else
	{
		x1Line = Center.xPoint - ((x2Line - x1Line) / 2 - size * cos);
		y1Line = Center.yPoint - ((y2Line - y1Line) / 2 - size * sin);
		x2Line = Center.xPoint + ((x2Line - x1Line) / 2 - size * cos);
		y2Line = Center.yPoint + ((y2Line - y1Line) / 2 - size * sin);
	}
}

void Lines::rotation(bool vector)
{
	Point Center;
	
	Center = this->Line_center();
	float Pril = x2Line - x1Line;
	float Protiv = y2Line - y1Line;
	float Gipot = this->line_lentch();

	

	float angle = 3.1415 / 180 * 2;
	float r = Gipot / 2;
	if (vector)
	{
		x2Line = Center.xPoint + r * cosf(Angle + angle);
		y2Line = Center.yPoint + r * sinf(Angle + angle);
		x1Line = Center.xPoint - r * cosf(Angle + angle);
		y1Line = Center.yPoint - r * sinf(Angle + angle);
		Angle += angle;
	}
	else
	{
		x2Line = Center.xPoint - r * cosf(Angle - angle);
		y2Line = Center.yPoint - r * sinf(Angle - angle);
		x1Line = Center.xPoint + r * cosf(Angle - angle);
		y1Line = Center.yPoint + r * sinf(Angle - angle);
		Angle -= angle;
	}
	
}
void Lines::build_line()
{
	this->build_new_line(x1Line, y1Line, x2Line, y2Line);
}











Point Lines::Line_center()
{
	Point Center;
	Center.xPoint = (x2Line + x1Line)/2;
	Center.yPoint = (y2Line + y1Line)/2;
	return Center;
}
class User
{
public:
	int xPers = -100;
	int yPers = -100;
};




class Map
{

public:
	int rebFoundation;
	int xStart = -Wide;
	int yStart = - Lent;
	Lines Other[100];
	Lines Current_Line;
	int Num = 0;
	User client;
	
	void build_other_lines();
	void save_line(Lines line);
	void Enter();
	void Read();
	void PersonDisplay();
}MAIN_MAP;


void Map::save_line(Lines line)
{
	Other[Num] = line;
	Num++;
}

void Map::build_other_lines()
{
	
	for (int i = 0; i < Num; i++)
	{
		Other[i].build_new_line(Other[i].x1Line, Other[i].y1Line, Other[i].x2Line, Other[i].y2Line);
	}
}

void Map::Read()
{
	ifstream f("FILE.txt"); // открыли файл для чтения
	f >> Num;
	for (int i = 0; i < Num; i++)
	{

		f >> Other[i].x1Line;
		f >> Other[i].y1Line;
		f >> Other[i].x2Line;
		f >> Other[i].y2Line;
	}
	f.close(); // закрываем файл
}

void Map::Enter()
{
	ofstream fin("FILE.txt", ios_base::trunc); // открыли файл для записи
	fin << Num;
	fin << " ";
	for (int i = 0; i < Num; i++)
	{
		fin << Other[i].x1Line;
		fin << " ";
		fin << Other[i].y1Line;
		fin << " ";
		fin << Other[i].x2Line;
		fin << " ";
		fin << Other[i].y2Line;
		fin << " ";
	}
	fin.close(); // закрываем файл
}
void Map::PersonDisplay()
{


	///Карта в углу
	Point center;
	center.xPoint = -600;
	center.yPoint = -600;

	Lines buff[100];

	for (int i = 0; i < MAIN_MAP.Num; i++)
	{

		buff[i].x1Line = (MAIN_MAP.Other[i].x1Line / 4) + center.xPoint;
		buff[i].y1Line = (MAIN_MAP.Other[i].y1Line / 4) + center.yPoint;
		buff[i].x2Line = (MAIN_MAP.Other[i].x2Line / 4) + center.xPoint;
		buff[i].y2Line = (MAIN_MAP.Other[i].y2Line / 4) + center.yPoint;
	}

	for (int i = 0; i < MAIN_MAP.Num; i++)
	{
		buff[i].build_new_line(buff[i].x1Line, buff[i].y1Line, buff[i].x2Line, buff[i].y2Line);
	}

	//Точка на карте
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.4, 1.0);
	glVertex2d(client.xPers / 4 + center.xPoint, client.yPers / 4 + center.yPoint);
	glEnd();





	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	int r = 800;
	int rStrich = 500;
	float rFi = 3.1415 / 180 * Fi;





	float alpha = 3.1415 / 2;
	float Player_angle = alpha / 2;


	float step = 2 * Wide / (alpha / 0.01);
	for (float i = 0; i < alpha; i += 0.01)
	{

		float xProect = cosf(rFi - i) * r;
		float yProect = sinf(rFi - i) * r;





		Lines buff;
		float chek1;
		float chek2;
		float chek3;
		float chek4;
		bool result = false;



		for (int j = 0; j < Num; j++)
		{

			chek1 = radAngel(xProect, yProect, Other[j].x1Line - client.xPers, Other[j].y1Line - client.yPers);

			chek2 = radAngel(xProect, yProect, Other[j].x2Line - client.xPers, Other[j].y2Line - client.yPers);

			chek3 = radAngel(Other[j].x2Line - Other[j].x1Line, Other[j].y2Line - Other[j].y1Line, client.xPers - Other[j].x1Line, client.yPers - Other[j].y1Line);

			chek4 = radAngel(Other[j].x2Line - Other[j].x1Line, Other[j].y2Line - Other[j].y1Line, client.xPers + xProect - Other[j].x1Line, yProect + client.yPers - Other[j].y2Line);

			////////




			////////

			if ((chek1 * chek2) <= 0 && (chek3 * chek4) <= 0)
			{
				result = true;
				Other[j].crossing = true;
			}

		}




		if (result == false)
		{
			glVertex2d(client.xPers / 4 + center.xPoint, client.yPers / 4 + center.yPoint);
			glVertex2d((client.xPers + xProect) / 4 + center.xPoint, (client.yPers + yProect) / 4 + center.yPoint);
		}
		else
		{
			///////
			float chek21;
			float chek22;
			for (int j = 0; j < Num; j++)
			{
				chek21 = radAngel(xProect, yProect, Other[j].x1Line - client.xPers, Other[j].y1Line - client.yPers);

				chek22 = radAngel(xProect, yProect, Other[j].x2Line - client.xPers, Other[j].y2Line - client.yPers);

				float xPr = Other[j].x1Line + (Other[j].x2Line - Other[j].x1Line) * (fabs(chek21) / fabs(chek22 - chek21));
				float yPr = Other[j].y1Line + (Other[j].y2Line - Other[j].y1Line) * (fabs(chek21) / fabs(chek22 - chek21));

				Other[j].normalDistance = Modul(xPr - client.xPers, yPr - client.yPers);
			}

			float Max = Wide;
			for (int j = 0; j < Num; j++)
			{
				if (Other[j].crossing == true)
				{
					if (Other[j].normalDistance < Max)
					{
						buff = Other[j];
						Max = Other[j].normalDistance;

					}
					Other[j].crossing = false;
				}
			}
			/////////



			float Z1 = radAngel(xProect, yProect, buff.x1Line - client.xPers, buff.y1Line - client.yPers);
			float Z2 = radAngel(xProect, yProect, buff.x2Line - client.xPers, buff.y2Line - client.yPers);
			float xPr = buff.x1Line + (buff.x2Line - buff.x1Line) * (fabs(Z1) / fabs(Z2 - Z1));
			float yPr = buff.y1Line + (buff.y2Line - buff.y1Line) * (fabs(Z1) / fabs(Z2 - Z1));
			glVertex2d(client.xPers / 4 + center.xPoint, client.yPers / 4 + center.yPoint);
			glVertex2d(xPr / 4 + center.xPoint, yPr / 4 + center.xPoint);


			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(1.0, 1.0, 1.0);
			glLineWidth(1);

			glVertex2d(-Wide + step, Lent * 40 * (fabs(1 / (Modul(xPr - client.xPers, yPr - client.yPers))))/cos(Player_angle - i));
			glVertex2d(-Wide + step, -Lent * 40 * (fabs(1 / (Modul(xPr - client.xPers, yPr - client.yPers)))) / cos(Player_angle - i));

			step += 1.9 * Wide / (alpha / 0.01);
		}

	}




	glEnd();


}















float Player_Angle()
{
	float alpha = 3.1415 / 2;
	float ang = (alpha / 2) + (Fi * 3.1415) / 180;
	return ang;
};

void init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//цвет экрана
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-Wide, Wide, Lent, -Lent, 200, -200);
	glMatrixMode(GL_MODELVIEW);
	dx = cosf(Player_Angle() + 3.1415 / 2);
	dy = sinf(Player_Angle() + 3.1415 / 2);

}


/////////////////math
float radAngel(float x1, float y1, float x2, float y2)
{


	float sinAng = (x1 * y2) - (x2 * y1);
	return sinAng;


}
//модуль вектора
float Modul(float xCoord, float yCoord)
{
	float Mod;
	Mod = powf((powf(xCoord, 2) + powf(yCoord, 2)), 0.5);
	return Mod;
}

void reviewMap()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.1);
	MAIN_MAP.Current_Line.build_new_line(MAIN_MAP.Current_Line.x1Line, MAIN_MAP.Current_Line.y1Line, MAIN_MAP.Current_Line.x2Line, MAIN_MAP.Current_Line.y2Line);
	glColor3f(1.0, 1.0, 0.9);
	MAIN_MAP.PersonDisplay();


	glutSwapBuffers();
}
void MapDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0, 0.0, 0.1);
	MAIN_MAP.Current_Line.build_new_line(MAIN_MAP.Current_Line.x1Line, MAIN_MAP.Current_Line.y1Line, MAIN_MAP.Current_Line.x2Line, MAIN_MAP.Current_Line.y2Line);
	glColor3f(1.0, 1.0, 0.9);
	//MAIN_MAP.build_foundation(MAIN_MAP.xStart, MAIN_MAP.yStart, Wide);
	MAIN_MAP.build_other_lines();
	
	

	glutSwapBuffers();
}

void inAngleMapDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Point center;
	center.xPoint = -600;
	center.yPoint = -600;

	Lines buff[100];

	for (int i = 0; i < MAIN_MAP.Num; i++)
	{
		
		buff[i].x1Line = (MAIN_MAP.Other[i].x1Line / 4) + center.xPoint;
		buff[i].y1Line = (MAIN_MAP.Other[i].y1Line / 4) + center.yPoint;
		buff[i].x2Line = (MAIN_MAP.Other[i].x2Line / 4) + center.xPoint;
		buff[i].y2Line = (MAIN_MAP.Other[i].y2Line / 4) + center.yPoint;
	}
	
	for (int i = 0; i < MAIN_MAP.Num; i++)
	{
		buff[i].build_new_line(buff[i].x1Line, buff[i].y1Line, buff[i].x2Line, buff[i].y2Line);
	}
	glutSwapBuffers();

}


int index = 0;
void EditDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	
	
	
	
	for (int i = 0; i < MAIN_MAP.Num; i++)
	{
		if (i == index)
		{
			
			//MAIN_MAP.Current_Line = MAIN_MAP.Other[i];
			glColor3f(1.0, 0.0, 0.1);
			MAIN_MAP.Current_Line.build_line();
			
			/*printf("%f  ", MAIN_MAP.Current_Line.x1Line);
			printf("%f\n\n", MAIN_MAP.Current_Line.y1Line);*/
			
		}
		else
		{
			glColor3f(1.0, 1.0, 0.9);
			MAIN_MAP.Other[i].build_line();
		}
		
	}
	//MAIN_MAP.build_foundation(MAIN_MAP.xStart, MAIN_MAP.yStart, Wide);


	glutSwapBuffers();
}
void Change_Func(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 247: {
		//MAIN_MAP.save_line(MAIN_MAP.Current_Line);
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Other[i] = MAIN_MAP.Current_Line;
			}
		}
		index++;
		if (index == MAIN_MAP.Num)
		{
			index = 0;
		}
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Current_Line = MAIN_MAP.Other[i];

			}
		}
	}; break;
	case 241: {
		//MAIN_MAP.save_line(MAIN_MAP.Current_Line);
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Other[i] = MAIN_MAP.Current_Line;
			}
		}
		index--;
		if (index < 0)
		{
			index = MAIN_MAP.Num - 1;
		}
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Current_Line = MAIN_MAP.Other[i];

			}
		}
	}; break;
	case 255: {
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				for (int j = i; j < MAIN_MAP.Num - 1; j++)
				{
					MAIN_MAP.Other[j] = MAIN_MAP.Other[j + 1];
				}
				i = MAIN_MAP.Num;
			}
		}
		index--;
		if (index < 0)
		{
			index = MAIN_MAP.Num - 1;
		}


		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Current_Line = MAIN_MAP.Other[i];

			}
		}
	}; break;
	}
}
////////////////////////////////////////////////
void CreateMainMenu(int A)
{
	switch (A)
	{
	case 4: {glutDisplayFunc(reviewMap);
		glutSpecialFunc(playerMove);
		init();
	}; break;
	case 5: {
		glutDisplayFunc(inAngleMapDisplay);
	}; break;

	}
}
///////////////////////////////////////////
void editMenu(int A)
{
	switch (A)
	{
	case 1: {
		
		MAIN_MAP.Current_Line.Init(0, 0, 200, 0);
		glutDisplayFunc(MapDisplay);
		glutSpecialFunc(Skeyboard);
		init();
	}; break;
	case 2: {
		
		MAIN_MAP.save_line(MAIN_MAP.Current_Line);
		MAIN_MAP.Enter();
		MAIN_MAP.Current_Line.Init(0, 0, 200, 0); init(); }; break;
		
	case 3: { 
		
		for (int i = 0; i < MAIN_MAP.Num; i++)
		{
			if (i == index)
			{
				MAIN_MAP.Current_Line = MAIN_MAP.Other[i];
			}
		}
		glutDisplayFunc(EditDisplay);
		glutSpecialFunc(Skeyboard);
		glutKeyboardFunc(Change_Func);
		
		
		//init();
		
	}; break;
	}
	//Editional = a;
}

void MenuInit ()
{
	int mainMenu = glutCreateMenu(CreateMainMenu);
	Editional = glutCreateMenu(editMenu);
	glutSetMenu(Editional);
	glutAddMenuEntry("Add", 1);
	glutAddMenuEntry("Save", 2);
	glutAddMenuEntry("All", 3);
	glutSetMenu(mainMenu);
	glutAddMenuEntry("See your proect", 4);
	glutAddSubMenu("Edition", Editional);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
//Animation
void Timer(int)
{

	glutPostRedisplay();

	glutTimerFunc(50, Timer, 0);

}
void Skeyboard(int key, int x, int y)
{
	int spead = 10;
	int size = 2;
	switch (key)
	{
	case GLUT_KEY_LEFT: {MAIN_MAP.Current_Line.x1Line -= spead;MAIN_MAP.Current_Line.x2Line -= spead; }; break;;
	case GLUT_KEY_UP: {MAIN_MAP.Current_Line.y1Line -= spead; MAIN_MAP.Current_Line.y2Line -= spead; }; break;
	case GLUT_KEY_RIGHT: {MAIN_MAP.Current_Line.x1Line += spead; MAIN_MAP.Current_Line.x2Line += spead; }; break;
	case GLUT_KEY_DOWN: {MAIN_MAP.Current_Line.y1Line += spead; MAIN_MAP.Current_Line.y2Line += spead; }; break;
	case GLUT_KEY_F1: {MAIN_MAP.Current_Line.change_size(true); }; break;
	case GLUT_KEY_F2: {MAIN_MAP.Current_Line.change_size(false); }; break;
	case GLUT_KEY_F3: {MAIN_MAP.Current_Line.rotation(true); }; break;
	case GLUT_KEY_F4: {MAIN_MAP.Current_Line.rotation(false); }; break;
	}
	glutPostRedisplay();
}
void playerMove(int key, int x, int y)
{


	
	float chek21;
	Lines P[4];
	float delt = 1;
	//Left
	P[0].Init(MAIN_MAP.client.xPers, MAIN_MAP.client.yPers, MAIN_MAP.client.xPers - 20, MAIN_MAP.client.yPers);
	//Right
	P[1].Init( MAIN_MAP.client.xPers,MAIN_MAP.client.yPers,MAIN_MAP.client.xPers + 20,MAIN_MAP.client.yPers );
	//Up
	P[2].Init( MAIN_MAP.client.xPers,MAIN_MAP.client.yPers,MAIN_MAP.client.xPers,MAIN_MAP.client.yPers - 20 );
	//Down
	P[3].Init( MAIN_MAP.client.xPers,MAIN_MAP.client.yPers,MAIN_MAP.client.xPers,MAIN_MAP.client.yPers + 20 );
	for (int i = 0; i < 4; i++)
	{
		float chek1;
		float chek2;
		float chek3;
		float chek4;

		for (int j = 0; j < MAIN_MAP.Num; j++)
		{

			chek1 = radAngel(P[i].x2Line - P[i].x1Line, P[i].y2Line - P[i].y1Line, MAIN_MAP.Other[j].x1Line - P[i].x1Line, MAIN_MAP.Other[j].y1Line - P[i].y1Line);

			chek2 = radAngel(P[i].x2Line - P[i].x1Line, P[i].y2Line - P[i].y1Line, MAIN_MAP.Other[j].x2Line - P[i].x1Line, MAIN_MAP.Other[j].y2Line - P[i].y1Line);

			chek3 = radAngel(MAIN_MAP.Other[j].x2Line - MAIN_MAP.Other[j].x1Line, MAIN_MAP.Other[j].y2Line - MAIN_MAP.Other[j].y1Line, P[i].x1Line - MAIN_MAP.Other[j].x1Line, P[i].y1Line - MAIN_MAP.Other[j].y1Line);

			chek4 = radAngel(MAIN_MAP.Other[j].x2Line - MAIN_MAP.Other[j].x1Line, MAIN_MAP.Other[j].y2Line - MAIN_MAP.Other[j].y1Line, P[i].x2Line - MAIN_MAP.Other[j].x1Line, P[i].y2Line - MAIN_MAP.Other[j].y2Line);



			if ((chek1 * chek2) <= 0 && (chek3 * chek4) <= 0)
			{
				P[i].crossing = true;
			}

		}
	}


	int spead = 10;
	
	switch (key)
	{
	case GLUT_KEY_LEFT: {
		if (P[0].crossing == true) {

			MAIN_MAP.client.xPers -= 10;


			P[0].crossing = false;

		}
		else {
			MAIN_MAP.client.xPers += spead * cosf(Player_Angle());
			MAIN_MAP.client.yPers += spead * sinf(Player_Angle());
		}
	}; break;
	case GLUT_KEY_UP: { if (P[2].crossing == true) {

		MAIN_MAP.client.xPers += spead * dx;
		MAIN_MAP.client.yPers += spead * dy;
		P[1].crossing = false;
	}
					else
	{
		MAIN_MAP.client.xPers -= spead * dx;
		MAIN_MAP.client.yPers -= spead * dy;
	}
	}; break;
	case GLUT_KEY_RIGHT: { if (P[1].crossing == true) {

		P[2].crossing = false;
	}
					   else { 
		MAIN_MAP.client.xPers -= spead * cosf(Player_Angle()); 
		MAIN_MAP.client.yPers -= spead * sinf(Player_Angle());
	} }; break;
	case GLUT_KEY_DOWN: {if (P[3].crossing == true) {

		P[3].crossing = false;
	}
					  else {
		MAIN_MAP.client.xPers += spead * dx;
		MAIN_MAP.client.yPers += spead * dy;
	} }; break;
	case GLUT_KEY_F1: {Fi += 2; if (Player_Angle() > 3.1415*2) { Fi -= 360; }
					dx = cosf(Player_Angle() + 3.1415 / 2);
					dy = sinf(Player_Angle() + 3.1415 / 2);
	}; break;
	case GLUT_KEY_F2: {Fi -= 2; if (Player_Angle() < 0) { Fi += 360; } 
					dx = cosf(Player_Angle() + 3.1415 / 2);
					dy = sinf(Player_Angle() + 3.1415 / 2);
	}; break;
	
	}
}

void printHelp()
{

	FILE* ptr;
	ptr = fopen("Education.txt", "r+");
	
	
	//вывод содержимого построчно
	const int N = 100;
	fseek(ptr, 0, SEEK_SET);
	for (int i = 0; feof(ptr) == 0;)
	{

		char str[N];
		char* proverka;
		//если не был прочитан ни один символ fgets возвращает NULL 
		proverka = fgets(str, sizeof(str), ptr);
		if (proverka != NULL)
			printf("%s", str);
	}
	fclose(ptr);
}





int main(int argc, char* argv[])
{
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");

	
	
	printHelp();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); /*Включаем двойную буферизацию и четырехкомпонентный цвет*/
	glutInitWindowSize(Wide, Lent);
	glutCreateWindow("My COOL Project");

	//glViewport(0, 0, Wide, Lent);


	//Чтение координат стен из файла 
	MAIN_MAP.Read();
	MenuInit();
	
	



	glutTimerFunc(50, Timer, 0);
	glutMainLoop();



}