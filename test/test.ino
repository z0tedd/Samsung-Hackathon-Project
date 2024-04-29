#include <WiFi.h>
#include <PubSubClient.h> // MQTT Client

const char* ssid = "free.wifi.kursksu.net";
const char* password = "kursksu.ru";

const char* mqttserver = "130.193.44.244"; //mqtt.cloud.yandex.net
const char* yandexIoTCoredeviceId = "arebm3o4d2kopsp0l494";
const char* mqttpassword = "yi5T76tLNadoxix7SXtR";
const int mqttport=8883;


String Bebra = String("{\"device_timestamp\": \"2024-04-17T08:28:47.340Z\", \"device_name\": \"iot_test_device\",  \"sensor_model\": \"sds011\", \"location\": [{\"latitude\": \"55.796441\"}, {\"longitude\": \"37.600502\"}], \"sensordatavalues\": [{\"value_type\": \"PM2_5\", \"value\": \"4.9\"}, {\"value_type\": \"PM10\", \"value\": \"7.1\"}]");
String topicCommands = String("$devices/")+String(yandexIoTCoredeviceId)+String("/commands/#");
String topicEvents = String("$devices/")+String(yandexIoTCoredeviceId)+String("/events/");
String SpecialMsg = String("{\"device_timestamp\":") + 
String("\"2024-09-17T08:15:47.340Z\",")+
String("\"device_name\": \"device_26\", ")+
String("\"sensor_model\": \"sds011\", \"location\":")+
String("[{\"latitude\": \"55.796441\"}, {\"longitude\":")+
String("\"37.600502\"}], \"sensordatavalues\": [{\"value_type\":")+
String("\"PM2_5\", \"value\": \"4.9\"},")+
String("{\"value_type\": \"PM10\", \"value\": \"7.1\"}]}");
const char* test_root_ca = \
"-----BEGIN CERTIFICATE-----\n \
MIIFGTCCAwGgAwIBAgIQJMM7ZIy2SYxCBgK7WcFwnjANBgkqhkiG9w0BAQ0FADAf\
MR0wGwYDVQQDExRZYW5kZXhJbnRlcm5hbFJvb3RDQTAeFw0xMzAyMTExMzQxNDNa\
Fw0zMzAyMTExMzUxNDJaMB8xHTAbBgNVBAMTFFlhbmRleEludGVybmFsUm9vdENB\
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAgb4xoQjBQ7oEFk8EHVGy\
1pDEmPWw0Wgw5nX9RM7LL2xQWyUuEq+Lf9Dgh+O725aZ9+SO2oEs47DHHt81/fne\
5N6xOftRrCpy8hGtUR/A3bvjnQgjs+zdXvcO9cTuuzzPTFSts/iZATZsAruiepMx\
SGj9S1fGwvYws/yiXWNoNBz4Tu1Tlp0g+5fp/ADjnxc6DqNk6w01mJRDbx+6rlBO\
aIH2tQmJXDVoFdrhmBK9qOfjxWlIYGy83TnrvdXwi5mKTMtpEREMgyNLX75UjpvO\
NkZgBvEXPQq+g91wBGsWIE2sYlguXiBniQgAJOyRuSdTxcJoG8tZkLDPRi5RouWY\
gxXr13edn1TRDGco2hkdtSUBlajBMSvAq+H0hkslzWD/R+BXkn9dh0/DFnxVt4XU\
5JbFyd/sKV/rF4Vygfw9ssh1ZIWdqkfZ2QXOZ2gH4AEeoN/9vEfUPwqPVzL0XEZK\
r4s2WjU9mE5tHrVsQOZ80wnvYHYi2JHbl0hr5ghs4RIyJwx6LEEnj2tzMFec4f7o\
dQeSsZpgRJmpvpAfRTxhIRjZBrKxnMytedAkUPguBQwjVCn7+EaKiJfpu42JG8Mm\
+/dHi+Q9Tc+0tX5pKOIpQMlMxMHw8MfPmUjC3AAd9lsmCtuybYoeN2IRdbzzchJ8\
l1ZuoI3gH7pcIeElfVSqSBkCAwEAAaNRME8wCwYDVR0PBAQDAgGGMA8GA1UdEwEB\
/wQFMAMBAf8wHQYDVR0OBBYEFKu5xf+h7+ZTHTM5IoTRdtQ3Ti1qMBAGCSsGAQQB\
gjcVAQQDAgEAMA0GCSqGSIb3DQEBDQUAA4ICAQAVpyJ1qLjqRLC34F1UXkC3vxpO\
nV6WgzpzA+DUNog4Y6RhTnh0Bsir+I+FTl0zFCm7JpT/3NP9VjfEitMkHehmHhQK\
c7cIBZSF62K477OTvLz+9ku2O/bGTtYv9fAvR4BmzFfyPDoAKOjJSghD1p/7El+1\
eSjvcUBzLnBUtxO/iYXRNo7B3+1qo4F5Hz7rPRLI0UWW/0UAfVCO2fFtyF6C1iEY\
/q0Ldbf3YIaMkf2WgGhnX9yH/8OiIij2r0LVNHS811apyycjep8y/NkG4q1Z9jEi\
VEX3P6NEL8dWtXQlvlNGMcfDT3lmB+tS32CPEUwce/Ble646rukbERRwFfxXojpf\
C6ium+LtJc7qnK6ygnYF4D6mz4H+3WaxJd1S1hGQxOb/3WVw63tZFnN62F6/nc5g\
6T44Yb7ND6y3nVcygLpbQsws6HsjX65CoSjrrPn0YhKxNBscF7M7tLTW/5LK9uhk\
yjRCkJ0YagpeLxfV1l1ZJZaTPZvY9+ylHnWHhzlq0FzcrooSSsp4i44DB2K7O2ID\
87leymZkKUY6PMDa4GkDJx0dG4UXDhRETMf+NkYgtLJ+UIzMNskwVDcxO4kVL+Hi\
Pj78bnC5yCw8P5YylR45LdxLzLO68unoXOyFz1etGXzszw8lJI9LNubYxk77mK8H\
LpuQKbSbIERsmR+QqQ==\
-----END CERTIFICATE-----\n";

