boolean FOC_Program_TYPE2(int odor1_dur,int odor2_dur,int odor5_dur,int odor5_2nd_dur,int shock_dur){

    return FOC_Program_TYPE1(odor1_dur,odor2_dur,odor5_dur,odor5_2nd_dur,shock_dur);

}

boolean SOC_Program_TYPE2(int odor1_dur,int odor3_dur,int odor5_dur,int pulse_dur){

    float timer = 0;
    float pulse = 0;
    encoder_tast = digitalRead(ENCODER_TAST);
    if (encoder_tast == ECT_GEDRUECKT){
       waitForButtonRelease();
       lcdMsg("   START SOC      ","                    ");

       
       while (encoder_tast == ECT_NICHT_GEDRUECKT){ 
         if(timer < odor5_dur){
           lcdMsg(socInfoMsg,"Odor5:"+String(int(odor5_dur-timer))+" sec          ");
           digitalWrite(VALVE_5, LOW); 
           delay(1000);
           timer += 1;           
           //Serial.println(timer); 
         }
         else if(timer >= odor5_dur and timer < (odor5_dur + odor3_dur)){  
           lcdMsg(socInfoMsg,"Odor3:"+String(int(odor5_dur + odor3_dur - timer))+" sec          ");
           digitalWrite(VALVE_5, HIGH); 
           digitalWrite(valve_num1, HIGH);      
           //digitalWrite(TRIGGER_SCHOCK, HIGH); 
           delay (1000);   
           timer += 1;
            
          }
          else if(timer >= (odor5_dur + odor3_dur) and timer < (odor5_dur + odor3_dur + odor1_dur)){
           lcdMsg(socInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur + odor3_dur - timer))+" sec          ");   
           digitalWrite(valve_num1, HIGH); 
           digitalWrite(valve_num2, HIGH);      
           digitalWrite(VALVE_5, LOW); 
           delay (pulse_dur);   
           timer += pulse_dur/1000;
           lcdMsg(socInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur + odor3_dur - timer))+" sec          ");   
           digitalWrite(valve_num1, HIGH); 
           digitalWrite(valve_num2, LOW);// Pause schwischen dem drücken damit der Taster nicht doppelt schalten kann  
           digitalWrite(VALVE_5, HIGH);
           for(int i=0;i<5-round(pulse_dur/1000);i++){
              Serial.println(5-round(pulse_dur/1000));
              if(i==0 && pulse_dur<1000){
                delay(1000-pulse_dur); 
                timer += 1-(pulse_dur/1000);
                lcdMsg(socInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur + odor3_dur - timer))+" sec          ");   
                Serial.println("Shock less than a second");
              }
              else if(i==0 && pulse_dur==1000){
                delay(1000); 
                timer += 1;
                lcdMsg(socInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur + odor3_dur - timer))+" sec          ");   
                Serial.println("Shock equal to a second");
              }
              else{
                 delay(1000); 
                 timer += 1;
                 lcdMsg(socInfoMsg,"Odor1:"+String(int(odor1_dur + odor5_dur + odor3_dur - timer))+" sec          ");   
              }
             
           }
           
              
            
          }
          else if (timer >= (odor5_dur + odor3_dur + odor1_dur) and timer < (odor5_dur + odor3_dur + odor1_dur + 45)){
            lcdMsg(socInfoMsg,"Odor5:"+String(int(odor1_dur + odor5_dur + odor3_dur + 45 - timer))+" sec          ");
            digitalWrite(VALVE_5, LOW); 
            digitalWrite(valve_num2, LOW); 
            digitalWrite(valve_num1, LOW); 
            timer += 1;
            delay(1000);
          }
          else if(timer>=(odor5_duration + odor3_duration + odor1_duration + odor5_duration)){
            digitalWrite(valve_num1, LOW);
            digitalWrite(valve_num2, LOW);
            digitalWrite(VALVE_5, HIGH);
            break;
          }
         encoder_tast = digitalRead(ENCODER_TAST); 
       }
       digitalWrite(VALVE_5, LOW); 
       digitalWrite(valve_num2, LOW); 
       digitalWrite(VALVE_2, LOW); 
       digitalWrite(valve_num1, LOW);      
       digitalWrite(TRIGGER_SCHOCK, LOW); 
       lcd.clear();
       waitForButtonRelease();
      
      
    }
  return true;
} //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
