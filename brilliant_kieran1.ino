// Henrique Sobral  Franzão

int pushbutton[] = {7, 6, 5, 4};
int led_pin[] = {12, 11, 10, 9};

int pushb_state = 0;
int turn = 0;

int sequenceArray[10];
int inputArray[10];

void setup()
{
 Serial.begin(9600);
  //defining leds and button pins
  for(int n = 0; n < 4; n++)
      {
        pinMode(led_pin[n], OUTPUT);
      }
  for(int x = 0; x < 4; x++)    
      {
        pinMode(pushbutton[x], INPUT);
        digitalWrite(pushbutton[x], LOW);
      }
  randomSeed(analogRead(0));
}

void loop()
{
  // flash all leds for each sequence
    digitalWrite(led_pin[0], HIGH);
    digitalWrite(led_pin[1], HIGH);
    digitalWrite(led_pin[2], HIGH);
    digitalWrite(led_pin[3], HIGH);
    delay(1000);
 
 	digitalWrite(led_pin[0], LOW);
    digitalWrite(led_pin[1], LOW);
    digitalWrite(led_pin[2], LOW);
    digitalWrite(led_pin[3], LOW);
    delay(600);
  
  //light leds in pseudo-random sequence
	
  sequenceArray[turn++] = (1,5); 
  for(int x =0; x < turn; x++)
  {
    Serial.print(sequenceArray[x]);
   //for each turn, generate a 'random' number (1 to 4)
	for(int y = 1; y <= turn; y++)
   //interate between each led pin and compare with 'random' number   
   {
    digitalWrite(led_pin[sequenceArray[y]], HIGH);
    delay(1000);
    digitalWrite(led_pin[sequenceArray[y]], LOW);
    delay(500);
     
    }
  }
  
 }

  