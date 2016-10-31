layout: '[post]'
title: Ubuntu 14.04系统下配置shadowsocks
date: 2016-10-31 20:43:57
tags: [Ubuntu 14.04, shadowsocks]
categories: Ubuntu
---

shadowsocks是一种我们经常使用的科学上网的工具，是一种非常方便快捷的代理工具。目前的shadowsocks已经支持全平台的服务支持，这篇文章主要介绍一下Ubuntu 14.04系统平台中shadowsocks的安装配置。
Ubuntu 14.04系统平台下的shadowsocks配置一共有两种方式，分别是安装[shadowsocks-gui][1]（Cross-platform GUI powered node and by Webkit）和在命令行中使用shadowsocks。

<!--more-->

### shadowsocks-qt5使用教程

首先确保你的Ubuntu版本是>=14.04的，然后通过添加PPA进行安装：
```
sudo add-apt-repository ppa:hzwhuang/ss-qt5
sudo apt-get update
sudo apt-get install shadowsocks-qt5
```
其他系统版本的安装过程见如下[安装教程][2]。

### 命令行配置shadowsocks

首先确保你的python版本是2.6或者2.7。
```
python --version ##查看python的版本
```
然后直接安装shadowsocks。
```
pip install shadowsocks ##如果没有pip请执行 apt-get install python-pip进行安装
```
然后在`/etc/shadowsocks`目录下新建一个文件`config.json`，（如果没有对应文件/文件夹则新建一个），文件包含如下内容：
```
{
    "server":"my_server_ip",
    "server_port":8388,
    "local_port":1080,
    "password":"barfoo!",
    "timeout":600,
    "method":"table"
}
```
其中各行的意义为：
```
server          your server IP (IPv4/IPv6), notice that your server will listen to this IP
server_port     server port
local_port      local port
password        a password used to encrypt transfer
timeout         in seconds
method          encryption method, "bf-cfb", "aes-256-cfb", "des-cfb", "rc4", etc. Default is table, which is not secure. "aes-256-cfb" is recommended
```
如果是在服务器或者VPS中配置shadowsocks，则在`config.json`文件所在的目录下执行`ssserver`命令开启服务器端：
```
cd /etc/shadowsocks/
ssserver -c /etc/shadowsocks/config.json
##此时已经开始运行，如果想在后台运行shadowsocks，则上一步应执行如下语句：
nohup ssserver > log &
```
如果是在本机配置shadowsocks，如果执行上述代码则会报如下错误：
```
...
socket.error: [Errno 99] Cannot assign requested address
```
此时应该执行如下命令：
```
sslocal -c /etc/shadowsocks/config.json -d start
```
此时shadowsocks应该就可以成功运行了。

### 使用代理
直接在浏览器相应的插件（比如chrome浏览器中使用Proxy SwitchySharp）中配置如下信息就可以使用shadowsocks代理上网啦！
```
protocol: socks5
hostname: 127.0.0.1
port:     your local_port
```

  [1]: https://github.com/shadowsocks/shadowsocks-gui
  [2]: https://github.com/shadowsocks/shadowsocks-qt5/wiki/Installation
