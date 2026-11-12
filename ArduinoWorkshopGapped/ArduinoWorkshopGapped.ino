const byte pb = 2;//INPUT_PULLUP
const byte red = 4;//OUTPUT
const byte blue = 6;//OUTPUT
const byte green = 5;//OUTPUT
const byte buzz = 8;//OUTPUT


//Hz to music Notes
const float c = 65.4;
const float d = 73.4;
const float e = 82.4;
const float f = 87.3;
const float g = 98;
const float a = 110;
const float b = 123.5;
const float hc = 130.8;

volatile bool Stop = false;
float bright = 0.0;

void setup()
{

  //Set pinmodes for pins above
  
  //Create Interrupt Falling
  
  Serial.begin(9600);
}

void loop() {
  //Check signal coming from LDR


  Serial.println(bright);
  Serial.println(Stop);
  //Call Buzzing or lighting function


  delay(500);
}

//Interrupt
void pb_isr(){
  Stop = !Stop;
}

//A function to turn on an LED when the LDR is dark
void lighting(){
  //If stop is true make RGB LED blue and dont light up LED
  if(Stop == true){
    //While loop to run when circuit is stopped making RGB LED blue and LED not light up
    while(Stop == true){
       digitalWrite(buzz, LOW);
       digitalWrite(green, LOW);
       digitalWrite(red, LOW);
       digitalWrite(blue, HIGH);
       Serial.println(Stop);
       if(Stop==false){
        break;
       }
       delay(450);
    }
  }
  //If LDR is bright make RGB LED red and light up LED
  if(bright > 600){

      digitalWrite(buzz, LOW);
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);

      return;
    }
    
    //otherwise (No else) make LED Green and LED bright.
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(buzz, HIGH);
    delay(450);
}

void buzzing(){
  //Set number of notes for tune
  uint8_t numNotes = 14;
  //Create Tune
  char notes[numNotes] = {c,c,g,g,a,a,g,f,f,e,e,d,d,c};
  //For loop running for the number of notes in the tune
  for(int i = 0; i<numNotes;i++){
    //If statement to check if circuit should be stopped
    if(Stop == true){
      //While loop to run when circuit is stopped making RGB LED blue and buzzer not buzz
      while(Stop == true){
        noTone(buzz);
        digitalWrite(green, LOW);
        digitalWrite(red, LOW);
        digitalWrite(blue, HIGH);
        Serial.println(Stop);
        //Check if circuit has been started again and leave the while loop
        if(Stop==false){
          break;
          return;
        }
        delay(450);
      }
    }
    //If statement to check brightness from LDR, if over a certain amount dont play tune and make RGB LED red
    if(bright > 600){
      noTone(buzz);
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);
      break;
      return;
    }
    //The default to make RGB LED green and play the tune
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone(buzz, notes[i]);
    delay(450);
  }
}
