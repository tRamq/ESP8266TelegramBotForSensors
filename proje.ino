#include "CTBot.h"
CTBot myBot;

//wifi baglanti bilgileri
String ssid  = "redmi123"; //wifi adi 
String pass  = "ankara12"; //wifi sifre
String token = "981265245:AAEcnzWxjQlwziWjx-o6sp4XoWwb8lxNEdg"; //Token bot Telegram

const int sensor=A0; // Assigning analog pin A0 to variable 'sensor'
double tempc;
double vout;


//led pinleri
uint8_t led1 = D4;
uint8_t led2 = D3;

void setup()
{


  
  Serial.begin(115200);
  Serial.println("telegram botuna baglaniyor...");



  //wifi baglantisi saglaniyor
  myBot.wifiConnect(ssid, pass);

  //telegram tokeni ayarlaniyor
  myBot.setTelegramToken(token);

  //baglantilar onaylanır.
  if (myBot.testConnection())
    Serial.println("baglanti Ok!");
  else
    Serial.println("hata!");

  //led modlari ayarlanir
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(sensor,INPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}

void loop()
{
  
  //telegram mesaj degiskenleri tanimlanir.
  TBMessage msg;

  //telegramdan msj alinir.
  if (myBot.getNewMessage(msg))
  {
   
    if (msg.text.equalsIgnoreCase("on1"))
    {
     
      digitalWrite(led1, LOW);
      
      myBot.sendMessage(msg.sender.id, "LED 1 YANIYO!");
    }
    else if (msg.text.equalsIgnoreCase("off1"))
    {
      digitalWrite(led1, HIGH);
      myBot.sendMessage(msg.sender.id, "LED 1 SONUYO!");
    }
    else if (msg.text.equalsIgnoreCase("on2"))
    {
      digitalWrite(led2, LOW);
      myBot.sendMessage(msg.sender.id, "LED 2 YANIYO!");
    }
    else if (msg.text.equalsIgnoreCase("off2"))
    {
      digitalWrite(led2, HIGH);
      myBot.sendMessage(msg.sender.id, "LED 2 SONUYO!");
    }

    else if(msg.text.equalsIgnoreCase("sicaklik"))
    {
       vout=analogRead(sensor);
        vout=((vout*500)/1024);
        
        tempc=vout; // Storing value in Degree Celsius
        String cevap;
        cevap=(String)"Sicaklik degeri  " +msg.sender.username+(String)tempc;
        
        myBot.sendMessage(msg.sender.id,cevap);
      
    }
    else
    {
      
      String reply;
      reply = (String)"MERHABA " + msg.sender.username + (String)"! YANLIS GIRIS YAPTİNİZ TEKRAR DENEYİN!";
      myBot.sendMessage(msg.sender.id, reply);
    }
  }
  delay(100);


}
