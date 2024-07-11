int x;

void setup() {
  Serial.begin(9600);            // Set baud rate to match the Python script
  pinMode(LED_BUILTIN, OUTPUT);  // Set LED pin as output
  digitalWrite(LED_BUILTIN, LOW);// Switch off LED initially
  Serial.println("Arduino ready");  // Indicate Arduino is ready
}

void loop() {
  // Wait for data to arrive
  while (!Serial.available()) {}

  // Read string data from Serial, assuming Python script sends an integer
  String data = Serial.readStringUntil('\n');
  x = data.toInt();

  // Blink the LED 'x' times with a 1-second interval
  for (int i = 0; i < x; i++) {
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED on
    delay(1000);                      // Wait for 1 second
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED off
    delay(1000);                      // Wait for 1 second
  }

  // Generate a random number between 1 and 10
  int randomNum = random(1, 11);  // Corrected range to 1-10

  // Send the random number back to the Python script
  Serial.println(randomNum);
  
  // Push the data through the serial channel.
  Serial.flush();  
}
