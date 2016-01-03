/**
 * 7-segment display
 *         a
 *      b     c
 *         d
 *      e     f
 *         g
 */

// Set your pin configuration here

#define A 7
#define B 2
#define C 8
#define D 5
#define E 4
#define F 6
#define G 3

#define BUTTON 12

// Change these numbers for different speeds
#define RANDOM_SPEED 50
#define RANDOM_DURATION 1000
#define ALICE_SPEED 700

void unreset() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void reset() {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

// c, f
void one() {
  reset();
  digitalWrite(C, HIGH);
  digitalWrite(F, HIGH);
}

// a, c, d, e, g
void two() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
}

// a, c, d, f, g
void three() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// b, c, d, f
void four() {
  reset();
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
}

// a, b, d, f, g
void five() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// a, b, d, e, f, g
void six() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// a, c, f
void seven() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(F, HIGH);
}

// a, b, c, d, e, f, g
void eight() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// a, b, c, d, f, g
void nine() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// a, b, c, e, f, g
void zero() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

// a, b, c, d, e, f
void letterA() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}

// b, e, g
void letterL() {
  reset();
  digitalWrite(B, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
}

// c, f
void letterI() {
  reset();
  digitalWrite(C, HIGH);
  digitalWrite(F, HIGH);
}

// a, b, e, g
void letterC() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
}

// a, b, d, e, g
void letterE() {
  reset();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);  
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
}

void displayN(int n) {
  switch(n) {
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      reset();
      break;
  }
}

void alice() {
  letterA();
  delay(ALICE_SPEED);
  letterL();
  delay(ALICE_SPEED);
  letterI();
  delay(ALICE_SPEED);
  letterC();
  delay(ALICE_SPEED);
  letterE();
  delay(ALICE_SPEED);
}

void displayRandom(int duration) {
  int repeats = duration / RANDOM_SPEED;
  for (int i = 0; i < repeats+1; i++) {
    displayN(random(10));
    delay(RANDOM_SPEED);
  }
}

void play() {
  displayRandom(RANDOM_DURATION);
  int randNumber = random(13);

  if (randNumber > 9) {
    alice();
    reset();
  } else {
    displayN(randNumber);
  }
}

void setup() {
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  if (button_down(BUTTON)) {
    play();
  }
}

int prev = -1;

boolean button_down(int buttonPin) {
  int now = digitalRead(buttonPin);
  boolean res = now != prev && prev == LOW;

  prev = now;
  // prevent debounce
  delay(30);
  return res;
}

