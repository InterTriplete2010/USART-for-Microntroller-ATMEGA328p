# USART-for-Microntroller-ATMEGA328p
Code to have two arduino UNO boards communicate with one other via USART

These two simple files are used to have two arduino boards communicate with one another via USART. While I am aware that what I am posting is something very basic, I hope it can be of some help to people new to microcontrollers. You will need two arduino boards to execute this code and the ATMEL ICE to burn the code provided in the file named "USART_ATMEL", as that code was written in Microchip Studio. Alternatively, you can obviously have one arduino board and buy an ATMEGA328p microcontroller and use it on your own board.

1) The file namedd "USART_Arduino.cpp" is used to have the first arduino board (AB1) to send "66" and to read data;

2) The file named "USART_ATMEL" is used to set the USART in the second arduino board (AB2). This code was written in Microchip Studio and was burnt into ATMEGA328p by using ATMEL ICE.

AB1 will send the code "66" to AB2, that will read the code and will send it back to AB1. When data are received and sent by AB@, the interrupts will kick in, causing a LED connected to AB2 to flash every 500 ms (Port PD5). Also, when the circuit first starts, a LED connected to PD7 will be on and will be switched off after the fourth time that the message will be read and transmitted by AB2. At that point, a seocnd interrupt will kick in switching on a LED connected to PD6. 

I hope that this code can be useful to soemone.

If you have any questions and/or want to report bugs, please e-mail me (Ale) at: pressalex@hotmail.com
