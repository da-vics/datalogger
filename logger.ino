#include "uvsen.h"
#include <SPI.h>
#include <SD.h>

#define DEBUG true
#define RX 2
#define TX 3
#define dht_apin A1
const int chipSelect = 4;

String HOST = "api.thingspeak.com";
String PORT = "80";
char AP[] = "project";
String PASS = "project101";


String API_v = "X0D8IS384RPRFPLH";
String API_c = "LL7RAIDAIJK7IQ1G";

String field1v = "field1";
String field2v = "field2";
String field1c = "field1";
String field2c = "field2";
String field7c = "field7";




int countTrueCommand;
int countTimeCommand;
boolean found = false;
int valSensor = 1;
double hum;
double temp;
double dust;
double rad;

float vol;
float vol2;
float current;
float current2;

bool connected_d = false;
double uvIntensity;

short indi = 13;


void setup() {

  Serial.begin(9600);


  pinMode(indi , OUTPUT);
  digitalWrite(indi , LOW);


  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");

  }
  if (!SD.exists("datalog2.txt")) {


    File datafile2 = SD.open("datalog2.txt", FILE_WRITE);

    Serial.println("card initialized.");

    datafile2.print("UV");
    datafile2.print("\t");
    datafile2.print("\t");

    datafile2.print("CURRENT 1");
    datafile2.print("\t");
    datafile2.print("\t");
    

    datafile2.print("CURRENT 2");
    datafile2.print("\t");
    datafile2.print("\t");
 
    datafile2.print("VOLTAGE 1");
    datafile2.print("\t");
    datafile2.print("\t");
  

    datafile2.print("VOLTAGE 2");
    datafile2.print("\t");
    datafile2.print("\t");

    datafile2.println();
    datafile2.close();
  }






} ///

void loop() {



  get_uv(uvIntensity);
  rawvalue(current , current2 , vol , vol2);
  File datafile = SD.open("datalog2.txt", FILE_WRITE);




  if (datafile) {


        datafile.print(uvIntensity, 3);
    datafile.print("\t");
    datafile.print("\t");
    
    datafile.print(current, 3);
    datafile.print("\t");
      datafile.print("\t");
      datafile.print("\t");
    
    
    ///dataFile.close();

    datafile.print(current2, 3);
    datafile.print("\t");
    datafile.print("\t");
     datafile.print("\t");

     

    datafile.print(vol, 3);
    datafile.print("\t");
    datafile.print("\t");
    datafile.print("\t");

    datafile.print(vol2, 3);
    

    datafile.println();
    datafile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog2.txt");
  }



}




void rawvalue(float &current , float &current2 , float &voltage , float &voltage2) {
  
  int VT_PIN = A4; 
  int  AT_PIN  = A2;
  
  int VT_PIN2 = A5; 
  int  AT_PIN2  = A3;
  
  int vt_read = analogRead(VT_PIN);
  int at_read = analogRead(AT_PIN);

  float vol = vt_read * (4.97 / 1024.0) * 4.97;
  float cur = at_read * (4.97 / 1024.0);

  current = cur;
  voltage = vol;
  
  Serial.print("Volts: "); 
  Serial.print(vol, 3);
  Serial.print("\tAmps: ");
  Serial.print(cur,3);
  Serial.println();

   int vt_read2 = analogRead(VT_PIN2);
  int at_read2 = analogRead(AT_PIN2);

  float vol2 = vt_read2 * (4.97 / 1024.0) * 4.97;
  float cur2 = at_read2 * (4.97 / 1024.0);

  current2 = cur2;
  voltage2 = vol2;
  
  Serial.print("Volts2: "); 
  Serial.print(vol2, 3);
  Serial.print("\tAmps2: ");
  Serial.print(cur2,3);
  Serial.println();
 

}


void timee(int x) {
  long long tim = millis();

  while (1) {



    if ( millis() - tim >= x) {
      break;
    }

  }

}
