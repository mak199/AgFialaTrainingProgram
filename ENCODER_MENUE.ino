//void lcdMsg(String msg,String msg2);
String typeOfProgram[3] = { "P-P", "P-U", "U-P" };
String programs[6] = {"A","B","C","D","E","F"};
int programNumber = 0;
int programTypeNumber = 0;

void ENCODER_MENUE () {
  foc_params_changed = false;
  soc_params_changed = false;

  // the switch calls the function depending on the current program visible on the LCD of hardware
  // the switch also calls a method to display message to LCD of hardware 
  // encoder_wert is updated when switch is turned
  switch(encoder_wert)
  {
      case 0 : encoder_wert = 1;                  break;  
      case 1 : lcdMsg("Program Type1            ","P-P       ");SELECT_PROGRAM();programTypeNumber = 1; break;  
      case 2 : lcdMsg("Program Type2     ","P-U        "); SELECT_PROGRAM();programTypeNumber = 2;break; 
      case 3 : lcdMsg("Program Type3           ","U-P       ");SELECT_PROGRAM();programTypeNumber = 3;break;  
      default: encoder_wert = 1;                  break; 
  }
  Serial.println(encoder_wert);
}


void SELECT_PROGRAM () {

  Serial.println("hello");
  float timer = 0;
  
  encoder_tast = digitalRead(ENCODER_TAST);
  if (encoder_tast == ECT_GEDRUECKT){       
     waitForButtonRelease();
     encoder_wert = 1;
     while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
        switch(encoder_wert)
        {   case 0 : encoder_wert = 7;                  break;  
            case 1 : lcdMsg("Program: A",typeOfProgram[programTypeNumber-1]);programNumber = 1;SELECT_PROTOCOL();break;  
            case 2 : lcdMsg("Program: B     ",typeOfProgram[programTypeNumber-1]); programNumber = 2;SELECT_PROTOCOL();break; 
            case 3 : lcdMsg("Program: C           ",typeOfProgram[programTypeNumber-1]);programNumber = 3;SELECT_PROTOCOL();break;  
            case 4 : lcdMsg("Program: D           ",typeOfProgram[programTypeNumber-1]);programNumber = 4;SELECT_PROTOCOL();break;   
            case 5 : lcdMsg("Program: E       ",typeOfProgram[programTypeNumber-1]);programNumber = 5;SELECT_PROTOCOL();break;  
            case 6 : lcdMsg("Program: F       ",typeOfProgram[programTypeNumber-1]);programNumber = 6;SELECT_PROTOCOL();break; 
            case 7 : lcdMsg("EXIT      ",typeOfProgram[programTypeNumber-1]);break; 
            default: encoder_wert = 1;                  break; 
        }
        Serial.println(encoder_wert);
         if(encoder_wert==7){
             delay(25);
             encoder_tast = digitalRead(ENCODER_TAST);
         }
     }
      waitForButtonRelease();


 }
 
}//###############################################
void SELECT_PROTOCOL(){

    float timer = 0;
    encoder_tast = digitalRead(ENCODER_TAST);
    if (encoder_tast == ECT_GEDRUECKT){       
       waitForButtonRelease();
       encoder_wert = 1;
       while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
         switch(encoder_wert)
         {  case 0 : encoder_wert = 5;                  break;  
            case 1 : lcdMsg("FOC Program          ",typeOfProgram[programTypeNumber-1]);callFOC();break;  
            case 2 : lcdMsg("SOC Program          ",typeOfProgram[programTypeNumber-1]);callSOC();break; 
            case 3 : lcdMsg("Change FOC parameters       ",typeOfProgram[programTypeNumber-1]);foc_params_changed = FOC_CHANGE_PARAMETERS();break; 
            case 4 : lcdMsg("Change SOC parameters       ",typeOfProgram[programTypeNumber-1]);soc_params_changed = SOC_CHANGE_PARAMETERS();break; 
            case 5 : lcdMsg("EXIT                ",typeOfProgram[programTypeNumber-1]);break; 
            default: encoder_wert = 1;                  break; 
         }
         Serial.println(encoder_wert);
         if(encoder_wert==5){
             delay(25);
             encoder_tast = digitalRead(ENCODER_TAST);
         }
        
       }
       waitForButtonRelease();
    }
    // return program to first program A

    

}

