#include <ArduinoJson.h>
 #include <EEPROM.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"

#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
//"WIFI_221";
//static const char* WIFI_PASS = "221_hostel61";
#include <ESP32Servo.h>
const char* ssid     = "WIFI_221";//"Suman-JioFiber-4G";//"realme 6";   //WIFI SSID WIFI_221//
const char* password = "221_hostel61";//"SDsuman06#";//"donotaskme";   //WIFI password221_hostel6"221_hostel6";//
//String token = "5457437715:AAGjlo3VKmrLI8Guv9D4roZfDAZ1uYnbyiM";//
 //String token=  "5868109345:AAFJMlKpi7S4lDWhBxHC2FqcEF_FUWedvWA";//
  //String token =   "6117248989:AAF-5vlZU1YUjWAX0CqpTrlNINwsUxtmwog";//
 String token = "5457437715:AAFMyoy0ubgH3RsgyrND6sKNODinpXoCniI";
           
String chat_id = "1058093244"; //;//
//String chat_id="1635819206";
//String chat_id="1116751308";
String Cht_ID = "";
//#define Cht_ID "1635819206"
String Cht_ID2 ="";
String Cht_ID3 ="";
/**/
WiFiClientSecure clientTCP;
UniversalTelegramBot bot(token, clientTCP);
Servo myservo;
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

//pins
#define PIR 13
#define LDR 15
#define RADAR 14
#define REL1 3
#define REL2 1
#define ServoPin  12
#define buzzer  2

#define Read_PIR   digitalRead(PIR)   
#define  Read_LDR  digitalRead(LDR) 
#define Read_RADAR digitalRead(RADAR) 
#define REL1_ON  digitalWrite(REL1,1) 
#define REL1_OFF digitalWrite(REL1,0) 
#define REL2_ON  digitalWrite(REL2,1) 
#define REL2_OFF digitalWrite(REL2,0) 

int pir1 = 0,L1=0,L2=0,RDR=0, count=0,count1=0, count2=0;
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
#define Waiting_period    3000   //milisec
#define Update_period    2000   //milisec
#define Ldr_threshold 700
#define Ldr_TurnoffRange 600

bool Relay1_status=false,Relay2_status=false,temp1=false,temp2=false,temp3=false,servos=false; 
uint32_t privious_time;
uint32_t privious_time1;

#define FLASH_LED_PIN 4
bool flashState = LOW,sendPhoto = false, motionDetected = false;

//*****************************
void myservo (int Pin_No, int angle){
int Time_pos= map(angle, 0,180,550,2450);int minval=2450-Time_pos;
  digitalWrite(Pin_No,1);  delayMicroseconds(Time_pos);
  digitalWrite(Pin_No,0);  delayMicroseconds(minval);
}*/
//*****************************
void EEPROMWRITE(int addr, const String &data)
{  byte Length = data.length();  EEPROM.write(addr, Length);EEPROM.commit(); 
  for (int i = 0; i < Length; i++){EEPROM.write(addr + 1 + i, data[i]);EEPROM.commit();   }
}

//*****************************

String EEPROMREAD(int addr)
{  int Length = EEPROM.read(addr);  char data[Length + 1];
  for (int i = 0; i < Length; i++)  {    data[i] = EEPROM.read(addr + 1 + i);  }  
  data[Length] = '\0';     return String(data);
}
//*******************************

void EEPROM_READ( ){pir1 = EEPROM.read(10);RDR = EEPROM.read(11);L1 = EEPROM.read(12);L2 = EEPROM.read(13);}
//*******************************

