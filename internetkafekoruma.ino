#include <dht11.h>


 int gaz_deger;//gaz sensöründen okunan gaz değeri
 int led_k=2;//kırmızı led1
 int led_y=3;//yeşil led2
 int buzzer=4;
 int led_s=5;//sarı led2
 int DHT11_pin=8;
 int trigPin=12;
 int echoPin=13;
 dht11 DHT11_sensor;
 
void setup() {
  
 Serial.begin(9600);
 pinMode(led_k,OUTPUT);//led çıkışı
 pinMode(led_y,OUTPUT);//led çıkışı
 pinMode(led_s,OUTPUT);//led çıkışı
 pinMode(buzzer, OUTPUT);
 pinMode(8, INPUT);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}

void loop() {
  
 gaz_deger=analogRead(A0);//co2 gaz değeri okunuyor

 Serial.print(gaz_deger);//değeri bilgisayar ekranına yazılıyor
 Serial.print("ppm");
 Serial.println("");
 delay(500);
 if(gaz_deger>900){
  digitalWrite(led_k,HIGH);//900 ppm den büyükse ledler yansın
  digitalWrite(led_y,LOW);
  digitalWrite(led_s,LOW);
  tone(buzzer,1000,150);
  delay(1000);
 }
 
else if (gaz_deger>600) {
  digitalWrite(led_k, LOW);
  digitalWrite(led_s, HIGH);
  digitalWrite(led_y, LOW);
  noTone(buzzer);
  delay(1000);
 }


 else {
  digitalWrite(led_k, LOW);
  digitalWrite(led_s, LOW);
  digitalWrite(led_y, HIGH);
  noTone(buzzer);
 }

 int chk = DHT11_sensor.read(DHT11_pin);
 
 Serial.print("Nem Orani (%):");
 Serial.println((float)DHT11_sensor.humidity, 2);

 Serial.print("Sicaklik (Celcius):");
 Serial.println((float)DHT11_sensor.temperature, 2);

 Serial.print("Sicaklik (Kelvin):");
 Serial.println(DHT11_sensor.kelvin(), 2);

 Serial.print("Sicaklik (Fahranheit):");
 Serial.println(DHT11_sensor.fahrenheit(), 2);

 Serial.print("Cig olusma Noktasi:");
 Serial.println(DHT11_sensor.dewPoint(), 2);
 Serial.println("-------------------------------------------");
 delay(1000);

 int sure, mesafe;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 sure = pulseIn(echoPin,HIGH);
 mesafe = (sure/2) / 29.1;
 if (mesafe<= 20 || mesafe <=0)
 {
  Serial.print(mesafe);
  Serial.println("cm");
  digitalWrite(buzzer,HIGH);
  digitalWrite(led_k,HIGH);
  digitalWrite(led_y,LOW);
  digitalWrite(led_s,LOW);
  delay(250);
 }
 else
 {
  digitalWrite(buzzer,LOW);
  delay(250);
  Serial.print(mesafe);
  Serial.println("cm");
  digitalWrite(led_k,LOW);
  digitalWrite(led_y,LOW);
  digitalWrite(led_s,LOW);
 }
 delay(250);
 
}
