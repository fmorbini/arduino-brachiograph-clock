/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <arduino.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin


int menuselect;
int zero[5][2] = {{0, 1}, {1, 1}, {1, -1}, {0, -1}, {0, 1}};
int one[2][2] = {{0, 1}, {0, -1}};
int two[6][2] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, -1}, {1, -1}};
int three[7][2] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 0}, {1, -1}, {0, -1}};
int four[5][2] = {{0, 1}, {0, 0}, {1, 0}, {1, 1}, {1, -1}};
int five[6][2] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, -1}, {0, -1}};
int six[7][2] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, -1}, {0, -1}, {0, 0}};
int seven[3][2] = {{0, 1}, {1, 1}, {1, -1}};
int eight[8][2] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, 1}, {0, -1}, {1, -1}, {1, 0}};
int nine[6][2] = {{1, 0}, {0, 0}, {0, 1}, {1, 1}, {1, -1}, {0, -1}};
float deltax = 1;
float xf = .5;
float yf = .5;

void liftPen();
void moveTo(float offsetx, float xf, float yf, float x, float y);

void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(4);  // attaches the servo on pin 9 to the servo object
  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  digitalWrite(22, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(24, LOW);   // turn the LED on (HIGH is the voltage level)
  liftPen();
  moveTo(deltax, xf, yf, 0, 0);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  // prints text and menu options for user to select from
  Serial.println(F("Please select a number from the options available"));
  Serial.println(F(" "));
  Serial.println(F("Main Menu"));
  Serial.println(F("---------"));
  Serial.println(F("1. change x"));
  Serial.println(F("2. change y"));
  Serial.println(F("3. print go"));
  Serial.println(F("4. print angle"));
  Serial.println(F("5. go"));
  Serial.println(F("6. clock"));
  Serial.println(F("7. away"));
  Serial.println(F("8. near"));
  goAway();
}

float l1 = 3;
float l2 = 3;
float l1s = pow(l1, 2);
float l2s = pow(l2, 2);
int clock[4] = {2, 1, 2, 9};

void incrementTimeByOneMinute() {
  if (clock[3] == 9) {
    clock[3] = 0;
    if (clock[2] == 5) {
      clock[2] = 0;
      if (clock[0] < 2 && clock[1] == 9) {
        clock[1] = 0;
        clock[0]++;
      } else if (clock[0] == 2 && clock[1] == 3) {
        clock[0] = 0;
        clock[1] = 0;
      } else {
        clock[1]++;
      }
    } else {
      clock[2]++;
    }
  } else {
    clock[3]++;
  }
}

void goAway() {
  digitalWrite(24, LOW);
  delay(100);
  digitalWrite(22, HIGH);
  delay(15000);
  digitalWrite(22, LOW);
}

void comeNear() {
  digitalWrite(22, LOW);
  delay(100);
  digitalWrite(24, HIGH);
  delay(15000);
  digitalWrite(24, LOW);
}

void liftPen() {
  myservo3.write(0);              // sets the servo position according to the scaled value
}

void lowerPen() {
  myservo3.write(40);              // sets the servo position according to the scaled value
}

