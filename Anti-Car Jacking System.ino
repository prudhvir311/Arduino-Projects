/*
 * The progrm is made for anti car /vehicle as jacking system... GSM 900A controlled relay in general..
 * sms is used for feedbacks and triggering using the STACK CONCEPT
 * FEEDBACKS are given when ever the car is started and stopped....successfully
 * EMERGENCY: if the module get's stopped in middle ...ensuring the security is_on is true...the car will stop in general...
 * DEVICE MUST SAVE....LOCATION PREVIOUS......PHONE_NUMBER_OF_THE_OWNER....on/off...EEPROM..set to +91(Indian...code)
 * GROUP 1-SOC -C 2018
 */
#include <SoftwareSerial.h>
#include "StringSplitter.h"
#define RELAY1  6
#define RELAY2  7
#define SERIAL_BUFFER_SIZE 500
const int ProxSensor=4;
int i=0;
SoftwareSerial modem(3,2); // RX, TX
void setup() {
  // put your setup code here, to run once:   
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);  
  pinMode(RELAY2, OUTPUT); 
  modem.print(SERIAL_BUFFER_SIZE);
  randomSeed(analogRead(0));
  //REGISTER TO THE NETWORK....
  send_AT_command("AT+CREG");//register...
  send_AT_command("AT+CMGF=1");
  delay(500);
  digitalWrite(RELAY1,HIGH);
}

boolean message=false;
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(ProxSensor)==LOW&&message==false)      //Check the sensor output
  {
//VEHICLE IS MOVING......  send and sms...
message=true;
send_sms("+918072691448","The car has started now...if you feel this is unauthorized send SRR for stopping the car and STO for starting the car.");
Serial.print("STARTED \n");
  }

 get_sms_unread();

 }

void car_control(bool is_on){
  //say users for the timer....
  if(is_on==true){
    i=0;
    Serial.print("Index now is: "+i);
while(i<30){
    Serial.print(i);
    digitalWrite(RELAY1,HIGH);
    delay(500);///500 ms...
    digitalWrite(RELAY1,LOW);
    delay(500);
    digitalWrite(RELAY1,HIGH);
    i++;
   }
   //RELAY 2...set to HIGH to stop the vehicle.....
   digitalWrite(RELAY2,HIGH);
  }else{
    //on the car...reset message...
    digitalWrite(RELAY2,LOW);
   //one beep...
       delay(1000);///500 ms...
    digitalWrite(RELAY1,LOW);
    delay(1000);
    digitalWrite(RELAY1,HIGH);
  }
}


/*
 * Remember to get the message and set it as read...must be from the owner.....
 * ERROR HADLING IS MUST....
 * if message in is found for the phone number .....check and stop/start the car....
 * 3 seconds...
 */

void get_sms_unread(){ 
  //918072691448
  
   send_AT_command("AT+CMGF=1");
      String op=send_AT_command("AT+CMGR=1");
   Serial.print("data is  IS : "+op+"\n");
       if(is_found(op,"SRR")!=false){
        Serial.print("SUCCESS.....");
                del_all_sms(op);
        send_sms("+918072691448","The car has stopped successfully.");
        delay(2000);
         car_control(true);
       }else if(is_found(op,"STO")!=false){
             Serial.print("SUCCESS.....2");
                     del_all_sms(op);
           send_sms("+918072691448","The car has been calibrated to start successfully.");
         delay(2000);
         message=false;
         car_control(false);
       }else{
       del_all_sms("");delay(5000);
       }
       
}
/*
 * Remember to send the message in CSV format, with a phone number in internatioal format.....
 * phone_num,message,loc..coordniates....
 */
void send_sms(String phone_num,String message){
  if(phone_num!=NULL&&message!=NULL){
    modem.begin(115200);//setting the BAUD rate...
    Serial.println("AT+CMGF=1");
    delay(1000);
    modem.println("AT+CMGS="+phone_num);
    delay(1000); 
    modem.print(message);
    delay(1000);
      Serial.print(modem.readString());
    modem.println((char)26);
  }
}

/*
 * Using the triangulation method....
 * QUERY USING THE COMMANDS ..
 * Time 5-6 sec....
 */
String get_coor(){
return "NOT_FOUND";        
}


String send_AT_command(String AT){
  modem.begin(115200);//setting the BAUD rate...
   modem.println(AT);
  delay(10);
    return modem.readString();
}

//4 sec delay....
void del_all_sms(String op){

String o=send_AT_command("AT+CMGD=1");//deletion...
Serial.print(o);
//alternative trigging from the owner....
}

boolean is_found(String strA,String strB){
  char str1[strA.length()+1];
  char str2[strB.length()+1];
  strcpy(str1, strA.c_str());
  strcpy(str2, strB.c_str());

   char *ret;

   ret = strstr(str1,str2);

   Serial.println("VAL IS : ");
if(ret!=NULL){
          Serial.println(ret);
          return true;
}else{
        Serial.println("NULL");
           return false;
}
  
}


/*
 * 9 6 7 7 1 8 9 0/1
 * 0 1 2 3 4 5 6 7
 */

