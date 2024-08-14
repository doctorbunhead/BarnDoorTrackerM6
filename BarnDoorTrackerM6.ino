/*
 * barn door tracker code for an M6 thread at 274mm from hinge
  */
#define OUT1  8
#define OUT2  9
#define OUT3  10
#define OUT4  11
#define IN1  12
#define OUT5  7
int steps = 0;
long totalSteps=0;
boolean Direction = 0;
//bool motorRun=true;
bool activeLED=false;
//bool stopped=false;
long time;
void setup() {
  Serial.begin(115200);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  //pinMode(IN1, INPUT);
  pinMode(OUT5, OUTPUT);
  Serial.println("Running...");
  time = micros();
}
void loop() {
  /*if(totalSteps>147320 && !stopped) {
      activeLED=false;
      digitalWrite(OUT1, LOW); 
      digitalWrite(OUT2, LOW);
      digitalWrite(OUT3, LOW);
      digitalWrite(OUT4, LOW);
      digitalWrite(OUT5, activeLED);
      Serial.println("Stopped.");
      Serial.print("Total Time Elapsed - ");
      Serial.println(micros());
      //stopped=true;
    }*/
  //if(motorRun && !stopped){
    
    //motorRun=true; //digitalRead(IN1);
    stepper(1);
    totalSteps++;
    if(!(totalSteps % 4096)) {
      Serial.print("Steps - ");
      Serial.println(totalSteps);
      Serial.print("     Time - ");
      Serial.println(micros());
      long aveTime = (micros()- time) /totalSteps;
      Serial.print("AverageTime=");
      Serial.println(aveTime);
    }
    if(!(totalSteps % 35)) {
      activeLED = !activeLED;
      digitalWrite(OUT5, activeLED);
    }
    //delay is 60M microseconds / (4096 * 1.1989) which is 4910.6944 = 12218.23129535407. Use modulus each 4825 to get 1116 extra us
    delayMicroseconds(8192);
    delayMicroseconds(3839); //took off 196us for latency
    if(!(totalSteps % 4825)) delayMicroseconds(1116);
    //Serial.println(time);
    
  //}
  /* else
  {
    digitalWrite(OUT1, LOW); 
    digitalWrite(OUT2, LOW);
    digitalWrite(OUT3, LOW);
    digitalWrite(OUT4, LOW);
    digitalWrite(OUT5, LOW);
    activeLED=false;
    totalSteps=0;
    time = micros();
    motorRun=true; //digitalRead(IN1);
    if(!motorRun && stopped) { 
      stopped=false;
    }
    
  }
  */
  //time = micros()-time;
  //Serial.println(time);
}

void stepper(int xw) {
  for (int x=0;x<xw;x++){
    
    switch(steps){
      case 0:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, HIGH);
      break; 
      case 1:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, HIGH);
        digitalWrite(OUT4, HIGH);
      break; 
      case 2:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, HIGH);
        digitalWrite(OUT4, LOW);
      break; 
      case 3:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, HIGH);
        digitalWrite(OUT3, HIGH);
        digitalWrite(OUT4, LOW);
      break; 
      case 4:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, HIGH);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, LOW);
      break; 
      case 5:
        digitalWrite(OUT1, HIGH); 
        digitalWrite(OUT2, HIGH);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, LOW);
      break; 
        case 6:
        digitalWrite(OUT1, HIGH); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, LOW);
      break; 
      case 7:
        digitalWrite(OUT1, HIGH); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, HIGH);
      break; 
      default:
        digitalWrite(OUT1, LOW); 
        digitalWrite(OUT2, LOW);
        digitalWrite(OUT3, LOW);
        digitalWrite(OUT4, LOW);
      break; 
  }
  SetDirection();
  }
} 
void SetDirection() {
  if(Direction==1){ steps++;}
  if(Direction==0){ steps--; }
  if(steps>7){steps=0;}
  if(steps<0){steps=7; }
  
}

