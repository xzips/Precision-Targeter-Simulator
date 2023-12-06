# Precision-Targeter-Simulator
## **Abstract**
Simulator for a personal project that involves a stepper motor driving a larger assembly rotating on a turntable bearing.

## **Results**
Max Acceleration & Deceleration  |  Slow Acceleration, Max Decceleration
:-------------------------:|:-------------------------:
![gif1_2](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/c9ab960f-3ade-42e8-b887-ea274d5854ec) |  ![gif 2](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/9fbc59d6-e2ab-41f6-b8b4-6821c343fe1e)

Max Acceleration, Zoomed & Slowed  |  Slow Acceleration, Max Decceleration, Zoomed in
:-------------------------:|:-------------------------:
![4](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/76fafce8-db93-447c-9f51-6600c923bfb6) | ![3](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/266da83e-c97a-4f17-b49d-175cfe1440d4)

## **Conext & Motivation**

I've been working on a project involving very precisely moving a camera by planar and pitch rotation. Part of that challange is determining how to drive the stepper motor to accelerate and deccelerate the spinning turntable mechanism. As it turns out, the torque output vs rpm curve for steppers is not linear, and must be measured for each motor. Since this curve is nonlinear, the actual calculations become very complicated to do analytically, and for that reason I build this simulator explore the behaviour of the mechanism under different conditions.



The image below is a CAD prototype to give context to the simulator's objective 
![image](https://github.com/xzips/Precision-Targeter-Simulator/assets/114827498/0a5f3225-865d-48bb-83a7-0d672e55b4a9)

## **Objectives**
- Accurately model and simulate the behaviour of a stepper motor under various load conditions at different speeds
- Allow algorithmic control over the simulation, to test how such algorithms might apply to the real prototype
- Display a clean user interface reporting relevant information about the simulation as it progresses
- Demonstrate my ability to convert from a design challange to a programmatic solution using an efficient and modular object-oriented approach


## **Roadmap**
- Convert stepper motor performance curves into runtime evaluable polynomials [DONE✅]
- Set up framework to allow modification of rotating mechanism mass distribution, friction force estimates, and gear ratio [DONE✅]
- Build steppable physics solver [DONE✅]
- Write live plotting GUI [DONE✅]
- Setup gear visualization [DONE✅]
- Finalize linking everything together and displaying results [DONE✅]


Disclaimer: The torque vs RPM curve used in this project is NOT property of the author (Aspen Erlandsson), and all rights are reserved to the respective owner, which remains unknown as the image was obtained from an Amazon product listing with a generic brand name.
