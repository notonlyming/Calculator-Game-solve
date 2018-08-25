/*
 * 这是一个用来计算一个叫Calculator游戏的小程序
 * Calculator是一个萌萌的计算器游戏
 * 通过限定次数，和用指定的按键来得到最终的结果
 * 这是一个数学游戏
 * 程序通过穷尽所有的组合来得到结果
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char operation; //加减乘除操作储存区
    int number; //操作数
}Button;  //存储按钮的详细信息

void printButtons(Button buttons[], int buttonNumber){
    printf("-----------------当前已有按钮-----------------\n");
    for (int i = 0; i < buttonNumber; i++){
        printf("按钮%i：【%c%i】\n", i+1, buttons[i].operation, buttons[i].number);
    }
    printf("---------------------------------------------\n");
}

int main(void){
    int result = 0; //储存计算后的结果，也是游戏中屏幕显示的内容
    printf("请输入计算器起始的数值：");
    scanf("%i", &result);
    getchar();  //拿掉换行符

    printf("请输入有多少个按钮：");
    int buttonNumber;
    scanf("%i", &buttonNumber);
    getchar();  //拿掉换行符
    Button *buttonArry = malloc(sizeof(Button) * buttonNumber);

    for (int i = 0; i < buttonNumber; i++){
        printf("请输入按钮信息(操作符和数字)：");
        scanf("%c%i", &(buttonArry[i].operation), &(buttonArry[i].number));
        getchar();  //拿掉换行符
        printButtons(buttonArry, i+1);
    }
    return 0;
}