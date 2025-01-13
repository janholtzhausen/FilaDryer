#ifndef DHT_H_
#define DHT_H_

#include "main.h"

/* Settings */
#define DHT_TIMEOUT                 10000   // Number of iterations after which the function will return empty values
#define DHT_POLLING_CONTROL         1       // Enable checking the frequency of sensor polling
#define DHT_POLLING_INTERVAL_DHT11  2000    // Polling interval for DHT11 (0.5 Hz according to the datasheet). Can be set to 1500, it will work
#define DHT_POLLING_INTERVAL_DHT22  1000    // Polling interval for DHT22 (1 Hz according to the datasheet)
#define DHT_IRQ_CONTROL                     // Disable interrupts during data exchange with the sensor
/* Structure of data returned by the sensor */
typedef struct {
    float hum;    // Humidity
    float temp;   // Temperature
} DHT_data;

/* Type of sensor used */
typedef enum {
    DHT11,
    DHT22
} DHT_type;

/* Sensor object structure */
typedef struct {
    GPIO_TypeDef *DHT_Port;    // Sensor port (GPIOA, GPIOB, etc)
    uint16_t DHT_Pin;          // Sensor pin number (GPIO_PIN_0, GPIO_PIN_1, etc)
    DHT_type type;             // Type of sensor (DHT11 or DHT22)
    uint8_t pullUp;            // Whether a pull-up is needed for the data line (GPIO_NOPULL - no, GPIO_PULLUP - yes)

    // Sensor polling frequency control. Do not fill in these values!
    #if DHT_POLLING_CONTROL == 1
    uint32_t lastPollingTime;  // Time of the last sensor polling
    float lastTemp;            // Last temperature value
    float lastHum;             // Last humidity value
    #endif
} DHT_sensor;

/* Function prototypes */
DHT_data DHT_getData(DHT_sensor *sensor); // Get data from the sensor

#endif