void printClock() {
  comeNear();
  goAway();
  for (int i = 0; i < 4; i++) {
    Serial.println("digit");
    int d = clock[i];
    int (*n)[2];
    int l;
    Serial.println(d);
    if (d == 0) {
      n = zero;
      l = sizeof(zero) / sizeof(zero[0]);
    }
    if (d == 1) {
      n = one;
      l = sizeof(one) / sizeof(one[0]);
    }
    if (d == 2) {
      n = two;
      l = sizeof(two) / sizeof(two[0]);
    }
    if (d == 3) {
      n = three;
      l = sizeof(three) / sizeof(three[0]);
    }
    if (d == 4) {
      n = four;
      l = sizeof(four) / sizeof(four[0]);
    }
    if (d == 5) {
      n = five;
      l = sizeof(five) / sizeof(five[0]);
    }
    if (d == 6) {
      n = six;
      l = sizeof(six) / sizeof(six[0]);
    }
    if (d == 7) {
      n = seven;
      l = sizeof(seven) / sizeof(seven[0]);
    }
    if (d == 8) {
      n = eight;
      l = sizeof(eight) / sizeof(eight[0]);
    }
    if (d == 9) {
      n = nine;
      l = sizeof(nine) / sizeof(nine[0]);
    }
    Serial.println(l);
    liftPen();
    delay(500);
    float ayf = yf * (1 + 0.1 * i);
    for (int j = 0; j < l; j++) {
      Serial.print("  segment ");
      Serial.println(j);
      if (j == 0) {
        moveTo(deltax + (i + 1), xf, ayf, n[j][0], n[j][1]);
        delay(500);
        lowerPen();
        delay(500);
      } else {
        plotSegment(30, deltax + (i + 1), xf, ayf, n[j - 1][0], n[j - 1][1], n[j][0], n[j][1]);
      }
    }
    Serial.println("done digit");
  }
  liftPen();
  delay(500);
  moveTo(deltax, xf, yf, 0, 0);
}

void convertToAngle(float x, float y, float & a1, float & a2) {
  float rs = pow(x, 2) + pow(y, 2);
  float gamma = atan(y / x);
  float r = sqrt(rs);
  float sa1 = acos((l2s - l1s - rs) / (-2 * l1 * r));
  float sa2 = acos((rs - l1s - l2s) / (-2 * l1 * l2));
  a1 = (sa1 + gamma) * RAD_TO_DEG;
  a2 = sa2 * RAD_TO_DEG;
}

void set(float a1, float a2) {
  myservo.write(a1);              // sets the servo position according to the scaled value
  myservo2.write(180 - a2);                // sets the servo position according to the scaled value
  delay(20);
}

void moveTo(float offsetx, float xf, float yf, float x, float y) {
  float a1, a2;
  convertToAngle(offsetx + (x * xf), y * yf, a1, a2);
  Serial.println(a1);
  Serial.println(a2);
  set(a1, a2);
}

void plotSegment(int steps, float offsetx, float xf, float yf, float x1, float y1, float x2, float y2) {
  float deltax = x2 - x1;
  float deltay = y2 - y1;
  deltax = deltax / steps;
  deltay = deltay / steps;
  for (int i = 0; i < steps; i++) {
    float nx = x1 + (deltax * i);
    float ny = y1 + (deltay * i);
    moveTo(offsetx, xf, yf, nx, ny);
  }
}

float gx = 0;
float gy = 0;
unsigned long lastIncrement = millis();
unsigned const long DEFAULT_PERIOD = 60000;
unsigned long period = DEFAULT_PERIOD;
long adjust = 0;
printClock();
void loop()
{
  unsigned long delta = millis() - lastIncrement;
  if (delta > period) {
    lastIncrement = millis();
    adjust -= (delta - DEFAULT_PERIOD);
    period = DEFAULT_PERIOD + adjust;
    incrementTimeByOneMinute();
    printClock();
  }
  /*
    if (Serial.available())  //Constantly checks to see if anything has been sent over the USB Connection and if it needs to be processed

    {
    char val = Serial.read(); //Reads a single letter
    if (val == '1') {
      while (!Serial.available()) {}
      gx = Serial.parseFloat();
    }
    if (val == '2') {
      while (!Serial.available()) {}
      gy = Serial.parseFloat();
    }
    if (val == '3') {
      Serial.println("print");
      Serial.println(gx);
      Serial.println(gy);
    }
    if (val == '4') {
      float a1, a2;
      convertToAngle(deltax + (gx * xf), gy * yf, a1, a2);
      Serial.println("print 2");
      Serial.println(deltax + (gx * xf));
      Serial.println(gy * yf);
      Serial.println(a1);
      Serial.println(a2);
    }
    if (val == '5') {
      moveTo(deltax, xf, yf, gx, gy);
    }
    if (val == '6') {
      printClock();
    }
    if (val == '7') {
      goAway();
    }
    if (val == '8') {
      comeNear();
    }
    }
  */
}
