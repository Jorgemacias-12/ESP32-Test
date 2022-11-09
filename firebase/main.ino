#include <WiFi.h>
#include <DHT.h>
#include <FirebaseESP32.h>

// Definir tipo de sensor
#define DHTTYPE DHT11
#define DHTPIN 19 // Puerto de conexión

// Creedenciales de acceso a internet
#define SSID "Iot"
#define PASS "1234568.R"

// Firebase API KEY
#define API_KEY "aquí"

// Usuario autorizado para insersion de datos
#define USER_EMAIL "Credencial aquí"
#define USER_PASS "Credencial aquí"

// URL de la base de datos
#define DB_URL "url aquí"

// Objetos usados por firebase
FirebaseData fdbo;
FirebaseAuth auth;
FirebaseConfig config;

// Guardar el UID del usuario
String user_uid;

// Variables para guardar las rutas para la base de datos
String TempPath;
String HumPath;

// Variables para guardar los datos del sensor
float Temperature;
float Humidity;

// Valores de espera (enviar nuevas lecturas cada N minutos)
unsigned long SendDataPrevMillis;
unsigned long TimerDelay = 2000;

DHT dht(DHTPIN, DHTTYPE);

void InitializeWifi()
{
    WiFi.begin(SSID, PASS);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }

    Serial.print("Your IP is:");
    Serial.println(WiFi.localIP());
}

void SendFloat(String path, float value)
{
    if (Firebase.RTDB.setFloat(&fdbo, path.c_str(), value))
    {
        Serial.print("Writting value: ");
        Serial.print(value);
        Serial.print(" on the following path: ");
        Serial.print(path);
        Serial.println("PASSED");
    }
    else
    {
        Serial.println("Failing sending data to the sever");
        Serial.println("REASON: " + fdbo.errorReason());
    }
}

void ConfigFirebase()
{
    // Asignar la api key
    config.api_key = API_KEY;

    // Asignar creedenciales de inicio de sesión
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASS;

    // Asignar la URL de la bd
    config.database_url = DB_URL;

    // establecer el temaño de respues y reconexión
    Firebase.reconnectWiFi(true);
    fdbo.setResponseSize(4096);

    // Asignar el máximo de intentos de generación del token
    config.max_token_generation_retry = 5;

    // Inicializar el uso de firebase
    Firebase.begin(&config, &auth); // autenticarse y establecer configuración

    Serial.println("Getting user UID");

    while ((auth.token.uid) == "")
    {
        Serial.print('.');
        delay(1000);
    }

    // Obtener el UID y guardarlo
    user_uid = auth.token.uid.c_str();

    // Imprimir el UID en consola
    Serial.println("SUCESS!");
    Serial.print("User UID: ");
    Serial.println(user_uid);

    // Actualizar rutas de acceso a la db
    TempPath = "/temperature";
    HumPath = "/humidity";
}

void setup()
{
    Serial.begin(115200);

    // Inicializar wifi
    InitializeWifi();

    // Inicializar el sensor
    pinMode(DHTPIN, OUTPUT);

    // Configurar firebase
    ConfigFirebase();
}

void loop()
{
    // Enviar lecturas a la db
    if (Firebase.ready() &&
        (millis() - SendDataPrevMillis > TimerDelay ||
         SendDataPrevMillis == 0))
    {
        // Obtener tiempo
        SendDataPrevMillis = millis();

        // Obtener lectura del sensor;
        Temperature = dht.readTemperature();
        Humidity = dht.readHumidity();

        // Enviar valores a firebase
        SendFloat(TempPath, Temperature);
        SendFloat(HumPath, Humidity);
    }
}