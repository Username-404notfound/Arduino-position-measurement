// Include the LiquidCrystal library
#include <LiquidCrystal.h>

// Initialize the LiquidCrystal library by associating LCD interface pins
// with the corresponding Arduino pin numbers
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd (rs, en, d4, d5, d6, d7);

// Parameters pre-defined
int count_peak = 0; // Peak number counted
int val; // Input voltage level
int data; // Original input read from the port
int former_result = 0; // Store the previous counting number result
int inPeak_false = 0; // Store the new counting number result
bool inPeak = false; // Set the initial logic judgement
unsigned long lastPeakTime = 0; // Store the last peak time
unsigned long debounceTime = 200; // Debounce time in ms

// A setup function that is used to do Settings at initialization
void setup() {
  pinMode(A0 , INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD
  lcd.print("Displacement:");
}
 // Enter the loop function
void loop() {
  data = digitalRead(A0); // Initial read for the input voltage value
  val = data; // Transfer the value to anothervariable
  
  // While loop condition setup for number counting 
  while (val == HIGH) {
    // Logic statement for judging whether encountering a peak
    if (!inPeak && (millis() - lastPeakTime > debounceTime && inPeak_false < 2)) {
      count_peak ++; // Counted peak plus one
      inPeak = true; // Reset judgenent parameter for the next counting process
      inPeak_false = 0; // Reset logic judgement parameter
      lastPeakTime = millis(); // Update the last peak time
      }
    
    //Other logic condition
    else if (inPeak_false > 1) {
      break; // Leave the while loop when encountering falling edge more than once
      }

    // Other logic condition
    else {
      inPeak = false; // Reset judgement parameter
      inPeak_false ++; // Add one to the counted falling edge 
      }
}

  // Pre-defined new parameters for the next judgement
  int distance; // Variable for storage of actual distance
  int new_result; // Variable for storgae of current counting result
  int result_peak = count_peak / 2; // Variable for the calculation of actual number of patterns 
  
  // Logic statement for judging whether the calculated number os fraction or integer
  if (result_peak % 1 == 0){
    new_result = result_peak; // Store the current result
    distance = result_peak * 520e-9 / (2 * 1.00029); // Calculate the actual distance with variables provided 
  } 
  
  // Other logic condition
  else{
    result_peak = result_peak + 0.5; // Make the actual pattern number to its nearest value
    new_result = result_peak; // Store the current result
    distance = result_peak * 520e-9 / (2 * 1.00029); // Calculate the actual distance with variables provided
  }

  lcd.setCursor(0, 1); // Initialize the second column of the LCD
  lcd.print(distance); // Output the calculated distance value
  delay(4500); // Delay time initialize

  // Other logic condition
  if (new_result > former_result){
    lcd.clear(); // Clear all system output
    lcd.print("Direction:"); // Output the title for the parameter
    lcd.setCursor(0, 1); // Initialize the second column of the LCD
    lcd.print("Move away from"); // Output the moving direction for the displacement
    delay(500); // Delay time initialize
  }

  // Other logic condition
  else{
    lcd.clear(); // Clear all system output
    lcd.print("Direction:"); // Output the title for the parameter
    lcd.setCursor(0, 1); // Initialize the second column of the LCD
    lcd.print("Move close to"); // Output the moving direction for the displacement
    delay(500); // Delay time initialize
  }
}