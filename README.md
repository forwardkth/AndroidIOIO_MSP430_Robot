# AndroidIOIO_MSP430_Robot
Introduction of the project         http://forwardkth.github.io/2015/08/27/tele-robot-1/

## Description:

This is my first generation Tele-operation robot  built during 2014. Now I have  already had my second generation robot with pure Linux OS. But the first one is still a interesting try.

The old google Nexus android phone is used as the controller as well as wireless communication module.&ensp The [IOIO-OTG](https://github.com/ytai/ioio/wiki) Open source board is employed to be the interface between android OS and other devices. Another Experimental board **EXP F5438** with  TI MSP430 F5438 mcu is connected with the IOIO board through RX/TX.

Maybe you have question like "this MSP430 board is not needed or not necessary". Yes, you are right. The IOIO board is enough for basic GPIOs, PWM control and so on. But this robot is my  experimental platform. 
It means that I would like to construct it as complex as this in order to do more experiments and explore more possibilities. 

The EXP F5438 board running uCOS II real-time operation system does all the real-time control job e.g motor control, sensor data capture, control other executer.
And the Android phone can focus its work on video, audio streaming, data communication, receiving orders from my laptop. On my laptop I write a GUI with JAVA as control terminal which communicate through WIFI with my Anroid controller APP.

The whole structure is not difficult to understand. But as we known, more complex  the system is, the more problem will happen. you will never know them until you actually debug it.

## Pictures:
![](http://ww3.sinaimg.cn/bmiddle/74505a4cgw1eddsn5e4qpj216n68t4qr.jpg)

## DEMO videos:

DEMO video in Youtube:
https://www.youtube.com/embed/vaqixZOrqzM