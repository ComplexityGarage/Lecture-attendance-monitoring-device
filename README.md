# UniLog

# Description of the project 
The UniLog device is designed to enhance the quality of the educational process and optimize teaching time during classes by automating student attendance tracking.

# Science and tech used 
- ESP32-S2 Feather
- MFRC522 RFID Reader
- OLED blue graphic display 1.3' 128x64px I2C
- Arduino IDE

# State of the art 
The UniLog has reached the prototype stage and is now ready for initial testing within the university environment.

# What next?
If the UniLog device proves successful during the limited testing phase, we have several proposals for further project development.

#### For large-scale deployment, the following improvements are proposed:

#### Hardware Updates:
- Switch to a more cost-effective and compact microcontroller, such as the ESP32-C3 or similar.
- Modify the RFID MF RC522 antenna to enhance the student card reading range.

#### Security and Integration:
- Add one-time tokens for API security.
- Additional encryption of student card UID codes to enhance privacy.
- Update the web platform to automatically detect lecture modes and handle student registration.
- Integration of the web platform with the Pegaz student system to synchronize attendance records.

These improvements will help make UniLog more practical and secure for wider use across the university. The whole system (both device and web platform) can be further refined based on testing results.

# Authors 
- Viktoriia Iashchuk
- Vitalii Kazakevich

# Sources 
- Adafruit ESP32-S2 Feather Pinouts – [https://learn.adafruit.com/adafruit-esp32-s2-feather/pinouts](https://learn.adafruit.com/adafruit-esp32-s2-feather/pinouts)
- Tinkercad – [https://tinkercad.com](https://www.tinkercad.com/)
- Image2cpp – [https://javl.github.io/image2cpp](https://javl.github.io/image2cpp/)
