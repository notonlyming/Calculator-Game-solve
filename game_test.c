/*
 * 程序计算过程跟踪测试
 */

#include <stdio.h>
#include "game_input.h"
#include "game_process.h"
#include "game_output.h"

int main(void)
{
	puts("请注意，这是一个程序计算过程观察测试程序！");
    do
    {
        puts("-------------------新的一关开始啦-------------------");
        getGameLevelInfo();
		int buttonIndex;
		int result = Game.startNum;
		for (int i=0; i<Game.allowMaxStep; i++)
		{
			printf("输入按钮编号：");
			scanf("%d", &buttonIndex);
			printf("按下按钮：【%s】\n", buttonStr(Game.buttons[buttonIndex-1]));
			printf("%d -> ", result);
			result = pressButton(Game.buttons[buttonIndex-1], result);
			printf("%d status:%s\n", result, Game.isOnError?"ERROR":"OK");
			puts("-----------------------------------------------------");
		}
        gameOver();
        puts("温馨提示：退出请按Ctrl+C");
    } while (1);
    return 0;
}
