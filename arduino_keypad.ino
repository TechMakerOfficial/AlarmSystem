
#include <Password.h> //http://playground.arduino.cc/uploads/Code/Password.zip //tells to use password library
#include <Keypad.h> //http://www.arduino.cc/playground/uploads/Code/Keypad.zip  //tells to use keypad library

Password password = Password( "234" ); //password to unlock, can be changed

const byte ROWS = 4; // Four rows
const byte COLS = 4; // columns
// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int sensor = 0;
int active=0;
void setup(){
  Serial.begin(9600);
  delay(3000); 
  pinMode(11, INPUT);  //green light
  pinMode(12, OUTPUT);  //red light  
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  
  
  }

void loop(){
 sensor = digitalRead(11);
if( sensor == HIGH&& active==1){

digitalWrite(12, HIGH);  
}
  keypad.getKey();
  }
  //take care of some special events
  void keypadEvent(KeypadEvent eKey){
  switch (keypad.getState()){
  case PRESSED:
  
  Serial.print("Enter:");
  Serial.println(eKey);
  delay(10);
  
  Serial.write(254);
  
  switch (eKey){
    case '*': checkPassword(); delay(1); break;
    
    case '1': password.reset(); delay(1); break;

    case '#': 
    password.reset();
    if(active == 0){
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(12, LOW);
    delay(50);
    digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(12, LOW);
    delay(5000);
        digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(50);
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    
    active=1; 
  }
     default: password.append(eKey); delay(1);
}
}
}
void checkPassword(){
  
if (password.evaluate()){  //if password is right 
  digitalWrite(12, HIGH);
    delay(50);
    digitalWrite(12, LOW);
    Serial.println("Accepted");
    
active=0;
digitalWrite(12, LOW);//turn off the alarm
delay(5000);

    
    
}
else{
    


    
}
}

