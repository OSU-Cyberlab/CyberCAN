# CyberCAN
CyberCAN: a benchmark simulator designed to simulate In-Vehicle Network traffic and Adversarial Attacks for vehicle operations using a real-world validated heavy-duty truck model.

**Developed by:**

Qazi Mairaj ud din (Centre for Automotive Research)

For any queries please email @ mairajuddin.1@osu.edu

Please feel free to use CyberCAN to generate, develop, test or validate your defense and control mechanisms.

Please cite the work if you use it for reference.

Mairaj ud din, Q. and Ahmed, Q., "CyberCAN: In-Vehicle Network and Attack Simulator," submitted to SAE Technical Paper 2025-01-****, 2025.

# About CyberCAN

![image](https://github.com/user-attachments/assets/8404e7a8-1ab3-4c9d-a842-adc8dbc60e0c)

This work introduces CyberCAN, a benchmark simulator designed to simulate IVN traffic for vehicle operations using a real-world validated heavy-duty truck model. 
CyberCAN is designed to assist system engineers & cybersecurity experts to evaluate impact of an attack on a vehicle model. And use the results to design appropriate safety and security mechanisms.

CyberCAN supports the J1939 CAN protocol and is flexible to be adapted for other
vehicle models as well. In addition to simulating normal driving conditions, it also simulates vehicle behavior under different
adversarial attacks on the vehicle network such as Denial of Service (DoS), Fuzzing, Replay, Plateau and Spoofing attacks.
CyberCAN also logs the network traffic under both normal and attack conditions in CAN format. The generated datasets from
CyberCAN offer valuable resources for developing and testing more resilient control and defence mechanisms, contributing
significantly to the safety and cybersecurity of automotive systems.


# How to use CyberCAN

![image](https://github.com/user-attachments/assets/ccbe2861-e2fc-4ee0-acc1-887aaa708444)

CyberCAN is designed in Matlab/Simulink environment, where the user can define a certain road scenario (CyberCAN comes with predefined Road Scenario) and driving profile for their test vehicle. The Vehicle model can be tweaked by the user to accomodate their desired specifications. 

1. Upon running the RunMe.m file, the user is asked for a set of inputs which defines the driving profile and the attack model.
   
![input](https://github.com/user-attachments/assets/7fce18e6-ff55-4ec4-83a4-be136407acbb)
_caption: An example showing the user inputs as per their requirements_

   i. **Enter the total simulation time:** _(this defines the total duration of the simulation)_

   ii. **Select Cruise Profile (Step decrease = 1, Constant 80kph = 2):** _(The simulation provides 2 options for the cruise speed profile of the vehicle, 1. the vehicle starts at 90 kph and would start decreasing 10kph after the first 50 secs with an interval of 100 sec, until it reaches 30 kph. 2. The vehicle would cruise at a set speed of 80kph)_

   iii.** Select the type of Attack (1= Fuzzy, 2=spoofing, 3=Plateau, 4=Replay Attack, 5 = GAttack, 6= C-GAttack, 7= No Attack, 8 = Denial of Service):** _(CyberCAN model incorporates 5 known types of adversarial attacks and 2 Generative AI based advanced attack types 'GAttack' and C-GAttack'. The user can choose the attack types and observe the impact of that particular attack on the vehicle)_

   iv. **Enter the desired frequency of attack:** _(Attack frequency (f) indicates the number of attack sequences, i.e. how many times the attack is to be executed on the vehicle during the drive cycle. The attack sequences are equally spaced and depend on the total simulation time and the start time for the attack)_

   v. **Enter the duration of each attack:** _(The attack duration (d) represents the total duration of each attack sequence executed on the vehicle)_

  vi. **Enter the time for attack:** _(The attack time (t), specifies the exact moments during the driving cycle when each attack is introduced, relative to the start of the drive cycle)_

  vii. **Set the spoofing value:** _(If the attack type selected is spoofing attack, then the user will be asked to enter the spoofing value for the attack)_

Once all the inputs are provided, the simulation would start running and produce detailed output related to vehicle behavior during the drive cycle. The simulation would automatically generate plots for:

a. Vehicle Speed & Cruise Speed Command 

b. Gear Selected

c. Engine Speed

d. Torque

e. Turbo Speed

f. Control inputs (Throttle Command, Clutch, Gear Request, EGR valve, VGT)

![image](https://github.com/user-attachments/assets/9bcc7be3-3b65-47a6-bce9-6d63f5a219d5)
![image](https://github.com/user-attachments/assets/433676f1-7b50-4f65-b76c-e836b3f759db)

**Experimental Results**

1. Denial of Service Attack

The attack is initiated at the defined attack time, by suppressing the targeted velocity feedback signal. The vehicle’s actual velocity (solid red line) begins to accelerate unexpectedly compared to the predicted normal velocity (dotted magenta line), as shown This discrepancy between the actual and expected velocities leads to unintended acceleration, causing hazardous conditions. Based on damage scenario assessment, as per Safety Standard, the impact of this scenario would be classified as ”Severe” as the abnormal behavior in the vehicle’s operation poses a high risk of potentially fatal outcomes.
   
![vehicle_dos](https://github.com/user-attachments/assets/b263317e-ad55-4339-8e9b-8f32d981fd19)

2. Fuzzing Attack

   The attack is initiated at the defined attack time, and the vehicle’s actual velocity (solid red line) begins to accelerate unexpectedly compared to the predicted normal velocity (dotted magenta line), as shown in Figure. This discrepancy
between the actual and expected velocities leads to unintended acceleration, causing hazardous conditions. Based on damage scenario assessment, as per Road Vehicle Functional Safety Standard ISO 26262, the impact of this scenario would be classified as ”Severe” as the abnormal behavior in the vehicle’s operation poses a high risk of potentially fatal outcomes

![fuzz](https://github.com/user-attachments/assets/9091714c-058e-48d4-88b1-de0cf63e1b6b)

3. Plateau Attack

  The attack duration set at 10 sec has a very marginal impact in the Plateau attack type, which reflects as an insignificant difference between vehicle’s actual velocity (solid red line) and the predicted normal velocity (dotted magenta line), as shown in Figure.
  
  ![vehicle_plateau](https://github.com/user-attachments/assets/0827ec11-95e3-46b3-b5fa-2dc7969080e9)

4. Replay Attack

The attack is initiated at the defined attack time, by replaying previously stored data. The vehicle’s actual velocity (solid red line) begins to accelerate unexpectedly compared to the predicted normal velocity (dotted magenta line), as shown in Figure.

![vehicle_replay](https://github.com/user-attachments/assets/38681661-697e-4d71-83c3-ffaea25b08c8)

5. Spoofing Attack

The attack is initiated at the defined attack time with spoofed value of 50 kph. The vehicle’s actual velocity (solid red line) begins to accelerate unexpectedly compared to the predicted normal velocity (dotted magenta line), as shown in Figure.

![vehicle_spoofing](https://github.com/user-attachments/assets/ed8ed90e-f4e0-4fd3-b50d-bce5889ed075)

Once the simulation is completed, a CAN Log file with the timestamp is automatically generated.

![image](https://github.com/user-attachments/assets/238213c6-25ee-4e7e-bcc3-293c44bea3e7)

![image](https://github.com/user-attachments/assets/84090114-dada-449f-b545-3d105352c57b)

An extrctor for the CAN log has been written (python - jupyter notebook) and provided here:

'mat2py_canlog_SAE.ipynb'

**Specifications of Test System:**

Matlab R2023a
'PCWIN64'
'Microsoft Windows 11 Home'
('NUMBER_OF_PROCESSORS')
 '8'
('GetCPU')
'11th Gen Intel(R) Core(TM) i7-11375H @ 3.30GHz'
('numCores')
MATLAB detected: 4 physical cores.
MATLAB detected: 8 logical cores.
MATLAB was assigned: 8 logical cores by the OS.
MATLAB is using: 4 logical cores.
memory
Maximum possible array:        4692 MB (4.920e+09 bytes) *
Memory available for all arrays:        4692 MB (4.920e+09 bytes) *
Memory used by MATLAB:        7245 MB (7.597e+09 bytes)
Physical Memory (RAM):       16084 MB (1.687e+10 bytes)
