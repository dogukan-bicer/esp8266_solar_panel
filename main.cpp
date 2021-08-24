/*
 1k ile 4.7k direnç kullanılmıştır
*/

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#define FIREBASE_HOST "esp8266-solar-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "qLwruiIyMoIFd4qh5pa0w7BNFR3Ikl0mo2ygtGnz"
#define WIFI_SSID "KENANBiCER"
#define WIFI_PASSWORD "7F8F77372552b"
unsigned long int gecen_zaman;
unsigned long int ayarlanan_zaman;
unsigned long int yeni_milis;

struct yeniMillis{ //millis(mcu nun çalışma süresi) fonksiyonun reset yapabilmesi için oluşturulmuş bir struct
  unsigned long offset =0;
  unsigned long milis(){ //millis ayarla
    return yeni_milis=millis()-offset; 
    }
    void sifirla (){ //millis i sıfırla
      offset = millis();
    }
}
yeni;
void setup() {
  pinMode(D8,OUTPUT);
  //Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //wifi kontrolleri
  //Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }
/*  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());*/
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);//firebase başlat
}

void loop() {
  gecen_zaman=yeni.milis();
 if (gecen_zaman>10000){//10sn de 1 veri gönder.
  float voltaj=analogRead (A0)*0.0176;// Analog sinyal değerini 0-18.70 aralığına ayarlıyoruz.
 /* Serial.print("Gecen zaman=");Serial.println(gecen_zaman);
  Serial.print("voltaj=");
  Serial.println(voltaj); */
  Firebase.setFloat("voltaj", voltaj); /////////////////////////////////////////////////////////////////////float tipi veri gönderme
    if (Firebase.failed()) {//hata kontrolü 
   /*   Serial.print(" ayarlama başarısız:");
      Serial.println(Firebase.error()); */
  }
   yeni.sifirla();//millisi sıfırla
 }

 String lambadurum =Firebase.getString("lamp");/////////////////////////////////////////////////////////////string tipi veri okuma
 //Serial.print("lambadurum=");Serial.println(lambadurum);

 if(lambadurum=="0"){
 digitalWrite(D8,LOW);
 }
 else if(lambadurum=="1"){
 digitalWrite(D8,HIGH);
 }
}