WiFiClientSecure  net;
PubSubClient client(net);
BearSSL::X509List x509(test_root_ca);

#define DEBUG_SERIAL Serial
#define DEBUG_SERIAL_BAUDRATE 115200

void connect() {
  delay(5000);
  DEBUG_SERIAL.print("Conecting to wifi ...");
  while (WiFi.status() != WL_CONNECTED) {
    DEBUG_SERIAL.print(".");
    delay(1000);
  }
  DEBUG_SERIAL.println(" Connected");
  net.setInsecure();
  DEBUG_SERIAL.print("Connecting to Yandex IoT Core as");
  DEBUG_SERIAL.print(yandexIoTCoredeviceId);
  DEBUG_SERIAL.print(" ...");
  while (!client.connect("Esp8266Client", yandexIoTCoredeviceId, mqttpassword)) {
    DEBUG_SERIAL.print(".");
    delay(1000);
  }
  DEBUG_SERIAL.println(" Connected");
  if (client.publish(topicEvents.c_str(), yandexIoTCoredeviceId)) {
      DEBUG_SERIAL.println("Publish ok");
    }
    else {
      DEBUG_SERIAL.println("Publish failed");
    }
  DEBUG_SERIAL.println("Subscribe to: ");
  DEBUG_SERIAL.print(topicCommands.c_str());
  client.subscribe(topicCommands.c_str());
}

void setup() {
  DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUDRATE);
  delay(10);
  DEBUG_SERIAL.println("Device started");
  WiFi.begin(ssid, password);
  client.setServer(mqttserver, mqttport);
  client.setCallback(messageReceived);
  client.setBufferSize(1024);
  client.setKeepAlive(15);
  connect();
}

