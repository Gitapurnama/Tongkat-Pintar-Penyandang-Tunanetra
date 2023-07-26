//Projek rancang bangun Tongkat pintar Tunanetra dengan menggunakan mikrokontroler Arduino
//SOURCH CODE GPS TONGKAT


//Mendefenisikan setiap library yang di butuhkan
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

static const int RXPin = 4, TXPin = 5; // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0); // V0 for virtual pin of Map Widget

SoftwareSerial ss(RXPin, TXPin); // The serial connection to the GPS device

BlynkTimer timer;

float spd; //Variable to store the speed
float sats; //Variable to store no. of satellites response
String bearing; //Variable to store orientation or direction of GPS

char auth[] = "rHuBPg2AQWQfvmYN-dHIkyoK-IW2qx7t"; //Token aplikasi Blynk
char ssid[] = "HOME"; //Nama WiFi atau hotspot Jaringan yang terhubung di EESP8266
char pass[] = "11333355555577777777"; //Pasword jaringan yang terhubung di EESP8266

//unsigned int move_index; // moving index, to be used later
unsigned int move_index = 1; // fixed location for now
  

void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
  }
}

void loop()
{
    while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{ 
  if (gps.location.isValid() ) 
  {    
    float latitude = (gps.location.lat()); //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT: ");
    Serial.println(latitude, 6); // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V13, String(latitude, 6));   
    Blynk.virtualWrite(V14, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph(); //get speed                      
  }
  
 Serial.println();
}
