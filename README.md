"# Smart_Atendence_System_with_Avr_Atmega32" 
Project Objective:
The objective of the RFID Attendance System is to automate the attendance process using
RFID technology. The system aims to read RFID tags carried by users, verify their identities by
checking against a database, and record attendance. The system will provide visual feedback
through LEDs and communicate the attendance status to a graphical user interface (GUI)
application.
1. Initialization:
• The system is ready to read an RFID tag.
2. User Interaction:
• When a user presents an RFID tag, the RFID module reads the tag data.
And the white led is on..
3. Data Processing:
• The ATmega32 microcontroller receives the RFID data and sends it to the GUI
application via UART communication.
4. Database Verification:
• The GUI application checks the received RFID data against a database of valid IDs.
• If the ID is found in the database, the GUI records the user's attendance and displays a
success message in the window.
• The GUI sends a success flag to the microcontroller via UART.
5. LED Feedback:
• Upon receiving the success flag, the microcontroller turns on the green LED for 1 second
to indicate successful attendance.
• If the ID is not found in the database, the GUI sends a failure flag to the microcontroller.
• The microcontroller turns on the red LED for 1 second to indicate unsuccessful
attendance.
6. Ready for Next Interaction:
• After the LED feedback, both the white and green (or red) LEDs are turned off.
• The microcontroller is then ready to read another RFID tag, and the system returns to the
initial state with the white LED turned on.
