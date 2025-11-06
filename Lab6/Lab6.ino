int MOSI_pin = 11;
int SlaveSelect_pin = 10;
int Clock_pin = 13;
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data){
  for (int i=7;i>=0;i--){
    digitalWrite(Clock_pin, LOW);
    digitalWrite(MOSI_pin, data & (1<<i));
    digitalWrite(Clock_pin, HIGH);
  }
}
void toMax(byte reg, byte col){
  digitalWrite(SlaveSelect_pin, LOW);
  putByte(reg);
  putByte(col);
  digitalWrite(SlaveSelect_pin, HIGH);
}

byte cur[8];
byte nxt[8];

inline uint8_t getCell(const byte grid[8], int r, int c){
  r &= 7; c &= 7;
  return (grid[r] >> (7 - c)) & 1;
}
inline void setCell(byte grid[8], int r, int c, uint8_t v){
  r &= 7; c &= 7;
  byte mask = (1 << (7 - c));
  if (v) grid[r] |= mask; else grid[r] &= ~mask;
}
uint8_t neighbors(const byte grid[8], int r, int c){
  uint8_t s=0;
  for(int dr=-1; dr<=1; dr++){
    for(int dc=-1; dc<=1; dc++){
      if (dr==0 && dc==0) continue;
      s += getCell(grid, r+dr, c+dc);
    }
  }
  return s;
}
void stepLife(){
  for(int r=0;r<8;r++){
    nxt[r]=0;
    for(int c=0;c<8;c++){
      uint8_t n = neighbors(cur,r,c);
      uint8_t alive = getCell(cur,r,c);
      uint8_t nextAlive = (alive ? (n==2 || n==3) : (n==3));
      if (nextAlive) nxt[r] |= (1<<(7-c));
    }
  }
  for(int r=0;r<8;r++) cur[r]=nxt[r];
}
void drawMatrix(const byte grid[8]){
  for(int r=0;r<8;r++) toMax(r+1, grid[r]);
}
bool allDead(const byte grid[8]){
  byte acc=0;
  for(int r=0;r<8;r++) acc |= grid[r];
  return acc==0;
}
void randomSeedLife(){
  randomSeed(analogRead(A0) ^ micros());
  for(int r=0;r<8;r++){
    cur[r]=0;
    for(int c=0;c<8;c++){
      if (random(100)<35) setCell(cur,r,c,1);
    }
  }
}

void setup(){
  pinMode(MOSI_pin, OUTPUT);
  pinMode(Clock_pin, OUTPUT);
  pinMode(SlaveSelect_pin, OUTPUT);
  digitalWrite(Clock_pin, HIGH);

  toMax(max7219_reg_scanLimit, 0x07);
  toMax(max7219_reg_decodeMode, 0x00);
  toMax(max7219_reg_shutdown, 0x01);
  toMax(max7219_reg_displayTest, 0x00);
  for (int i=1;i<=8;i++) toMax(i,0x00);
  toMax(max7219_reg_intensity, 0x03);

  randomSeedLife();
}

void loop(){
  drawMatrix(cur);
  delay(120);
  stepLife();
  if (allDead(cur)) randomSeedLife();
}