void EEPROM_WRITE(int addr, int val ){EEPROM.write(addr,val);EEPROM.commit();}
//*******************************
void handleNewMessages(int numNewMessages){//Serial.println(" 1New message"); 
  for (int i = 0; i < numNewMessages; i++)  {// Serial.println(" New message"); 
    String chat_id = bot.messages[i].chat_id;      // Serial.print(" chat id "); Serial.println(chat_id);// Cht_ID=chat_id;
    String text = bot.messages[i].text;   // Serial.print(" message is"); Serial.println(text); 
    EEPROM_READ( );
   String from_name = bot.messages[i].from_name;   
   if (from_name == "")      from_name = "Guest";    
if (text == "/SENSOROFF"){pir1 = 0;RDR=0 ;  EEPROM_WRITE(10,pir1);EEPROM_WRITE(11,RDR);      bot.sendMessage(chat_id, "ALL SENSORS ARE OFF", "");    }
if (text == "/SENSORON"){pir1 = 1;RDR=1 ;EEPROM_WRITE(10,pir1); EEPROM_WRITE(11,RDR);bot.sendMessage(chat_id, "ALL SENSORS ARE ON", "");    }
if (text == "/PIR1OFF")    { pir1=0;  EEPROM_WRITE(10,pir1);       bot.sendMessage(chat_id, "PIR SENSOR IS OFF", "");    }
 if (text == "/PIR1ON")    { pir1=1;  EEPROM_WRITE(10,pir1);       bot.sendMessage(chat_id, "PIR SENSOR IS ON", "");    }
if (text == "/RadarOFF")    { RDR=0;  EEPROM_WRITE(11,RDR);      bot.sendMessage(chat_id, "Radar SENSOR IS OFF", "");    }
 if (text == "/RadarON")    { RDR=1;  EEPROM_WRITE(11,RDR);      bot.sendMessage(chat_id, "Radar SENSOR IS ON", "");    }
            
 if (text == "/status")  {EEPROM_READ();
 String text1="";
if (pir1==1){ text1="PIR SENSOR IS ON\n" ;   } if (pir1==0){text1="PIR SENSOR IS OFF\n" ;    }
if (RDR==1){ text1+="Radar SENSOR IS ON\n"; }if (RDR==0){text1+="Radar SENSOR IS OFF\n";     }
if (L2==1){ text1+="RELAY2 IS ON\n"; } if (L2==0) {  text1+="RELAY2 IS OFF\n";     }
if (L1==1){ text1+="RELAY1 IS ON\n"; }if (L1==0){  text1+="RELAY1 IS OFF\n";     }
  bot.sendMessage(chat_id, text1, ""); 
 }
if (text=="/SERVOOFF"){  servos=false; myservo.write(10);;bot.sendMessage(chat_id, "SERVO IS OFF", "");}
if (text=="/SERVOON"){  servos=true;bot.sendMessage(chat_id, "SERVO IS ON", "");}

if (text == "/ADDCHATID"){Cht_ID=chat_id;EEPROMWRITE(50, chat_id);bot.sendMessage(chat_id, "Chat ID "+chat_id+" is added", "");}
if (text == "/RELAY2ON"){if (!Relay2_status){REL2_ON;Relay2_status=true;bot.sendMessage(chat_id, "Relay2 is on", "");EEPROM_WRITE(13,1);}}
if (text == "/RELAY2OFF"){REL2_OFF;Relay2_status=false;bot.sendMessage(chat_id, "Relay2 is off", "");EEPROM_WRITE(13,0);}

if (text == "/photo"){bot.sendMessage(chat_id, "Sending photo", "");sendPhotoTelegram();delay(1000);}
if (text == "/start")
    { String welcome = "TELEGRAM USER..., " + from_name + ".\n";
      welcome += "/SENSORON : to turn on  all the sensors \n";
      welcome += "/SENSOROFF : to turn off all the sensors\n";
      welcome += "/status : to check the status of the sensors\n";
      welcome += "/start : to get welcome SMS\n";
      welcome +=  "/PIR1OFF : to turn off PIR Sensor\n";
      welcome +=  "/PIR1ON : to turn on PIR Sensor\n";
      welcome +=  "/RadarON : to turn on Radar Sensor\n";
      welcome +=  "/RadarOFF : to turn off Radar Sensor\n";
      welcome +=  "/RELAY2ON : to turn on relay2\n";
      welcome +=  "/RELAY2OFF : to turnoff relay2\n";
      welcome +=  "/ADDCHATID : to add new chat id\n";
       welcome +=  "/photo : to get photo\n";
       welcome +=  "/SERVOON : to Start the servo\n";
       welcome +=  "/SERVOOFF : to Stop the servo\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
}}
//****************************
String sendPhotoTelegram(){
  const char* myDomain = "api.telegram.org";
  String getAll="", getBody = "";
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {     delay(1000);    ESP.restart();   return "Camera capture failed";  }  
   
   if (clientTCP.connect(myDomain, 443)) { //Serial.println("Connected to " + String(myDomain));
    String head = "--India\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + Cht_ID + "\r\n--India\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
       String tail = "\r\n--India--\r\n";
    uint16_t imageLen = fb->len;
    uint16_t extraLen = head.length() + tail.length();
    uint16_t totalLen = imageLen + extraLen;
    clientTCP.println("POST /bot"+token+"/sendPhoto HTTP/1.1");
    clientTCP.println("Host: " + String(myDomain));
    clientTCP.println("Content-Length: " + String(totalLen));
    clientTCP.println("Content-Type: multipart/form-data; boundary=India");
    clientTCP.println();
    clientTCP.print(head);
      uint8_t *fbBuf = fb->buf;    size_t fbLen = fb->len;
   for (size_t n=0;n<fbLen;n=n+1024) {      if (n+1024<fbLen) 
 {      clientTCP.write(fbBuf, 1024);    fbBuf += 1024;   }      else if (fbLen%1024>0) 
{      size_t remainder = fbLen%1024;      clientTCP.write(fbBuf, remainder);      }    }  
     clientTCP.print(tail); esp_camera_fb_return(fb);    
    int waitTime = 10000;   // timeout 10 seconds
    long startTime = millis(); boolean state = false;
     while ((startTime + waitTime) > millis())
    { Serial.print(".");  delay(100);      
      while (clientTCP.available()) { char c = clientTCP.read();
          if (c == '\n') {if (getAll.length()==0) state=true; getAll = ""; } 
          else if (c != '\r')  getAll += String(c);
          if (state==true) getBody += String(c);          startTime = millis();   }
       if (getBody.length()>0) break;  }
    clientTCP.stop();// Serial.println(getBody);  
    }
  else { getBody = "Connection to telegram failed.";
    //Serial.println("Connection to telegram failed."); 
    }
    return getBody;
    }
//***************************
  static void IRAM_ATTR detectsMovement(void * arg){
 if (pir1==1){  sendPhoto=true;}}
 

//*************************
void camera_config(){
camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;  config.ledc_timer = LEDC_TIMER_0;  config.pin_d0 = Y2_GPIO_NUM;  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;  config.pin_d3 = Y5_GPIO_NUM;  config.pin_d4 = Y6_GPIO_NUM;  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;  config.pin_d7 = Y9_GPIO_NUM;  config.pin_xclk = XCLK_GPIO_NUM;  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;  config.pin_href = HREF_GPIO_NUM;  config.pin_sscb_sda = SIOD_GPIO_NUM;  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;  config.pin_reset = RESET_GPIO_NUM;  config.xclk_freq_hz = 20000000;  config.pixel_format = PIXFORMAT_JPEG;
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;    config.jpeg_quality = 10;  //0-63 lower number means higher quality
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;    config.jpeg_quality = 12;  //0-63 lower number means higher quality
    config.fb_count = 1;  }
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {    //Serial.printf("Camera init failed with error 0x%x", err);  
  delay(1000);    ESP.restart();  }
  sensor_t * s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_CIF);  // UXGA|SXGA|XGA|SVGA|VGA|CIF|QVGA|HQVGA|QQVGA
  err = gpio_isr_handler_add(GPIO_NUM_13, &detectsMovement, (void *) 13);  
  if (err != ESP_OK){    }
  err = gpio_set_intr_type(GPIO_NUM_13, GPIO_INTR_POSEDGE);
  if (err != ESP_OK){      }

