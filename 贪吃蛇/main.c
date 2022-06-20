#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>
#include "wall.h"
#include "snake.h"
#include "food.h"

int score = 0;
int gapTime = 300;

// 设置控制台光标位置
void gotoXY(int x, int y) {
	if (x == 0 && y == 0) return;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void update() {
	// 显示蛇
	for (int i = 0; i < snake.size; i++) {
		gotoXY(snake.body[i].x, snake.body[i].y);
		if (i == 0) {
			printf("@");
		}
		else {
			printf("#");
		}
	}

	// 显示食物
	gotoXY(food.x, food.y);
	printf("X");

	// 蛇尾位置清除
	gotoXY(tile_x, tile_y);
	printf(" ");

	// 修改成环bug
	if (isRoll) {
		gotoXY(snake.body[0].x, snake.body[0].y);
		printf("@");
	}

	gotoXY(0, HEIGHT);
	printf("Score:%d\n", score);
}

void gameOver(int mode) { // 1.撞自身 2.撞墙
	if (mode == 1) {
		gotoXY(snake.body[0].x, snake.body[0].y);
		printf("@");
	}

	gotoXY(0, HEIGHT + 1);
	printf("Game Over!\n");
	system("pause");
	exit(1);
}

// 隐藏光标
void HideCursor(bool Visible) {
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = !Visible;
	Cursor.dwSize = sizeof(Cursor);
	HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(Hand, &Cursor);
}

int main() {
	// 去掉光标显示
	HideCursor(true);
	srand((unsigned int)time(NULL)); // 随机数种子
	initWall(); // 初始化墙
	initSnake();// 初始化蛇
	initFood();
	update();   // 更新显示
	
	char key = 'd'; // 默认方向向右
	char preKey = 'd'; // 上次方向

	// 没有撞墙
	while (snake.body[0].x >= 1 && snake.body[0].x <= WIDTH - 2 && snake.body[0].y >= 1 && snake.body[0].y <= HEIGHT - 2)
	{
		// 键盘没有输入则返回0
		if (_kbhit()) {
			key = _getch(); // 获取字符，不会显示
		}
		// 检测按键是否冲突
		if (key == 'd' && preKey == 'a' || key == 'a' && preKey == 'd' || 
			key == 'w' && preKey == 's' || key == 's' && preKey == 'w') {
			key = preKey; // 方向冲突，本次视为无效
		}
		else {
			preKey = key;// 不冲突，更新上一次方向
		}
		
		switch (key)
		{
		case 'w':
			offset_x = 0;
			offset_y = -1;
			break;
		case 'a':
			offset_x = -1;
			offset_y = 0;
			break;
		case 's':
			offset_x = 0;
			offset_y = 1;
			break;
		case 'd':
			offset_x = 1;
			offset_y = 0;
			break;
		default:
			break;
		}

		// 检测是否碰撞自身
		for (int i = 1; i < snake.size; i++) {
			if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
				gameOver(1);
			}
		}

		// 吃食物判断
		if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
			snake.size++;
			score += 100;
			gapTime = (gapTime >= 50 ? gapTime - 50 : gapTime);
			initFood();
		}

		// 记录蛇尾的位置
		tile_x = snake.body[snake.size - 1].x;
		tile_y = snake.body[snake.size - 1].y;

		// 蛇身移动
		for (int i = snake.size - 1; i > 0; i--) {
			snake.body[i].x = snake.body[i - 1].x;
			snake.body[i].y = snake.body[i - 1].y;
		}
		// 蛇头移动
		snake.body[0].x += offset_x;
		snake.body[0].y += offset_y;

		// 是否成环
		if (snake.body[0].x == tile_x && snake.body[0].y == tile_y) {
			isRoll = 1;
		}
		else {
			isRoll = 0;
		}
		// 更新蛇的位置
		update();
		Sleep(gapTime); // 单位毫秒
	}
	gameOver(2); // 撞墙
	return 0;
}