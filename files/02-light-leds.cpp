#include "cookingUtils.h"
#include "cookingClasses.h"
#include "arduPi.h"

#define RED_LED_PIN 2
#define GREEN_LED_PIN 3
#define BLUE_LED_PIN 4

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
}

void loop() {
    printf("***  Lighting LEDs in sequence Red / Green / Blue   ***\n");
	int i;
  	for (i = 2; i <= 4; i++) {
  		digitalWrite(i, HIGH);   // turn the LED on (HIGH is the voltage level)
  		delay(1000);              // wait for a second
  		digitalWrite(i, LOW);    // turn the LED off by making the voltage LOW
  		delay(1000);
  	}
}

int main (){
   setup();
   while(1){
      loop();
   }
   return (0);
}