  // Henrique Sobral  Franzão

  int pushbutton[] = {7, 6, 5, 4};
  int led_pin[] = {12, 11, 10, 9};
  int sequence_length = 0;
  int generated_sequence[100];

  unsigned long button_time_limit = 3000;
  unsigned long game_time = 0;

  bool game_running = true;
  
  void setup() {
    //defining leds and button pins
    Serial.begin(9600);
    randomSeed(analogRead(0));
    for (int n = 0; n < 4; n++) {
      pinMode(led_pin[n], OUTPUT);
      pinMode(pushbutton[n], INPUT_PULLUP);
    }
  }

  void generate_sequence() {
    
    for (int i = 0; i < sequence_length; i++) {
      digitalWrite(led_pin[generated_sequence[i]], HIGH);
      delay(500);
      digitalWrite(led_pin[generated_sequence[i]], LOW);
      delay(300);
      Serial.print(led_pin[generated_sequence[i]]);
    }
    //it can't put a led immediatly after the sequence
    /*generated_sequence[sequence_length] = led_pin[random(0,4)];
    sequence_length++;
    delay(100);
    */
  }
  /*
    void wait_input(){
    for(int i = 0; i < sequence_length; i++){
    input();
                      
    }
    }
  */
  int input() {
    game_time = millis();
    //read user inputs, aka, buttons pressed.
    while (true) {
      for (int i = 0; i < 4; i++) {
        int pushb_pin = digitalRead(pushbutton[i]);
        if (pushb_pin == LOW) {
          Serial.print(i);
          return i; //return the pressed button pin.

        }
      }
      delay(10);
    }

  }
  void light_leds(int led_pin_number) {
    digitalWrite(led_pin[led_pin_number], HIGH);
    delay(300);
    digitalWrite(led_pin[led_pin_number], LOW);
  }

  //void play_user_sequence(){}

  bool check_sequence() {
    if(millis() - game_time > button_time_limit){
    	game_over();
    }
    for (int i = 0; i < sequence_length; i++) {
      int game_sequence = generated_sequence[i];
      int pressed_button = input();
      light_leds(pressed_button);
      if (pressed_button != game_sequence) {
        return false;
      }
    }
    return true;
  }

  void game_over() {
    //flash the red LED, indicating that the user's input didn't match with the generated sequence.
    sequence_length = 0;
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
  }

  void loop() {
    if (game_running) {
      generated_sequence[sequence_length] = random(0, 4);
      sequence_length++;

      generate_sequence();
      input();
      if (!check_sequence()) {
        game_running = false;
        game_over();

      }
      delay(500);
    }
    delay(1000);
  } //loop func            
