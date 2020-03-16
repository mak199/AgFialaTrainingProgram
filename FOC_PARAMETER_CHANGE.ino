// this function is used to select the parameters for FOC program
boolean FOC_CHANGE_PARAMETERS(){

    // Reads the value of button 0 or 1
    encoder_tast = digitalRead(ENCODER_TAST);
    // Checks if the button was pressed or not
    if (encoder_tast == ECT_GEDRUECKT){
 

       // the program needs to wait for the user to release the hardware button after selecting the current program
       //waitForButtonRelease();

       
       // the interrupt must be changed to call SELECT_PARAMETERS method in order to get the value of paramters selected 
       attachInterrupt(0,SELECT_PARAMETERS,RISING);

       
       // the following functions are called to allow the user to set the value of paramters
       // they can be rearraged in any order required
       setShockDuration();
       setOdor1Duration();
       setOdor2Duration();
       setOdor5Duration();
       setOdor5Duration_2();
      
       // since the paramters have been selected for FOC program, we set value of encoder_wert = 3 to display FOC directly
       encoder_wert = 1;
       lcd.clear();

       // interrupt needs to be changed back to ENCODER_AUSWERTUNG to allow the programs of the hardware to be selected
       attachInterrupt(0,ENCODER_AUSWERTUNG,RISING);

       
 

      
    }
    return true;

} //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
void waitForButtonRelease(){
   while (encoder_tast == ECT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
   {
    delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
    encoder_tast = digitalRead(ENCODER_TAST); 
   }
  
}
*/

// displays message on the LCD
void displayMsgOnLCD(String msg,String msg2){
   lcd.clear();
   lcd.home(); 
   lcd.print(msg);
   lcd.setCursor(0,1);
   lcd.print(msg2);
}

// to select duration of shock
void setShockDuration(){
   
      
       displayMsgOnLCD("Shock Duration: ",String(parameter_wert));
       waitForButtonRelease();
       
       while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,SELECT_PARAMETERS,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
            displayMsgOnLCD("Shock Duration: ",String(parameter_wert)+"00 ms");            
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       shock_duration = parameter_wert*100;
       encoder_wert = 0;
       parameter_wert = 0;
}

// to select duration of odor1
void setOdor1Duration(){
      
       displayMsgOnLCD("Odor1 Duration: ",String(parameter_wert));
       
       waitForButtonRelease();

        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,Select_Parameters,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
            displayMsgOnLCD("Odor1 Duration: ",String(parameter_wert*5)+" sec");   
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       odor1_duration = parameter_wert*5;
       encoder_wert = 0;
       parameter_wert = 0;
  
}
// to select duration of odor2
void setOdor2Duration(){
     

       displayMsgOnLCD("Odor2 Duration: ",String(parameter_wert*5)+" sec");
       
       waitForButtonRelease();
       
        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,Select_Parameters,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
            displayMsgOnLCD("Odor2 Duration: ",String(parameter_wert*5)+" sec");   
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       odor2_duration = parameter_wert*5;
       encoder_wert = 0;
       parameter_wert = 0;
}
// to select duration of odor5
void setOdor5Duration(){
       
       
       displayMsgOnLCD("Odor5 Duration: ",String(parameter_wert*5)+" sec");
       waitForButtonRelease();

        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

         
          if(interrupt_occured){
            displayMsgOnLCD("Odor5 Duration: ",String(parameter_wert*5)+" sec");  
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       odor5_duration = parameter_wert*5;
       parameter_wert = 0;
       encoder_wert = 0;
}

// to select 2nd duration of odor5
void setOdor5Duration_2(){
  
       displayMsgOnLCD("Odor5_2 Duration: ",String(parameter_wert*5)+" sec");
       
       
       waitForButtonRelease();

        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,Select_Parameters,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
            displayMsgOnLCD("Odor5_2 Duration: ",String(parameter_wert*5)+" sec");  
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       odor5_duration_2 = parameter_wert*5;
       parameter_wert = 0;
  
}
