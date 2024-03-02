  // Henrique Sobral  Franzão

  int pushbutton[] = {7, 6, 5, 4};
  int led_pin[] = {12, 11, 10, 9};

  int pushb_state = 0;
  int sequence_length = 0;
  int randomArray[100];

  void setup(){
  //defining leds and button pins
  randomSeed(analogRead(0));
  for(int n = 0; n < 4; n++){
                    
  pinMode(led_pin[n], OUTPUT);
  }
  for(int x = 0; x < 4; x++){
                    
  pinMode(pushbutton[x], INPUT);
  digitalWrite(pushbutton[x], INPUT_PULLUP);
  } 
  }
  void generate_sequence(){
  for(int y = 0; y < sequence_length; y++)
  {
  digitalWrite(randomArray[y], HIGH);
  delay(1000);
  digitalWrite(randomArray[y], LOW);
  delay(500); 
  }
  randomArray[sequence_length] = led_pin[random(0,4)];
  sequence_length++;
  delay(100);
  }
/*
  void wait_input(){
  for(int i = 0; i < sequence_length; i++){
  input();
                    
  }
  }
*/
 int input(){  
  while(true){
  for (int x = 0; x < 4; x++) {
  pushb_state = digitalRead(randomArray[x]);                 
  if(pushb_state == LOW){
    return x; //return the pressed button pin
  }
  }
  delay(10);
 }
}

  bool game_over(){
  for(int i = 0; i < sequence_length; i++){
  if(pushb_state != randomArray[i]){
    return false;
    digitalWrite(12, HIGH);
    delay(300);
    digitalWrite(12, LOW);
    delay(100);
  }
  }
  return true;
  digitalWrite(10, HIGH);
  delay(300);
  digitalWrite(10, LOW);
  delay(100);
  }

  void loop()
  {

  generate_sequence();       
  input();         
  if(!game_over()){
    game_over();
    
  }
  delay(500);

  }//loop func            