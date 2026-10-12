#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// -------------------------
// Configuración DS18B20
// -------------------------
#define DS18B20_PIN 4


OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// -------------------------
// Configuración LCD I2C
// -------------------------
#define SDA_PIN 21
#define SCL_PIN 22
#define enfriar 16 //tx
#define calentar 17 //rx
#define boton_1 32
#define boton_2 33
#define boton_3 34
int HL = 60; 
int LL = 30;
bool modoLL = true;               // true: botones cambian LL, false: cambian HL

// Para detectar solo el "flanco" de cada botón (una pulsación = un cambio)
bool prev1 = false, prev2 = false, prev3 = false;
#define PRESSED(x) (digitalRead(x)==0) 
#define on_enfriar digitalWrite (enfriar, HIGH)
#define off_enfriar digitalWrite (enfriar, LOW)
#define on_calentar digitalWrite (calentar, HIGH)
#define off_calentar digitalWrite (calentar, LOW)

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(115200);

    // Inicializar I2C
    Wire.begin(SDA_PIN, SCL_PIN);

    // Inicializar sensor
    sensors.begin();

    // Inicializar LCD
    lcd.init();
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura");
    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");

    delay(2000);

    pinMode(enfriar, OUTPUT);
     pinMode(calentar, OUTPUT);
     pinMode(boton_1, INPUT_PULLUP);
     pinMode(boton_2, INPUT_PULLUP);
     pinMode(boton_3, INPUT_PULLUP);
}

void loop()
{
    // Solicitar medición
    sensors.requestTemperatures();

    // Obtener temperatura en Celsius
    float temperatura = sensors.getTempCByIndex(0);

    if (temperatura >= HL) {
         on_enfriar;
         off_calentar;

        
     }
     if (temperatura <= LL) {
         off_enfriar;
         on_calentar;
                
    }
    
    bool p1 = PRESSED(boton_1);
    bool p2 = PRESSED(boton_2);
    bool p3 = PRESSED(boton_3);

    if (p3 && !prev3) modoLL = !modoLL;

    if (modoLL) {
        if (p1 && !prev1) LL = min(LL + 10, HL - 10);   // LL siempre menor que HL
        if (p2 && !prev2) LL = max(LL - 10, 0);
    } else {
        if (p2 && !prev2) HL = min(HL + 10, 100);
        if (p1 && !prev1) HL = max(HL - 10, LL + 10);   // HL siempre mayor que LL
    }
    prev1 = p1; prev2 = p2; prev3 = p3;


    // Mostrar por monitor serial
    Serial.print("Temperatura: ");

    if (temperatura == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Sensor desconectado");
    }
    else
    {
        Serial.print(temperatura);
        Serial.println(" °C");
    }

    // Mostrar en LCD
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("AL: ");

    lcd.setCursor(3, 0);

    if (temperatura == DEVICE_DISCONNECTED_C)
    {
        lcd.print("Error sensor");
    }
    else
    {
        lcd.print(temperatura, 1);
        lcd.print((char)223);  // Simbolo °
        lcd.print("C");
    }

    lcd.setCursor(0, 1);
         lcd.print("HL: ");

         lcd.setCursor(3, 1);
         lcd.print(HL, 1);
         lcd.print((char)223); 
         lcd.print("C");


         lcd.setCursor(8, 1);
         lcd.print("LL: ");

         lcd.setCursor(11, 1);
         lcd.print(LL, 1);
         lcd.print((char)223); 
         lcd.print("C");

            // Indicador de qué límite se está ajustando
        lcd.setCursor(12, 0);
        lcd.print(modoLL ? "[LL]" : "[HL]");



    delay(1000);
}