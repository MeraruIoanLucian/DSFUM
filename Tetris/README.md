# Tetris on Arduino Mega (Wokwi Simulation)

![Arduino](https://img.shields.io/badge/Arduino-Mega-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Status](https://img.shields.io/badge/Status-Complete-success?style=for-the-badge)

A fully functional, classic Tetris implementation built for the **Arduino Mega**, designed and simulated within the Wokwi environment. This project features a custom driver for a 16x32 LED matrix display, a 7-segment score tracker, and non-blocking sound effects.

## 🎮 Core Features

### 1. Advanced Custom Display Driver
-   **Hardware**: 8x MAX7219 8x8 LED Matrices daisy-chained.
-   **Resolution**: 16x32 pixels (Split across two 8x32 blocks).
-   **Custom Calibration Logic**:
    -   Manages complex physical rotation (90° Left Block / 270° Right Block).
    -   Corrects non-standard wiring and gravity orientation issues.
-   **Flicker-Free Rendering**: Implements conditional double-buffering for a smooth 60 FPS refresh rate.

### 2. Classic Game Mechanics
-   **Tetrominos**: Full implementation of all standard pieces (I, J, L, O, S, T, Z).
-   **Mechanics Included**:
    -   Left/Right Movement
    -   Rotation (90° increments)
    -   Soft Drop (Fast Fall)
    -   Line Clearing & Gravity
    -   Game Over Detection

### 3. Hardware Integration
-   **Score Display**: 4-digit 7-segment display controlled by 2x 74HC595 Shift Registers.
-   **Sound**: Passive Buzzer with non-blocking tone generation (optimized not to halt the main loop).
-   **Input**: Control handled via 4 push buttons, implemented with software debouncing.

## 🛠️ Hardware Configuration (Wokwi)

| Component | Pin / Connection | Notes |
| :--- | :--- | :--- |
| **LED Matrix (DIN)** | Pin 11 | Data In |
| **LED Matrix (CLK)** | Pin 13 | Clock |
| **LED Matrix (CS)** | Pin 10 | Chip Select |
| **Shift Register (DATA)** | Pin 9 | 74HC595 DS |
| **Shift Register (LATCH)** | Pin 8 | 74HC595 STCP |
| **Shift Register (CLOCK)** | Pin 7 | 74HC595 SHCP |
| **Buzzer** | Pin 49 | Passive |
| **Button (Rotate)** | Pin 41 | Blue |
| **Button (Left)** | Pin 43 | Yellow |
| **Button (Right)** | Pin 45 | Green |
| **Button (Drop)** | Pin 47 | Red |

## 🚀 Getting Started

1.  Open the project in [Wokwi](https://wokwi.com/).
2.  Upload the `Tetris.ino` file.
3.  Start the simulation.

### Controls

-   🔵 **Blue**: Rotate Piece
-   🟡 **Yellow**: Move Left
-   🟢 **Green**: Move Right
-   🔴 **Red**: Fast Drop

## 📂 Project Structure

-   `Tetris.ino`: The main source code containing the game engine, display driver, and hardware logic.
-   `LedControl.h`: Library used for interfacing with the MAX7219 matrices.
-   `diagram.json`: The Wokwi simulation configuration file.

## 🧠 Technical Deep Dive

-   **Matrix Mapping**: The project uses a sophisticated coordinate transformation system to correctly map a logical 16x32 game grid onto 8 physically rotated and daisy-chained 8x8 matrices.
-   **Performance Optimization**: The main loop is capped at approximately 60Hz to balance the display refresh rate with the interrupt-driven tone generation, ensuring smooth gameplay and accurate sound rendering.

## 📜 License

This project is released under an open-source license. Feel free to clone, use, and modify it for learning purposes!
