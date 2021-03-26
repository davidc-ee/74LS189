#include <avr/sleep.h>

// Arduino PIN -> 74LS189 PIN
//           2 -> A0 (PIN  1 on 74LS189)
//           3 -> A1 (PIN 15 on 74LS189)
//           4 -> A2 (PIN 14 on 74LS189)
//           5 -> A3 (PIN 13 on 74LS189)

#define memoryIC_A0 2
#define memoryIC_A1 3
#define memoryIC_A2 4
#define memoryIC_A3 5

// Arduino PIN -> 74LS189 PIN
//           6 -> D1 (PIN  4 on 74LS189)
//           7 -> D2 (PIN  6 on 74LS189)
//           8 -> D3 (PIN 10 on 74LS189)
//           9 -> D4 (PIN 12 on 74LS189)

#define memoryIC_D1 6
#define memoryIC_D2 7
#define memoryIC_D3 8
#define memoryIC_D4 9

// Arduino PIN -> 74LS189 PIN
//          10 -> O1 (PIN  5 on 74LS189)
//          11 -> O2 (PIN  7 on 74LS189)
//          12 -> O3 (PIN  9 on 74LS189)
//          13 -> O4 (PIN 11 on 74LS189)

#define memoryIC_O1 10
#define memoryIC_O2 11
#define memoryIC_O3 12
#define memoryIC_O4 13

// Write Enable PIN
// Arduino PIN -> 74LS189 PIN
//          14 -> WE (PIN  3 on 74LS189)
#define memoryIC_WE 14

// Serial Console Speed
#define conSpeed 250000

void setup() {

  // ADDRESS LINES on the Arduino are OUTPUT
  // because we need to INPUT on the 74LS189
  pinMode(memoryIC_A0, OUTPUT);
  pinMode(memoryIC_A1, OUTPUT);
  pinMode(memoryIC_A2, OUTPUT);
  pinMode(memoryIC_A3, OUTPUT);

  // DATA LINES on the Arduino are OUTPUT
  // because we need to INPUT on the 74LS189
  pinMode(memoryIC_D1, OUTPUT);
  pinMode(memoryIC_D2, OUTPUT);
  pinMode(memoryIC_D3, OUTPUT);
  pinMode(memoryIC_D4, OUTPUT);
  
  // OUTPUT LINES on the Arduino are INPUT
  // because we need to OUTPUT on the 74LS189
  pinMode(memoryIC_O1, INPUT);
  pinMode(memoryIC_O2, INPUT);
  pinMode(memoryIC_O3, INPUT);
  pinMode(memoryIC_O4, INPUT);

  // WRITE ENABLE PIN
  pinMode(memoryIC_WE, OUTPUT);

  // Enable Serial Console
  Serial.begin(conSpeed);
}

void loop() {
  
  int count      = 0;
  int delayTime  = 50;
  int delayWrite = 1;
  int errorCount = 0;

  Serial.print("------------------\n");
  Serial.print("Beginning New Test\n");
  Serial.print("------------------\n");
  

  // Cycle through each memory location.
  // Turn all BITS ON, then check the OUTPUT to make sure all BITS are ON
  // Remember, the OUTPUT is inverse logic, so when all BITS are ON,
  // we should actually be reading 0's. So if we read a 1 instead of a 0,
  // there is an error.
  //
  // After that...
  //
  // Turn all BITS OFF, then check the OUTPUT to make sure all BITS are OFF
  // Noting once again the inverse logic. So we should be reading 1's when
  // the BITS are OFF.
    
  for (count = 0 ; count <= 15 ; count++ ) {
    Serial.print("Count: ");
    Serial.print(count);
    Serial.print("\n");

    // Use BIT LOGIC operations to cycle through
    // the various memory address locations 
    digitalWrite(memoryIC_A0, (count & 0x01) == 0x01);
    digitalWrite(memoryIC_A1, (count & 0x02) == 0x02);
    digitalWrite(memoryIC_A2, (count & 0x04) == 0x04);
    digitalWrite(memoryIC_A3, (count & 0x08) == 0x08);

    // Turn all bits ON
    digitalWrite(memoryIC_D1, HIGH);
    digitalWrite(memoryIC_D2, HIGH);
    digitalWrite(memoryIC_D3, HIGH);
    digitalWrite(memoryIC_D4, HIGH);

    // Enable WRITE
    digitalWrite(memoryIC_WE, LOW);

    // Wait the defined amount of time
    delay(delayWrite);

    // Disable WRITE
    digitalWrite(memoryIC_WE, HIGH);

    // Wait the defined amount of time
    delay(delayWrite);


    // Read back the value from the IC
   
    if (digitalRead(memoryIC_O1) == 1) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING ON CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 0");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O2) == 1) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING ON CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 1");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O3) == 1) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING ON CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 2");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O4) == 1) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING ON CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 3");
      Serial.print("\n\n\n");
      delay(delayTime);
    }    
    
    // Turn all bits OFF
    digitalWrite(memoryIC_D1, LOW);
    digitalWrite(memoryIC_D2, LOW);
    digitalWrite(memoryIC_D3, LOW);
    digitalWrite(memoryIC_D4, LOW);

    // Enable WRITE
    digitalWrite(memoryIC_WE, LOW);

    // Wait the defined amount of time
    delay(delayWrite);

    // Disable WRITE
    digitalWrite(memoryIC_WE, HIGH);

    // Wait the defined amount of time
    delay(delayWrite);

    
    // Read back the value from the IC
    
    if (digitalRead(memoryIC_O1) == 0) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING OFF CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 0");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O2) == 0) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING OFF CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 1");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O3) == 0) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING OFF CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 2");
      Serial.print("\n\n\n");
      delay(delayTime);
    }
    if (digitalRead(memoryIC_O4) == 0) {
      errorCount++;
      Serial.print("\nERROR DETECTED DURING OFF CYCLE\n");
      Serial.print("Memory Location: ");
      Serial.print(count);
      Serial.print("\tBIT: 3");
      Serial.print("\n\n\n");
      delay(delayTime);
    }  
  } // end of for loop

  
  
  // Now we just want to output some final information to the user
  Serial.print("\n");
  
  // Error report
  if (errorCount > 0) {
    Serial.print("!!! ");
    Serial.print(errorCount);
    if (errorCount == 1) {
      Serial.print(" error detected !!!\n");
    } else {
      Serial.print(" errors detected !!!\n");
    }
  } else {
    Serial.print("No errors detected.\n");
  }
  
  // All done.
  Serial.print("\nTest is done.\n\n");
  delay(delayTime);
  
  // No need to rerun the test in an infinite loop, so just
  // put the Arduino to sleep when the test is done.
  cli();
  sleep_enable();
  sleep_cpu();
} // end of program
