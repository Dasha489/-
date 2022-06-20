#include "food.h"

void initFood() {
	int flag = 0;

	while (1)
	{
		food.x = rand() % (WIDTH - 2) + 1;
		food.y = rand() % (HEIGHT - 2) + 1;

		// 判断食物和蛇身体是否重叠
		for (int i = 0; i < snake.size; i++) {
			if (snake.body[i].x == food.x && snake.body[i].y == food.y) {
				flag = 1;
				break;
			}
		}

		// 没有重叠
		if (flag == 0) {
			break;
		}
		else {
			flag = 0;
		}
	}

}