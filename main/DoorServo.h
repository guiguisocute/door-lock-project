// DoorServo.h， 只是“画出”这个模块的外壳和使用规则，但不写任何逻辑细节。
#pragma once
#include <Servo.h>

// DoorServo 类封装了一个可非阻塞地开门并在指定时间后关门的舵机动作逻辑
class DoorServo {
public:
  /**
   * 构造函数：
   * @param pin    连接到舵机信号线的引脚编号
   * @param openA  打开角度（默认为 90°）
   * @param holdMs 打开后保持时间（毫秒），默认 3000 ms
   */
  DoorServo(uint8_t pin, uint8_t openA = 110, uint16_t holdMs = 3000)
    : _pin(pin), _openA(openA), _hold(holdMs) {}

  /**
   * 触发一次开门动作：舵机会旋转到 openA 角度，并在后续 update() 调用
   * 达到保持时间后自动返回 0°。
   * 只有在当前状态为 IDLE 时才会触发，避免重复 attach。
   */
  void openThenClose();

  /**
   * 放在主循环 loop() 中反复调用，用于管理舵机状态机：
   * - 如果处于 OPEN_WAIT 状态且保持时间到，则执行关门并 detach。
   * - IDLE 状态则不做任何操作。
   */
  void update();

private:
  // 状态机枚举：IDLE（空闲），OPEN_WAIT（等待关闭）
  enum State {IDLE, OPEN_WAIT};

  Servo _sv;          // Servo 对象，用于产生 PWM 波形驱动舵机
  uint8_t _pin;       // 舵机信号线连接引脚
  uint8_t _openA;     // 打开角度
  uint32_t _t0;       // 记录 openThenClose() 时的 millis() 时间戳
  uint32_t _hold;     // 持续保持时间（毫秒）
  State _st = IDLE;   // 初始状态为 IDLE
};