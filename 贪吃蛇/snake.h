#pragma once
#include "wall.h"
#include <stdio.h>

// ��ÿһ�ڵĽṹ��
struct Body
{
	int x;
	int y;
};

// �����ߵĽṹ��
struct Snake
{
	struct Body body[(HEIGHT - 2) * (WIDTH - 2)];
	int size;
}snake; // �߽ṹ�����

// ��ʼ����
void initSnake();

// �ߵ�ƫ����
int offset_x;
int offset_y;

// ��β��λ��
int tile_x;
int tile_y;

// �Ƿ�ѭ��
int isRoll;