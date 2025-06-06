/*
   multiStepper.h - Libreria hecha con las patas para controlar motores a pasos
   multiStepper.h - Poorly made library aimed to control stepper motors

   28BYJ_48 con controlador ULN2003
   NEMA 17 con controlador a4988

   Creado por CaffeineSnorter
   Created by CaffeineSnorter
*/

#ifndef multiStepper_h
#define multiStepper_h

#if (ARDUINO >= 100)
#include "Arduino.h"

#else
#include "WProgram.h"

#endif

//Variables Globales

const byte fSLT_array[4][4] PROGMEM = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};
const byte fSHT_array[4][4] PROGMEM = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};
const byte hS_array[8][4] PROGMEM = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

//byte stepLogic;

class multiStepper {

  private:

    //Variables privadas

    //Pines de motor
    int A;
    int B;
    int C;
    int D;
    int stepPin;
    int dirPin;

    //Parametros del Motor
    String motorType;
    long int stepsPerRev = 0;
    int RPM = 0;
    int steps = 0;
    int maxFreq = 0;
    float delayPerRev = 0;
    float minDelayPerRev = 0;
    int cyclesPerRev;
    int turnsPerRev;
    int cycles;


  public:

    //Constructor
    multiStepper(String motorType_, int maxFreq_, int A_, int B_, int C_, int D_);

    multiStepper(String motorType_, int stepPin_, int dirPin_);

    //metodos
    void init();
    //void setRPM(int RPM_);
    void fullStepLowTorque(int RPM_, int steps_ = 2048);
    void fullStepHighTorque(int RPM_, int steps_ = 2048);
    void halfStep(int RPM_, int steps_ = 4096);
};

#endif
