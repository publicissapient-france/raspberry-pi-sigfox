#include "cookingClasses.h"
#include "cookingUtils.h"
#include "arduPi.h"


#define BUTTON_PIN = 7;
// Button
int buttonState = 0;

void setup() {
	pinMode(BUTTON_PIN, INPUT);
	printf("*** Waiting for user action (push button) ***\n");
}

void loop() {
	buttonState = digitalRead(BUTTON_PIN);
	if (buttonState == HIGH) {
    	printf("Button pressed\n");
	}
}

int main (){
	setup();
  	while(1){
      	loop();
   	}
   	return (0);
}