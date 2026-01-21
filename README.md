# Bubble Pressure Surface Tension Meter  
**Embedded Systems | Instrumentation**

## Project Overview
Designed and implemented an **embedded instrumentation system** to measure liquid surface tension using the **bubble pressure method**. The system automatically detects the peak pressure during bubble formation and performs **real-time processing** to compute surface tension with minimal user intervention.

This project demonstrates skills in **embedded systems design, sensor data acquisition, signal processing, and algorithm development**.

---

## Technical Description
- Pressure sensors measure atmospheric and capillary pressures.  
- ADC-based sampling is used to acquire real-time pressure signals.  
- The firmware continuously monitors pressure values and automatically detects the **maximum pressure point**.  
- Surface tension is computed using embedded algorithms and displayed to the user.

---

## Technologies Used
- **Microcontroller:** ATmega328P (Arduino)  
- **Programming:** Embedded C / C++  
- **Sensors:** MPS20N0040D-D Pressure Sensors  
- **Techniques:** ADC Signal Processing, Peak Detection Algorithms  
- **Peripherals:** LCD Display, Keypad  
- **Design Tools:** Proteus  
- **Measurement Method:** Bubble Pressure Method  

---

## Applications
- Laboratory instrumentation  
- Chemical and pharmaceutical quality control  
- Liquid property analysis  
- Educational and research systems  

---

## Procedure
1. Power on the system using the **power button**.  
2. Ensure that the **capillary tube is properly submerged** in the liquid under test.  
3. When prompted on the LCD display (*“Enter Density”*), input the liquid density using the keypad.  
4. Gradually press the **syringe** to increase air pressure until a bubble is formed and detaches from the capillary tip; the pressure sensors continuously measure the pressure during this process.  
5. Press the **Calculate** button.  
6. The calculated **surface tension** value is displayed on the LCD screen.
