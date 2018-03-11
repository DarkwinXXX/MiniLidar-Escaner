#include <Servo.h>
#include <Wire.h>
#include <LIDARLite.h>
#include <SD.h>

//Retardo entre cada muestra para evitar bamboleo mecánico
#define DELAY_BETWEEN_SAMPLES 100

// Tamaño de los pasos de YAW / PITCH en grados (1 = resolución completa)
#define PITCH_STEP 1
#define MATH_PI 3.1415f
#define GRAD2RAD 0.0174533f

//Variables
PasosStepper = 200; //modificar si se usa micropasos
AngPasos = PasosStepper / 360f; //calculo grados por cada paso= nº de pasos que dará el motor dividido por 360º

LIDARLite myLidarLite;
r = myLidarLite.distance();
//theta es el ángulo de giro en X
theta = (float)AngPasos acumulado por cada paso!; 
//theta = (float)reemplazo * PI / 360.0f;
//phi es al ángulo de giro entre Y y Z
phi = (float)AngPasos acumulado por cada paso!;
//phi = (float)pitchAngle * PI / 160.0f;

//Conversión de grados a radianes
thetarad = (float)theta * GRAD2RAD;
phirad = (float)phi * GRAD2RAD;

// Calcular y enviarlos
sprintf(s, "%d,%d,%d\n\0", (int)(r * cos(phiard)*cos(thetarad)), (int)(r * cos(phirad)*sin(thetarad)), (int)(r * sin(phirad)));
 
Serial.print(s);
Serial.print(" - ");
Serial.println(myLidarLite.distance()); 
 
myFile.println(s);
myFile.close();
}

void sensar() {
  myFile = SD.open("log.txt", FILE_WRITE);
  delay(5000);// espera

  if (myFile && bandera == true) {

    digitalWrite(rojo, LOW);
    //Barrido Yaw servomotor
    for (int b = 0; b <= PasosStepper; b++) {
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
