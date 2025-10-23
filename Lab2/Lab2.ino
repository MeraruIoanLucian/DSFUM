const int led = 13, led2 = 12;
int bright = 0, dir = 1, acc = 0;
int bright2 = 0, dir2 = 1, acc2 = 0;
unsigned long t1 = 0, t2 = 0, t2b = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  if (now != t1) {
    t1 = now;
    acc += bright;
    digitalWrite(led, acc >= 100);
    if (acc >= 100) acc -= 100;

    acc2 += bright2;
    digitalWrite(led2, acc2 >= 100);
    if (acc2 >= 100) acc2 -= 100;
  }
  if (now - t2 >= 10) {
    t2 = now;
    bright += dir * 3;
    if (bright >= 100 || bright <= 0) dir = -dir;
  }
  if (now - t2b >= 7) {
    t2b = now;
    bright2 += dir2 * 3;
    if (bright2 >= 100 || bright2 <= 0) dir2 = -dir2;
  }
}