---
title: Ubuntu14.04系统Chromium安装Adobe Flash插件
date: 2017-01-04 14:12:41
categories: Ubuntu
tags: [Ubuntu, Adobe Flash]
---

经历了好几次重装Ubuntu系统，每次安装都需要配置一大堆东西，对于一个几乎放弃了windows系统的人来说，每次重装系统的第一件事就是安装一个Chromium浏览器，谁让我的所有收藏夹都在Chromium账号中。然而每次安装Chromium的Flash插件都需要去网上查找各种教程，每次都要搞好久才能弄好，这次专门记录一下，以便以后需要时用到。

<!--more-->

## 下载插件
首先是下载Adobe Flash插件，下载链接如下：
[下载Adobe Flash][1]
网页会自动检测你所用系统的信息，然后需要点选一下下载插件的压缩格式，一般.tar.gz格式的即可；

## 添加插件
首先将压缩包解压：
```
tar -xvf xxx.tar.gz
```

然后将解压目录中的`libpepflashplayer.so`复制到`/usr/lib/chromium-browser/plugins`中去；
```
sudo cp libpepflashplayer.so /usr/lib/chromium-browser/plugins
```

## 更改配置
修改`/etc/chromium-browser/default`文件中的配置：
```
sudo gedit /etc/chromium-browser/default

#在打开的文件中输入以下内容
CHROMIUM_FLAGS="--ppapi-flash-path=/usr/lib/chromium-browser/plugins/libpepflashplayer.so --ppapi-flash-version= XXXX"
```
其中`XXXX`表示你所使用的Adobe Flash的插件版本，比如下图中的版本即为：24.0.0.186。
![Adobe Flash][2]


## 启动插件
打开Chromium浏览器，地址栏输入：`chrome://plugins/`， 启用Adobe插件即可；
如下图所示（图中显示的是我以前安装的老版本），这样在Ubuntu系统下也可以愉快的听音乐和看视频了！
![Chromium Plugins][3]


  [1]: https://get.adobe.com/cn/flashplayer/?no_redirect
  [2]: https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2017/01-04/2017-01-04-Adobe-Flash.png
  [3]: https://raw.githubusercontent.com/haoyuanliu/blog_pic/master/2017/01-04/2017-01-04-Chromium-Plugins.png