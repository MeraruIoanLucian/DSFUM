// directie unghi repetari viteza

#include <IRremote.hpp>
#include <Stepper.h>

#define IR_RECEIVE_PIN 15
#define LED_PIN 2
#define STEPPER_PIN1 26
#define STEPPER_PIN2 27
#define STEPPER_PIN3 14
#define STEPPER_PIN4 12
#define STEPS_PER_REV 360
#define STEPS_PER_DEGREE (STEPS_PER_REV / 360.0)
#define KEY_0 0x68
#define KEY_1 0x30
#define KEY_2 0x18
#define KEY_3 0x7A
#define KEY_4 0xB0
#define KEY_5 0x38
#define KEY_6 0x5A
#define KEY_7 0x42
#define KEY_8 0x52
#define KEY_9 0x4A
#define KEY_POWER 0xA2 // configu
#define KEY_PLUS 0x10  // +
#define KEY_MINUS 0x98 // -
#define KEY_REPEAT 0x02

Stepper stepper(STEPS_PER_REV, STEPPER_PIN1, STEPPER_PIN2, STEPPER_PIN3,
                STEPPER_PIN4);

bool configMode = false;
bool ledState = false;
unsigned long lastLedToggle = 0;

int configValues[4] = {0, 0, 0, 0}; // directie, unghi, repetari, viteza
int configIndex = 0;
String currentNumber = "";

int motorDirection = 0;
int motorAngle = 0;
int motorRepetitions = 0;
int motorSpeed = 5;

void setup() {
  Serial.begin(115200);
  Serial.println("Apasa POWER pentru configurare");
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  stepper.setSpeed(10);
}

int irCodeToNumber(uint16_t code) {
  switch (code) {
  case KEY_0:
    return 0;
  case KEY_1:
    return 1;
  case KEY_2:
    return 2;
  case KEY_3:
    return 3;
  case KEY_4:
    return 4;
  case KEY_5:
    return 5;
  case KEY_6:
    return 6;
  case KEY_7:
    return 7;
  case KEY_8:
    return 8;
  case KEY_9:
    return 9;
  default:
    return -1;
  }
}

void blinkLed() {
  if (millis() - lastLedToggle > 200) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastLedToggle = millis();
  }
}

void enterConfigMode() {
  configMode = true;
  configIndex = 0;
  currentNumber = "";
  for (int i = 0; i < 4; i++)
    configValues[i] = 0;

  Serial.println("\nMOD CONFIGURARE");
}

void exitConfigMode(bool save) {
  configMode = false;
  digitalWrite(LED_PIN, LOW);

  if (save && validateConfig()) {
    motorDirection = configValues[0];
    motorAngle = configValues[1];
    motorRepetitions = configValues[2];
    motorSpeed = configValues[3];

    Serial.println("\nCONFIGURARE SALVATA");
    Serial.print("Directie: ");
    Serial.println(motorDirection == 0 ? "LEFT" : "RIGHT");
    Serial.print("Unghi: ");
    Serial.print(motorAngle);
    Serial.println(" grade");
    Serial.print("Repetari: ");
    Serial.println(motorRepetitions);
    Serial.print("Viteza: ");
    Serial.println(motorSpeed);
    Serial.println("//////////////////////\n");
    executeMotorMovement();
  } else if (save) {
    Serial.println("Configurare invalida! Nu s-a salvat");
  } else {
    Serial.println("Configurare anulata");
  }
}

bool validateConfig() {
  if (configValues[0] != 0 && configValues[0] != 1) {
    Serial.println("Eroare: Directia trebuie sa fie 0 sau 1");
    return false;
  }
  if (configValues[1] == 0) {
    Serial.println("Eroare: Unghiul nu poate fi 0");
    return false;
  }
  if (configValues[2] == 0) {
    Serial.println("Eroare: Numarul de repetari nu poate fi 0");
    return false;
  }
  if (configValues[3] < 1 || configValues[3] > 9) {
    Serial.println("Eroare: Viteza trebuie sa fie intre 1 si 9");
    return false;
  }
  return true;
}

void saveCurrentNumber() {
  if (currentNumber.length() > 0 && configIndex < 4) {
    configValues[configIndex] = currentNumber.toInt();
    Serial.print("Valoare ");
    Serial.print(configIndex + 1);
    Serial.print(": ");
    Serial.println(configValues[configIndex]);
    configIndex++;
    currentNumber = "";
  }
}

void executeMotorMovement() {
  Serial.println("\nExecut miscarea motorului..");
  int rpm = map(motorSpeed, 1, 9, 15, 2);
  stepper.setSpeed(rpm);
  int steps = (int)(motorAngle * STEPS_PER_DEGREE);

  Serial.print("Directie configurata: ");
  Serial.println(motorDirection == 0 ? "LEFT" : "RIGHT");
  int dir = (motorDirection == 0) ? 1 : -1;

  for (int i = 0; i < motorRepetitions; i++) {
    Serial.print("Repetarea ");
    Serial.print(i + 1);
    Serial.print("/");
    Serial.println(motorRepetitions);
    int stepsToMove = steps * dir;
    stepper.step(stepsToMove);
    delay(500);
    stepper.step(-stepsToMove);
    delay(100);
  }
  digitalWrite(STEPPER_PIN1, LOW);
  digitalWrite(STEPPER_PIN2, LOW);
  digitalWrite(STEPPER_PIN3, LOW);
  digitalWrite(STEPPER_PIN4, LOW);

  Serial.println("Miscare completa!\n");
}

void loop() {
  if (configMode) {
    blinkLed();
  }
  if (IrReceiver.decode()) {
    uint16_t command = IrReceiver.decodedIRData.command;
    if (command == KEY_REPEAT) {
      IrReceiver.resume();
      return;
    }

    if (!configMode) {
      if (command == KEY_POWER) {
        enterConfigMode();
      }
    } else {
      if (command == KEY_POWER) {
        saveCurrentNumber();
        exitConfigMode(true);
      } else if (command == KEY_PLUS || command == KEY_MINUS) {
        saveCurrentNumber(); 
      } else {
        int num = irCodeToNumber(command);
        if (num >= 0) {
          currentNumber += String(num);
        }
      }
    }

    IrReceiver.resume();
  }
}
