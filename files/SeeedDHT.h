#ifndef __SEEED_DHT__
#define __SEEED_DHT__
#include "arduPi.h"

// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 85

#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

class DHT {
    
private:
    uint8_t data[6];
    uint8_t _pin, _type, _count;
    boolean read(void);
    unsigned long _lastreadtime;
    boolean firstreading;

public:
    DHT(uint8_t pin, uint8_t type, uint8_t count);
    
    void begin(void);
    float readTemperature(bool S=false);
    float convertCtoF(float);
    float readHumidity(void);
    
public:         // api for seeed graphical programming project
    /*
     * Function Name: TemperatureHumidityRead
     * Input - PinName: pin to connect
     *         th - chanel choose
     *              'T' - read temperature
     *              'H' - read humidity
     * Return - temperature or humidity
     */
    float TemperatureHumidityRead(int PinName, char th)
    {
        _pin = PinName;
        
        switch(th)
        {
            case 'T':       // temperature
            return readTemperature();

            case 'H':       // humidity
            return readHumidity();
        }
    }

};
#endif
