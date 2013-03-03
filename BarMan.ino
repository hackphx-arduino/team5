#include <SoftwareSerial.h>
#include <Shieldbot.h>

Shieldbot shieldbot = Shieldbot();
int polls[5];
int line;
int deliver=1;
boolean stopped=0;
byte postion=0;
byte lastDir=0;
void setup(){
  Serial.begin(19200);
  pinMode(13, OUTPUT);
  digitalWrite(13,1);
}

void loop(){
  if(onLine()){
    if(onSquare()){
      shieldbot.drive(0,0);
      delay(1000);
      shieldbot.drive(100,100);
      postion+=1;
      postion=postion%5;
      if(postion==deliver){
        digitalWrite(13,0);
        shieldbot.drive(40,40);
        delay(500);
        digitalWrite(13,1);
      }
    }else if(!polls[2]){
      shieldbot.forward();
    }else if(!polls[1]){
      shieldbot.drive(80,0);
      lastDir=0;
    }else if(!polls[3]){
      shieldbot.drive(0,80);
      lastDir=1;
    }else if(!polls[0]){
      shieldbot.drive(50,0);
      lastDir=0;
    }else if(!polls[4]){
      shieldbot.drive(0,50);
      lastDir=1;
    }
    
    for(int i=0;i<5;i++){
      Serial.print(polls[i]);
      Serial.print(',');
    }
    Serial.print(onLine());
    Serial.println(';');
  }
  //If not on line, reverse towards last know direction
  if(lastDir==0){
    shieldbot.drive(0,-32);
  }
  else{shieldbot.drive(-32,0);}
}

boolean onLine(){
  pollSensors();
  if(!polls[0]||!polls[1]||!polls[2]||!polls[3]||!polls[4]){
    return true;
  }
  else{return false;}
}

boolean onSquare(){
  pollSensors();
  if(!polls[0]&&!polls[1]&&!polls[2]&&!polls[3]&&!polls[4]){
    return true;
  }
  else{return false;}
}

void pollSensors(){
  polls[0]=shieldbot.readS1();
  polls[1]=shieldbot.readS2();
  polls[2]=shieldbot.readS3();
  polls[3]=shieldbot.readS4();
  polls[4]=shieldbot.readS5();
}

/*
int lineRead(int sensor){
  readings[0]=analogRead(sensor);
  digitalWrite(sensor, 1);
  readings[1]=analogRead(sensor);
  digitalWrite(sensor,0);
  readings[2]=analogRead(sensor);
  return(readings[1]-(readings[0]+readings[2])/2);
}
*/
