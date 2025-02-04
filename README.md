




# 🚗 Smart Parking Garage System


![AGPL License](https://img.shields.io/badge/Arduino-Project-darkcyan)

![Logo](https://images2.imgbox.com/0b/94/9MfUt3cm_o.png)


This smart parking garage system was built to make parking easier and more organized. It automatically manages car entry and exit, shows available spaces, and guides drivers to the nearest empty spot.

We worked on this project as a group of four friends: two of us studying computer science and two studying electrical engineering. By combining our skills, we made a working system using both software and hardware.

One important thing we learned is that you can start with small-scale projects like this and then expand them to solve bigger real-world problems.







## Key Features :

- #### __✅ Automated Entry/Exit :__ 
Servo motors and infrared sensors (IR) control the garage gates automatically based on vehicle detection.

- #### __🅿️ Real-Time Availability Tracking :__ 
LCD displays show the number of available spaces and the closest available parking lot.
 
- #### __📍 Intelligent Space Allocation :__

Guides vehicles to the nearest available parking lot based on entrance location.

- #### __💡 Energy Efficiency :__
Automatic lighting using LDR (Light Dependent Resistor) for illumination during low light conditions.

## Technical Overview :
__System Design :__ 
- __Parking Zones :__ 
Three zones (Park 1, Park 2, Park 3), each with a three-car capacity.
- __Entrances :__
Two entrances guiding cars to the nearest available park based on sensor inputs.
- __Gate Control :__
Servo motors open and close gates based on sensor triggers.
##
 __Hardware Components :__ 
- IR Sensors for vehicle detection
- SG90 Servo Motors for gate control
- LCD Displays with I2C Modules for availability information
- LDR for automatic lighting control
- Arduino Uno for central control
##
__Software :__ 
- C++ code for hardware integration and control logic
- Arduino IDE for programming and testing 

## Conclusion :
This project allowed us to explore the potential of combining hardware and software to create smart systems that solve everyday problems. By working as a multidisciplinary team, we successfully developed a functional parking garage prototype that manages vehicle flow and provides efficient parking solutions.

The experience reinforced the idea that small-scale projects can serve as blueprints for larger, real-world applications. As technology continues to advance, solutions like these can be scaled up to contribute to the development of smart cities and intelligent transportation systems.

## Demo

Check out the demo through this youtube shorts link : https://youtube.com/shorts/CsPosTnCOk8


## Credits

This project is maintained by @malikmaky.

For any inquiries or feedback, please contact malikmhmd@hotmail.com

