求生之路IPV6连接工具
============

L4D2IPV6ConnectHelper
============

Homepage: https://github.com/ll2594/L4D2IPV6ConnectHelper

介绍Introduction
------------

一个基于Qt的简单项目，实现让求生之路连接纯IPV6服务器。
A Simple project based on Qt,which can make Left 4 Dead 2 to connect IPV6 Server.]

编译Compilation
-----------

支持:Windows,Linux

Supports: Windows, Linux

1. 克隆项目 Clone
   
   ```bash
   git clone https://github.com/ll2594/L4D2IPV6ConnectHelper.git
   ```

2. cmake and build
   
   如果cmake提示找不到Qt，请手动指定Qt路径，在CmakeLists.txt添加
   
   If cmake prompts that Qt cannot be found, please manually specify the Qt path and add it in CmakeLists.txt
   
   > set(Qt5_DIR "C:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5"
   
   ```bash
   cmake -S . -B build
   cd build
   make
   ```

使用方法Usage
----------------------------

## 客户端 Client

选择本机对应的IPV4和IPV6地址，输入服务端的IPV6域名，点击获取服务器IPV6，输入远程服务器IPV6端口，点击启动转发器，服务器连接指令将显示在下方，复制粘贴近游戏，enjoy it!

Select the IPV4 and IPV6 addresses corresponding to the local machine, enter the IPV6 domain name of the server, click to obtain the server's IPV6, enter the remote server's IPV6 port, click to start the router, the server connection command will be displayed below, copy and paste near the game, enjoy it!

![](https://github.com/ll2594/L4D2IPV6ConnectHelper/blob/main/img/ui.png)

## 服务端 Server

至于服务端，请使用socat，我们提供了一个工具来生成socat命令

As Server,Please use socat,We Provide a tool to gen sockat command.

1. 安装socat
2. install socat 

```bash
apt install socat # debian/Ubuntu
yum install socat #centos 
```

2. 使用socatCmdGenerator生成命令
3. gen command 

```bash
./socatCmdGenerator <你的服务端域名> <你的服务端IPV6端口> <你的服务端IPV4端口>
```

3. 复制生成的命令，运行
4. copy command ,paste,and run

致谢 Thanks
----------------------------

感谢贴吧用户[🤤🤤🤤](https://tieba.baidu.com/home/main?id=tb.1.e1fbdec0.HIZFbFNTZqjjjUdjvUI30w%3Ft%3D1647573978) 提供的思路，原帖链接->[https://tieba.baidu.com/p/821528821](https://tieba.baidu.com/p/8215288821)   

如果觉得项目不错，请点一点Star，谢谢

If you think the project is good, please Star the Project, thanks a lot.
