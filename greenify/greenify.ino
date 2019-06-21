
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht.h>
#define DHT11_PIN D7

int relayPompa = D1;
int relayKipas = D0;

char auth[] = "c40006ccc0344d2aa2d6767318ec2f3b";

char ssid[] = "Project Ars";
char pass[] = "Hymnxavi";

WidgetLCD lcd(V0);
WidgetLCD lcd2(V1);
WidgetLCD lcd3(V2);

//Deklarasi Sensor & Pin
dht DHT;
int pinKipas;
int pinPompa;
float sensorPin = A0;


void setup() {


  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
    lcd.clear();
    lcd.print(0, 0, "Temp in C");
    lcd2.clear();
    lcd2.print(0, 0, "Humidity");
    lcd3.clear();
    lcd3.print(0, 0, "Soil Humidity");
}

void loop() {

//LCD Blynk
  lcd.clear();
    lcd.print(0, 0, "Temp in C");
    lcd2.clear();
    lcd2.print(0, 0, "Humidity Ruangan");
    lcd3.clear();
    lcd3.print(0, 0, " Soil Humidity ");

    //Temperature

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C");
  lcd.print(7, 1, DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  lcd2.print(7, 1, DHT.humidity);
  Serial.print("Kelembapan Tanah: ");
  Serial.println(soilSensor());
  lcd3.print(0, 1, soilSensor());


  if(pinKipas == 1){
    pinMode(relayKipas, OUTPUT);
    }
   else{
    pinMode(relayKipas, INPUT);
   }

   if(pinPompa == 1){
    pinMode(relayPompa, OUTPUT);
    }
   else{
    pinMode(relayPompa, INPUT);
   }
}
//Virtual Button Pompa
BLYNK_WRITE(V3){
   pinPompa = param.asInt();
  Serial.println(pinPompa);
  }

//Virtual Button Kipas
BLYNK_WRITE(V4){
   pinKipas = param.asInt();
  Serial.println(pinKipas);
  }

//Kelembapan Tanah
float soilSensor(){
  float nilai = analogRead(sensorPin);
  return 1023 -  nilai;
  }
