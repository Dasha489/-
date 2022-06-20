#pragma once
#include "wall.h"
#include <stdio.h>

// 蛇每一节的结构体
struct Body
{
	int x;
	int y;
};

// 整个蛇的结构体
struct Snake
{
	struct Body body[(HEIGHT - 2) * (WIDTH - 2)];
	int size;
}snake; // 蛇结构体变量

// 初始化蛇
void initSnake();

// 蛇的偏移量
int offset_x;
int offset_y;

// 蛇尾的位置
int tile_x;
int tile_y;

// 是否循环
int isRoll;