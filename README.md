
### 程序简介  
这是一个用来计算并得到一个叫Calculator游戏的解的小程序。  
程序通过穷尽所有方案，找到可用解  

### 游戏介绍  
你之前可能用过计算器，但是你*"玩过"*它吗？  
Calculator就是一个萌萌的计算器手机游戏。  
在游戏里，你可以把数字加，减，替换，转置，甚至传送数字。  
通过限定次数，和用指定的按键来得到最终的结果。

### 关于这个游戏  
该游戏在APP Store上获得了**4.8分**的评分  
并且Calculator: the game支持IOS/Android平台  

### 下载地址  
[苹果平台(App Store)](https://itunes.apple.com/cn/app/calculator-the-game/id1243055750?mt=8)  
[安卓平台(Google Play)](https://play.google.com/store/apps/details?id=com.sm.calculateme)

### 测试环境  
**Ubuntu 18.04 | termux**

### 程序打开方式  

#### Linux 发行版  
1.首先要确保系统已经安装好clang编译器和自动化构建工具make以及git  
以ubuntu为例：  
`sudo apt install clang make git`

2.克隆仓库并切换到目录  
`git clone https://github.com/notonlyming/Calculator-Game-solve.git`  
`cd Calculator-Game-solve`

3.编译和构建  
对于只要使用程序的计算关卡所有有效解功能的用户只需构建主程序
`make` 或者 `make calculator-game.exe`  
如果程序没有正确计算出解，或者做了什么稀奇古怪的事情  
你可以使用程序计算过程跟踪程序来输入解，它可以打印程序的计算过程  
`make game_test.exe`

4.运行  
开始你的计算器之旅吧😌  
`./calculator-game.exe`

#### Mac os  
1.需要安装xcode命令行开发工具(如果没有)  
在终端中输入*gcc*回车。弹出下载xcode命令行工具对话框  
点安装，等待下载完毕  

在命令行中输入`gcc --version`或者`clang --version`  
若有输出版本提示信息，则为安装成功！

2.克隆仓库并切换到目录  
`git clone https://github.com/notonlyming/Calculator-Game-solve.git`  
`cd Calculator-Game-solve`

3.编译构建
基本程序:  
`clang main.c game.c game_input.c game_output.c game_process.c -Wall -Wextra -Werror -lm -o calulator_game.exe`
因为我不确定在mac上能不能使用make😂  
若要构建game-test程序，请参考makefile

4.运行  
boom~  
`./calculator-game.exe`

#### Windows  
由于windows的特殊性，在windows上编译纯C代码  
暂时没找到简单可靠的解决方案，不过我应该很快就会找到的🤔  

Code by LittleMing 2018.08.25
