
#include <Servo.h>

// ULTRASSONICO
const int trigPin = 9;
const int echoPin = 10;

// LEDS E BUZZER
const int ledVerde = 2;
const int ledVerm = 3;
const int buzzer = 4;

// SERVO
const int pinServo = 11;

const float limiteDistancia = 15.0;

Servo servo;

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 10000);

  if (duracao == 0) {
    return -1;
  }

  return duracao * 0.0343 / 2;
}

void lerSensor(int angulo) {
  float distancia = medirDistancia();

  Serial.print("Angulo: ");
  Serial.print(angulo);
  Serial.print(" | Distancia: ");

  if (distancia < 0) {
    Serial.println("Sem retorno");
  } 
  else {
    Serial.print(distancia, 1);
    Serial.println(" cm");
  }

  // DETECCAO DE OBSTACULOS
  if (distancia > 0 && distancia <= limiteDistancia) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVerm, HIGH);

    // Som agudo
    tone(buzzer, 2500);
  } 
  else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVerm, LOW);

    noTone(buzzer);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVerm, OUTPUT);
  pinMode(buzzer, OUTPUT);

  servo.attach(pinServo);
  servo.write(0);

  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVerm, LOW);
  noTone(buzzer);

  delay(1000);
}

void loop() {
  // VARREDURA DE 0 A 180 GRAUS
  for (int a = 15; a <= 165; a++) {
    servo.write(a);
    lerSensor(a);
  }

  // VARREDURA DE 180 A 0 GRAUS
  for (int a = 165; a >= 15; a--) {
    servo.write(a);
    lerSensor(a);
  }
}