//****************************
  
 // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(config.pixel_format == PIXFORMAT_JPEG){
    if(psramFound()){
      config.jpeg_quality = 10;
      config.fb_count = 2;
      config.grab_mode = CAMERA_GRAB_LATEST;
    } else {
      // Limit the frame size when PSRAM is not available
      config.frame_size = FRAMESIZE_SVGA;
      config.fb_location = CAMERA_FB_IN_DRAM;
    }
  } else {
    // Best option for face detection/recognition
    config.frame_size = FRAMESIZE_240X240;
#if CONFIG_IDF_TARGET_ESP32S3
    config.fb_count = 2;
#endif
  }
#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif
  // drop down frame size for higher initial frame rate
  if(config.pixel_format == PIXFORMAT_JPEG){
    s->set_framesize(s, FRAMESIZE_QVGA);
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif


}

//*************************


void setup() {  //Serial.begin(115200);
 WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
   EEPROM.begin(200);
   pinMode(PIR, INPUT); 
   pinMode(RADAR, INPUT);  
   pinMode(LDR, INPUT); 
   pinMode(REL1, OUTPUT);
   pinMode(REL2, OUTPUT); 
   pinMode(buzzer, OUTPUT);
   pinMode(FLASH_LED_PIN, OUTPUT);digitalWrite(FLASH_LED_PIN ,0);
 digitalWrite(RADAR, 0); REL1_OFF;REL2_OFF ; delay(10);
Cht_ID=EEPROMREAD(50);
EEPROM_READ( );
camera_config();

myservo.attach(ServoPin);//pinMode(ServoPin, OUTPUT); 

   WiFi.mode(WIFI_STA);  Serial.println("");
  //Serial.print("Connecting to ");  Serial.println(ssid);
  WiFi.begin(ssid, password);    long int StartTime=millis();
  while (WiFi.status() != WL_CONNECTED) 
  {digitalWrite(FLASH_LED_PIN ,1);   delay(500);digitalWrite(FLASH_LED_PIN ,0);    if ((StartTime+10000) < millis()) break;  } 
  digitalWrite(FLASH_LED_PIN ,0);
 clientTCP.setCACert(TELEGRAM_CERTIFICATE_ROOT);
 if (WiFi.status() != WL_CONNECTED) {   } //ESP.restart(); Serial.println("Reset"); 
  
bot.sendMessage(chat_id, "hii.... device started", "");


}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);//Serial.println(numNewMessages);
    while (numNewMessages) {        handleNewMessages(numNewMessages);  //Serial.println("got response");  
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }    lastTimeBotRan = millis();
  }
  
