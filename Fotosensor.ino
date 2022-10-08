#define LIGHT_SENSOR_PIN 2
#define LED_PIN 5

void setup()
{
    Serial.begin(9600);
    Serial.println("Hola");
    pinMode(LED_PIN, OUTPUT);
    delay(1000);
}

void loop()
{
    int Light;

    Light = analogRead(LIGHT_SENSOR_PIN);

    Serial.println(Light);

    if (Light < 40)
    {
        Serial.println(" => Dark");
        digitalWrite(LED_PIN, HIGH);
    }
    else if (Light < 800)
    {
        Serial.println(" => Dim");
        digitalWrite(LED_PIN, HIGH);
    }
    else if (Light < 2000)
    {
        Serial.println(" => Light");
        digitalWrite(LED_PIN, LOW);
    }
    else if (Light < 3200)
    {
        Serial.println(" => Bright");
        digitalWrite(LED_PIN, LOW);
    }
    else
    {
        Serial.println(" => Very bright");
        digitalWrite(LED_PIN, LOW);
    }

    delay(2000);
}