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

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin


int menuselect;
int two[6][2] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}, {0, -1}, {1, 1}};
float deltax = 1;
float xf = 1;
float yf = 1;

void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(4);  // attaches the servo on pin 9 to the servo object
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

}

float l1 = 3;
float l2 = 3;
float l1s = pow(l1, 2);
float l2s = pow(l2, 2);

void convertToAngle(float x, float y, float & a1, float & a2) {
  float rs = pow(x, 2) + pow(y, 2);
  float gamma = atan(y / x);
  Serial.println(gamma);
  float r = sqrt(rs);
  Serial.println(r);
  float sa1 = acos((l2s - l1s - rs) / (-2 * l1 * r));
  Serial.println(sa1);
  float sa2 = acos((rs - l1s - l2s) / (-2 * l1 * l2));
  Serial.println(sa2);
  a1 = (sa1 + gamma) * RAD_TO_DEG;
  a2 = sa2 * RAD_TO_DEG;
}

void set(float a1, float a2) {
  myservo.write(180-a1);                // sets the servo position according to the scaled value
  myservo2.write(180-a2);                  // sets the servo position according to the scaled value
}

void moveTo(float offsetx, float xf, float yf, float x, float y) {
  float a1, a2;
  convertToAngle(offsetx + (x * xf), y * yf, a1, a2);
  set(a1, a2);
}

void plotSegment(float offsetx, float xf, float yf, float x1, float y1, float x2, float y2) {
  float deltax = x2 - x1;
  float deltay = y2 - y1;
  deltax = deltax / 100;
  deltay = deltay / 100;
  for (int i = 0; i < 100; i++) {
    float nx = x1 + (deltax * i);
    float ny = y1 + (deltay * i);
    moveTo(offsetx, xf, yf, nx, ny);
  }
}

  float gx = 0;
  float gy = 0;
void loop()
{
  if (Serial.available())  //Constantly checks to see if anything has been sent over the USB Connection and if it needs to be processed

  {
    char val = Serial.read(); //Reads a single letter
    if (val == '1') {
        gx = Serial.parseFloat();
    }
    if (val == '2') {
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
  }
}
