//Problema 1

void setup ()
{
  pinMode(4,OUTPUT); // pinul pentru latch (blocare)
  pinMode(7,OUTPUT); // pin pentru sincronizarea ceasului
  pinMode(8,OUTPUT); // pin pentru transmiterea datelor
}
 
void loop()
{
  afiseazaValoare(207, 241);//1
  delay(1000);
  afiseazaValoare(36, 241);//2
  delay(1000);
  afiseazaValoare(6, 241);//3
  delay(1000);
  afiseazaValoare(11, 241);//4
  delay(1000);
  afiseazaValoare(18, 241); // 5
  delay(1000);
  afiseazaValoare(16, 241);//6
  delay(1000);
  afiseazaValoare(199, 241);//7
  delay(1000);
  afiseazaValoare(0, 241);//8
  delay(1000);
  afiseazaValoare(2, 241);//9
  delay(1000);
}
 
void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, MSBFIRST, valoare);
  shiftOut(8, 7, MSBFIRST, segment);
  digitalWrite(4,HIGH);
}

//Problema 4


void setup ()
{
  pinMode(4,OUTPUT); // pinul pentru latch (blocare)
  pinMode(7,OUTPUT); // pin pentru sincronizarea ceasului
  pinMode(8,OUTPUT); // pin pentru transmiterea datelor
}
 
void loop()
{
  afiseazaValoare(8, 241);//A
  delay(1000);
  afiseazaValoare(3, 241);//b
  delay(1000);
  afiseazaValoare(70, 241);//C
  delay(1000);
  afiseazaValoare(33, 241);//d
  delay(1000);
  afiseazaValoare(6, 241); // E
  delay(1000);
  afiseazaValoare(14, 241);//F
  delay(1000);
}
 
void afiseazaValoare(byte valoare, byte segment)
{
  digitalWrite(4,LOW);
  shiftOut(8, 7, MSBFIRST, valoare);
  shiftOut(8, 7, MSBFIRST, segment);
  digitalWrite(4,HIGH);
}
