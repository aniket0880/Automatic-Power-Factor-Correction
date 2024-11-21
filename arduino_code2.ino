// Define the analog pins connected to the ZMPT101B and the current sensor
const int analogPinVoltage = A0; // ZMPT101B
const int analogPinCurrent = A1;  // Current sensor

// Define the pin connected to the relay
const int relayPin = 7; // Adjust the pin number as needed

// Track the last time the relay was toggled
unsigned long previousMillis = 0;
const unsigned long interval = 30000; // 30 seconds in milliseconds
bool relayState = true; // Start with the relay in the "on" state

// Define the reference voltage for scaling
const float referenceVoltage = 5.0;  // Adjust based on your board (5V for most Arduino boards)
const int adcMaxValue = 1023;  // Max value of the ADC

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

  // Convert the sensor values to voltage and current
  float voltage = (sensorValueVoltage / float(adcMaxValue)) * referenceVoltage;
  float current = (sensorValueCurrent / float(adcMaxValue)) * referenceVoltage;

  // Calculate the power (P = V * I)
  float power = voltage * current;

  // Approximate the power factor as the ratio of real power to apparent power
  float apparentPower = voltage * current; // Apparent power (V * I)
  float powerFactor = power / apparentPower;

  // Print the analog values and calculated power factor to the serial monitor
  Serial.print("Voltage (V): ");
  Serial.print(voltage, 2);
  Serial.print(" | Current (A): ");
  Serial.print(current, 2);
  Serial.print(" | Power Factor: ");
  Serial.println(powerFactor, 2); // Display the power factor with 2 decimal places

  // Small delay for better readability in the serial monitor
  delay(500); // Adjust as needed
}
