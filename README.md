
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
            - [WSL方案](#wsl方案)
                - [安装适用于Linux的Windows子系统](#安装适用于linux的windows子系统)
                - [从Windows应用商店下载并安装](#从windows应用商店下载并安装)
                - [完成发行版的初始化](#完成发行版的初始化)
                - [设置新的Linux用户帐户](#设置新的linux用户帐户)
                - [更换软件源](#更换软件源)
                - [更新Linux子系统](#更新linux子系统)
            - [TCC方案](#tcc方案)
                - [安装TCC](#安装tcc)
                - [用tcc从源代码编译构建](#用tcc从源代码编译构建)
                - [切换代码页](#切换代码页)
                - [运行构建好的程序](#运行构建好的程序)
- [程序使用说明](#程序使用说明)
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

DEV C++方案虽然自带gcc，但是windows命令行对UTF-8编码一向不太友好。

导致笔者现在都不在windows上写C

但是有折中的办法：

WSL方案(推荐)。[WSL官方文档传送门](https://docs.microsoft.com/en-us/windows/wsl/about)

TCC方案。[TCC项目简介传送门](https://bellard.org/tcc/)

### WSL方案

> Windows子系统Linux允许开发人员直接在Windows上运行GNU / Linux环境 - 包括大多数命令行工具，实用程序和应用程序 - 未经修改，无需虚拟机的开销。   --微软官方

注：以下文档来源于[微软官方](https://docs.microsoft.com/en-us/windows/wsl/install-win10)。这是官方文档的中文翻译，但并不保证最新。

翻译于2018.09.01 Power by Google translate

安装适用于Linux的Windows子系统
---------------------------

在为WSL安装任何Linux发行版之前，必须确保启用“Windows子系统for Linux”可选功能：

1.以管理员身份打开PowerShell并运行：

`Enable-WindowsOptionalFeature -Online -FeatureName Microsoft-Windows-Subsystem-Linux`

2.出现提示时重新启动计算机

从Windows应用商店下载并安装
------------------------

注：适用于Windows build 16215或更高版本

1.打开Microsoft Store并选择您喜欢的Linux发行版。

这里仅给出Ubuntu的下载地址：[Ubuntu](https://www.microsoft.com/store/p/ubuntu/9nblggh4msv6)

2.从发行版页面中选择“获取”

完成发行版的初始化
---------------

下载并安装发行版后，您需要完成新发行版的初始化：

要完成新安装的发行版的初始化，请启动新实例。您可以通过单击Windows应用商店应用中的“启动”按钮，或从“开始”菜单启动发行版来执行此操作：

> 提示：您可能希望将最常用的发行版固定到“开始”菜单和/或任务栏！

新安装的发行版第一次运行时，将打开一个控制台窗口，您将被要求等待一两分钟才能完成安装。

> 在安装的最后阶段，发行版的文件被解压缩并存储在您的PC上，随时可以使用。这可能需要大约一分钟或更长时间，具体取决于PC存储设备的性能。只有在清洁安装发行版时才需要此初始安装阶段 - 所有未来新安装发行版都应该不到一秒钟。

设置新的Linux用户帐户
------------------

安装完成后，系统将提示您创建新的用户帐户（及其密码）。

此用户帐户适用于您在启动发行版时默认登录的普通非管理员用户。

> 您可以选择任何您想要的用户名和密码 - 它们与您的Windows用户名无关。

当您打开一个新的发行版实例时，系统不会提示您输入密码，但如果您使用提升进程sudo，则需要输入密码，因此请确保选择一个易于记忆的密码！

更换软件源
--------

针对国内用户下载软件慢的状况，一般建议换源

推荐的源：[清华大学开源镜像站](https://mirrors.tuna.tsinghua.edu.cn/)、[中国科学技术大学开源镜像站](https://mirrors.ustc.edu.cn/)、[阿里云镜像站](https://opsx.alibaba.com/mirror)

这里假设安装的子系统是ubuntu18.04LTS版本（2018.09.01），并设置使用清华大学的源

若版本发生变化，请阅读镜像站给出的文档

使用vim编辑软件源：`sudo vim.tiny /etc/apt/sources.list`

输入密码后回车

按下gg回到第一行，按下大写V进入行选择模式，再按下大写G选择到行尾。按下小写d删除原有软件源配置信息。

复制下列配置信息：

```
# 默认注释了源码镜像以提高 apt update 速度，如有需要可自行取消注释
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-updates main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-backports main restricted universe multiverse
deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-security main restricted universe multiverse

# 预发布软件源，不建议启用
# deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multiverse
# deb-src https://mirrors.tuna.tsinghua.edu.cn/ubuntu/ bionic-proposed main restricted universe multi
```

回到Ubuntu按下小写i进入插入模式，右击鼠标粘贴

ESC退出插入模式 输入英文状态下的`:wq`并回车，保存退出。

更新Linux子系统
------------------------

输入命令回车，并在需要你确认的地方输入y并回车：

`sudo apt update && sudo apt upgrade`

你完成了！

接下来可以参照本文档的[Linux部分](#linux-发行版)烹饪源代码了。

### TCC方案

如果你发现无法安装WSL，你可以使用TCC作为备选方案。

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

方法二：使用[GitHub Desktop](https://desktop.github.com/)克隆，这里不过多叙述。

2.切换工作目录

方法一：打开文件资源管理器(此电脑)，进入包含下载的源代码的文件夹。按住Shift键不放，在空白处右击在此处打开PowerShell。此时打开的Powershell工作目录即为源代码文件夹。

方法二：在cmd或powershell窗口中，使用`cd + "路径"`后回车切换至源代码文件夹。若提示符开头的目录变为需要切换的目录，则操作成功。

Note：在cmd中 请尽量始终使用 `cd /D "路径"`切换

### 切换代码页

重要！该操作是为了解决cmd通过默认代码页解析UTF-8出现乱码的问题。

 **请在编译前或运行程序前执行一次本操作**，以正确显示用UTF-8编码的中文(包括本程序)

在cmd或powershell中输入：`chcp 65001`来切换至正确的代码页

3.编译

主程序：`tcc src/*.c -Wall -Wextra -Werror -o calculator_game.exe`

若编译器无报错则编译成功！

Note:在cmd和powershell中复制完后，若要粘贴复制的内容只需在窗口中按鼠标右键。

运行构建好的程序
--------------

编译成功后，同样由于编码问题。编译出来的balabala.exe文件中文默认以Ascii解析。因此需要使用cmd或powershell[切换默认代码页](#切换代码页)后打开。

如果没有执行过编译操作的，需要先执行[编译操作](#用tcc从源代码编译构建)。之后命令行便处于含有编译好的可执行文件的工作目录下。

Fianlly，输入`.\calculator_game.exe` 运行程序。

程序使用说明
-----------

### 如何录入关卡

运行起来后需要输入如下信息：

* 计算器的起始数值：每一关开始计算器屏幕上的数值

* 允许的最大步数

* 游戏要达到的目标

* 按钮信息：一字不漏地输入每个按钮上的文字，按钮之间用空格分隔

note：输入的按钮是去除clear、设置等按钮后，真正能对计算器的数字进行操作的按钮

### 如何使用输出信息

输入信息成功后，程序会计算。如果程序正确运行，会打印出解到屏幕上。

### 如果没有找到解

请检查输入的按钮是否有问题。如果确实没有问题，而且该题已经找到确定解。可以使用程序自带的计算过程跟踪功能（加参数debug）检查程序有没有异常行为。之后可以到GitHub上发issue，或自行解决问题。

### 如何退出程序

在每次询问是否继续时输入n回车即可退出

也可以在任意时刻使用键盘中断 Ctrl + C 来退出
