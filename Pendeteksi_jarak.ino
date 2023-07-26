// Projek rancang bangun Tongkat pintar Tunanetra dengan menggunakan mikrokontroler Arduino
// SOURCH CODE PENDETEKSI JARAK


// Mendefinisikan nomor pin
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;

// definisi variable
long duration;
int distance;
int safetyDistance;


void setup() 
{
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // 
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// menyetel TringPin pada  status Tinggi selama 10 mikro detik
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

//membaca pin Echo, mengembalikan waktu tempuh gelombang suara dalam mokro detik
duration = pulseIn(echoPin, HIGH);

// menghitung jarak
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 30)
{
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin, HIGH);
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
}

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}
