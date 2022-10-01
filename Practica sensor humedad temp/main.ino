#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200); // Comunicación con puerto serial a 115200 baudios
    dht.begin();
}

void loop()
{
    int Temp;
    int Hum;

    Temp = dht.readTemperature();
    Hum = dht.readHumidity();

    Temp = Temp * (9 / 5) + 32; // Celcius formula

    Serial.println("Temperatura: ", Temp)
    Serial.println("Humedad: ", Hum);

}