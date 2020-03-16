
/**************************************************************************************************************************************************
   2019041701 Olafktometer Schock

   Author: Jan Hoffmann,Muhammad Afaque Khan
   
   Date: 2019.06.03
   
***************************************************************************************************************************************************/

/////////////
// IMPORTS //
/////////////
#include <MsTimer2.h>                                //Library that calls function in a time interval
#include <LiquidCrystal.h>                           //Library for LCD blinking
#include <EEPROM.h>                                  //Bibliotek für das interne EEPROM einbinden





void ENCODER_AUSWERTUNG ();
void EINRICHTUNG();
////////////////////
// INPUT & OUTPUT //
////////////////////

//Following pins/variables are used to define input and output of the hardware
// Pinning Map
int ENCODER_B          = 0;
//int                    = 1;
int OPTIONAL_IO        = 2; // EXT Inerrupt 1
int ENCODER_A          = 3; // EXT Inerrupt 0
int ENCODER_TAST       = 4;
//                       5 = LCD RS
int VALVE_2            = 6; // HIGH = ON
int TRIGGER_SCHOCK     = 7; // HIGH = ON  // EXT Inerrupt 4
int VALVE_3            = 8; // HIGH = ON
int VALVE_4            = 9; // HIGH = ON
int VALVE_5            = 10;// HIGH = OFF Frischluft 
//int                    = 11;
int VALVE_1            = 12;// HIGH = ON
//                       13 = LCD D7

int valve_num1 = 0;
int valve_num2 = 0;
boolean foc_params_changed = false;
boolean soc_params_changed = false;

// Function prototype to provide information to compiler about function defined later
// Default parameters have been given to prototype functions
// If the functions are called without any parameters then default functions are used by the function.Eg:firstOrderConditioning()
// If functions are called with parameters then those parameters are used by the called function.Eg:firstOrderConditioning(40,10,50,60,30)
boolean FOC_Program_TYPE1(int odor1 = 60,int odor2 = 60,int odor5 = 90,int odor5_2 = 45,int shock = 1000);
boolean SOC_Program_TYPE1(int odor1 = 60,int odor3 = 7,int odor5 = 90,int pulse_dur = 1000);

boolean FOC_Program_TYPE2(int odor1 = 60,int odor2 = 60,int odor5 = 90,int odor5_2 = 45,int shock = 1000);
boolean SOC_Program_TYPE2(int odor1 = 60,int odor3 = 7,int odor5 = 90,int pulse_dur = 1000);

boolean FOC_Program_TYPE3(int odor1 = 60,int odor2 = 60,int odor5 = 90,int odor5_2 = 45,int shock = 1000);
boolean SOC_Program_TYPE3(int odor1 = 60,int odor3 = 7,int odor5 = 90,int pulse_dur = 1000);

LiquidCrystal lcd(A4,A3,A2,A1,A0,13);                //Pinbelegeung für das LCD definieren LiquidCrystal name(rs,enable,D4,D5,D6,D7);
/*                |  |  |  |  |  |-------------------D7
                  |  |  |  |  |----------------------D6
                  |  |  |  |-------------------------D5
                  |  |  |----------------------------D4
                  |  |-------------------------------enable
                  |----------------------------------rs */
   

///////////////////////////
// VARIABLES & CONSTANTS //
///////////////////////////

int JA = HIGH;
int NEIN = LOW;
int AN = HIGH;
int AUS = LOW;

int encoder_tast = 0;
int encoder_wert = 0; // variable to store current value of program selected from the hardware switch
int parameter_wert = 0; // variable to store the current value of paramters in the program from the hardware switch
boolean interrupt_occured = false;

int einmal = LOW;
int abgeschlossen = HIGH;


int ECT_GEDRUECKT = LOW;
int ECT_NICHT_GEDRUECKT = HIGH;

int time_count = 0;

// Global variables that hold the value of odor duration and shock duration 
int odor1_duration = 0;
int odor2_duration = 0;
int odor3_duration = 0;
int odor4_duration = 0;
int odor5_duration = 0;
int odor5_duration_2 = 0;
int shock_duration = 0;
int pulse_duration = 0;



int TP = 25;
// Eigene LCD Zeichen************************************************************

byte JH[8] = {  //Zeichen defenieren
  B00000,//
  B11111,//#####
  B00100,//  #
  B11111,//#####
  B10101,//# # #
  B10111,//# ###
  B00000,//
};





void setup() {
  

//  PIN als Ein/Ausgang Definieren ###############################################################################################

  attachInterrupt(0,ENCODER_AUSWERTUNG,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
 // attachInterrupt(5,ENCODER_AUSWERTUNG, CHANGE);              //  OPTIONAL_IO ISR
  
  pinMode     (ENCODER_B, INPUT);
  digitalWrite(ENCODER_B, HIGH);

  pinMode     (ENCODER_A, INPUT);
  digitalWrite(ENCODER_A, HIGH);

  pinMode     (ENCODER_TAST, INPUT);
  digitalWrite(ENCODER_TAST, HIGH);

  pinMode     (VALVE_1, OUTPUT);
  digitalWrite(VALVE_1, LOW);  
  
  pinMode     (VALVE_2, OUTPUT);
  digitalWrite(VALVE_2, LOW); 

  pinMode     (VALVE_3, OUTPUT);
  digitalWrite(VALVE_3, LOW); 

  pinMode     (VALVE_4, OUTPUT);
  digitalWrite(VALVE_4, LOW); 

  pinMode     (VALVE_5, OUTPUT);
  digitalWrite(VALVE_5, LOW); 

  pinMode     (TRIGGER_SCHOCK, OUTPUT);
  digitalWrite(TRIGGER_SCHOCK, LOW);  

  pinMode     (OPTIONAL_IO, OUTPUT);
  digitalWrite(OPTIONAL_IO, HIGH);  
    
 // MsTimer2::set(500, TimerISR); // 500ms period

  Serial.begin(9600);                              // Serielle Komunikation Starten

  lcd.begin(16, 2);                                  //Größe des LCD definieren 16 Zeichen pro Zeile 2 Zeilen


}//+++++++++++++++++++++++Ende Setup++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// the program continuously loops in this method
void loop() {
  //if statement is only checked once
  if (einmal != abgeschlossen)
  {
  EINRICHTUNG ();    
  }

  // the function called is to check the program selected using the hardware switch
  ENCODER_MENUE ();

}//+++++++++++++++++++++++Ende der Loop++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
