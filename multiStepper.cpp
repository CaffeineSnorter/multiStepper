/*
   ============================================================================
                           ¡¡D I S C L A I M E R!!
   ============================================================================

   Estas a punto de leer el codigo más perro puerco de tu vida
   si por alguna razón lo llegas a leer sientete libre de
   mentarme la madre o enviarme una critica constructiva a:

            Caffeine.Snorter@gmail.com

  ==============================================================================
  ==============================================================================

   multiStepper.cpp - Libreria hecha con las patas para controlar motores a pasos

   28BYJ_48 con controlador ULN2003
   NEMA 17 con controlador a4988

   Creado por CaffeineSnorter
*/

#include "multiStepper.h"

multiStepper::multiStepper(String motorType_, int maxFreq_, int A_, int B_, int C_, int D_) {

  A = A_;
  B = B_;
  C = C_;
  D = D_;

  motorType = motorType_;
  //stepsPerRev = stepsPerRev_;
  maxFreq = maxFreq_;
}

multiStepper::multiStepper(String motorType_, int maxFreq_, int stepPin_, int dirPin_) {

  stepPin = stepPin_;
  dirPin = dirPin_;

  motorType = motorType_;
}

void multiStepper::init() {

  Serial.begin(9600);

  if (motorType == "28BYJ_48") {

    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);

    minDelayPerRev = (1000 / maxFreq);

    cyclesPerRev = 8;
    turnsPerRev = 64;

  }

  else if (motorType == "a4988") {

    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    minDelayPerRev = (1 / maxFreq) * 1000;
  }
}

/*void multiStepper::setRPM(int RPM_) {
  switch (motorType){
    case "28BYJ_48":

    }
  }*/

void multiStepper::fullStepLowTorque(int RPM_, int steps_) {
  //Serial.println(motorType);
  if (motorType == "28BYJ_48") {

    cycles = 4;

    stepsPerRev = cycles * cyclesPerRev * turnsPerRev;
    delayPerRev = 60 * 1000L / (RPM_ * double(stepsPerRev));

    //Serial.print("delayPerRev: "); Serial.println(delayPerRev);
    if (ceil(delayPerRev) < minDelayPerRev) {
      int maxRPM = ceil(60 * 1000L / (minDelayPerRev * stepsPerRev));

      Serial.println("fullStepLowTorque() - RPM Error:  set RPMs exceed max RPM supported by the device");
      Serial.print("Max RPM for 28BYJ_48 device is: "); Serial.println(maxRPM);
      Serial.print("Change the code to continue...");
      while (true) {};
    }

    for (int p = 0; p <= steps_; p++) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(A, pgm_read_byte_near(&fSLT_array[i][0]));
        digitalWrite(B, pgm_read_byte_near(&fSLT_array[i][1]));
        digitalWrite(C, pgm_read_byte_near(&fSLT_array[i][2]));
        digitalWrite(D, pgm_read_byte_near(&fSLT_array[i][3]));
        delay(int(delayPerRev));
      }
    }
  }
}

void multiStepper::fullStepHighTorque(int RPM_, int steps_) {
  if (motorType == "28BYJ_48") {

    cycles = 4;

    stepsPerRev = cycles * cyclesPerRev * turnsPerRev;
    delayPerRev = 60 * 1000L / (RPM_ * double(stepsPerRev));

    //Serial.print("delayPerRev: "); Serial.println(delayPerRev);
    if (ceil(delayPerRev) < minDelayPerRev) {
      int maxRPM = ceil(60 * 1000L / (minDelayPerRev * stepsPerRev));

      Serial.println("fullStepHighTorque() - RPM Error:  set RPMs exceed max RPM supported by the device");
      Serial.print("Max RPM for 28BYJ_48 device is: "); Serial.println(maxRPM);
      Serial.print("Change the code to continue...");
      while (true) {};
    }

    for (int p = 0; p <= steps_; p++) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(A, pgm_read_byte_near(&fSHT_array[i][0]));
        digitalWrite(B, pgm_read_byte_near(&fSHT_array[i][1]));
        digitalWrite(C, pgm_read_byte_near(&fSHT_array[i][2]));
        digitalWrite(D, pgm_read_byte_near(&fSHT_array[i][3]));
        delay(int(delayPerRev));
      }
    }
  }
}

void multiStepper::halfStep(int RPM_, int steps_ ) {

  if (motorType == "28BYJ_48") {
    cycles = 8;

    stepsPerRev = cycles * cyclesPerRev * turnsPerRev;
    delayPerRev = 60 * 1000L / (RPM_ * double(stepsPerRev));

    //Serial.print("delayPerRev: "); Serial.println(delayPerRev);
    if (ceil(delayPerRev) < minDelayPerRev) {
      int maxRPM = ceil(60 * 1000L / (minDelayPerRev * stepsPerRev));

      Serial.println("fullStepLowTorque() - RPM Error:  set RPMs exceed max RPM supported by the device");
      Serial.print("Max RPM for 28BYJ_48 device is: "); Serial.println(maxRPM);
      Serial.print("Change the code to continue...");
      while (true) {};
    }

    for (int p = 0; p <= steps_; p++) {
      for (int i = 0; i < 8; i++) {
        digitalWrite(A, pgm_read_byte_near(&fSLT_array[i][0]));
        digitalWrite(B, pgm_read_byte_near(&fSLT_array[i][1]));
        digitalWrite(C, pgm_read_byte_near(&fSLT_array[i][2]));
        digitalWrite(D, pgm_read_byte_near(&fSLT_array[i][3]));
        delay(int(delayPerRev));
      }
    }
  }
}
