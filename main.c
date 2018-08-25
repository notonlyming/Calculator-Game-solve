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

struct{
    int startNum; //储存计算后的结果，也是游戏中屏幕显示的内容
    int buttonNum; //按钮个数
    int allowMaxStep; //允许的最大步数
    int gameAchieve; //游戏目标
    Button *buttons; //按钮数组头指针
}Game;

void printButtons(Button buttons[], int buttonNumber){
    printf("-----------------当前已有按钮-----------------\n");
    for (int i = 0; i < buttonNumber; i++){
        printf("按钮%i：【%c%i】\n", i+1, buttons[i].operation, buttons[i].number);
    }
    printf("---------------------------------------------\n");
}

int pressButton(Button buttonToPress, int currentNumber){
    int result = currentNumber;
    switch (buttonToPress.operation){
        case '+':
            result += buttonToPress.number;
            break;
        case '-':
            result -= buttonToPress.number;
            break;
        case '*':
            result *= buttonToPress.number;
            break;
        case '/':
            result /= buttonToPress.number;
            break;
        case '<':
            result = (int)(result / 10);
            break;
        case 'a':
            result = result*10 + buttonToPress.number;
            break;
    }
    return result;
}

void getGameLevelInfo(){
    printf("请输入计算器起始的数值：");
    scanf( "%i", &(Game.startNum) );
    getchar();  //拿掉换行符

    printf("请输入允许的最大步数：");
    scanf( "%i", &(Game.allowMaxStep) );
    getchar();  //拿掉换行符

    printf("请输入游戏目标：");
    scanf( "%i", &(Game.gameAchieve) );
    getchar();  //拿掉换行符

    printf("请输入有多少个按钮：");
    scanf("%i", &(Game.buttonNum) );
    getchar();  //拿掉换行符
    Game.buttons = malloc(sizeof(Button) * Game.buttonNum);

    for (int i = 0; i < Game.buttonNum; i++){
        printf("请输入按钮信息(操作符和数字)：");
        scanf("%c%i", &(Game.buttons[i].operation), &(Game.buttons[i].number));
        getchar();  //拿掉换行符
        printButtons(Game.buttons, i+1);
    }
}

//有必要写一个为某一进制位加一的函数减轻复杂度,直接加1返回0，发生进位返回-1
int bitAdd(unsigned short number[], unsigned short witchBit, unsigned short radix){
    if (number[witchBit]+1 != radix){
        number[witchBit] += 1;
        return 0;
    }else{
        //发生进位
        number[witchBit] = 0;
        return -1;
    }
}

//该函数用于实现特定的进制数加1，多少进制的数用来表示那个按钮按下，当进制数溢出，返回-1，即为所有情况试错完成，否则返回0
int numerationAddOne(unsigned short number[], unsigned short radix, unsigned short numberWidth){
//    if (number[0]+1 < radix){
//        number[0] += 1;
//    }else{
//        number[0] = 0;
//        if (number[1]+1 < radix){
//            number[1] += 1;
//        }else{
//            number[1] = 0;
//            if (number[2]+1 < radix){
//                number[2] += 1;
//            }else{
//                return -1;
//            }
//        }
//    }
    unsigned short witchBit;
    for(witchBit=0; witchBit<numberWidth; witchBit++){
        if(bitAdd(number, witchBit, radix) == 0){
            //位加1成功且未发生进位
            break;
        }else{
            //位加1成功，发生进位
            if(witchBit == numberWidth - 1){
                //已经"溢出"，恢复状态
                number[witchBit] = radix - 1;
                return -1;
            }else{
                //未溢出，继续给高位加一
                continue;
            }
        }
    }
    //加一操作顺利结束，未发生数满溢出
    return 0;
}

void solveIt(){
    int tempResult; //试错临时结果变量
    unsigned short *answer = malloc( sizeof(unsigned short) * Game.allowMaxStep ); //用于存储解的过程

    //从最少的步数开始尝试，看看有没有最优解
    for (int stepsNum=1; stepsNum<=Game.allowMaxStep; stepsNum++){
        for (int i=0; i<Game.allowMaxStep; i++)
            answer[i] = 0; //所有位初始化为0
        do{
            tempResult = Game.startNum;
            //逐个"按下"按钮
            for(int step=0; step<stepsNum; step++){
                tempResult = pressButton(Game.buttons[ answer[step] ], tempResult);
            }
            //判断是否成功
            if(tempResult == Game.gameAchieve){
                printf("发现解(%d步)：" , stepsNum);
                //打印解
                for (int step=0; step<stepsNum; step++){
                    printf("(%c%d) ", Game.buttons[ answer[step] ].operation, Game.buttons[ answer[step] ].number);
                }
                printf("结果：%d", tempResult);
                putchar('\n');
            }
        }while(numerationAddOne(answer, Game.buttonNum, stepsNum)!=-1);
    }
}

int main(void){
    getGameLevelInfo();
    solveIt();
    return 0;
}