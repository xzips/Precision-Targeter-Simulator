# Precision-Targeter-Simulator
**Abstract**
Simulator for a personal project that involves a stepper motor driving a larger assembly rotating on a turntable bearing. This readme begins with the results, and then explains the context.

**Results**
TODO

**Conext & Motivation**
I've been working on a project very precisely move a camera on planr and pitch rotation, and part of that is determining how to drive the stepper motor to accelerate and deccelerate the spinning turntable mechanism. As it turns out, the torque output vs rpm curve for stepper motors is not linear, and must be measured for each motor. 

The image below is a CAD prototype to give context to the simulator's objective 
![image](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/0a5f3225-865d-48bb-83a7-0d672e55b4a9)

**Objectives**
- Accurately model and simulate the behaviour of a stepper motor under various load conditions at different speeds
- Allow algorithmic control over the simulation, to test how such algorithms might apply to the real prototype
- Display a clean user interface reporting relevant information about the simulation as it progresses
- Demonstrate my ability to convert from a design challange to a programmatic solution using an efficient and modular object-oriented approach


**Roadmap**
- Convert stepper motor performance curves into runtime evaluable polynomials [DONE]
- Set up framework to allow modification of rotating mechanism mass distribution, friction force estimates, and gear ratio [DONE]
- Build steppable physics solver [DONE]
- Write live plotting GUI [DONE]
- Setup gear visualization with traces [WIP]
- Implement approximation for motor behaviour under direction reversal
- Finalize linking everything together and displaying results [TODO]


Disclaimer: The torque vs RPM curve used in this project is NOT property of the author (Aspen Erlandsson), and all rights are reserved to the respective owner, which remains unknown as the image was obtained from an Amazon product listing with a generic brand name.
