# HomeMonitor
PC's camera is used as a Home Guard. PC camera collect pictures and send them to your another Host using TCP protocol.

# Design's details
1. server collect picture using the Normal PC's camera, in OPEVCV3.0
2. and server uses 'select networking model' to communicate with clients
3. client receive image data, and show it.

![design](https://github.com/Guguant/HomeMonitor/blob/master/demo/design.png)

# Usage
```c
server: server.exe <IP> <PORT>
client: client.exe <PORT> (ps: client's PORT is same as server's)

```

# Simple Demo
![client](https://github.com/Guguant/HomeMonitor/blob/master/demo/client_command.PNG)

![server](https://github.com/Guguant/HomeMonitor/blob/master/demo/test_1.PNG)

# Problems
1. 图像传输数据量太大，一帧 = 640 * 480 * 3 bytes.
2. 采用差值传输方案，需考虑关照因素
3. 数据压缩传输

# Contact
:blush:
E-mail:bearsugar[at]foxmail.com
