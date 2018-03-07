#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <SD.h>

//Retardo entre cada muestra para evitar bamboleo mecánico
#define DELAY_BETWEEN_SAMPLES 100

// Tamaño de los pasos de YAW / PITCH en grados (1 = resolución completa)
#define YAW_STEP 2
#define PITCH_STEP 2
#define MATH_PI 3.1415f

//Variables
LIDARLite myLidarLite;
Servo servoYaw;
Servo servoPitch;

//variable pololu
const int dirPin = 8;
const int stepPin = 9;

//variables
const int steps = 200;
int microPausa = 10000;
char s[15];
int yawAngle;
int pitchAngle;
int x;
int y;
int z;
int r;
int rojo = 2 ;
int azul = 5;
int verde = 7;

int boton = 6;

float theta;
float phi;
int reemplazo;
boolean bandera = false;
File myFile;

void setup() {
  // Inicialice la conexión en serie para visualizar las lecturas de distancia
  Serial.begin(115200);

  Serial.println("inicializacion exitosa");

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  pinMode(verde, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(rojo, OUTPUT);

  pinMode(boton, INPUT_PULLUP);

  digitalWrite(rojo, HIGH);

  //Servo init
  servoPitch.attach(3);
  
  //Lidar Lite v3 init
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);

  if (!SD.begin(4)) {
    return;
  }
}

void loop() {
  if (digitalRead(boton) == LOW) {
    bandera = true;
    sensar();
  } else {
    Serial.println("stand By");
  }
}

//Función para adquirir, convertir y enviar la medición.
void sendMeasurement() {
  digitalWrite(azul, HIGH);
  myFile = SD.open("log.txt", FILE_WRITE);
  delay(DELAY_BETWEEN_SAMPLES);
  digitalWrite(azul, LOW);
  //Obtener coordenadas esféricas
  r = myLidarLite.distance(false);
  theta = (float)reemplazo * PI / 360.0f;
  phi = (float)pitchAngle * PI / 180.0f;

  // Convertir y enviarlos
  sprintf(s, "%d,%d,%d\n\0", (int)(r * cos(phi)*cos(theta)), (int)(r * cos(phi)*sin(theta)), (int)(r * sin(phi)));
  Serial.print(s);
  myFile.println(s);
  myFile.close();
}

void sensar() {
  myFile = SD.open("xyz.txt", FILE_WRITE);
  delay(5000);// espera

  if (myFile && bandera == true) {

    digitalWrite(rojo, LOW);
    //Barrido Yaw paso a passo
    for (int b = 0; b <= steps; b++) {
      digitalWrite(dirPin, HIGH);//determinas direccion
      reemplazo = b;
      reemplazo = map(reemplazo, 0, 200, 0, 360);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(microPausa);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(microPausa);

      //Sweep Pitch servomotor. The direction depends on the current directory
      if (pitchAngle < 90) {
        for (pitchAngle = 0; pitchAngle <= 180; pitchAngle += PITCH_STEP) {
          servoPitch.write(pitchAngle);
          sendMeasurement();
        }
      } else {
        for (pitchAngle = 180; pitchAngle >= 0; pitchAngle -= PITCH_STEP) {
          servoPitch.write(pitchAngle);
          sendMeasurement();
        }
      }
    }
    digitalWrite(azul, LOW);
    digitalWrite(verde, HIGH);
    bandera = false;
    servoPitch.write(0);

  } else {
    Serial.println("Error al abrir el archivo");
  }
}
