// DoorServo.cpp
#include <Arduino.h>        // 提供 delay()、millis() 等 Arduino 核心函数声明
#include "DoorServo.h"

void DoorServo::openThenClose() {
    // 仅在空闲时触发，避免重复 attach
    if (_st == IDLE) {
        _sv.attach(_pin);      // 将 servo 对象绑定到指定引脚
        _sv.write(_openA);     // 舵机转动到打开角度
        _t0 = millis();        // 记录当前时间，用于后续判断保持时长
        _st = OPEN_WAIT;       // 切换到等待关闭状态
    }
}

void DoorServo::update() {
    // 如果处于 OPEN_WAIT 且已过保持时长，则执行关闭动作
    if (_st == OPEN_WAIT && millis() - _t0 >= _hold) {
        _sv.write(0);        // 将舵机旋转回 0°
        delay(1000);          // 给舵机一些时间完成动作，避免立即 detach 导致抖动
        _sv.detach();        // 释放 PWM 输出，节省功耗并避免舵机保持抖动
        _st = IDLE;          // 状态机回到空闲
    }
}