void messageReceived(char* topic, byte* payload, unsigned int length) {
  String topicString = String(topic);
  DEBUG_SERIAL.print("Message received. Topic: ");
  DEBUG_SERIAL.println(topicString.c_str());
  String payloadStr = "";
  for (int i=0;i<length;i++) {
    payloadStr += (char)payload[i];
  }
  DEBUG_SERIAL.print("Payload: ");
  DEBUG_SERIAL.println(payloadStr);
}

void loop() {
  // put your main code here, to run repeatedly:
  client.loop();
  if (!client.connected()) {
    connect();
  }
  if (client.publish(topicEvents.c_str(), Bebra.c_str())) {
      DEBUG_SERIAL.println("Publish ok\n");
    }
    else {
      DEBUG_SERIAL.println("Publish failed\n");
    }
    DEBUG_SERIAL.println("Subscribe to: ");
    DEBUG_SERIAL.print(topicCommands.c_str());
    client.subscribe(topicCommands.c_str());
  delay(1000);
}

/*
#include <ESP8266WiFi.h>

IPAddress ip(192,168,1,1);
IPAddress shluz(192,168,1,1);
IPAddress podset(255,255,255,0);
WiFiServer server(80);

const char* ssid = "IT Academy Wi-Fi";
const char* password = "05524204";
const int LED_0 = 16;
bool Led1status = LOW;
int a = 0;
float temperature = 27.8f;

void setup(){
   Serial.begin(115200);
   pinMode(LED_0,OUTPUT);
   WiFi.mode(WIFI_AP);
   WiFi.softAPConfig(ip,shluz,podset);
   WiFi.softAP(ssid,password);

   delay(350);
   Serial.print("\n\r");
   Serial.print("Подклю");
   Serial.print("\n\r");

   while ((WiFi.softAPgetStationNum() == 0)&& (a<58)){
      Serial.print('.');
      delay(350);
      a++;
      if(a==29) Serial.print("\n\r");
      if (a==58){
        Serial.print("\n\r");
        Serial.println("WIFI IS TURNED OFF");
      }
   }
   if ((WiFi.softAPgetStationNum() != 0)){
      Serial.print("\n\r");
        Serial.println("WIFI IS TURNED onn");
      for (byte s=0;s<3;s++){
        Serial.println("diod onn");
        delay(350);
        Serial.println("diod off");
        delay(350);
      }
   }
   
}
void loop(){
  WiFiClient client = server.available();
  if (!client){return ;}
  Serial.println("get");
  while(!client.available())  {delay(1);}

  String req = client.readStringUntil('\r');
  req = req.substring(5);
  req.replace("%20"," ");
  int h = req.indexOf(" HTTP/1.1");
  String name = req.substring(0,h);
  Serial.println(name);

  controller(req,client);
  client.flush();

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s+= temperature     ;

  client.print(s);
  delay(1);
  Serial.println("Finish");
  Serial.print("\n\r");
}

void controller(String req, WiFiClient client){
  if (req.indexOf("ledon")!= -1){
      Serial.println("diod on");
  }
  else 
  if (req.indexOf("ledof")!=-1)
  {
    Serial.println("diod off");
  }
  else{
    Serial.println("fooo");
  }
}
*/

/* 
 *  
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(D8, D7); // RX (получение данных) на D3, TX (отправка данных) на D4

void setup() {
  BTSerial.listen();
  Serial.begin(9600); // Скорость обмена данными с монитором порта
  BTSerial.begin(9600); // Скорость обмена данными с Bluetooth модулем
}

void loop() {
  if (BTSerial.available()) { // Если доступны данные от Bluetooth
    char receivedChar = BTSerial.read(); // Считываем данные
    Serial.println(receivedChar); // Выводим принятые данные в монитор порта
  }
  delay(100);
}
*/

