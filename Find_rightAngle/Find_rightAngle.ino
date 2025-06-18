/*此代码如名称，利用串口通信的优势，可以达到实时调整伺服舵机旋转角度，便于在安装时快速找到最合适的旋转与复位角度，避免反复修改程序的麻烦*/
#include <Servo.h>    
int angle = 0;       
Servo myServo;        

void setup() {
myServo.attach(8);    //把 数字 8 号引脚绑定到对象里；从此库函数会在8引脚输出PWM
Serial.begin(9600);
}

void loop() {

  while(Serial. available() == 0);    //忙等语句，没收到数据就卡在这里；一旦串口收到任意字节就继续
  angle = Serial.parseInt();          //从缓冲区按十进制解析一个整数：默认遇到 非数字、超时(1 s)、或换行 就结束。读到的数存进 angle 并覆盖旧值。
  Serial.println(angle);              //把收到的值返回到串口监视器
  myServo.write(angle);               //通知 Servo 库产生对应脉冲
}
