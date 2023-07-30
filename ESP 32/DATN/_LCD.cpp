#include "_LCD.h"

LiquidCrystal_I2C lcd(0x3F, 20, 4);

extern float temperature, huminity;
extern int peoples;
extern bool busIsStarted;

extern float longitude, latitude;

void initLCD(){
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Starting ...");
}

void LCDRunTask(void *parameter){
  bool currSystemState = true;
  while(true){
    if(busIsStarted){
      currSystemState = busIsStarted;
      
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(int(temperature));
      lcd.print("   Humi: ");
      lcd.print(int(huminity));
  
      lcd.setCursor(0, 1);
      lcd.print("Peoples: ");
      lcd.print(peoples);
      if(peoples >= 0 && peoples < 10) lcd.print("   ");
      else if(peoples >= 10 && peoples < 100) lcd.print("  ");
      else if(peoples > 100) lcd.print(" ");
      else if(peoples < 0 && peoples > -10) lcd.print("  ");
      else if(peoples > -100 && peoples < -10) lcd.print(" ");
      
      lcd.setCursor(13, 3);
      lcd.print("STARTED");
    }
    else{
      if(currSystemState != busIsStarted){
        lcd.clear();
        currSystemState = busIsStarted;
      }
      lcd.setCursor(13, 3);
      lcd.print("STOPPED");
    }

//      lcd.setCursor(0, 0);
//      lcd.print("lon: ");
//      lcd.print(longitude, 5);
//      lcd.setCursor(0, 1);
//      lcd.print("lat: ");
//      lcd.print(latitude, 5);

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