if (sendPhoto) {  bot.sendMessage(chat_id, "THIEF DETECTED ON PIR", ""); digitalWrite(FLASH_LED_PIN ,1); 
                  sendPhotoTelegram();digitalWrite(FLASH_LED_PIN ,0);  sendPhoto=false;    delay(1000); }
                  
if ((Read_LDR==1)&&(Read_PIR==1)&&(Relay1_status==false)){  REL1_ON; EEPROM_WRITE(12,1);Relay1_status=true;} 
else if((Read_LDR==1)&&(Relay1_status==true)) {  REL1_OFF;Relay1_status=false;EEPROM_WRITE(12,0);
}

if (pir1==1){ 
if (Read_PIR==1){temp1=true;count1++; if(count1==2){tone(buzzer, 200,1500);
bot.sendMessage(Cht_ID,"Object  DETECTED  on PIR", "");sendPhoto=true; noTone(buzzer);    } }
else{count1=0;temp1=false;}}else{}//Serial.println("loopd1 ");

if (RDR==1){
if ((Read_RADAR)&&(millis() - privious_time > Waiting_period))
{  temp2=true;count2++;count=0;if(count2==1){ bot.sendMessage(Cht_ID,"Object  DETECTED  on RADAR", "");count2++;}
 privious_time=millis();
 }else{ temp2=false;count1=0;count2=0;count++;if(count==1){   count++;}}
}

if (servos==true){//int num=text.toInt();
  for (int a=10;a<100;a++){   myservo.write(a); delay(80); }
  for (int a=100;a>10;a--){   myservo.write(a); delay(80); }
}

if (millis() - privious_time1 > Update_period){
 privious_time1=millis();//Serial_Update();
}
