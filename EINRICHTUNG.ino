void EINRICHTUNG(){

// Erste Worte auf dem LCD


lcd.home();                               //Curser in die obere linke Ecke
lcd.clear();                              //LCD Löschen
lcd.print(" Olfak. Schock  ");             //Schrift für die erste zeile senden
lcd.createChar(0, JH);                    // EIGENES Kürzel laden 
lcd.setCursor(15,0);                       //Curser in die 2te  Zeile legen
lcd.write(byte(0));  
lcd.setCursor(0,1);                       //Curser in die 2te  Zeile legen
lcd.print("SSF 06.2019 V1  ");            //schrift für die 2te Zeile senden
delay(3000);

//Timer Starten-----------------------------
//MsTimer2::start();


// LCD Löschen und dann gets los------------
lcd.clear();                              //LCD Löschen

// Merker für Schleife erledigt setzen------
einmal = abgeschlossen;
}//ENDE#####################################################################
