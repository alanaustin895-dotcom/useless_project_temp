// =====================================================
// ESP32 FOUR-BAR MECHANISM
// + 5 LED COUNTER
// + POTENTIOMETER SPEED CONTROL
// + ULTRASONIC OBJECT DETECTION
// + SERIAL PLOTTER
// + BUZZER AFTER 5 COUNTS
// =====================================================


// =====================================================
// LED PINS
// =====================================================

const int LED1 = 13;
const int LED2 = 14;
const int LED3 = 27;
const int LED4 = 32;
const int LED5 = 33;


// =====================================================
// BUZZER
// =====================================================

const int BUZZER_PIN = 23;


// =====================================================
// HC-SR04 ULTRASONIC SENSOR
// =====================================================

const int TRIG_PIN = 4;
const int ECHO_PIN = 15;


// =====================================================
// POTENTIOMETER
// =====================================================

const int POT_PIN = 34;


// =====================================================
// L293D MOTOR DRIVER
// =====================================================

const int MOTOR_ENABLE = 25;   // L293D EN1
const int MOTOR_INPUT  = 26;   // L293D IN1


// =====================================================
// PWM SETTINGS
// =====================================================

const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;


// =====================================================
// COUNTER
// =====================================================

int count = 0;


// =====================================================
// ULTRASONIC SETTINGS
// =====================================================

const float DETECTION_DISTANCE = 6.0;   // cm

const unsigned long DETECTION_TIME = 10;


// =====================================================
// OBJECT DETECTION VARIABLES
// =====================================================

bool objectDetected = false;
bool objectCounted = false;

unsigned long objectStartTime = 0;


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);


  // -------------------------------------------------
  // LEDs
  // -------------------------------------------------

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);


  // Turn LEDs OFF

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);


  // -------------------------------------------------
  // Buzzer
  // -------------------------------------------------

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);


  // -------------------------------------------------
  // Ultrasonic sensor
  // -------------------------------------------------

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);


  // -------------------------------------------------
  // Motor
  // -------------------------------------------------

  pinMode(MOTOR_INPUT, OUTPUT);

  // Forward direction
  digitalWrite(MOTOR_INPUT, HIGH);


  // -------------------------------------------------
  // PWM
  // -------------------------------------------------

  // New ESP32 LEDC API

  ledcAttach(
    MOTOR_ENABLE,
    PWM_FREQ,
    PWM_RESOLUTION
  );


  // Motor initially stopped

  ledcWrite(
    MOTOR_ENABLE,
    0
  );


  // -------------------------------------------------
  // Startup
  // -------------------------------------------------

  delay(500);

  Serial.println("System ready");

  delay(500);

}


// =====================================================
// MAIN LOOP
// =====================================================

void loop() {


  // ===================================================
  // 1. READ POTENTIOMETER
  // ===================================================

  int potValue = analogRead(POT_PIN);


  int motorSpeed = map(
    potValue,
    0,
    4095,
    0,
    255
  );


  // Control four-bar motor speed

  ledcWrite(
    MOTOR_ENABLE,
    motorSpeed
  );


  // ===================================================
  // 2. MEASURE DISTANCE
  // ===================================================

  float distance = getDistance();


  // ===================================================
  // 3. DETECTION STATUS
  // ===================================================

  // 0 = No object
  // 1 = Object detected
  // 2 = Object counted

  int detectionStatus = 0;


  // ===================================================
  // 4. CHECK IF OBJECT IS WITHIN RANGE
  // ===================================================

  if (
    distance > 0 &&
    distance <= DETECTION_DISTANCE
  ) {


    // Object detected

    detectionStatus = 1;


    // -------------------------------------------------
    // Object has just entered detection area
    // -------------------------------------------------

    if (!objectDetected) {

      objectDetected = true;

      objectCounted = false;

      objectStartTime = millis();

    }


    // -------------------------------------------------
    // Object must stay for required time
    // -------------------------------------------------

    if (
      !objectCounted &&
      millis() - objectStartTime >= DETECTION_TIME
    ) {


      // Count the object

      count++;


      // ------------------------------------------------
      // Update LEDs
      // ------------------------------------------------

      updateLEDs();


      // Prevent counting same object again

      objectCounted = true;


      // Detection confirmed

      detectionStatus = 2;


      // ------------------------------------------------
      // AFTER 5 OBJECTS
      // ------------------------------------------------

      if (count >= 5) {

        // Blink all 5 LEDs for 4 cycles
        blinkAllLEDs();


        // Buzzer sounds
        buzzerAlert();


        // Reset counter
        count = 0;


        // Turn all LEDs OFF
        updateLEDs();

      }

    }

  }


  // ===================================================
  // 5. OBJECT LEFT DETECTION AREA
  // ===================================================

  else {

    objectDetected = false;

    objectCounted = false;

    detectionStatus = 0;

  }


  // ===================================================
  // 6. SERIAL PLOTTER OUTPUT
  // ===================================================

  Serial.print("Distance:");
  Serial.print(distance);

  Serial.print("\tDetection:");
  Serial.print(detectionStatus);

  Serial.print("\tCount:");
  Serial.print(count);

  Serial.print("\tMotorSpeed:");
  Serial.println(motorSpeed);


  // ===================================================
  // 7. SMALL DELAY
  // ===================================================

  delay(50);

}


// =====================================================
// ULTRASONIC DISTANCE FUNCTION
// =====================================================

float getDistance() {


  // -------------------------------------------------
  // Send trigger pulse
  // -------------------------------------------------

  digitalWrite(TRIG_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);


  // -------------------------------------------------
  // Measure echo
  // -------------------------------------------------

  long duration = pulseIn(
    ECHO_PIN,
    HIGH,
    30000
  );


  // -------------------------------------------------
  // No echo
  // -------------------------------------------------

  if (duration == 0) {

    return -1;

  }


  // -------------------------------------------------
  // Convert time to distance
  // -------------------------------------------------

  float distance =
    duration * 0.0343 / 2.0;


  return distance;

}


// =====================================================
// UPDATE LEDs
// =====================================================

void updateLEDs() {


  // LED 1

  digitalWrite(
    LED1,
    count >= 1 ? HIGH : LOW
  );


  // LED 2

  digitalWrite(
    LED2,
    count >= 2 ? HIGH : LOW
  );


  // LED 3

  digitalWrite(
    LED3,
    count >= 3 ? HIGH : LOW
  );


  // LED 4

  digitalWrite(
    LED4,
    count >= 4 ? HIGH : LOW
  );


  // LED 5

  digitalWrite(
    LED5,
    count >= 5 ? HIGH : LOW
  );

}


// =====================================================
// BLINK ALL 5 LEDs
// =====================================================

void blinkAllLEDs() {


  // 4 complete blink cycles

  for (int i = 0; i < 4; i++) {


    // -----------------------------------------------
    // LEDs ON
    // -----------------------------------------------

    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);


    delay(300);


    // -----------------------------------------------
    // LEDs OFF
    // -----------------------------------------------

    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);


    delay(300);

  }

}


// =====================================================
// BUZZER ALERT
// =====================================================

void buzzerAlert() {


  // Buzzer ON

  digitalWrite(BUZZER_PIN, HIGH);

  delay(1000);


  // Buzzer OFF

  digitalWrite(BUZZER_PIN, LOW);

}
