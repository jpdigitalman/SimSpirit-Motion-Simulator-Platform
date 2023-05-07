#include <Button2.h>

/////////////////////////////////////////////////////////////////

#define BUTTON_PIN  0

/////////////////////////////////////////////////////////////////

Button2 BOOT_SETUP;

/////////////////////////////////////////////////////////////////
void longClick(Button2& btn);
void longClickDetected(Button2& btn);

void setupBTN() {
  
  Serial.println("\n\nButton Setup");
  BOOT_SETUP.begin(BUTTON_PIN);

  // button.setLongClickDetectedRetriggerable(true);

  BOOT_SETUP.setLongClickHandler(longClick);
  BOOT_SETUP.setLongClickDetectedHandler(longClickDetected);

  Serial.println("\n\nButton Setup Done");
}

/////////////////////////////////////////////////////////////////

void doBTN() {
  BOOT_SETUP.loop();
  if(setupMode){
    if(millis() - lastBeepTime > intervalBeep){
        Serial.println("buzing");
        if (buzVal==HIGH) {
            buzzer(true);
            buzVal = LOW;
        }else{
            buzzer(false);
            buzVal = HIGH;
        }
        lastBeepTime = millis();
    }    
  }
}

/////////////////////////////////////////////////////////////////

void longClick(Button2& btn) {
    unsigned int time = btn.wasPressedFor();
    Serial.print("You clicked ");
    if (time > 4000) {        
        setupMode = true;
        Serial.print("a really really long time.");
    } else if (time > 1000) {
        Serial.print("a really long time.");
    } else if (time > 500) {
        Serial.print("a long time.");        
    } else {
        Serial.print("short."); 
        buzzer(false);
        doYaw();
        //save defaultPRzero
        setInitZero(calib360);
        doCalibrate();       
    }
    Serial.print(" (");        
    Serial.print(time);        
    Serial.println(" ms)");
}

/////////////////////////////////////////////////////////////////

void longClickDetected(Button2& btn) {
    Serial.print("long click #");
    Serial.print(btn.getLongClickCount());
    Serial.println(" detected");
}