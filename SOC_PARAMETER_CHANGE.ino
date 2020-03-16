// this function is used to select the parameters for SOC program
boolean SOC_CHANGE_PARAMETERS(){
  
    // Reads the value of button 0 or 1
    encoder_tast = digitalRead(ENCODER_TAST);
    // Checks if the button was pressed or not
    if (encoder_tast == ECT_GEDRUECKT){
      
       // the program needs to wait until the button is released by the user
       //waitForButtonRelease();

        // the interrupt must be changed to call SELECT_PARAMETERS method in order to get the value of paramters selected 
       attachInterrupt(0,SELECT_PARAMETERS,RISING);

       // the following functions are called to allow the user to set the value of paramters
       setPulse();
       setOdor1Duration();
       setOdor3Duration();
       setOdor5Duration();
        
     
       // since the paramters have been selected for FOC program, we set value of encoder_wert = 4 to display FOC directly
       encoder_wert = 2;
       lcd.clear();

       // interrupt needs to be changed back to ENCODER_AUSWERTUNG to allow the programs of the hardware to be selected
       attachInterrupt(0,ENCODER_AUSWERTUNG,RISING);
      
    }
    return true;

} //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void setPulse(){
  
       displayMsgOnLCD("Pulse Duration: ",String(parameter_wert*100)+" ms");
       
       waitForButtonRelease();
       
        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,SELECT_PARAMETERS,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
             /*if(parameter_wert>=10){
                parameter_wert = 10;
             }*/
            displayMsgOnLCD("Pulse Duration: ",String(parameter_wert*100)+" ms");   
            interrupt_occured = false;
          }
         
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       pulse_duration = parameter_wert*100;
       encoder_wert = 0;
       parameter_wert = 0;
}


void setOdor3Duration(){
     

       displayMsgOnLCD("Odor3 Duration: ",String(parameter_wert*5)+" sec");
       
       waitForButtonRelease();
       
        while (encoder_tast == ECT_NICHT_GEDRUECKT)                            //hier warten darauf das der Taster losgelassen wird
       {

          //attachInterrupt(0,Select_Parameters,RISING);        // Call Channel A of ENCODER Function while on CH1 Signal Changing
          if(interrupt_occured){
            displayMsgOnLCD("Odor3 Duration: ",String(parameter_wert)+" sec");   
            interrupt_occured = false;
          }
          
          
          delay (25);                                    // Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
          encoder_tast = digitalRead(ENCODER_TAST); 
       }
       waitForButtonRelease();
       odor3_duration = parameter_wert;
       encoder_wert = 0;
       parameter_wert = 0;
}
