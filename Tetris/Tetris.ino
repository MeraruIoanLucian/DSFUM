#include "LedControl.h"

#define PIN_BUTON_ROTIRE 41  // Albastru
#define PIN_BUTON_STANGA 43  // Galben
#define PIN_BUTON_DREAPTA 45 // Verde
#define PIN_BUTON_JOS 47     // Rosu
#define PIN_BUZER 49
#define PIN_MATRICE_DIN 11
#define PIN_MATRICE_CLK 13
#define PIN_MATRICE_CS 10
#define PIN_REG_DATE 9
#define PIN_REG_LATCH 8
#define PIN_REG_CEAS 7
// face matrice
LedControl lc = LedControl(PIN_MATRICE_DIN, PIN_MATRICE_CLK, PIN_MATRICE_CS, 8);

const int LATIME = 16;
const int INALTIME = 32;
int harta[LATIME][INALTIME] = {0}; // 0 e gol, 1 e ocupat
byte displayBuffer[8][8];
int tipPiesa;
int rotatie;
int pozX;
int pozY;
unsigned long lastFallTime = 0;
int vitezaCadere = 500;
unsigned long lastDebounce = 0;
const int debounceDelay = 150;
int scor = 0;
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988

const int forme[7][4][4][2] = {
    // I
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}},
     {{2, 0}, {2, 1}, {2, -1}, {2, -2}},
     {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
     {{1, 0}, {1, 1}, {1, -1}, {1, -2}}},
    // J
    {{{0, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
     {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {1, 1}, {1, 2}, {0, 2}}},
    // L
    {{{2, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
     {{0, 0}, {1, 0}, {1, 1}, {1, 2}}},
    // O
    {{{1, 0}, {2, 0}, {1, 1}, {2, 1}},
     {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
     {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
     {{1, 0}, {2, 0}, {1, 1}, {2, 1}}},
    // S
    {{{1, 0}, {2, 0}, {0, 1}, {1, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
     {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {2, 2}}},
    // T
    {{{1, 0}, {0, 1}, {1, 1}, {2, 1}},
     {{1, 0}, {1, 1}, {2, 1}, {1, 2}},
     {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
     {{1, 0}, {0, 1}, {1, 1}, {1, -1}}},
    // Z
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     {{2, 0}, {1, 1}, {2, 1}, {1, 2}},
     {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
     {{2, 0}, {1, 1}, {2, 1}, {1, 2}}}};

const byte digitMap[] = {
    80,  // 0
    215, // 1
    100, // 2
    69,  // 3
    195, // 4
    73,  // 5
    72,  // 6
    213, // 7
    0,   // 8
    65   // 9
};

const byte digitsSelect[] = {32, 64, 128, 1};

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BUTON_ROTIRE, INPUT);
  pinMode(PIN_BUTON_STANGA, INPUT);
  pinMode(PIN_BUTON_DREAPTA, INPUT);
  pinMode(PIN_BUTON_JOS, INPUT);

  pinMode(PIN_BUZER, OUTPUT);
  // config registru deplasare
  pinMode(PIN_REG_DATE, OUTPUT);
  pinMode(PIN_REG_LATCH, OUTPUT);
  pinMode(PIN_REG_CEAS, OUTPUT);

  // config matrice 8 dispoz
  for (int i = 0; i < 8; i++) {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
    for (int r = 0; r < 8; r++)
      displayBuffer[i][r] = 0;
  }

  randomSeed(analogRead(0));
  piesaNoua();

  tone(PIN_BUZER, NOTE_E5, 100);
  delay(150);
  tone(PIN_BUZER, NOTE_B4, 100);
  delay(150);
  noTone(PIN_BUZER);
}

void loop() {
  unsigned long currentMillis = millis();
  citesteButoane();
  // gravitatia
  if (currentMillis - lastFallTime > vitezaCadere) {
    if (eValid(pozX, pozY + 1, rotatie)) {
      pozY++;
    } else {
      fixeazaPiesa();
      verificaLinii();
      piesaNoua();
      if (!eValid(pozX, pozY, rotatie)) {
        sfarsitJoc();
      }
    }
    lastFallTime = currentMillis;
  }

  actualizareMatrice();
  afisareScor(scor);
}

// logica

void piesaNoua() {
  tipPiesa = random(0, 7);
  rotatie = 0;
  pozX = LATIME / 2 - 2;
  pozY = 0;
  vitezaCadere = 500;
}

bool eValid(int x, int y, int rot) {
  for (int i = 0; i < 4; i++) {
    int px = x + forme[tipPiesa][rot][i][0];
    int py = y + forme[tipPiesa][rot][i][1];

    if (px < 0 || px >= LATIME || py >= INALTIME)
      return false;
    if (py >= 0 && harta[px][py] != 0)
      return false; // coliziune
  }
  return true;
}

void fixeazaPiesa() {
  for (int i = 0; i < 4; i++) {
    int px = pozX + forme[tipPiesa][rotatie][i][0];
    int py = pozY + forme[tipPiesa][rotatie][i][1];
    if (py >= 0)
      harta[px][py] = 1;
  }
}

void verificaLinii() {
  int linesCleared = 0;
  for (int y = INALTIME - 1; y >= 0; y--) {
    bool full = true;
    for (int x = 0; x < LATIME; x++) {
      if (harta[x][y] == 0) {
        full = false;
        break;
      }
    }

    if (full) {
      linesCleared++;
      for (int k = y; k > 0; k--) {
        for (int x = 0; x < LATIME; x++) {
          harta[x][k] = harta[x][k - 1];
        }
      }
      y++;
      tone(PIN_BUZER, NOTE_G4, 50);
      delay(60);
    }
  }

  if (linesCleared > 0) {
    scor += linesCleared;
    tone(PIN_BUZER, NOTE_C5, 100);
    delay(120);
    tone(PIN_BUZER, NOTE_E5, 100);
    delay(120);
    tone(PIN_BUZER, NOTE_G5, 100);
    delay(120);
    noTone(PIN_BUZER);
  }
}

void citesteButoane() {
  if (millis() - lastDebounce < debounceDelay)
    return;

  if (digitalRead(PIN_BUTON_STANGA) == HIGH) {
    if (eValid(pozX - 1, pozY, rotatie)) {
      pozX--;
      tone(PIN_BUZER, NOTE_A3, 20);
      lastDebounce = millis();
    }
  }

  if (digitalRead(PIN_BUTON_DREAPTA) == HIGH) {
    if (eValid(pozX + 1, pozY, rotatie)) {
      pozX++;
      tone(PIN_BUZER, NOTE_A3, 20);
      lastDebounce = millis();
    }
  }

  if (digitalRead(PIN_BUTON_ROTIRE) == HIGH) {
    int nextRot = (rotatie + 1) % 4;
    if (eValid(pozX, pozY, nextRot)) {
      rotatie = nextRot;
      tone(PIN_BUZER, NOTE_D4, 20);
      lastDebounce = millis();
    }
  }

  if (digitalRead(PIN_BUTON_JOS) == HIGH) {
    vitezaCadere = 50;
    tone(PIN_BUZER, NOTE_B2, 10);
  } else {
    vitezaCadere = 500;
  }
}

bool starePixel(int x, int y) {
  if (x >= 0 && x < LATIME && y >= 0 && y < INALTIME) {
    if (harta[x][y])
      return true;
  }

  for (int i = 0; i < 4; i++) {
    int px = pozX + forme[tipPiesa][rotatie][i][0];
    int py = pozY + forme[tipPiesa][rotatie][i][1];
    if (px == x && py == y)
      return true;
  }

  return false;
}

// Functie principala de desenare scrie direct in buffer-ul hardware si face
// update doar la diferente
void actualizareMatrice() {
  // Construim starea curenta a display-ului in memorie
  byte newBuffer[8][8]; // [device][row]
  for (int i = 0; i < 8; i++)
    for (int r = 0; r < 8; r++)
      newBuffer[i][r] = 0;

  // Iteram prin toti pixelii logici (16x32) si ii mapam in newBuffer
  for (int y = 0; y < INALTIME; y++) {
    for (int x = 0; x < LATIME; x++) {
      if (starePixel(x, y)) {

        bool isLeftMatrix = (x < 8);
        int localX = isLeftMatrix ? x : (x - 8);
        int localY = y;

        int blockIndex = localY / 8;
        int device = 0;

        if (isLeftMatrix) {
          device = 7 - blockIndex;
        } else {
          device = 0 + blockIndex;
        }

        int hwRow = 0;    // Axa X
        int hwColBit = 0; // Axa Y

        if (isLeftMatrix) {
          hwRow = 7 - localX;
          hwColBit = localY % 8;
        } else {
          hwRow = localX;
          hwColBit = 7 - (localY % 8);
        }

        // Setam bitul in buffer
        if (hwRow >= 0 && hwRow < 8 && hwColBit >= 0 && hwColBit < 8) {
          newBuffer[device][hwRow] |= (1 << hwColBit);
        }
      }
    }
  }

  // Comparare si Actualizare Hardware
  for (int i = 0; i < 8; i++) {
    for (int r = 0; r < 8; r++) {
      if (displayBuffer[i][r] != newBuffer[i][r]) {
        lc.setRow(i, r, newBuffer[i][r]);
        displayBuffer[i][r] = newBuffer[i][r];
      }
    }
  }
}

// --- AFISAJ 7 SEGMENTE (REGISTRU DEPLASARE) ---
void afisareScor(int num) {
  int d1 = (num / 1000) % 10;
  int d2 = (num / 100) % 10;
  int d3 = (num / 10) % 10;
  int d4 = num % 10;

  int digits[4] = {d1, d2, d3, d4};

  for (int i = 0; i < 4; i++) {
    digitalWrite(PIN_REG_LATCH, LOW);
    shiftOut(PIN_REG_DATE, PIN_REG_CEAS, MSBFIRST, digitsSelect[i]);     // SR2
    shiftOut(PIN_REG_DATE, PIN_REG_CEAS, MSBFIRST, digitMap[digits[i]]); // SR1

    digitalWrite(PIN_REG_LATCH, HIGH);
  }
}

void sfarsitJoc() {
  tone(PIN_BUZER, NOTE_C3, 400);
  delay(450);
  tone(PIN_BUZER, NOTE_C3, 300);
  delay(350);
  tone(PIN_BUZER, NOTE_C3, 100);
  delay(150);
  tone(PIN_BUZER, NOTE_DS3, 600);
  delay(650);
  noTone(PIN_BUZER);

  for (int x = 0; x < LATIME; x++)
    for (int y = 0; y < INALTIME; y++)
      harta[x][y] = 0;
  scor = 0;
  piesaNoua();
}
