Simple speedo based on wheel base and reed switch. It is done in MPLAB C for 8bit PICs. It doesn't catch interrupt from reed, but uses run loop. It measures current sessions Kms passed and overall Kms passed, as current speed. Overall Kms passed are stored in eeprom and range is 0-999Km.

Magnet should be positioned somewhere at wheel, and REED somewhere on front forks. Distance between magnet and reed switch should be less then 10mm when magnet passing reed 

For components list and schematicks please visit [wiki page](https://github.com/markodjurovic/speedometer/wiki)

To build source on 16f628 you need licenced compiler. To build it using free compiler you got to use some microcontroller with more instructions memory.

[Lab action](https://www.youtube.com/watch?v=33Hf6KTkfwc)
