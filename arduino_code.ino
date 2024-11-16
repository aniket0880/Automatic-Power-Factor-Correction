// Define the analog pins connected to the ZMPT101B and the current sensor
const int analogPinVoltage = A0; // ZMPT101B
const int analogPinCurrent = A1;  // Current sensor

// Define the pin connected to the relay
const int relayPin = 7; // Adjust the pin number as needed

// Track the last time the relay was toggled
unsigned long previousMillis = 0;
const unsigned long interval = 30000; // 30 seconds in milliseconds
bool relayState = true; // Start with the relay in the "on" state

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);
  
  // Set the relay pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Initialize the relay to the "on" state
  digitalWrite(relayPin, HIGH);
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 30 seconds have passed since the last toggle
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the relay was toggled
    previousMillis = currentMillis;

    // Toggle the relay state (on to off or off to on)
    relayState = !relayState;
    digitalWrite(relayPin, relayState ? HIGH : LOW);
  }

  // Read the analog values continuously
  int sensorValueVoltage = analogRead(analogPinVoltage);
  int sensorValueCurrent = analogRead(analogPinCurrent);

  // Print the analog values to the serial monitor
  Serial.print("Voltage Sensor Value: ");
  Serial.print(sensorValueVoltage);
  Serial.print(" | Current Sensor Value: ");
  Serial.println(sensorValueCurrent);

  // Small delay for better readability in the serial monitor
  delay(500); // Adjust as needed
}
