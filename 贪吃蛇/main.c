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

// ���ÿ���̨���λ��
void gotoXY(int x, int y) {
	if (x == 0 && y == 0) return;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void update() {
	// ��ʾ��
	for (int i = 0; i < snake.size; i++) {
		gotoXY(snake.body[i].x, snake.body[i].y);
		if (i == 0) {
			printf("@");
		}
		else {
			printf("#");
		}
	}

	// ��ʾʳ��
	gotoXY(food.x, food.y);
	printf("X");

	// ��βλ�����
	gotoXY(tile_x, tile_y);
	printf(" ");

	// �޸ĳɻ�bug
	if (isRoll) {
		gotoXY(snake.body[0].x, snake.body[0].y);
		printf("@");
	}

	gotoXY(0, HEIGHT);
	printf("Score:%d\n", score);
}

void gameOver(int mode) { // 1.ײ���� 2.ײǽ
	if (mode == 1) {
		gotoXY(snake.body[0].x, snake.body[0].y);
		printf("@");
	}

	gotoXY(0, HEIGHT + 1);
	printf("Game Over!\n");
	system("pause");
	exit(1);
}

// ���ع��
void HideCursor(bool Visible) {
	CONSOLE_CURSOR_INFO Cursor;
	Cursor.bVisible = !Visible;
	Cursor.dwSize = sizeof(Cursor);
	HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(Hand, &Cursor);
}

int main() {
	// ȥ�������ʾ
	HideCursor(true);
	srand((unsigned int)time(NULL)); // ���������
	initWall(); // ��ʼ��ǽ
	initSnake();// ��ʼ����
	initFood();
	update();   // ������ʾ
	
	char key = 'd'; // Ĭ�Ϸ�������
	char preKey = 'd'; // �ϴη���

	// û��ײǽ
	while (snake.body[0].x >= 1 && snake.body[0].x <= WIDTH - 2 && snake.body[0].y >= 1 && snake.body[0].y <= HEIGHT - 2)
	{
		// ����û�������򷵻�0
		if (_kbhit()) {
			key = _getch(); // ��ȡ�ַ���������ʾ
		}
		// ��ⰴ���Ƿ��ͻ
		if (key == 'd' && preKey == 'a' || key == 'a' && preKey == 'd' || 
			key == 'w' && preKey == 's' || key == 's' && preKey == 'w') {
			key = preKey; // �����ͻ��������Ϊ��Ч
		}
		else {
			preKey = key;// ����ͻ��������һ�η���
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

		// ����Ƿ���ײ����
		for (int i = 1; i < snake.size; i++) {
			if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
				gameOver(1);
			}
		}

		// ��ʳ���ж�
		if (snake.body[0].x == food.x && snake.body[0].y == food.y) {
			snake.size++;
			score += 100;
			gapTime = (gapTime >= 50 ? gapTime - 50 : gapTime);
			initFood();
		}

		// ��¼��β��λ��
		tile_x = snake.body[snake.size - 1].x;
		tile_y = snake.body[snake.size - 1].y;

		// �����ƶ�
		for (int i = snake.size - 1; i > 0; i--) {
			snake.body[i].x = snake.body[i - 1].x;
			snake.body[i].y = snake.body[i - 1].y;
		}
		// ��ͷ�ƶ�
		snake.body[0].x += offset_x;
		snake.body[0].y += offset_y;

		// �Ƿ�ɻ�
		if (snake.body[0].x == tile_x && snake.body[0].y == tile_y) {
			isRoll = 1;
		}
		else {
			isRoll = 0;
		}
		// �����ߵ�λ��
		update();
		Sleep(gapTime); // ��λ����
	}
	gameOver(2); // ײǽ
	return 0;
}