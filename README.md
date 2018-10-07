
项目简介
-------

这是一个用来计算并得到一个叫Calculator游戏的解的小程序。

程序通过穷尽所有方案，找到可用解。

Code by LittleMing 2018.08.25

目录
----
- [Calculator游戏](#calculator-游戏)
    - [游戏介绍](#游戏介绍)
    - [关于游戏](#关于游戏)
    - [下载地址](#下载地址)
- [项目烹饪说明](#项目烹饪说明)
    - [测试环境](#测试环境)
    - [编译和构建程序](#编译和构建程序)
        - [Linux 发行版](#linux-发行版)
        - [Mac os系统](#mac-os)
        - [Windows系统](#windows)
- [程序使用说明](#程序使用说明)
    - [下载和运行程序](下载和运行程序)
    - [如何录入关卡](#如何录入关卡)
    - [如何使用输出信息](#如何使用输出信息)
    - [如果没有找到解](#如果没有找到解)
    - [如何退出程序](#如何退出程序)

Calculator 游戏
--------------

### 游戏介绍

你之前可能用过计算器，但是你 **"玩过"** 它吗？

Calculator就是一个萌萌的计算器手机游戏。

在游戏里，你可以把数字加，减，替换，转置，甚至传送数字。

通过限定次数，和用指定的按键来得到最终的结果。

### 关于游戏

该游戏在APP Store上获得了 **4.8** 的评分

并且Calculator: the game支持IOS/Android平台

### 下载地址

[苹果平台(App Store)](https://itunes.apple.com/cn/app/calculator-the-game/id1243055750?mt=8)

[安卓平台(Google Play)](https://play.google.com/store/apps/details?id=com.sm.calculateme)

项目烹饪说明
-----------

### 测试环境

Windows 10.0.17134 **Pass**

Ubuntu 18.04 **Pass**

termux **Pass**

编译和构建程序
-------------

### Linux 发行版

1.首先要确保系统已经安装好clang编译器和自动化构建工具make以及git

以ubuntu为例：

`sudo apt install clang make git`

2.克隆仓库并切换到目录

`git clone https://github.com/notonlyming/Calculator-Game-solve.git`

`cd Calculator-Game-solve`

3.编译和构建

构建主程序

`make`

4.运行

开始你的计算器之旅吧😌

`./calculator-game`

### Mac os  
1.需要安装xcode命令行开发工具(如果没有)

在终端中输入*gcc*回车。弹出下载xcode命令行工具对话框

点安装，等待下载完毕

在命令行中输入`clang --version`

若有输出版本提示信息，则为安装成功！

2.克隆仓库并切换到目录

要使用git工具，请先在mac上安装git。

`git clone https://github.com/notonlyming/Calculator-Game-solve.git`

`cd Calculator-Game-solve`

Note：如果不希望安装git可以使用[GitHub Desktop](https://desktop.github.com/)克隆

3.编译构建

基本程序:

`make`

4.运行

`./calculator-game`

### Windows

由于windows的特殊性，在windows上编译纯C代码比较曲折。

使用Mingw的gcc可以编译，本项目也可使用更轻量的TCC编译

TCC方案。[TCC项目简介传送门](https://bellard.org/tcc/)

安装TCC
-------

1.下载TCC，并解压

下载地址：  
[百度云](https://pan.baidu.com/s/1cHBKMMT3DxOy4vQ1Rv54VQ)  适用于64位系统和处理器  
[官方下载](http://download.savannah.gnu.org/releases/tinycc/)   慢

2.安装到系统目录或自定义目录

以下提供是建议且保险的做法：直接放置在系统盘根目录下

将以tcc为名字的文件夹(请注意里面是有很多文件的)复制到C:下

Note：这时C盘下应该有一个名字是tcc的文件夹，并且文件夹里面有很多文件

3.修改环境变量

!以下操作以win10操作系统为例，其他版本可能略有差异

3.1 右击此电脑，点击属性

3.2 在左侧的导航栏中找到高级系统设置

3.3 在弹出的对话框中点击环境变量按钮，弹出环境变量对话框

3.4 注意到下方的 **系统变量** 分组框

3.5 在该分组框下的列表框中名为变量的一列中找到Path这一行，并 **单击** 选中它

3.6 单击下方的编辑按钮，弹出编辑环境变量对话框

3.7 单击新建，列表框末尾的新行被选中，并等待输入

3.8 在其中 **一字不漏地** 输入 `C:\tcc\`，并回车。此时刚刚输入的内容已经添加为新行。

3.9 点击3次确定关闭并保存刚刚的操作。再点一次叉叉把系统属性窗口关闭。

3.10 测试

同时按住键盘上的win键(即微软微标键，通常在 Ctrl键 与 alt键 之间)
和R键，弹出运行对话框

在编辑框中输入cmd后回车，弹出命令提示符窗口

窗口中输入`tcc -v`后回车，若出现tcc version的版本信息，则tcc安装成功

否则，请重复并仔细核对 **步骤3 修改环境变量** 中的每个步骤

用tcc从源代码编译构建
-------------------

1.下载源代码

方法一：直接在[项目地址](https://github.com/notonlyming/Calculator-Game-solve)的页面上单击文件列表右上方(约2点钟方向)的clone or download,然后点击下载 zip。下载后解压。

方法二：使用[GitHub Desktop](https://desktop.github.com/)或[Git](https://git-scm.com/)克隆，这里不过多叙述。

2.切换工作目录

方法一：打开文件资源管理器(此电脑)，进入包含下载的源代码的文件夹。按住Shift键不放，在空白处右击在此处打开PowerShell。此时打开的Powershell工作目录即为源代码文件夹。

方法二：在cmd或powershell窗口中，使用`cd + "路径"`后回车切换至源代码文件夹。若提示符开头的目录变为需要切换的目录，则操作成功。

Note：在cmd中 请始终使用 `cd /D "路径"`切换

3.编译

主程序：`tcc src/*.c -Wall -Wextra -Werror -o calculator_game.exe`

若编译器无报错则编译成功！

Note:在cmd和powershell中复制完后，若要粘贴复制的内容只需在窗口中按鼠标右键。

运行构建好的程序
--------------

输入`.\calculator_game.exe` 运行程序。

程序使用说明
-----------

### 下载和运行程序

可在Release页面下载对应系统版本的二进制文件：<a href="https://github.com/notonlyming/Calculator-Game-solve/releases" target="_blank">Release页面</a>

windows下可双击运行，unix或类unix系统可在终端中运行

### 如何录入关卡

运行起来后需要输入如下信息：

* 计算器的起始数值：每一关开始计算器屏幕上的数值

* 允许的最大步数

* 游戏要达到的目标

* 按钮信息：一字不漏地输入每个按钮上的文字，按钮之间用空格分隔

note：输入的按钮是去除clear、设置等按钮后，真正能对计算器的数字进行操作的按钮

* 是否有传送门，在180关以上会出现传送门

note：传送门入口位置表示从右边开始数，数字会消失的位置。出口表示数字会出现的位置。

### 如何使用输出信息

输入信息成功后，程序会计算。如果程序正确运行，会打印出解到屏幕上。

### 如果没有找到解

请检查输入的按钮是否有问题。如果确实没有问题，而且该题已经找到确定解。可以使用程序自带的计算过程跟踪功能（加参数debug）检查程序有没有异常行为。之后可以到GitHub上发issue，或自行解决问题。

### 如何退出程序

在每次询问是否继续时输入n回车即可退出

也可以在任意时刻使用键盘中断 Ctrl + C 来退出
