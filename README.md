# Description

Simple ROS listener to write messages to LCD1602 display, connected via I2C.
I'm using it with Jetson Nano, with display connected to pins 27 and 28 (I2C).

Uses GPL library from BitBank Software, written by Larry Bank.

Usage:
```
$ rosrun lcd1602_driver lcd1602_driver
...
$ rostopic pub /lcd1602 std_msgs/String -1 "Hello world"
$ rostopic pub /lcd1602 std_msgs/String -1 -f multiline.txt
```

Where `multiline.txt` contains two lines with extra linefeed:
```
First line

Second line
```