/*
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "IT Academy Wi-Fi"; // Замените на имя вашей Wi-Fi сети
const char *password = "05524204"; // Замените на пароль от вашей Wi-Fi сети

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Ожидание подключения к Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Запуск веб-сервера
  server.on("/data", HTTP_POST, [](){
    if (server.hasArg("plain")) {
      Serial.println("Received data: " + server.arg("plain"));
    }
    server.send(200, "text/plain", "OK");
  });
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

*/
/*
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "IT Academy Wi-Fi";      // Название вашей Wi-Fi сети
const char* password = "05524204";  // Пароль от вашей Wi-Fi сети

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Подключение к Wi-Fi сети
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  // Запуск веб-сервера на порту 80
  server.on("/", HTTP_GET, [](){
    server.send(200, "text/plain", "Hello from ESP8266");
  });
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP());
  //Serial.println(server.localIP());
}

void loop() {
  server.handleClient();
}
*/
/*#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(100);

  // Подключение к Wi-Fi сети
  WiFi.begin("IT Academy Wi-Fi", "05524204");

  Serial.println("");
  Serial.println("Подключение к Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Успешно подключено к Wi-Fi!");

  // Вывод IP-адреса
  Serial.print("IP-адрес: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
*/
/*
#include<ESP8266WiFi.h>

// WiFi Definitions
const char* ssid = "IT Academy Wi-Fi";
const char* password = "05524204"; // has to be longer than 7 chars
const char* value = "";

int ledPin = 13; // GPIO13
WiFiServer server(80);

void setup() {

   Serial.begin(115200);
   delay(10);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH); // turn on

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password, 1, 1);
  
   server.begin();
   Serial.println(WiFi.localIP());
}

void loop() {
  // Check of client has connected
  WiFiClient client = server.available();
  if(!client) {
    return;
  }

  // Read the request line
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match request
  if(request.indexOf("/led/on") != -1) {
     digitalWrite(ledPin, HIGH);
     value = "on";
  } else if (request.indexOf("/led/off") != -1) {
     digitalWrite(ledPin, LOW);
      value = "off";
  }
  
  client.flush();
   
  // JSON response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: application/json\r\n\r\n";
  s += "{\"data\":{\"message\":\"success\",\"value\":\"";
  s += value;
  s += "\"}}\r\n";
  s += "\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected when the function returns and the client object is destroyed
}
*/
/*

// библиотека для работы программного Serial

#include <SoftwareSerial.h>
 
// создаём объект для работы с программным Serial
// и передаём ему пины TX и RX
SoftwareSerial mySerial(8, 7);
 
// serial-порт к которому подключён Wi-Fi модуль
#define WIFI_SERIAL    mySerial
 
void setup()
{
  // открываем последовательный порт для мониторинга действий в программе
  // и передаём скорость 9600 бод
  Serial.begin(9600);
  while (!Serial) {
  // ждём, пока не откроется монитор последовательного порта
  // для того, чтобы отследить все события в программе
  }
  Serial.print("Serial init OK\r\n");
  // открываем Serial-соединение с Wi-Fi модулем на скорости 9600 бод
  WIFI_SERIAL.begin(9600);
}
 
void loop()
{
  // если приходят данные из Wi-Fi модуля - отправим их в порт компьютера
  if (WIFI_SERIAL.available()) {
    Serial.write(WIFI_SERIAL.read());
  }
  // если приходят данные из компьютера - отправим их в Wi-Fi модуль
  if (Serial.available()) {
    WIFI_SERIAL.write(Serial.read());
  }
}

*/



/*
#include <SDS011.h>

float p10, p25;
int error;

SDS011 my_sds;

void setup() {
	my_sds.begin(D8, D7); //RX, TX
	Serial.begin(9600);
}
void readDataFromSDS011(){
  error = my_sds.read(&p25, &p10);
	if (!error) {
		Serial.println("P2.5: " + String(p25));
		Serial.println("P10:  " + String(p10));
	}
}
void loop() {
		delay(100);
}
*/
