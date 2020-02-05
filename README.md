
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
    - [下载和运行程序](#下载和运行程序)
    - [如何录入关卡](#如何录入关卡)
    - [特殊按钮说明](#特殊按钮说明)
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

Caldulator2 已推出，本解算器已支持所有新特性。

### 下载地址

[Calculator1 苹果平台(App Store)](https://itunes.apple.com/cn/app/calculator-the-game/id1243055750?mt=8)  
[Calculator2 苹果平台(App Store)](https://apps.apple.com/cn/app/%E8%AE%A1%E7%AE%97%E5%99%A82-%E6%B8%B8%E6%88%8F/id1436348748)

[Calculator1 安卓平台(Google Play)](https://play.google.com/store/apps/details?id=com.sm.calculateme)  
[Calculator2 安卓平台(Google Play)](https://play.google.com/store/apps/details?id=com.simplemachine.calculator2)

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

主程序：`tcc src/*.c -Ofast -Wall -Wextra -Werror -o calculator_game.exe`

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

### 乱码问题

若windows下出现乱码（一般为非win10系统），请先安装<a href="https://github.com/notonlyming/Calculator-Game-solve/releases/download/1.0.1/lucon.ttf" target="_blank">该字体</a>

并右击标题栏点属性将字体切换为Lucia Console后确定。重启程序后，乱码问题应当得到解决。

### 如何录入关卡

运行起来后需要输入如下信息：

* 计算器的起始数值：每一关开始计算器屏幕上的数值

* 允许的最大步数

* 游戏要达到的目标, 如果有多个目标，中间用空格分开。

* 按钮信息：一字不漏地输入每个按钮上的文字，按钮之间用空格分隔。特殊按钮输入见下方。

note：输入的按钮是去除clear、设置等按钮后，真正能对计算器的数字进行操作的按钮

* 是否有传送门，在180关以上会出现传送门

note：传送门入口位置表示从右边开始数，数字会消失的位置。出口表示数字会出现的位置。

### 特殊按钮说明
delete
======
这是在第二版中出现的按钮，它可以删除任意位的数字。  
在录入按钮时使用delete即可，但程序内部实际上实现了一个删除特定位的按钮。  
因此delete实际上会在内部被替换为：delete1 delete2 delete3 delete4 delete5 delete6  
你将会看到6个按钮，不要惊慌~  
delete位是从左边开始数起的位置

shift
=====
这也是在第二版中出现的按钮，区别在于它可以移动任意方向任意次数，且只记一次步数。  
程序内部同样实现了一个按特定次数位移的按钮。  
只要输入shift，字符串就被替换为：shift1 shift2 shift3 shift4 shift5 shift6  
将会有6个按钮。

replace
=======
将任意位替换为指定数字。  
输入replace?    ?是会替换成的数字。  
内部实现了一个指定位替换的按钮。所以同上，你的按钮会被替换。  

round
======
同上

insert
======
同上

按位加
=====
第二版中好像是紫色按钮的+?表示可在任意位上加上一个数。   
录入时请使用：bit+?   的格式。?是要加上的数字。   
同上，他会被替换成6个按钮，分别对应所有位。

store
=====
似乎在某次更新以后ios和android版本的store长按也是记录次数的。  
解算器已经更新为store长按记录次数。  

ABC
===
这是第二版中出现的按钮。首先如果输入的目标中包含字母，都会被自动解密成数字。  
其次ABC按钮一般实在最后才使用进行转换，所以不需要尝试。  
输入的ABC按钮会被替换为+0。并且最大步数-1用来预留给最后按一下ABC。  
含ABC按钮的关卡，会在每个的后面增加一个ABC按钮。  

lock
====
第二版中锁按钮，持续一个回合。  
特别注意lock后的数字表示从右边数起的位。  

### 如何使用输出信息

输入信息成功后，程序会计算。如果程序正确运行，会打印出解到屏幕上。

### 如果没有找到解

请检查输入的按钮是否有问题。如果确实没有问题，而且该题已经找到确定解。可以使用程序自带的计算过程跟踪功能（加参数debug）检查程序有没有异常行为。之后可以到GitHub上发issue，或自行解决问题。

### 如何退出程序

在每次询问是否继续时输入n回车即可退出

也可以在任意时刻使用键盘中断 Ctrl + C 来退出
