// this function is called by attachInterrupt when switch is turned to select a program from the hardware
void ENCODER_AUSWERTUNG(){
  
  boolean Aread = false;
  boolean Bread = false;
  boolean Cread = false;
  Aread=digitalRead(ENCODER_A);
  Bread=digitalRead(ENCODER_B);

  // user can select between 6 programs 
  if ((Aread==true && Bread==false) || (Aread==false && Bread==true)){
    if(encoder_wert <= 7 and encoder_wert >= 0){
      encoder_wert++;
      Serial.println(encoder_wert);
    }    
    Serial.println("hello");
  }
  if ((Aread==false && Bread==false) || (Aread==true&& Bread==true)){
    if(encoder_wert>0 and encoder_wert <= 7){
      Serial.println(encoder_wert);
      encoder_wert--;
    }
    Serial.println("Hello");
  }

  
}

// this function is called by attachInterrupt when the switch is turned to select the parameters for a protocol in FOC and SOC editable programs
void SELECT_PARAMETERS (){
  boolean Aread = false;
  boolean Bread = false;
  boolean Cread = false;
  Aread=digitalRead(ENCODER_A);
  Bread=digitalRead(ENCODER_B);

  interrupt_occured = true;

  // the user can select the parameters between 0 and 90
  if ((Aread==true && Bread==false) || (Aread==false && Bread==true)){
    if(parameter_wert <= 90 and parameter_wert >= 0){
      parameter_wert++;
    }
    
    
  // the user can select the parameters between 0 and 90
  }
  if ((Aread==false && Bread==false) || (Aread==true&& Bread==true)){
    if(parameter_wert>0 and parameter_wert <= 90){
      parameter_wert--;
    }
    
  }

  
}
