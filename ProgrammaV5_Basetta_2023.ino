int R = 10; //in ohm
int medie = 10;
boolean checkIV;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(7, LOW);
  digitalWrite(13, LOW);
  analogWriteResolution(12);
  analogReadResolution(12);
  Serial.begin(9600);
  //Serial.println("LED OFF");  
}

void loop() {
  while(Serial.available() > 0) {
    char inst = Serial.read();
    int num = Serial.parseInt();

    if (inst == 'D') {
      //int num = Serial.parseInt();
      Serial.flush();
      setDac(num);
    }
    else if (inst == 'I') {
      Serial.flush();    
      IV();
    }
    else if (inst == 'L'){
      Serial.flush();
      digitalWrite(7, num);
      if (num == 0) Serial.println("LED OFF");
      else Serial.println("LED ON");
    }
    else if (inst == 'S'){
      Serial.flush();
      ISC();
    }
    else if (inst == 'M'){
      Serial.flush();
      ISCM();
    }
  }
}

void ISC() {
  int valA0=0; int valA1=0; int valA2=0;
  analogWrite(DAC0, 0);
  for(int jj=0; jj<medie; jj++) {
    delay(200);
    valA0 += analogRead(A0);
    valA1 += analogRead(A1);
    valA2 += analogRead(A2);
  }
  float V0 = ((valA0/medie)*3.3)/4095;
  float V1 = ((valA1/medie)*3.3)/4095;
  float V2 = ((valA2/medie)*3.3)/4095;
  float V = V2-V0;
  float I = (V1-V2)/R*1000; //in mA

  Serial.print(V,3); Serial.print(", "); Serial.print(I,2); Serial.print(", "); Serial.print(V0,3); Serial.print(", "); Serial.print(V1,3); Serial.print(", "); Serial.print(V2,3);
  
  Serial.println();
  digitalWrite(13, LOW);
  return;
}

void ISCM() {
 for(int ii=0; ii<4000; ii=ii+100)
  {
  int valA0=0; int valA1=0; int valA2=0;
  digitalWrite(13, HIGH);
  analogWrite(DAC0, 0);
  analogWrite(DAC1, ii);
  for(int jj=0; jj<medie; jj++) {
    delay(200);
    valA0 += analogRead(A0);
    valA1 += analogRead(A1);
    valA2 += analogRead(A2);
  }
  float V0 = ((valA0/medie)*3.3)/4095;
  float V1 = ((valA1/medie)*3.3)/4095;
  float V2 = ((valA2/medie)*3.3)/4095;
  float V = V2-V0;
  float I = (V1-V2)/R*1000; //in mA

  Serial.print(V,3); Serial.print(", "); Serial.print(I,2); Serial.print(", "); Serial.print(V0,3); Serial.print(", "); Serial.print(V1,3); Serial.print(", "); Serial.println(V2,3);
  }
  digitalWrite(13, LOW);
  return;
}

void IV() {
  for(int ii=0; ii<4090; ii=ii+20)
  {
    int valA0=0; int valA1=0; int valA2=0; int valA3=0; int valA4=0; int valA5=0; int valA6=0;
    digitalWrite(13, HIGH);
    analogWrite(DAC0, ii);
    
    for(int jj=0; jj<medie; jj++) {
      delay(20);
      valA0 += analogRead(A0);
      valA1 += analogRead(A1);
      valA2 += analogRead(A2);
      /*valA3 += analogRead(A3);
      valA4 += analogRead(A4);
      valA5 += analogRead(A5);
      valA6 += analogRead(A6);*/
      }
    float V0 = ((valA0/medie)*3.3)/4095;
    float V1 = ((valA1/medie)*3.3)/4095;
    float V2 = ((valA2/medie)*3.3)/4095;
    /*float V3 = valA3/medie*3.3/4095/2;
    float V4 = valA4/medie*3.3/4095/10;
    float V5 = valA5/medie*3.3/4095/100;
    float V6 = valA6/medie*3.3/4095/1000;*/
    float V = V2-V0;
    float I = (V1-V2)/R*1000; //in mA

    //Serial.print(V,3); Serial.print(", "); Serial.print(I,2); Serial.print(", ");
    Serial.print(V,3); Serial.print(", "); Serial.print(I,2); Serial.print(", "); Serial.print(V0,3); Serial.print(", "); Serial.print(V1,3); Serial.print(", "); Serial.print(V2,3); Serial.print(", ");
  }
  Serial.println();
  digitalWrite(13, LOW);
  return;
}

void setDac(int val) {
  analogWrite(DAC1, val);
  Serial.println("DAC1 = " + (String) val);
  return;
}
