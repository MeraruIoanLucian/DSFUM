# Tetris pe Arduino Mega (Simulare Wokwi)

![Arduino](https://img.shields.io/badge/Arduino-Mega-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Complet-success?style=for-the-badge)

O implementare complet functionala a jocului Tetris pentru Arduino Mega, proiectata si simulata in Wokwi. Acest proiect include un driver personalizat pentru matricea LED 16x32, afisaj de scor pe 7 segmente si efecte sonore.

## 🎮 Functionalitati

### 1. Driver Avansat pentru Afisaj
-   **Hardware**: 8x Matrice LED 8x8 MAX7219 conectate in serie.
-   **Rezolutie**: 16x32 pixeli (Impartit in doua blocuri 8x32).
-   **Calibrare Personalizata**:
    -   Gestioneaza rotatia fizica complexa (90° Bloc Stanga / 270° Bloc Dreapta).
    -   Corecteaza cablarea non-standard si orientarea gravitatiei.
-   **Fara Palpaire**: Implementeaza double-buffering conditional pentru o randare fluida la 60FPS.

### 2. Logica Clasica de Joc
-   **Forme**: Implementare completa a formelor standard (I, J, L, O, S, T, Z).
-   **Mecanici**:
    -   Miscare Stanga/Dreapta
    -   Rotire (90°)
    -   Cadere Rapida (Soft Drop)
    -   Eliminare Linii & Gravitatie
    -   Detectie Sfarsit Joc (Game Over)

### 3. Integrare Hardware
-   **Afisaj Scor**: Afisaj 7-Segmente cu 4 cifre controlat de 2x Registre de Deplasare 74HC595.
-   **Sunet**: Buzzer Pasiv cu generare de tonuri non-blocante (optimizat pentru a nu bloca procesorul).
-   **Intrare**: Control cu 4 butoane si debounce software.

## 🛠️ Configurare Hardware (Wokwi)

| Componenta | Pin / Conexiune | Note |
| :--- | :--- | :--- |
| **Matrice LED (DIN)** | Pin 11 | Data In |
| **Matrice LED (CLK)** | Pin 13 | Clock |
| **Matrice LED (CS)** | Pin 10 | Chip Select |
| **Registru Deplasare (DATA)** | Pin 9 | 74HC595 DS |
| **Registru Deplasare (LATCH)** | Pin 8 | 74HC595 STCP |
| **Registru Deplasare (CLOCK)** | Pin 7 | 74HC595 SHCP |
| **Buzzer** | Pin 49 | Pasiv |
| **Buton (Rotire)** | Pin 41 | Albastru |
| **Buton (Stanga)** | Pin 43 | Galben |
| **Buton (Dreapta)** | Pin 45 | Verde |
| **Buton (Jos)** | Pin 47 | Rosu |

## 🚀 Cum sa Rulezi

1.  Deschide proiectul in [Wokwi](https://wokwi.com/).
2.  Incarca `Tetris.ino`.
3.  Porneste simularea.

### Controale

-   🔵 **Albastru**: Rotire Piesa
-   🟡 **Galben**: Miscare Stanga
-   🟢 **Verde**: Miscare Dreapta
-   🔴 **Rosu**: Cadere Rapida

## 📂 Structura Proiectului

-   `Tetris.ino`: Codul sursa principal care contine motorul jocului, driverul de afisaj si logica hardware.
-   `LedControl.h`: Biblioteca pentru controlul matricelor MAX7219.
-   `diagram.json`: Configuratia simularii Wokwi.

## 🧠 Detalii Tehnice

-   **Mapare Matrice**: Proiectul foloseste un sistem complex de transformare a coordonatelor pentru a mapa o grila logica 16x32 pe 8 matrice 8x8 rotite fizic si conectate in serie.
-   **Optimizare**: Bucla principala este limitata la ~60Hz pentru a echilibra rata de reimprospatare a afisajului cu generarea tonurilor prin intreruperi, asigurand redarea corecta a sunetului.

## 📜 Licenta

Acest proiect este open source. Simte-te liber sa il folosesti si sa il modifici pentru invatare!
