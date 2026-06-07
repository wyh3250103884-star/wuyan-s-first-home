#include <Arduino.h>

// 流水灯连接的 GPIO 引脚（从左到右排列）
const int LED_PINS[] = {2, 4, 5, 18};
const int LED_COUNT = 4;

// 流水速度（毫秒），改这个值就能调节快慢
int flowDelay = 150;

void setup() {
  // 把所有 LED 引脚设为输出模式
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);  // 初始全部熄灭
  }
}

void loop() {
  // 阶段1：依次点亮
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(flowDelay);
  }
  // 阶段2：依次熄灭
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
    delay(flowDelay);
  }
}
