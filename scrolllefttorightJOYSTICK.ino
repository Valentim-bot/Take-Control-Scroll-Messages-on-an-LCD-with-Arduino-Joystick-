#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Joystick connections
const int joyXPin = A0; // Joystick X-axis analog pin
const int joyYPin = A1; // Joystick Y-axis analog pin

// Message to be scrolled
const char message[] = "Hello, World! ";

// Interval for scrolling in milliseconds
const unsigned long defaultScrollInterval = 250; // Default scrolling interval
unsigned long scrollInterval = defaultScrollInterval;

// Length of the message
int messageLength;

// Current position of scrolling
int scrollPosition = 0;

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();
  
  // Print a message to the LCD
  lcd.setCursor(0, 0);
  lcd.print(message);
  
  messageLength = strlen(message);
}

void loop() {
  // Read the X-axis value of the joystick
  int joyX = analogRead(joyXPin);

  // Map the joystick X-axis value to the scroll interval
  scrollInterval = map(joyX, 0, 1023, defaultScrollInterval * 2, defaultScrollInterval / 2);
  
  unsigned long currentMillis = millis(); // Get the current time
  
  // Check if it's time to update the scroll position
  if (currentMillis % scrollInterval == 0) {
    // Clear the display
    lcd.clear();
    
    // Set the cursor position for scrolling
    int startPos = scrollPosition;
    for (int i = 0; i < 16; i++) {
      lcd.setCursor(i, 0);
      if (startPos + i >= 0 && startPos + i < messageLength) {
        lcd.print(message[startPos + i]);
      } else {
        lcd.print(" ");
      }
    }
    
    // Increment the scroll position
    scrollPosition--;
    if (scrollPosition <= -messageLength) {
      scrollPosition = 0; // Reset scroll position
    }
  }
}
