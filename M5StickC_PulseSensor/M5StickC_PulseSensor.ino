#include <M5StickC.h>
#include <PulseSensorPlayground.h>

const int PULSE_INPUT = 26; // Pulse Sensor输入引脚，根据你的连接修改
const int THRESHOLD = 550;  // 设定一个阈值，这个阈值依赖于你的环境和传感器放置

PulseSensorPlayground pulseSensor;

void setup() {
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.setRotation(3); // 根据需要调整屏幕方向
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextSize(2.8);
  M5.Lcd.setTextColor(WHITE);

  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.setThreshold(THRESHOLD);

  if (!pulseSensor.begin()) {
    Serial.println("Could not find a PulseSensor.");
    while (1); // 如果没有找到传感器，无限循环
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) { // 如果检测到心跳开始
    int heartRate = pulseSensor.getBeatsPerMinute(); // 读取心率值

    M5.Lcd.fillScreen(BLACK); // 清屏
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.print("Heart Rate:");
    M5.Lcd.print(heartRate);
    M5.Lcd.println("BPM");

    Serial.print("Heart Rate:");
    Serial.print(heartRate);
    Serial.println("BPM");
  }
  delay(20);
}
