#include"graphics.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
using namespace std;
bool check = false;
int nb = 10;
int px, py, lx, ly, i = 0, fx, fy, no_of_food = 0, left_to_inc, speed = 50;
bool direction[4]; //0 - up, 1 - left, 2 - right, 3 - down
class body
{
	int x, y, code;
public:
	body(int a, int b, int c)
	{
		x = a;
		y = b;
		code = c;
	}
	body(){}
	int getsx() { return x; }
	int getsy() { return y; }
	int color() { return code; }
	void svalues(int a, int b, int c)
	{
		x = a; y = b; code = c;
	}
	void svalues(int a, int b)
	{
		x = a;
		y = b;
	}
};
body temp(50, 35, RED), eraser;
vector<body> bd;
void food_coord()
{
a:
	fx = rand() % 97 + 1;
	fy = rand() % 62 + 1;
	for (int i = 0; i < bd.size(); i++)
		if (bd[i].getsx() == fx && bd[i].getsy() == fy)
			goto a;
	left_to_inc += bd.size() / 4;
	if (speed > 30)
		speed--;
}
bool clash()
{
	if (bd[0].getsx() == bd.back().getsx() && bd[0].getsy() == bd.back().getsy())
	{
		food_coord();
		bd.back().svalues(fx, fy);
	}
	for (int j = 1; j < bd.size(); j++)
		if (bd[0].getsx() == bd[j].getsx() && bd[j].getsy() == bd[0].getsy())
			return true;
	return false;
}
void swap(int&a, int&b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}
void process()
{
	temp = bd[nb - 1];
	for (i = nb; i >= 1; i--)
	{
		bd[i].svalues(bd[i - 1].getsx(), bd[i - 1].getsy());
	}
	if (left_to_inc)
	{
		left_to_inc--;
		bd.insert(bd.begin() + nb++, temp);
	}
}
void initial()
{
	bd.push_back(temp);
	for (i = 1; i < nb; i++)
	{
		temp.svalues(50 - i, 35, YELLOW);
		bd.push_back(temp);
	}
	temp.svalues(50 - nb, 35, BLACK);
	bd.push_back(temp);
	food_coord();
	temp.svalues(fx, fy, GREEN);
	bd.push_back(temp);
	//cout << bd.size() << endl;
	//system("pause");
}
void print(body h)
{
	setcolor(h.color());
	setfillstyle(SOLID_FILL, h.color());
	rectangle(h.getsx() * 10 - 10, h.getsy() * 10 - 10, h.getsx() * 10, h.getsy() * 10);
	floodfill(h.getsx() * 10 - 5, h.getsy() * 10 - 5, h.color());
	setcolor(0);
}
void printsnake(int yo) // yo is just some variable to differentiate this function with otherone
{
	for (i = 0; i < bd.size(); i++)
	{
		//cout << "i: " << i << endl;
		print(bd[i]);
	}
}
void printsnake()
{
	print(bd[0]);
	print(bd[1]);
	print(bd[nb]);
	print(bd.back());
	delay(speed);
}
int opp(int num)
{
	if (num == 0)return 3;
	else if (num == 1)return 2;
	else if (num == 2)return 1;
	else return 0;
}
bool test_case(int &x, int &y, int key)
{
	switch (key)
	{
	case KEY_UP:
	{
		x = 0; 
		y = -1;
		if (py != 1)
			return true;
		py = 65;
		break;
	}
	case KEY_DOWN:
	{
		x = 0;
		y = 1;
		if (py != 64)
			return true;
		py = 0;
		break;
	}
	case KEY_LEFT:
	{
		x = -1;
		y = 0;
		if (px != 1)
			return true;
		px = 100;
		break;
	}
	case KEY_RIGHT:
	{
		x = 1;
		y = 0;
		if (px != 99)
			return true;
		px = 0;
		break;
	}
	default:
		cout << "px: " << px << " py: " << py << " key: " << key << endl;
		return false;
	}
	return true;
}
void cursor()
{
	int X, Y, x, y;
	char ch;
a:
	ch = getch();
	if (ch == 72 || ch == 75 || ch == 77 || ch == 80)
	{
		while (1)
		{
		b:
			if (ch == 75)ch = 74;
			else if (ch == 77) ch = 76;
			else if (ch == 80)ch = 78;
			X = ch;
			//cout << "came: " << X << endl;
			for (int i = 0; i < 4; i++)
			{
				if (ch == 2 * i + 72)
				{
					do
					{
						px = bd[0].getsx();
						py = bd[0].getsy();
						//cout << "but here i: " << i << " \n";
						if (test_case(x, y, i*2 + 72) && !direction[opp(i)])
						{
							//cout << "here\n";
							process();
							//cout << "not here\n";
							bd[0].svalues(px + x, py + y);
							if (clash())
								return;
							printsnake();
							for (int j = 0; j < 4; j++)
								if (j == i)
									direction[j] = true;
								else
									direction[j] = false;
						}
					} while (!kbhit());
				}
			}
			ch = getch();
			if (ch == 'Q' || ch == 'q')
				return;
		}
	}
	else goto a;
}
int main()
{
	initial();
	srand(time(NULL));
	char ch;
	int w1 = initwindow(1000, 650, " ");
	printsnake(0);
	cursor();
	closegraph();
	return 0;
}