
#include <Wire.h> // Comes with Arduino IDE

#include <LiquidCrystal_I2C.h>
#include "DHT.h"

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT dht;

const int noWater = 99;    // sensor minimum
const int exWater = 650; // sensor maximum
//const int gdWater = 400-650;
//const int okWater = 300-400;
//const int ndWater = 100-300;

void setup()
{
    Serial.begin(9600);

    lcd.begin(20, 4);
    dht.setup(2);

    for (int i = 0; i < 3; i++)
    {
        lcd.backlight();
        delay(250);
        lcd.noBacklight();
        delay(250);
    }
    lcd.backlight(); // finish with backlight on

    lcd.setCursor(2, 0); //Start at character 0 on line 0
    lcd.print("Sistema de riego");

} /*--(end setup )---*/

void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{

    int sensorReading = analogRead(A0);
   

    delay(dht.getMinimumSamplingPeriod());

    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    lcd.setCursor(0, 1);
    lcd.print(String("H: ") + String(humidity, 1) + String("RH") + String("   T: ") + String(temperature, 1) + String("C"));
    lcd.setCursor(0, 2);
    lcd.print("Estado de la Planta:");
   

    Serial.print(dht.getStatusString());
    Serial.print("\t");
    Serial.print(humidity, 1);
    Serial.print("\t\t");
    Serial.print(temperature, 1);
    Serial.print("\t\t");
    Serial.println(dht.toFahrenheit(temperature), 1);

    if (sensorReading <= noWater){
        
        lcd.setCursor(0, 3);
        lcd.print("                    ");
        lcd.setCursor(0, 3);
        lcd.print(String("Urgido/Desconectado ") + String(sensorReading));
        Serial.println("Rain Warning");}
    else if (sensorReading >= exWater){
        
        lcd.setCursor(0, 3);
        lcd.print("                    ");
        lcd.setCursor(0, 3);
        lcd.print(String("Muy Alto ") + String(sensorReading));
    }
        else if (sensorReading >= 400 && sensorReading <= 649){
            
            lcd.setCursor(0, 3);
            lcd.print("                    ");
            lcd.setCursor(0, 3);
            lcd.print(String("Muy Bueno ") + String(sensorReading));
        }
    else if (sensorReading >= 300 && sensorReading <= 399){
            
            lcd.setCursor(0, 3);
            lcd.print("                    ");
            lcd.setCursor(0, 3);
            lcd.print(String("Bueno ") + String(sensorReading));
        }
        else if (sensorReading >= 100 && sensorReading <= 299){
            
            lcd.setCursor(0, 3);
            lcd.print("                    ");
            lcd.setCursor(0, 3);
            lcd.print(String("Necesita Agua ") + String(sensorReading));
        }
    

    
}
