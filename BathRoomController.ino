
const byte lightRelayPin = 16;
const byte fanRelayPin = 14;
const byte sensorPin = 5;

bool sensorStat = false;
bool lightStat = false;
bool fanStat = false;

byte fanDelay = 0;
byte fanDelaySet = 15;
byte lightCounterSet = 60; 
byte fanCounterSet = 90; 

uint16_t lightCounter;
uint16_t fanCounter;

unsigned long lightTimer = 0;
unsigned long fanTimer = 0;
unsigned long sensorTimer = 0;

uint16_t lightInterval = 1000;
uint16_t fanInterval = 1000;
uint16_t sensorInterval = 100;


void getSensorStat() {
  if (millis() - sensorTimer >= sensorInterval) {
    sensorTimer = millis();
    sensorStat = digitalRead(sensorPin);
    if (sensorStat) {
      lightStat = true;
      fanStat = true;
      lightCounter = lightCounterSet;
      fanCounter = fanCounterSet;
    }
  }
}
void lightController() {
  if (lightStat) {
    if (millis() - lightTimer >= lightInterval) {
      lightTimer = millis();
      // printf("lightTimer : %d Sec fanTimer : %d Sec\n", lightCounter, fanCounter);
      lightCounter--;
      digitalWrite(lightRelayPin, HIGH);
    }
    if (lightCounter <= 0) {
      lightStat = false;
      digitalWrite(lightRelayPin, LOW);
    }
  }
}

void fanController() {

  if (fanStat) {
    if (millis() - fanTimer >= fanInterval) {
      fanTimer = millis();
      printf("lightTimer : %d Sec fanTimer : %d Sec\n", lightCounter, fanCounter);
      fanCounter--;
      fanDelay++;
      if (fanDelay >= fanDelaySet) {
        digitalWrite(fanRelayPin, HIGH);
      }
    }
    if (fanCounter <= 0) {
      fanStat = false;
      fanDelay = 0;
      digitalWrite(fanRelayPin, LOW);
    }
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(lightRelayPin, OUTPUT);
  pinMode(fanRelayPin, OUTPUT);

  digitalWrite(lightRelayPin, LOW);
  digitalWrite(fanRelayPin, LOW);
}
void loop() {
  getSensorStat();
  lightController();
  fanController();
}