Water Level Monitoring System Using Arduino UNO, HC-SR04 Ultrasonic Sensor & I2C LCD
This project implements a real-time water level monitoring system using the Arduino UNO, HC-SR04 ultrasonic sensor, and a 16×2 LCD with I2C interface.
The system measures the distance between the sensor and water surface, calculates the water level, and displays both centimeters (cm) and percentage (%) on the LCD.

📌 Project Overview
Traditional water level indicators often rely on float switches, which may wear out or give inaccurate readings.
This project offers a non-contact, reliable, and low-cost alternative using ultrasonic sensing.

The device continuously:

Measures distance using ultrasonic waves

Calculates water height

Converts it to tank fill percentage

Displays the results on an LCD

Prints the values in Serial Monitor

🛠 Features
✔ Non-contact water level sensing
✔ Real-time display on 16×2 I2C LCD
✔ Adjustable tank depth
✔ Serial output for monitoring/debugging
✔ Low-cost and beginner-friendly
✔ Can be expanded with buzzer, Wi-Fi module, or motor control

📦 Components Required
Component	Quantity	Description
Arduino UNO R3	1	Main microcontroller
HC-SR04 Ultrasonic Sensor	1	Measures distance
16×2 I2C LCD Display	1	Shows water level
Jumper Wires	—	Connections
USB Cable	1	Power + Upload code
Water Tank / Container	1	For testing
🔌 Circuit Connections
HC-SR04 Ultrasonic Sensor → Arduino UNO
HC-SR04 Pin	Arduino Pin
VCC	5V
GND	GND
TRIG	D12
ECHO	D11
16×2 I2C LCD → Arduino UNO
LCD Pin	Arduino Pin
VCC	5V
GND	GND
SDA	A4
SCL	A5
📟 Working Principle
The ultrasonic sensor sends a high-frequency sound pulse.

The pulse reflects back from the water surface.

Arduino calculates the time of flight to determine distance:

distance = (duration × speed of sound) / 2
Water level is computed using:

waterLevel = tankDepth – measuredDistance
Percentage = (waterLevel / tankDepth) × 100

Results are displayed on the LCD and printed on Serial Monitor.

💻 Arduino Code
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 12;
const int echoPin = 11;
long duration;
int distance;

// Set according to your tank depth (in cm)
const int TANK_DEPTH_CM = 10;
const float SOUND_SPEED_CM_PER_US = 0.034;
const int LOOP_DELAY_MS = 100;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(7);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * SOUND_SPEED_CM_PER_US / 2;

  int waterLevel = TANK_DEPTH_CM - distance;
  if (waterLevel < 0) waterLevel = 0;
  if (waterLevel > TANK_DEPTH_CM) waterLevel = TANK_DEPTH_CM;

  int percentage = (waterLevel * 100) / TANK_DEPTH_CM;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);
  lcd.print(waterLevel);
  lcd.print("cm (");
  lcd.print(percentage);
  lcd.print("%)");

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.print(" cm (");
  Serial.print(percentage);
  Serial.println("%)");

  delay(LOOP_DELAY_MS);
}
📚 Required Libraries
Install the following in Arduino IDE:

✔ LiquidCrystal_I2C
Go to: Sketch → Include Library → Manage Libraries

Search: LiquidCrystal_I2C

Install (by Frank de Brabander recommended)

(Wire.h is built-in)

🧪 How to Use
Assemble the circuit according to the wiring diagram.

Install the required library.

Open Arduino IDE → Select board: Arduino UNO

Upload the code.

Set the tank depth inside code:

const int TANK_DEPTH_CM = 10;
Place the sensor at the top of the tank.

Observe readings on LCD and Serial Monitor.

📐 Adjustments
To change LCD address
If your LCD shows nothing, try changing:

LiquidCrystal_I2C lcd(0x27, 16, 2);
to:

LiquidCrystal_I2C lcd(0x3F, 16, 2);
To increase accuracy
Keep sensor stable

Avoid splashes hitting the sensor

Use a narrow test pipe for stability

📷 Project Images

/connections/circuit.png
🚀 Applications
Home overhead tanks

Industrial liquid monitoring

Disaster management systems

Automatic pump control (expandable)

Agriculture irrigation tanks

🌟 Future Improvements
Wi-Fi monitoring using ESP8266

Buzzer alarm for low/high levels

Auto motor ON/OFF control via relay

Mobile app notification

🧾 Conclusion
This project demonstrates a simple yet powerful method to measure water levels using ultrasonic sensing. It is reliable, affordable, and easily customizable, making it suitable for real-world use in homes, farms, and industrial setups.



