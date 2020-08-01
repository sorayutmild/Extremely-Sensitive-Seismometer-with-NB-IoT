# Extremely-Sensitive-Seismometer-with-NB-IoT
Arduino code part Sensor Measuring and filtering : https://create.arduino.cc/projecthub/mircemk/extremely-sensitive-cheap-homemade-seismometer-175231


there are 2 part. First is  Sensor Measuring and filtering. From Original code, I've changed some code to communicate between two Arduino UNO board with I2C protocol. 
anther part, I've used another Arduino UNO board to sending data to Node-red with NB-IoT shield UDP protocol.

# reason why i use 2 arduino
because when i used one Arduino, there was some delay from sending command cause filtering was wrong. So i decided to use 2 Arduino board 1 for Measuering and filtering and one for sending data specify.
