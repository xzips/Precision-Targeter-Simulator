# Precision-Targeter-Simulator
Simulator for a personal project that involves a stepper motor driving a larger assembly rotating on a turntable bearing.

Simulator goal is to allow accurate simulation of mechanism behaviour, accurately modeling the stepper motor torque curve and power specifications.

The image below is a CAD prototype to give context to the simulator's objective 
![image](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/0a5f3225-865d-48bb-83a7-0d672e55b4a9)


**Roadmap**
- Convert stepper motor performance curves into runtime evaluable polynomials [WIP]
- Set up framework to allow modification of rotating mechanism mass distribution, friction force estimates, and gear ratio [TODO]
- Build steppable physics solver [TODO]
- Write live plotting GUI [TODO]
- Finalize linking everything together and displaying results [TODO]



Disclaimer: The torque vs RPM curve used in this project is NOT property of the author (Aspen Erlandsson), and all rights are reserved to the respective owner, which remains unknown as the image was obtained from an Amazon product listing with a generic brand name.
