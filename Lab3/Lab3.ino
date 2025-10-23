const int led = 13;
int mode = 0;
long interval = 500;
long t1, t2 = 0;
int bright = 0, dir = 1;

String ce_primesc;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop()
{
   while (Serial.available()) {
    char c = Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      if (ce_primesc.length() > 0) parseLine(ce_primesc);
      ce_primesc = "";
    } else ce_primesc += c;
  }

  long now = millis();
  if(mode == 2 && now - t1 >= interval/2)
  {
    t1 = now;
    digitalWrite(led, !digitalRead(led));
  }

  if(mode == 3 && now -t2 >= interval/100)
  {
    t2=now;
    bright+=dir*3;
    if(bright >= 500)
    {
      bright = 500;
      dir = -1;
    }
    if(bright <=0)
    {
      bright = 0;
      dir = 1;
    }
    analogWrite(led, bright);
  }

  if(mode == 4 && now - t2 >= interval/100)
  {
    t2= now;
    bright -= dir * 3;
    if(bright <=0)
    {
      bright = 0;
      dir = -1;
    }
    if(bright >= 500)
    {
      bright = 500;
      dir = 1;
    }
    analogWrite(led, bright);
  }
}

void parseline()
{
  int c1 = line.indexOf(',');
  int c2 = line.indexOf(',', c1+1);
  if(c1<0 || c2<0) return;
  String pinStr = line.substring(0,c1);
  String cmd = line.substring(c1+1, c2);
  String timeStr = line.substring(c2+1);
  interval = timeStr.toInt();
  if(cmd == "off")
  {
    mode = 0;
    digitalWrite(led, LOW);
  }
  else if(cmd == "on")
  {
    mode = 1;
    digitalWrite(led, HIGH);
  }
  else if(cmd == "blink")
  {
    mode = 2;
  }
  else if(cmd == "fadein")
  {
    mode = 3;
    dir = 1;
    bright = 0;
  }
  else if(cmd == "fadeout")
  {
    mode = 4;
    dir = -1;
    bright = 500;
  }
}
