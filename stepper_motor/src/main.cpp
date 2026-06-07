#include <Arduino.h>

// ULN2003 驱动板 → ESP32 引脚连接
// IN1 → GPIO18, IN2 → GPIO19, IN3 → GPIO21, IN4 → GPIO22
const int PIN1 = 18;
const int PIN2 = 19;
const int PIN3 = 21;
const int PIN4 = 22;

// 28BYJ-48 步进电机转一整圈需要 2048 步
const int STEPS_PER_REVOLUTION = 2048;

// 每步之间的延迟（毫秒），越小转得越快
int motorSpeed = 2;

// ---- 步进序列 ----
// 用二维数组定义每一步四个引脚的输出电平
// 正转：stepSequence[0]→[1]→[2]→[3]→[0]→...
// 反转：stepSequence[3]→[2]→[1]→[0]→[3]→...
const int STEP_SEQUENCE[4][4] = {
  // IN1, IN2, IN3, IN4   (GPIO18, GPIO19, GPIO21, GPIO22)
  { LOW,  LOW,  HIGH, HIGH },   // 第 0 步 →  0011
  { LOW,  HIGH, HIGH, LOW  },   // 第 1 步 →  0110
  { HIGH, HIGH, LOW,  LOW  },   // 第 2 步 →  1100
  { HIGH, LOW,  LOW,  HIGH },   // 第 3 步 →  1001
};

// 把四个引脚的电平设置到对应的步进序列
void setMotorStep(int step) {
  digitalWrite(PIN1, STEP_SEQUENCE[step][0]);
  digitalWrite(PIN2, STEP_SEQUENCE[step][1]);
  digitalWrite(PIN3, STEP_SEQUENCE[step][2]);
  digitalWrite(PIN4, STEP_SEQUENCE[step][3]);
}

// 顺时针旋转指定步数
void rotateClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    setMotorStep(i % 4);   // 0 → 1 → 2 → 3 → 0 → ...
    delay(motorSpeed);
  }
}

// 逆时针旋转指定步数
void rotateCounterClockwise(int steps) {
  for (int i = 0; i < steps; i++) {
    setMotorStep(3 - (i % 4));   // 3 → 2 → 1 → 0 → 3 → ...
    delay(motorSpeed);
  }
}

void setup() {
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);

  Serial.begin(115200);
  Serial.println("=== 步进电机控制就绪 ===");
  Serial.print  ("接线：IN1→GPIO18  IN2→GPIO19  IN3→GPIO21  IN4→GPIO22\n");
  Serial.print  ("转速: ");
  Serial.print  (motorSpeed);
  Serial.println("ms/步\n");
}

void loop() {
  Serial.println("正转一圈 (2048步)...");
  rotateClockwise(STEPS_PER_REVOLUTION);
  Serial.println("√ 完成\n");

  delay(1000);   // 停顿 1 秒

  Serial.println("反转一圈 (2048步)...");
  rotateCounterClockwise(STEPS_PER_REVOLUTION);
  Serial.println("√ 完成\n");

  delay(1000);   // 停顿 1 秒
}
