#include <LiquidCrystal_I2C.h>

// Initialize LCD at I2C address 0x3F (adjust if different)
// I2C LCD wiring for Arduino UNO:
// - SDA: Connect to pin A4
// - SCL: Connect to pin A5
// - VCC: Connect to 5V
// - GND: Connect to GND
LiquidCrystal_I2C lcd(0x27, 16, 2); // 16x2 LCD

// Define ultrasonic sensor pins
const int trigPin = 12; // Trigger pin for ultrasonic sensor
const int echoPin = 11; // Echo pin for ultrasonic sensor

// Variables for distance measurement
long duration;
int distance;

// Constants for calculations and timing
const float SOUND_SPEED_CM_PER_US = 0.034; // Speed of sound in cm per microsecond
const int TANK_DEPTH_CM = 15;             // Tank depth in cm (adjust as needed)
const int LOOP_DELAY_MS = 100;             // Delay between measurements

void setup() {
  // Set pin modes for ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on backlight (if supported)
  lcd.clear();      // Clear any residual display
}

void loop() {
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(7);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure echo pulse duration
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance to water surface in cm
  distance = duration * SOUND_SPEED_CM_PER_US / 2;

  // Calculate water level (distance from bottom of tank to water surface)
  int waterLevel = TANK_DEPTH_CM - distance;
  
  // Ensure water level is within valid range (0 to TANK_DEPTH_CM)
  if (waterLevel < 0) waterLevel = 0;
  if (waterLevel > TANK_DEPTH_CM) waterLevel = TANK_DEPTH_CM;
  
  // Calculate water level percentage
  int percentage = (waterLevel * 100) / TANK_DEPTH_CM;

  // Clear LCD only once per loop to reduce flickering
  lcd.clear();
  lcd.setCursor(0, 0);
  
  // Display water level on LCD
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);
  lcd.print(waterLevel);
  lcd.print("cm (");
  lcd.print(percentage);
  lcd.print("%)");
  
  // Serial output for debugging
  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.print(" cm (");
  Serial.print(percentage);
  Serial.println("%)");

  // Delay for next measurement
  delay(LOOP_DELAY_MS);
}