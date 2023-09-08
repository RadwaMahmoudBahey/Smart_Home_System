I'd like to share my graduation project for ITI (Information Technology Institute) , Smart home System

Implemented using two AVR ECUs : 

  The First one is designed to interact with the user (HMI_ECU),

  The Second one(Control_ECU) is specified for receiving signals from sensors and controlling actuators.

--The system asks the user to enter password and renter it again in case it's the first time setting it up , it also shows 2 options for : 

1) Open door : where it asks the home owner to enter password for more security and opens the door ( dc motor moves in clockwise motion ) then hold the door for 3 seconds then closes the door ( Anticlockwise for 15 seconds) 

2) Change Password : asks the user for the original password then asks for the new password and re-entering of it again for more security , if the last two didn't match it displays error message on the screen (LCD).

--System always displays the temperature taken from temperature sensor : if it exceeded certain threshold Fan will be activated automatically and it's led activates with it.

--Password is always saved in EEPROM through I2C , so when checking it , if it didn't match for 3 times consecutively : BUZZER will be on and an error message is displayed , the whole system will be locked no inputs from Keypad will be accepted during this time period.


>>> The drivers used are as follows: 

For MCAL: 

1-       GPIO

2-       I2C

3-       UART

4-       Timer

5-       ADC

6-      GIE (global interrupt)

For HAL:  

1-       LCD

2-       Keypad

3-       DC-motor

4-       buzzer

5-       EEPROM

6-       Temperature sensor

7-       Door Motor
