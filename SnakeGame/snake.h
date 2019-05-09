#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
bool game_over;
const int width = 20;
const int height = 20;
int score;
int highscore;
int speed;
enum move_direction { STOP = 0, UP, DOWN, LEFT, RIGHT };
move_direction theDirection;
struct food {
	int x;
	int y;
};
struct heads {
	int x;
	int y;
};
struct body {
	int x[100];
	int y[100];
	int lenght;
};
heads head;
food fruit;
food bonus;
body tail;
void setup()
{
	game_over = false;
	theDirection = RIGHT;
	head.x = width / 2;
	head.y = height / 2;
	tail.lenght = 0;
	fruit.x = rand() % width;
	fruit.y = rand() % height;
	bonus.x = rand() % width;
	bonus.y = rand() % height;
	score = 0;
	speed = 50;
}
void draw()
{
	system("cls");
	for (int top = 0; top <= width; top++)
		cout << "#";
	cout << endl;
	for (int side = 0; side < height; side++)
	{
		for (int sidew = 0; sidew < width; sidew++)
		{
			if (sidew == 0)
				cout << "#";
			if (side == head.y && sidew == head.x)
				cout << "O";
			else if (side == fruit.y && sidew == fruit.x)
				cout << "F";
			else if (side == bonus.y && sidew == bonus.x)
				cout << "B";
			else {
				bool drawn = false;
				for (int step = 0; step < tail.lenght; step++)
				{
					if (tail.x[step] == sidew&&tail.y[step] == side)
					{
						cout << "o";
						drawn = true;
					}
				}
				if (!drawn)
					cout << " ";
			}
			if (sidew == width - 2)
				cout << "#";
		}
		cout << endl;
	}
	for (int bottom = 0; bottom <= width; bottom++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score;
	cout << endl;
	cout << "Press 'x' to exit.";
	cout << endl;
	cout << "Press 'h' for hard or press 'e' for easy.";

}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			if (theDirection == RIGHT)
				break;
			theDirection = LEFT;
			break;
		case 'd':
			if (theDirection == LEFT)
				break;
			theDirection = RIGHT;
			break;
		case 'w':
			if (theDirection == DOWN)
				break;
			theDirection = UP;
			break;
		case 's':
			if (theDirection == UP)
				break;
			theDirection = DOWN;
			break;
		case 'x':
			game_over = true;
			break;
		case 'e':
			speed = 50;
			break;
		case'h':
			speed = 0;
			break;
		}
	}
}
void logic()
{
	heads prev;
	prev.x = tail.x[0];
	prev.y = tail.y[0];
	heads prev2;
	tail.x[0] = head.x;
	tail.y[0] = head.y;
	for (int step = 1; step < tail.lenght; step++)
	{
		prev2.x = tail.x[step];
		prev2.y = tail.y[step];
		tail.x[step] = prev.x;
		tail.y[step] = prev.y;
		prev.x = prev2.x;
		prev.y = prev2.y;
	}
	switch (theDirection)
	{
	case UP:
		if (theDirection == DOWN)
			break;
		head.y--;
		break;
	case DOWN:
		if (theDirection == UP)
			break;
		head.y++;
		break;
	case LEFT:
		if (theDirection == RIGHT)
			break;
		head.x--;
		break;
	case RIGHT:
		if (theDirection == LEFT)
			break;
		head.x++;
		break;
	default:
		break;
	}
	//if (head.x > width-2 || head.x < 0|| head.y>height || head.y<0)
	//	game_over = true;
	if (head.x >= width - 1)
		head.x = 0;
	else if (head.x < 0)
		head.x = width - 2;
	if (head.y >= height)
		head.y = 0;
	else if (head.y < 0)
		head.y = height - 1;
	for (int step = 0; step < tail.lenght; step++)
	{
		if (tail.x[step] == head.x&&tail.y[step] == head.y)
			game_over = true;
	}
	if (head.x == fruit.x && head.y == fruit.y)
	{
		tail.lenght++;
		score += 1;
		fruit.x = rand() % width;
		fruit.y = rand() % height;
	}
	if (head.x == bonus.x && head.y == bonus.y)
	{
		tail.lenght++;
		score += 2;
		speed += 10;
		bonus.x = rand() % width;
		bonus.y = rand() % height;
	}
}

void play() {
	system("cls");
	setup();
	while (!game_over)
	{
		draw();
		input();
		logic();
		Sleep(speed);
	}
	system("cls");
	cout << "If you want to play again press SPACEBAR" << endl;
	cout << endl << "Press any other key close the program." << endl;
	cout << endl << "	Your score is: " << score << endl;
	switch (_getch())
	{
	case ' ':
		play();
	case '\n':
		break;
	}
}