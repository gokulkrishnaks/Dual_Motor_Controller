# Dual Motor Controller with LCD & 7-Segment Timer (PIC16F877A)

This project demonstrates a **dual motor control system** using the **PIC16F877A** microcontroller.  
It allows controlling the direction of two DC motors (Push / Pull) with **push buttons**,  
displays status messages on an **LCD**, and shows a **10-second countdown** on a **7-segment display**.

---

## Features

- **Two-direction motor control** (Push & Pull)
- **LCD (16x2) interface** for displaying system status
- **7-segment display** countdown timer (10 seconds)
- **Reset button** to restart the system
- Designed using **XC8 compiler** and **MPLAB X IDE**
- Works with **PIC16F877A** @ **20 MHz crystal**

---

## Hardware Components

| Component | Description |
|------------|-------------|
| PIC16F877A | Main microcontroller |
| L293D / L298N | Dual H-Bridge motor driver |
| LCD (16x2) | Display for motor status |
| 7-Segment Display | Countdown timer |
| Push Buttons | BTN1 (Pull), BTN2 (Push), Reset |
| 20 MHz Crystal | Clock source |
| Power Supply | +5V regulated |

---

## Pin Configuration

### **Motor Control (PORTB)**
| Motor Function | Pin | Description |
|-----------------|-----|-------------|
| IN1 | RB3 | Motor 1 direction control |
| IN2 | RB2 | Motor 1 direction control |
| IN3 | RB1 | Motor 2 direction control |
| IN4 | RB0 | Motor 2 direction control |

### **LCD Interface**
| LCD Pin | MCU Pin |
|----------|----------|
| RS | RB4 |
| EN | RB5 |
| D0–D7 | PORTC |

### **Push Buttons**
| Button | MCU Pin | Function |
|---------|----------|----------|
| BTN1 | RB6 | Pull direction |
| BTN2 | RB7 | Push direction |
| RESET | RD7 | Reset system |

### **7-Segment Display**
| Segment Data | MCU Port |
|---------------|----------|
| a–g | PORTD (except RD7) |

---

## Working Principle

1. **System Initialization**  
   - LCD displays "System Ready".  
   - Motors are off initially.  

2. **Button Press (BTN1 or BTN2)**  
   - **BTN1 pressed** → Motor enters *Pulling* mode.  
   - **BTN2 pressed** → Motor enters *Pushing* mode.  
   - LCD displays current mode (“Motor Pulling” or “Motor Pushing”).  
   - 7-segment display counts down from 9 → 0 (10 seconds).  

3. **Reset Button (RD7)**  
   - Stops current operation.  
   - LCD resets to “System Ready”.  

4. **No button pressed** → Motor stops automatically.

---

## Code Overview

### Main Sections:
- **LCD Functions:** `cmd()`, `data()`, `print()`, `init()`
- **Motor Functions:** `push()`, `pull()`, `stop()`
- **Timer Function:** `count()` — runs a 10-second countdown on 7-segment
- **Main Loop:** Continuously checks button states and triggers appropriate motor actions

---

## Development Environment

- **IDE:** MPLAB X IDE  
- **Compiler:** XC8  
- **Microcontroller:** PIC16F877A  
- **Clock Frequency:** 20 MHz  

---

## How to Use

1. Open the project in **MPLAB X IDE**.  
2. Connect hardware as per pin configuration.  
3. Compile and upload the `.hex` file to your **PIC16F877A**.  
4. Power the board and observe LCD and 7-segment outputs.  

---

## LCD Display Messages

| Event | LCD Line 1 | LCD Line 2 |
|--------|-------------|------------|
| System Ready | System Ready |  |
| BTN1 Pressed | Motor | Pulling |
| BTN2 Pressed | Motor | Pushing |
| Reset Pressed | Reset | System Ready |

---

## License

This project is open-source under the **MIT License** — feel free to modify and use it in your applications.

---

## ✍️ Author

**Name:** GOKUL KRISHNA K S
**Platform:** Embedded Systems Developer (PIC)  
**Language:** Embedded C (XC8)  
