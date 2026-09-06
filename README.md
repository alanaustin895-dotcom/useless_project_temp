<img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# Rube Goldberg mini system 🎯


## Basic Details
- Lead by: AUSTIN M.A - scms school of engineering and technology


### Project Description
Converts rotational motion into a swinging motion and the number of swings are counted using an esp32 that uses a sonar senser. 

### The Problem (that doesn't exist)
the over suefullness of products 

### The Solution (that nobody asked for)
by using ESP32-based “useless” project designed primarily for entertainment. The main objective of this project is to entertain the user by demonstrating a creative combination of mechanical motion and electronics in the form of a Rube Goldberg-style chain reaction.

## Technical Details
### Technologies/Components Used
For Software:
- c++
- arduino ide

For Hardware:
-- esp32 dev module, arduino uno
- led 5
- resistors 220ohm
- li-ion battery 3.7v
- sonar sensor


# Schematic & Circuit
Circuit<img width="1536" height="1024" alt="Untitled design" src="https://github.com/user-attachments/assets/14426b32-dd2c-44e8-a633-734086266380" />

*Add caption explaining connections*

![Schematic](Add your schematic diagram here)
*Add caption explaining the schematic*

# Build Photos
Components

<img width="1600" height="1200" alt="WhatsApp Image 2026-09-06 at 4 57 47 AM" src="https://github.com/user-attachments/assets/20c3a974-f3e0-4455-9427-4766efc3ab14" />


*List out all components shown*

Build<img width="1408" height="768" alt="image_ee4713dd" src="https://github.com/user-attachments/assets/da5596ca-e37f-4cfa-b4be-33c024eeb420" />

*Explain the build steps*
1. start by finding the measurments of the linkages of the mechanical parts using the given ratios.
2. then connect all the linkages
3. then connect all the leds series with the resistors on the positive terminal
4. connect the positive part of the leds to the gpio pins
5. connect all the negative pins to common gnd
6. connect the sonar sensor ,use the 5v supply from the arduino uno
7. connect the motor driver to the motor
8. appload the code to esp32 and compile the code and run.
9. place the sonar sensor below the output of the last linkage 
  
Final<img width="974" height="1600" alt="WhatsApp Image 2026-09-06 at 5 04 42 AM" src="https://github.com/user-attachments/assets/faacf439-0cbd-427c-b0bb-8db51c76c1c9" />

Basically, what I have made is a Rube Goldberg machine. Usually, people use dominoes and other physical objects to create a sequence of events in these machines. However, in my project, I have used mechanical and electronic components to demonstrate the same concept.

Here, the motor generates rotary motion, which is transferred through a four-bar linkage mechanism to produce a swinging motion at the output. This swinging motion is detected using a sonar sensor, and the sensor data is sent to an ESP32 microcontroller.

The ESP32 controls five LEDs, which are used to count the number of swings. Each time the mechanism completes a swing, the corresponding LED is activated, creating a visual representation of the sequence.

### Project Demo


# Additional Demos
(https://drive.google.com/file/d/1QtBaWT42bCI_CGHfu-jAAXTXgpLAqFlM/view?usp=drivesdk)


---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)



