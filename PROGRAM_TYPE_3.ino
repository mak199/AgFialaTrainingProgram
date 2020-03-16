boolean FOC_Program_TYPE3(int odor1_dur,int odor2_dur,int odor5_dur,int odor5_2nd_dur,int shock_dur){

    float timer = 0;
    encoder_tast = digitalRead(ENCODER_TAST);
    if (encoder_tast == ECT_GEDRUECKT){
       
       waitForButtonRelease();
       lcdMsg("   START FOC     ","              ");
       delay(1000);
       
       
       while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
         if(timer < odor5_dur){
           lcdMsg(focInfoMsg,"Odor5:"+String(int(odor5_dur-timer))+" sec          ");
           delay(1000);
           timer += 1;           
           digitalWrite(VALVE_5, LOW);          
         }
         else if(timer >= odor5_dur and timer <(odor5_dur + odor1_dur)){ 
           lcdMsg(focInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur - timer))+" sec          ");
           digitalWrite(VALVE_5, HIGH); 
           digitalWrite(valve_num1, HIGH);      
           digitalWrite(TRIGGER_SCHOCK, HIGH); 
           delay (shock_dur);   
           timer += shock_dur/1000;
           lcdMsg(focInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur - timer))+" sec          ");
           digitalWrite(TRIGGER_SCHOCK, LOW);// Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
           for(int i=0;i<5-round(shock_dur/1000);i++){
              Serial.println(5-round(shock_dur/1000));
              if(i==0 && shock_dur<1000){
                delay(1000-shock_dur); 
                timer += 1-(shock_dur/1000);
                lcdMsg(focInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur - timer))+" sec          ");
              
              }
              else if(i==0 && shock_dur==1000){
                delay(1000); 
                timer += 1;
                lcdMsg("FOC           ","Odor1:"+String(int(odor1_dur + odor5_dur - timer))+" sec          ");
              }
              else{
                 delay(1000); 
                 timer += 1;
                 lcdMsg("FOC           ","Odor1:"+String(int(odor1_dur + odor5_dur - timer))+" sec          ");
              }
             
           }
           
           //timer +=(5-(shock_dur/1000));
 
          }
          else if(timer >= (odor5_dur + odor1_dur) and timer < (odor5_dur + odor5_2nd_dur + odor1_dur)){
            lcdMsg(focInfoMsg,"Odor5 2nd:"+String(int(odor5_dur + odor5_2nd_dur + odor1_dur - timer))+" sec          ");
            digitalWrite(valve_num1, LOW);
            digitalWrite(VALVE_5, LOW);    
            delay (1000);   
            timer += 1;   
          }
          else if (timer >= (odor5_2nd_dur + odor5_dur + odor1_dur) and timer < (odor5_2nd_dur + odor5_dur + odor1_dur + odor2_dur)){
            lcdMsg(focInfoMsg,"Odor2:"+String(int(odor5_2nd_dur + odor5_dur + odor1_dur + odor2_dur - timer))+" sec          ");
            digitalWrite(valve_num2, HIGH);
            digitalWrite(VALVE_5, HIGH);    
            delay (1000);   
            timer += 1;   

          }
          else if(timer >= (odor5_2nd_dur + odor5_dur + odor1_dur + odor2_dur)){
            digitalWrite(valve_num2, LOW);
            break;
          }
         encoder_tast = digitalRead(ENCODER_TAST); 

         
       }
       digitalWrite(VALVE_5, LOW); 
       digitalWrite(valve_num1, LOW); 
       digitalWrite(valve_num2, LOW);      
       digitalWrite(TRIGGER_SCHOCK, LOW); 
       lcd.clear();
       encoder_wert = 0;
       waitForButtonRelease();
       
      
      
    }
    return true;

}

boolean SOC_Program_TYPE3(int odor1_dur,int odor3_dur,int odor5_dur,int pulse_dur){

  return SOC_Program_TYPE1(odor1_dur,odor3_dur,odor5_dur,pulse_dur);
} //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
