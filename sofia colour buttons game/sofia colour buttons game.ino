#define ANIMATION_SPEED 200

int currButton = -1;

typedef struct
{
  int led;
  int button;
  bool state; // on/off
} led_button;

led_button led_buttons[] = {
  {8,  2, false}, // red
  {9,  3, false}, // blue
  {10, 4, false}, // green
  {11, 5, false}, // yellow
};

void randomCurrent() {
  currButton = random(4);
}

void init_game() {
  for(int i=0; i<(sizeof(led_buttons) / sizeof(led_buttons[0])); i++) {
    pinMode(led_buttons[i].led, OUTPUT);
    turn_off(&led_buttons[i]);
    pinMode(led_buttons[i].button, INPUT_PULLUP);
  }

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  randomCurrent();
}

void turn_on(led_button *lb) {
  if(lb->state) return;
  
  digitalWrite(lb->led, HIGH);
  lb->state = true;
}

void turn_off(led_button *lb) {
  if(!lb->state) return;
  
  digitalWrite(lb->led, LOW);
  lb->state = false;
}

void flash_leds() {
  for(int i=0; i<(sizeof(led_buttons) / sizeof(led_buttons[0])); i++) {
    turn_on(&led_buttons[i]);
    delay(ANIMATION_SPEED);
    turn_off(&led_buttons[i]);
    delay(ANIMATION_SPEED);
  }

  for(int i=(sizeof(led_buttons) / sizeof(led_buttons[0])) - 2; i>=0; i--) {
    turn_on(&led_buttons[i]);
    delay(ANIMATION_SPEED);
    turn_off(&led_buttons[i]);
    delay(ANIMATION_SPEED);
  }
}

void setup() {
  init_game();
  flash_leds();
}

void loop() {
  int button_val = digitalRead(led_buttons[currButton].button);

  if (button_val == LOW) {
    turn_off(&led_buttons[currButton]);
    randomCurrent();
    turn_on(&led_buttons[currButton]);
  } else {
    turn_on(&led_buttons[currButton]);
  }
}
