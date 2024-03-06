  // Henrique Sobral  Franzão

  int pushbutton[] = {7, 6, 5, 4};
  int led_pin[] = {12, 11, 10, 9};
  int generated_sequence[100];

  int sequence_length = 0;
  int current_round = 0;
  int max_rounds = 7; //rounds to win

  bool game_running = true;
  
  void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    for (int n = 0; n < 4; n++) {
      pinMode(led_pin[n], OUTPUT);
      pinMode(pushbutton[n], INPUT_PULLUP);
    }
  }

  void generate_sequence(){
  //generate the sequence which the user has to match
    
    for (int i = 0; i < sequence_length; i++) {
      digitalWrite(led_pin[generated_sequence[i]], HIGH);
      delay(400);
      digitalWrite(led_pin[generated_sequence[i]], LOW);
      delay(400);
      Serial.print(led_pin[generated_sequence[i]]);
    }
  }
  int input() {
    //read user inputs, aka, buttons pressed.
    
    while (true) {
      for (int i = 0; i < 4; i++) {
        int pushb_pin = digitalRead(pushbutton[i]);
        if (pushb_pin == LOW) {
          Serial.print(i);
          return i; //return the pressed button pin.
        }
      }
    }
  }

  void light_leds(int led_pin_number) {
    //when pressed a button, light the corresponding led to that button
    
    digitalWrite(led_pin[led_pin_number], HIGH);
    delay(300);
    digitalWrite(led_pin[led_pin_number], LOW);
  }

  bool check_sequence() {
    //see if the input from the player is identical to the program generate sequence
    
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
    //light all leds if the player has the wrong input and resets the sequence
    
    sequence_length = 0;
    for(int i =0; i < 4; i++){
    digitalWrite(led_pin[i], HIGH);
    }
  }
  void won(){
    //if the player manages to win the game then all the leds will first light, from red to blue in sequence
    //after that, all leds will be turned on
    
    for (int i = 0; i < 4; i++) {
    digitalWrite(led_pin[i], HIGH);
    delay(200); // Delay to keep the LED on
    digitalWrite(led_pin[i], LOW);
    delay(50);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(led_pin[i], HIGH);
  }
}
  void loop() {
    //first checks if the game is running and if the current round is less than max number of rounds
    //after each iteration, a new led is placed at the end of the sequence
    //if the user has the wrong input or reached the maximum round, game_running is turned to false and the game stops needing to be reset
    
    if (game_running && current_round < max_rounds) {
      generated_sequence[sequence_length] = random(0, 4);
      sequence_length++;
      current_round++;
      generate_sequence();
      if (!check_sequence()) {
        game_running = false;
        game_over();
      }
      if(current_round == max_rounds){
        game_running = false;
        won();
      }
      delay(500);
    }
    delay(1000);
  }           
