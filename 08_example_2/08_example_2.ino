// Arduino pin assignment
#define PIN_LED  9
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25      // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)
#define _DIST_MIN 100.0   // minimum distance to be measaured (unit: mm)
#define _DIST_MAX 300.0   // maximum distance to be measured (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // maximum echo waiting time (unit: usec)
#define SCALE (0.001 * 0.5 * SND_VEL) // coefficent to convert duration to distance

unsigned long last_sampling_time;   // unit: msec

void setup() {
  // initialize GPIO pins
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // sonar TRIGGER
  pinMode(PIN_ECHO, INPUT);   // sonar ECHO
  digitalWrite(PIN_TRIG, LOW);  // turn-off Sonar 
  
  // initialize serial port
  Serial.begin(57600);
}

void loop() {
  float distance;
  int light;
  // 다음 샘플링 시간까지 기다립니다 
  // millis()는 프로그램이 시작된 이후의 밀리초 수를 반환합니다
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance

  if (distance <= 100) {
      distance = _DIST_MIN - 10.0;     // Set Higher Value
      light = 255; 
  }else if(distance <= 200){
       light = 255 - int((distance - 100) * (255 / 100));
  }
  else if (distance <= 300){
      light = int((distance - 200) * (255 / 100));          
  }
  else if (distance <= 0.0 || distance >= 300.0){
    distance = _DIST_MAX + 10.0; 
    light = 255;
  }
  else {
    light = 255;
  }
  analogWrite(PIN_LED, light);  
  

  // 직렬 포트까지의 거리를 출력
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.print(",LED:");       Serial.print(light); 
  Serial.println("");
  
  // 마지막 샘플링 시간 업데이트
  last_sampling_time += INTERVAL;
}

// USS로부터 거리 판독을 받으세요. 반환 값은 밀리미터 단위입니다.
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}
