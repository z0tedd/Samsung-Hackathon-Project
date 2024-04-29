#include <SDS011.h> //библиотека для работы с SDS011
#include <SoftwareSerial.h> // библиотека для работы программного Serial
#include <TroykaMeteoSensor.h>
TroykaMeteoSensor meteoSensor;
#define BTXPin D10 //Bluetooth Software serial tx pin
#define BRXPin D9 //Bluetooth Software serial rx pin
//#define Serial1 HM10

SDS011 my_sds;
//SoftwareSerial HM10(BTXPin, BRXPin);
//SoftwareSerial *softSerial = new SoftwareSerial(D8, D7);
//HardwareSerial port(1);
HardwareSerial Serial1(D2, D8);
void setup() {
  meteoSensor.begin();
  Serial1.begin(9600);
	my_sds.begin(D9,D10); //RX, TX
	Serial.begin(9600);
  while (!Serial){}
  Serial.print("Serial init OK\r\n");
  //mySerial.begin(9600);
}
//بباببانشامبسشنسابينتاشبااغلاخصىوشخعع
void readDataFromSDS011(){
  float p10, p25;
  int error;
  if (p25 > 75) Serial1.println("Dangerous level of pollution!");
  error = my_sds.read(&p25, &p10);
	if (!error) {
    Serial.println("P2.5: " + String(p25));
    Serial.println("P10:  " + String(p10));
		Serial1.println("P2.5: " + String(p25));
		Serial1.println("P10:  " + String(p10));
	}
 /*
  else{
    Serial.println("Error");
  }
  */
}
void readDataFromMeteo(){
  int stateSensor = meteoSensor.read();
  // проверяем состояние данных
  switch (stateSensor) {
    case SHT_OK:
      // выводим показания влажности и температуры
      Serial.println("Data sensor is OK");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureC());
      Serial.println(" C \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureK());
      Serial.println(" K \t");
      Serial.print("Temperature = ");
      Serial.print(meteoSensor.getTemperatureF());
      Serial.println(" F \t");
      Serial.print("Humidity = ");
      Serial.print(meteoSensor.getHumidity());
      Serial.println(" %\r\n");
      break;
    // ошибка данных или сенсор не подключён
    case SHT_ERROR_DATA:
      Serial.println("Data error or sensor not connected");
      break; 
    // ошибка контрольной суммы
    case SHT_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
  }
}
void readDataFromMeteo1(){
  int stateSensor = meteoSensor.read();
  // проверяем состояние данных
  switch (stateSensor) {
    case SHT_OK:
      // выводим показания влажности и температуры
      Serial1.println("Data sensor is OK");
      Serial1.print("Temperature = ");
      Serial1.print(meteoSensor.getTemperatureC());
      Serial1.println(" C \t");
      Serial1.print("Temperature = ");
      Serial1.print(meteoSensor.getTemperatureK());
      Serial1.println(" K \t");
      Serial1.print("Temperature = ");
      Serial1.print(meteoSensor.getTemperatureF());
      Serial1.println(" F \t");
      Serial1.print("Humidity = ");
      Serial1.print(meteoSensor.getHumidity());
      Serial1.println(" %\r\n");
      break;
    // ошибка данных или сенсор не подключён
    case SHT_ERROR_DATA:
      Serial1.println("Data error or sensor not connected");
      break; 
    // ошибка контрольной суммы
    case SHT_ERROR_CHECKSUM:
      Serial1.println("Checksum error");
      break;
  }
}
void loop() {
    //(*softSerial).listen();
    readDataFromSDS011();
    readDataFromMeteo();
    readDataFromMeteo1();
    //HM10.listen();
    if (Serial.available()) Serial1.write(Serial.read());
    if (Serial1.available()) Serial.write(Serial1.read());
    
		delay(1000);
}
