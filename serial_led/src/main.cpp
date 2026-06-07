#include <Arduino.h>

// LED 引脚定义（和流水灯项目接线一致）
const int LED_PINS[] = {2, 4, 5, 18};
const int LED_COUNT = 4;

// 每颗 LED 当前状态（HIGH=亮, LOW=灭）
int ledState[4] = {LOW, LOW, LOW, LOW};

void setup() {
  // 初始化所有 LED 引脚为输出，初始熄灭
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  // 初始化串口
  Serial.begin(115200);
  Serial.println("=== 串口 LED 控制器已就绪 ===");
  Serial.println("指令说明：发送 1~4 切换对应 LED 的亮灭状态");
  Serial.println("示例：发送字符 '1' 切换 LED1（GPIO2）\n");
}

void loop() {
  // 检查串口是否有数据到达
  if (Serial.available() > 0) {
    // 读取一个字节，就是用户发送的 ASCII 字符
    char cmd = Serial.read();

    // 计算指令对应的 LED 索引（'1'→索引0, '2'→索引1, ...）
    int ledIndex = cmd - '1';  // 巧妙：字符相减得到数字

    // 判断指令是否在有效范围
    if (ledIndex >= 0 && ledIndex < LED_COUNT) {
      // 切换该 LED 状态
      ledState[ledIndex] = !ledState[ledIndex];
      digitalWrite(LED_PINS[ledIndex], ledState[ledIndex]);

      // 向串口助手回传执行结果
      Serial.print("LED");
      Serial.print(ledIndex + 1);  // +1 恢复成人类习惯的编号
      if (ledState[ledIndex] == HIGH) {
        Serial.println("亮");
      } else {
        Serial.println("灭");
      }
    }
    // 指令无效（比如发 '5', 'a', '4' 当前只配了4颗LED）→ 不执行任何动作

    // 吞掉可能跟在后面的换行符，避免下次误读
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
