This project using: 
- Kit TM4C123GH6PM
- Software: CCS 10.0.0
- Library: TIVAWARE
Project: Autonomous Door StateMachine
- When detect motion, system control door open by set pin OPENDOOR
- After detect no motion in 10s, close door by clear pin OPENDOOR
- While detecting motion, system output Ledred to announce with 1Hz Frequency.
- The system detect motion when receive signal from sensor continously in 50ms, and detect no motion when don't receive motion continously in 50ms 
