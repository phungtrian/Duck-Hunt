#include "graphics.h"
#pragma comment(lib, "graphics.lib")
#include <iostream>
#include <string>

using namespace std;

#define Round(a) (int)(a + 0.5) // lam trong so
#define Max(a, b) a > b ? a : b // tra ve gia tri lon nhat gia 2 so

void rules_interface();
int drawBtExit();
struct Point
{
	int x, y;
};

Point viTri[5]; //vịt và virus
Point viendan[4];
int to = 30;//độ to của vịt
int bullet = 3; //số đạn
int score = 0;
int dis_score = 0; // khoảng cách trắng cách ở điểm số

void lineDDA(int x1, int y1, int x2, int y2, int color)
{
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc, y_inc;
	float step = Max(abs(Dx), abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	float x = x1, y = y1;// Khoi tao cac gia tri ban dau
	putpixel(x, y, color);
	int k = 1;
	while (k <= step) {

		x += x_inc;
		y += y_inc;

		putpixel(Round(x), Round(y), color);
		k++;
	}
}
void ScanLine(Point p[], int v, int color)
{
	int xmin, xmax, ymin, ymax, c, mang[500];
	xmin = xmax = p[0].x;
	ymin = ymax = p[0].y;
	for (int i = 0; i < v; i++) {
		if (xmin > p[i].x) xmin = p[i].x;
		if (xmax < p[i].x) xmax = p[i].x; if (ymin > p[i].y) ymin = p[i].y;
		if (ymax < p[i].y) ymax = p[i].y;
	}
	float y;
	y = ymin + 0.000001;
	while (y <= ymax) {
		int x, x1, x2, y1, y2, tg;
		c = 0;
		for (int i = 0; i < v; i++) {

			x1 = p[i].x;
			y1 = p[i].y;
			x2 = p[i + 1].x;
			y2 = p[i + 1].y;
			if (y2 < y1) {
				tg = x1; x1 = x2; x2 = tg;
				tg = y1; y1 = y2; y2 = tg;
			}

			if (y <= y2 && y >= y1) {
				if (y1 == y2)  x = x1;
				else {
					x = ((y - y1) * (x2 - x1)) / (y2 - y1);
					x += x1;
				}
				if (x <= xmax && x >= xmin)
					mang[c++] = x;
			}
		}
		setcolor(color);
		for (int i = 0; i < c; i += 2) {

			line(mang[i], y, mang[i + 1], y);
		}
		y++;
	}
}
void boundaryFill(int x, int y, int f_color, int b_color)
{
	if (getpixel(x, y) != f_color && getpixel(x, y) != b_color)
	{
		putpixel(x, y, f_color);
		boundaryFill(x + 1, y, f_color, b_color);
		boundaryFill(x, y + 1, f_color, b_color);
		boundaryFill(x - 1, y, f_color, b_color);
		boundaryFill(x, y - 1, f_color, b_color);
		/*boundaryFill(x-1, y - 1, f_color, b_color);
		boundaryFill(x - 1, y + 1, f_color, b_color);
		boundaryFill(x + 1, y-1, f_color, b_color);
		boundaryFill(x + 1, y + 1, f_color, b_color);*/
	}
}
void drawCircle_Bre(int xc, int yc, int radius, int color)
{
	int x1 = 0, y1 = radius;
	int p = 3 - 2 * radius;

	putpixel(xc + x1, yc + y1, color);
	putpixel(xc - x1, yc + y1, color);
	putpixel(xc + x1, yc - y1, color);
	putpixel(xc - x1, yc - y1, color);
	putpixel(xc + y1, yc + x1, color);
	putpixel(xc - y1, yc + x1, color);
	putpixel(xc + y1, yc - x1, color);
	putpixel(xc - y1, yc - x1, color);

	while (x1 <= y1)
	{
		x1++;
		if (p > 0)
		{
			y1--;
			p += 4 * (x1 - y1) + 10;
		}
		else
			p += 4 * x1 + 6;

		putpixel(xc + x1, yc + y1, color);
		putpixel(xc - x1, yc + y1, color);
		putpixel(xc + x1, yc - y1, color);
		putpixel(xc - x1, yc - y1, color);
		putpixel(xc + y1, yc + x1, color);
		putpixel(xc - y1, yc + x1, color);
		putpixel(xc + y1, yc - x1, color);
		putpixel(xc - y1, yc - x1, color);

		//delay(1);
	}
}
void drawRec(int x1, int y1, int x2, int y2, int color) {
	lineDDA(x1, y1, x2, y1, color);
	lineDDA(x2, y1, x2, y2, color);
	lineDDA(x2, y2, x1, y2, color);
	lineDDA(x1, y2, x1, y1, color);
}
void initBullet()
{
	viendan[1].x = 800; viendan[1].y = 650;
	viendan[2].x = 850; viendan[2].y = 650;
	viendan[3].x = 900; viendan[3].y = 650;
}
void drawBullet()
{
	initBullet();
	for (int i = bullet; i > 0; i--)
	{
		drawRec(viendan[i].x, viendan[i].y, viendan[i].x + 20, viendan[i].y + 30, 15);
	}
}
void drawArchery(int xc, int yc, int radius)
{
	int x1 = 0, y1 = radius;
	int p = 3 - 2 * radius;

	putpixel(xc + x1, yc + y1, WHITE);
	putpixel(xc - x1, yc + y1, WHITE);
	/*putpixel(xc + x1, yc - y1, WHITE);
	putpixel(xc - x1, yc - y1, WHITE);*/
	putpixel(xc + y1, yc + x1, WHITE);
	putpixel(xc - y1, yc + x1, WHITE);
	/*putpixel(xc + y1, yc - x1, WHITE);
	putpixel(xc - y1, yc - x1, WHITE);*/
	lineDDA(xc - y1, yc + x1, xc + y1, yc + x1, WHITE);// ngan
	lineDDA(xc + x1, yc - y1, xc - x1, yc + y1 + (radius / 2), WHITE);// mui ten
	lineDDA(xc + x1, yc - y1, xc + x1 - (radius / 4), yc - y1 + (radius / 4), WHITE);
	lineDDA(xc + x1, yc - y1, xc + x1 + (radius / 4), yc - y1 + (radius / 4), WHITE);
	while (x1 <= y1)
	{
		x1++;
		if (p > 0)
		{
			y1--;
			p += 4 * (x1 - y1) + 10;
		}
		else
			p += 4 * x1 + 6;

		putpixel(xc + x1, yc + y1, WHITE);
		putpixel(xc - x1, yc + y1, WHITE);
		/*putpixel(xc + x1, yc - y1, WHITE);
		putpixel(xc - x1, yc - y1, WHITE);*/
		putpixel(xc + y1, yc + x1, WHITE);
		putpixel(xc - y1, yc + x1, WHITE);
		/*putpixel(xc + y1, yc - x1, WHITE);
		putpixel(xc - y1, yc - x1, WHITE);*/

		//delay(50);
	}

}
void drawDuck(int xc, int yc, int radius)
{
	int x1 = 0, y1 = radius;
	int p = 3 - 2 * radius;
	int xmt, xmp, ymt, ymp;// tọa độ mắt trái mắt phải
	xmt = xc - (radius / 3); ymt = yc - (radius / 3);
	xmp = xc + (radius / 3); ymp = yc - (radius / 3);
	drawCircle_Bre(xmt, ymt, radius / 5, WHITE);// vẽ mắt trái
	//boundaryFill(xmt, ymt, 15, 15);
	drawCircle_Bre(xmt + (radius / 50), ymt, radius / 15, BLACK);// vẽ tròng mắt trái
	//boundaryFill(xmt, ymt, 0, 0);
	drawCircle_Bre(xmp, ymp, radius / 5, WHITE);// vẽ mắt phải
	//boundaryFill(xmp, ymp, 15, 15);
	drawCircle_Bre(xmp - (radius / 50), ymp, radius / 15, BLACK);// vẽ tròng mắt phải
	//boundaryFill(xmp, ymp, 0, 0);

	Point gBung;// tọa độ tâm bụng
	gBung.x = xc; gBung.y = yc + (radius / 2);
	drawCircle_Bre(gBung.x, gBung.y, radius / 2, WHITE);// vẽ bụng
	//boundaryFill(gBung.x, gBung.y, 15, 15);


	Point m[4]; // tọa độ mỏ
	m[0].x = xc - (radius / 10); m[0].y = yc - (radius / 10);
	m[1].x = xc + (radius / 10); m[1].y = yc - (radius / 10);
	m[2].x = xc; m[2].y = yc + (radius / 4);
	m[3] = m[0];
	lineDDA(m[0].x, m[0].y, m[1].x, m[1].y, YELLOW);//vẽ mỏ
	lineDDA(m[1].x, m[1].y, m[2].x, m[2].y, YELLOW);
	lineDDA(m[2].x, m[2].y, m[0].x, m[0].y, YELLOW);
	//ScanLine(m, 3, 14);// tô màu mỏ


	Point canhTrai;
	canhTrai.x = xc - y1; canhTrai.y = yc + x1;
	Point ct[4];//tọa độ vẽ cánh
	ct[0].x = canhTrai.x; ct[0].y = canhTrai.y - (radius / 4);
	ct[1].x = canhTrai.x; ct[1].y = canhTrai.y + (radius / 4);
	ct[2].x = canhTrai.x - (radius / 4 * 3); ct[2].y = canhTrai.y + (radius / 4 * 3);
	ct[3] = ct[0];
	lineDDA(ct[0].x, ct[0].y, ct[1].x, ct[1].y, WHITE);//vẽ cánh trái
	lineDDA(ct[1].x, ct[1].y, ct[2].x, ct[2].y, WHITE);
	lineDDA(ct[2].x, ct[2].y, ct[0].x, ct[0].y, WHITE);

	Point canhPhai;
	canhPhai.x = xc + y1; canhPhai.y = yc + x1;
	Point cp[4];//tọa độ vẽ cánh
	cp[0].x = canhPhai.x; cp[0].y = canhPhai.y - (radius / 4);
	cp[1].x = canhPhai.x; cp[1].y = canhPhai.y + (radius / 4);
	cp[2].x = canhPhai.x + (radius / 4 * 3); cp[2].y = canhPhai.y + (radius / 4 * 3);
	cp[3] = cp[0];
	lineDDA(cp[0].x, cp[0].y, cp[1].x, cp[1].y, WHITE);//vẽ cánh phải
	lineDDA(cp[1].x, cp[1].y, cp[2].x, cp[2].y, WHITE);
	lineDDA(cp[2].x, cp[2].y, cp[0].x, cp[0].y, WHITE);

	Point chanTrai;// tọa độ chân trái
	chanTrai.x = xc - (radius / 10); chanTrai.y = yc + radius;
	Point chanT[5];//tọa độ vẽ chân
	chanT[0].x = chanTrai.x; chanT[0].y = chanTrai.y;
	chanT[1].x = chanTrai.x - (radius / 5); chanT[1].y = chanTrai.y;
	chanT[2].x = chanTrai.x - (radius / 5); chanT[2].y = chanTrai.y + (radius / 7);
	chanT[3].x = chanTrai.x; chanT[3].y = chanTrai.y + (radius / 7);
	chanT[4] = chanT[0];
	lineDDA(chanT[0].x, chanT[0].y, chanT[1].x, chanT[1].y, YELLOW);// vẽ chân trái
	lineDDA(chanT[1].x, chanT[1].y, chanT[2].x, chanT[2].y, YELLOW);
	lineDDA(chanT[2].x, chanT[2].y, chanT[3].x, chanT[3].y, YELLOW);
	lineDDA(chanT[3].x, chanT[3].y, chanT[0].x, chanT[0].y, YELLOW);
	//ScanLine(chanT, 4, YELLOW);// tô màu chân trái

	Point chanPhai;// tọa độ chân Phải
	chanPhai.x = xc + (radius / 10); chanPhai.y = yc + radius;
	Point chanP[5];//tọa độ vẽ chân
	chanP[0].x = chanPhai.x; chanP[0].y = chanPhai.y;
	chanP[1].x = chanPhai.x + (radius / 5); chanP[1].y = chanPhai.y;
	chanP[2].x = chanPhai.x + (radius / 5); chanP[2].y = chanPhai.y + (radius / 7);
	chanP[3].x = chanPhai.x; chanP[3].y = chanPhai.y + (radius / 7);
	chanP[4] = chanP[0];
	lineDDA(chanP[0].x, chanP[0].y, chanP[1].x, chanP[1].y, YELLOW);// vẽ chân phải
	lineDDA(chanP[1].x, chanP[1].y, chanP[2].x, chanP[2].y, YELLOW);
	lineDDA(chanP[2].x, chanP[2].y, chanP[3].x, chanP[3].y, YELLOW);
	lineDDA(chanP[3].x, chanP[3].y, chanP[0].x, chanP[0].y, YELLOW);
	//ScanLine(chanP, 4, YELLOW);// tô màu chân phải

	//vẽ thân hình tròn
	drawCircle_Bre(xc, yc, radius, WHITE);

}
void drawVirus(int xc, int yc, int radius)
{
	drawCircle_Bre(xc, yc, radius, RED);
	Point c[8]; //tọa độ gốc của gai virut
	c[0].x = xc - radius, c[0].y = yc;
	double gocQuayRa = 3.1415 * 45 / 180;
	for (int i = 1; i < 8; i++)
	{

		c[i].x = (c[i - 1].x - xc) * cos(gocQuayRa) - (c[i - 1].y - yc) * sin(gocQuayRa) + xc;
		c[i].y = (c[i - 1].x - xc) * sin(gocQuayRa) + (c[i - 1].y - yc) * cos(gocQuayRa) + yc;

	}

	Point d[8];//tọa độn đỉnh của gai virut
	int gai = radius / 2;// dộ dài của gai
	d[0].x = xc - radius - gai, d[0].y = yc;

	for (int i = 1; i < 8; i++)
	{

		d[i].x = (d[i - 1].x - xc) * cos(gocQuayRa) - (d[i - 1].y - yc) * sin(gocQuayRa) + xc;
		d[i].y = (d[i - 1].x - xc) * sin(gocQuayRa) + (d[i - 1].y - yc) * cos(gocQuayRa) + yc;

	}

	for (int i = 0; i < 8; i++) // vẽ gai
	{
		lineDDA(c[i].x, c[i].y, d[i].x, d[i].y, RED);
		drawCircle_Bre(d[i].x, d[i].y, radius / 5, RED);
		//boundaryFill(d[i].x + 2, d[i].y + 1, RED, RED);

	}
}
double calDis(Point m, Point n)
{
	return sqrt(pow((m.x - n.x) * 1.0, 2) + pow((m.y - n.y) * 1.0, 2));
}

bool checkDucKIsHit()
{
	Point mouse[1];
	mouse[0].x = -1; mouse[0].y = -1;
	getmouseclick(WM_LBUTTONDOWN, mouse[0].x, mouse[0].y);
	if (mouse[0].x != -1 && mouse[0].y != -1)
	{
		if (calDis(viTri[1], mouse[0]) <= to)
		{
			score += 10;
			if (score == 100 || score == 1000 || score == 10000)
				dis_score += 10;
			return true;
		}
		if (calDis(viTri[1], mouse[0]) > to)
		{
			bullet -= 1;
			return false;
		}
	}
	return false;
}

int duckFly()
{
	int stepx[5]; //bước nhảy để dịch chuyển vịt
	int stepy[5];
	int show = 2; // kiểm soát tổng giá trị xuất hiện
	setcolor(15);
	settextstyle(10, 0, 3);
	for (int i = 1; i < 5; i++)
	{
		stepx[i] = 10;
		stepy[i] = 10;
	}

	for (int i = 1; i < 5; i++)
	{
		viTri[i].x = rand() % 999 + 1;
		viTri[i].y = rand() % 499 + 1;
	}

	while (bullet > 0)
	{
		for (int i = 1; i <= show; i++)
		{
			viTri[i].x += stepx[i];
			viTri[i].y += stepy[i];
		}

		cleardevice();
		drawDuck(viTri[1].x, viTri[1].y, to);
		drawBullet();
		for (int i = 2; i <= show; i++)
		{
			drawVirus(viTri[i].x, viTri[i].y, 30);
		}

		drawArchery(500, 640, 40);

		char a[15] = "SCORE: ";
		outtextxy(50, 670, a);
		stringstream strs; // chuyển kiểu số sang dạng char
		strs << score;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();
		outtextxy(120 + dis_score, 670, char_type);

		if (score == 50 && show == 2 || score == 200 && show == 3 || score == 10000 && show == 4)
		{
			show += 1;
			for (int i = 1; i <= show; i++)
			{
				viTri[i].x = rand() % 999 + 1;
				viTri[i].y = rand() % 499 + 1;
			}
		}

		int random = rand() % 2;
		if (random == 0)
			random = 1;
		else
			random = -1;
		if (checkDucKIsHit() == true)
		{
			char a[14] = "HuHu Bye Bye";
			outtextxy(viTri[1].x + 10, viTri[1].y - 45, a);
			delay(1000);
			for (int i = 1; i <= show; i++)
			{
				viTri[i].x = rand() % 999 + 1;
				viTri[i].y = rand() % 499 + 1;
			}
			for (int i = 1; i <= show; i++)
			{
				stepx[i] = rand() % 10 + 5;
				stepy[i] = rand() % 10 + 5;
			}

		}
		/*if (butlet < 3 && check_text == 0 )
		{
			char a[9] = "CMIYC hihi";
			outtextxy(viTri[1].x + 10, viTri[1].y - 45, a);
		}
		if (check_count == 50)
			check_text = 1;
		check_count++;*/
		for (int i = 1; i <= show; i++) // 4 cạnh màn hình
		{
			if (viTri[i].x >= 1000)
			{
				stepx[i] = -rand() % 10 + 0; // rand hướng vào lại
				stepy[i] = random * rand() % 10 + 0;
			}
			if (viTri[i].x <= 0)
			{
				stepx[i] = rand() % 10 + 0;
				stepy[i] = random * rand() % 10 + 0;
			}
			if (viTri[i].y >= 500)
			{
				stepy[i] = -rand() % 10 + 0;
				stepx[i] = random * rand() % 10 + 0;
			}
			if (viTri[i].y <= 0)
			{
				stepy[i] = rand() % 10 + 0;
				stepx[i] = random * rand() % 10 + 0;
			}
		}
		delay(50);
	}
	if (drawBtExit() == 1)
		return 1;
	else
	{
		score = 0;
		bullet = 3;
		int dis_score = 0;
		duckFly();
	}
}

void menu()
{
	int xMid = getmaxx() / 2; //500
	int yMid = getmaxy() / 2; //350
	setcolor(YELLOW);
	settextstyle(10, 0, 8);
	settextjustify(1, 1);
	char a[10] = "DUCK HUNT";
	outtextxy(xMid, yMid - 250, a);

	drawDuck(500, 200, 50);
	drawVirus(150, 200, 50);
	drawVirus(850, 200, 50);

	drawRec(xMid - 150, yMid - 100, xMid + 150, yMid - 50, GREEN);
	setcolor(WHITE);
	settextstyle(10, 0, 3); //font, direction, size
	char b[10] = "Start";
	outtextxy(xMid, yMid - 70, b);

	yMid += 100;
	drawRec(xMid - 150, yMid - 100, xMid + 150, yMid - 50, GREEN);

	char d[10] = "Rules";
	char f[10] = "Exit";
	outtextxy(xMid, yMid - 70, f);


	char g[30] = "Initially, you have 3 shots.";
	outtextxy(505, 450, g);

	char h[45] = "If you hit the duck, you will get 10 points.";
	outtextxy(505, 450 + 50, h);

	char i[45] = "Conversely, if you hit the bomb or miss , ";
	outtextxy(510, 450 + 90, i);

	char o[40] = "you will probably lose 1 shot.";
	outtextxy(510, 450 + 130, o);

	char p[50] = "Upon 3 shots are running out. The game is over";
	outtextxy(505, 450 + 190, p);
}

int drawBtExit()
{
	int check_re = 0;
	while (true)
	{
		if (check_re == 0)
		{
			cleardevice();
			check_re = 1;
		}
		int xMid = getmaxx() / 2; //500
		int yMid = getmaxy() / 2; //350
		/*yMid = yMid + 150;*/
		drawRec(xMid - 150, yMid + 50, xMid + 150, yMid + 100, GREEN);
		setcolor(WHITE);
		settextstyle(10, 0, 3); //font, direction, size
		char b[10] = "Replay";
		outtextxy(xMid, yMid + 80, b);

		yMid = yMid + 100;
		drawRec(xMid - 150, yMid + 50, xMid + 150, yMid + 100, GREEN);
		char e[15] = "Back to menu";
		outtextxy(xMid, yMid + 80, e);

		setcolor(RED);
		settextstyle(10, 0, 8);
		settextjustify(1, 1);
		char a[30] = "GAME OVER";
		outtextxy(xMid, yMid - 200, a);

		setcolor(YELLOW);
		settextstyle(10, 0, 5);
		char y[40] = "Your score is: ";
		outtextxy(xMid - 50, yMid - 100, y);
		stringstream strs; //thủ tục để chuyển kiểu số sang dạng char
		strs << score;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();
		outtextxy(xMid + 150 + dis_score, yMid - 100, char_type);

		setcolor(15);
		settextstyle(10, 0, 3);

		if (ismouseclick(WM_LBUTTONDOWN))
		{
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (xMid - 150 <= x && x <= xMid + 150)
			{
				if (400 <= y && y <= 450)
					return 0;
				if (500 <= y && y <= 550)
					return 1;
			}
		}
	}
}

void rules_interface()
{
	cleardevice();
	setcolor(15);
	settextjustify(1, 1);
	setcolor(YELLOW), settextstyle(10, 0, 5);
	char g[10] = "RULES";
	outtextxy(500, 130, g);


	int x = 100, y = 240;
	settextjustify(0, 0);
	settextstyle(10, 0, 3); setcolor(15);
	char a[100] = "Initially, you have 3 shots.";
	outtextxy(x, y, a);

	char b[100] = "If you hit the duck, you will get 10 points.";
	outtextxy(x, y + 50, b);

	char c[100] = "Conversely, if you hit the bomb, you will lose 10 points.";
	outtextxy(x, y + 90, c);

	char d[100] = "When you miss or hit a bomb,";
	outtextxy(x, y + 150, d);

	char e[100] = "you will probably lose 1 shot.";
	outtextxy(x, y + 170, e);

	char f[100] = "Upon 3 shots are running out. The game is over";
	outtextxy(x, y + 220, f);

	if (ismouseclick(WM_LBUTTONDOWN))
	{
		int x, y;
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if (10 <= x && x <= 100)
		{
			if (10 <= y && y <= 100)
				cleardevice();
		}
	}

}

int main()
{
	initwindow(1000, 700, "Duck hunt");
	int check_start = 0;
	menu();

	int xMid = getmaxx() / 2; //500
	int yMid = getmaxy() / 2; //350

	while (true)
	{
		if (check_start == 1)
		{
			cleardevice();
			bullet = 3;
			score = 0;
			int dis_score = 0;
			check_start = 0;
		}

		menu();
		if (ismouseclick(WM_LBUTTONDOWN))
		{
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (xMid - 150 <= x && x <= xMid + 150)
			{
				if (250 <= y && y <= 300)
				{
					if (duckFly() == 1)
					{
						cleardevice();
						check_start = 1;
						//delay(20000);
					}
				}
				if (350 <= y && y <= 400)
					exit(0);
			}
		}
	}
	drawBullet();

	getch();
	/*closegraph();*/
	return 0;
}