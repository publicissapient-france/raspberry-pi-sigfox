#include "cookingClasses.h"
#include "cookingSigfox.h"
#include "cookingUART.h"
#include "cookingUtils.h"
#include "arduPi.h"
#include "SeeedDHT.h"

//////////////////////////////////////////////
//Asign to UART0
//////////////////////////////////////////////
uint8_t sock = SOCKET0;

#define DHT_PIN 8
#define DHT_TYPE 22
#define DHT_COUNT 16
DHT dht(DHT_PIN, DHT_TYPE, DHT_COUNT);

#define BUTTON_PIN 7
// Button
int buttonState = 0;

#define LUM_PIN 0

// Sigfox
uint8_t dataSigfox[12];
uint8_t size;
union
{
  uint8_t  value1[4];
  float    value2;
}t_union;
union
{
  uint8_t  value1[2];
  uint16_t value2;
}l_union;
uint8_t status;

// Luminance
float Vout[] = {0.0011498, 0.0033908, 0.011498, 0.15199, 0.53367, 1.3689, 1.9068, 2.3};
float Lux[] = {1.0108, 3.1201, 9.8051, 27.43, 69.545, 232.67, 645.11, 73.52, 1000};


float read_V_out(uint8_t apin) {
  float MeasuredVout = analogRead(0) * (3.0 / 1023.0);
  return MeasuredVout ;
}

float FmultiMap(float val, float * _in, float * _out, uint8_t size) {
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];
  uint8_t pos = 1;
  while (val > _in[pos]) pos++;
  if (val == _in[pos]) return _out[pos];
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

float read_luminance(uint8_t apin) {
  float MeasureVout = analogRead(0) * (3.0 /1023.0);
  float Luminance = FmultiMap(MeasureVout, Vout, Lux, 9);
  return Luminance;
}

void setup() {
	pinMode(BUTTON_PIN, INPUT);
    pinMode(LUM_PIN, INPUT);
    pinMode(DHT_PIN, INPUT);

    status = Sigfox.ON(sock);
    // Check status
    if (status == 0)
    {
    printf("***  Switch Sigfox ON *** \n");
    }
    else
    {
    printf("Switch Sigfox ON : ERROR\n");
    }
    printf("*** Waiting for user action (push button) ***\n");
}

void loop()
{
  buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH) {
    float h = dht.TemperatureHumidityRead(DHT_PIN, 'H');
    float t = dht.TemperatureHumidityRead(DHT_PIN, 'T');
    float l = read_luminance(LUM_PIN);

    printf("***  Measures   ***\n");
    printf("Luminance : %f lux\n", l);
    printf("Humidity : %f %\n", h);
    printf("Temperature : %f°C\n", t);
    printf("*** Sending data to Sigfox ***\n");

    // fill data array
    t_union.value2 = t;
    dataSigfox[0] = t_union.value1[3];
    dataSigfox[1] = t_union.value1[2];
    dataSigfox[2] = t_union.value1[1];
    dataSigfox[3] = t_union.value1[0];

    dataSigfox[4] = (uint8_t) h;

    l_union.value2 = (uint16_t) l;
    dataSigfox[5] = l_union.value1[1];
    dataSigfox[6] = l_union.value1[0];
    size = 7;

    // Final Frame to send in "data"
    //printf("Final Frame to send: 0x%X\n", dataSigfox);

    // Sending packet to Sigfox
    status = Sigfox.send(dataSigfox,size);

    // Check sending status
    if( status == 0 )
    {
      printf("*** Sigfox packet sent ***\n");
    }
    else
    {
      printf("*** Sigfox packet sent ERROR ***\n");
    }
    printf("*** Waiting for user action (push button) ***\n");
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
