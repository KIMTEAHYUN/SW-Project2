// LED 핀 설정
const int LED_PIN = 7;
int toggle = 0;  
void setup() {
  // LED 핀을 출력으로 설정
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // LED 켜기
  digitalWrite(LED_PIN, 0);
  delay(1000); // 1초 동안 유지

  // LED 끄기
  digitalWrite(LED_PIN, 1);
  delay(1000); // 1초 동안 유지

  // 5회 깜빡이기
  for (int i = 0; i < 10; i++) {
    digitalWrite(LED_PIN, toggle);
    toggle = 1 - toggle;
    delay(200); // 0.2초 동안 유지
  }

  while(1){ 
    ;
  }
}
