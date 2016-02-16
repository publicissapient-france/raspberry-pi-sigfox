#include "cookingClasses.h"
#include "cookingUtils.h"
#include "arduPi.h"
#include "SeeedDHT.h"

//////////////////////////////////////////////
#define DHT_PIN 8;
#define DHT_TYPE 22;
#define DHT_COUNT 16;
DHT dht(DHT_PIN, DHT_TYPE, DHT_COUNT);


void loop() {
  	float h = dht.TemperatureHumidityRead(DHT_PIN, 'H');
  	float t = dht.TemperatureHumidityRead(DHT_PIN, 'T');

	printf("***  Measures   ***\n");
    printf("Humidify : %f %\n", h);
    printf("Temperature : %f°C\n", t);

    delay(1000);
}

int main (){
   while(1){
      loop();
   }
   return (0);
}