void callFOC(){
  switch(programTypeNumber){
    case 1:FOC_TYPE1();break;
    case 2:FOC_TYPE2();break;
    case 3:FOC_TYPE3();break;
    default:break;
  }
}

void FOC_TYPE1(){
  boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!foc_params_changed){
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE1();break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE1();break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE1();break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE1();break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE1();break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE1();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE1(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          default: programNumber = 0;
        }
      }
      if(complete){
        break;
      }
      //delay(25);
      //encoder_tast = digitalRead(ENCODER_TAST);
    }
    waitForButtonRelease();
  }
  
}

void FOC_TYPE2(){
  boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    Serial.println("In FOC");
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!foc_params_changed){
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE2();break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE2();break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE2();break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE2();break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE2();break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE2();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE2(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          default: programNumber = 0;
        }
      }
      if(complete){
        break;
      }
      //delay(25);
      //encoder_tast = digitalRead(ENCODER_TAST);
    }
    waitForButtonRelease();
  }

  
}

void FOC_TYPE3(){
  boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    Serial.println("In FOC");
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!foc_params_changed){
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE3();break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE3();break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE3();break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE3();break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE3();break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE3();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_1,VALVE_2); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_2,VALVE_1); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_1,VALVE_3); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_3,VALVE_1); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_2,VALVE_3); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_3,VALVE_2); complete = FOC_Program_TYPE3(odor1_duration,odor2_duration,odor5_duration,odor5_duration_2,shock_duration);break;
          default: programNumber = 0;
        }
      }
      if(complete){
        break;
      }
      //delay(25);
      //encoder_tast = digitalRead(ENCODER_TAST);
    }
    waitForButtonRelease();
  }

  
}

void setFOC_SOC_Odor(int val1,int val2){
  Serial.println("Odor value set");
  valve_num1 = val1;
  valve_num2 = val2;
}
void callSOC(){
  switch(programTypeNumber){
    case 1:SOC_TYPE1();break;
    case 2:SOC_TYPE2();break;
    case 3:SOC_TYPE3();break;
    default:break;
  }
}


void SOC_TYPE1(){
  boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    Serial.println("In SOC");
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!soc_params_changed){
         switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE1();break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE1();break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE1();break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE1();break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE1();break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE1();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE1(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          default: programNumber = 0;
        }
      }
     
      if(complete){
        break;
      }
    }
    waitForButtonRelease();
  }
  
  
}


void SOC_TYPE2(){
     boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    Serial.println("In SOC");
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!soc_params_changed){
         switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE2();break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE2();break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE2();break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE2();break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE2();break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE2();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE2(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          default: programNumber = 0;
        }
      }
     
      if(complete){
        break;
      }
    }
    waitForButtonRelease();
  }
}


void SOC_TYPE3(){
     boolean complete = false;
  if(digitalRead(ENCODER_TAST)==ECT_GEDRUECKT){
    Serial.println("In SOC");
    waitForButtonRelease();
    while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
      if(!soc_params_changed){
         switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE3();break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE3();break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE3();break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE3();break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE3();break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE3();break;
          default: programNumber = 0;
        }
      }
      else{
        switch(programNumber){
          case 1: setFOC_SOC_Odor(VALVE_3,VALVE_1);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 2: setFOC_SOC_Odor(VALVE_3,VALVE_2);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 3: setFOC_SOC_Odor(VALVE_2,VALVE_1);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 4: setFOC_SOC_Odor(VALVE_2,VALVE_3);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 5: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          case 6: setFOC_SOC_Odor(VALVE_1,VALVE_2);complete = SOC_Program_TYPE3(odor1_duration,odor3_duration,odor5_duration,pulse_duration);break;
          default: programNumber = 0;
        }
      }
     
      if(complete){
        break;
      }
    }
    waitForButtonRelease();
  }
}

void waitForButtonRelease(){
   while (encoder_tast == ECT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
   {
    delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
    encoder_tast = digitalRead(ENCODER_TAST); 
   }
  
}

// following method is to print message on LCD of the hardware
void lcdMsg(String msg,String msg2){
   //lcd.clear();
   lcd.home();                               //Curser in die obere linke Ecke 
   lcd.print(msg+"        ");              //Schrift für die erste zeile senden
   lcd.setCursor(0,1);                       //Curser in die 2te  Zeile legen
   lcd.print(msg2);              //Schrift für die erste zeile senden
}
