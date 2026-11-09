const byte pb = 2;//INPUT_PULLUP
const byte red = 4;//OUTPUT
const byte blue = 6;//OUTPUT
const byte green = 5;//OUTPUT
const byte buzz = 7;//OUTPUT
const byte trig = 9;//OUTPUT
const byte echo = 10;//INPUT

//Hz to music Notes
const float c = 65.4;
const float d = 73.4;
const float e = 82.4;
const float f = 87.3;
const float g = 98;
const float a = 110;
const float b = 123.5;
const float hc = 130.8;

float currTemp;
float duration, distance;
volatile bool Stop = false;

void setup()
{

  //Set pinmodes for pins above
  pinMode(pb, INPUT_PULLUP);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buzz , OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  //Create Interrupt
  attachInterrupt(digitalPinToInterrupt(pb),pb_isr, FALLING);
  
  Serial.begin(9600);
}

void loop()
{  
  //Call Buzzing Function
  buzzing();
}

//Interrupt
void pb_isr(){
  Stop = !Stop;
}

//Buzzing Function
void buzzing(){
  //Set number of notes for tune
  uint8_t numNotes = 14;
  //Create Tune
  char notes[numNotes] = {c,c,g,g,a,a,g,f,f,e,e,d,d,c};
  
  for(int i = 0; i<numNotes;i++){
    //Measure Duration
    digitalWrite(trig, LOW);
    delay(2);
    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
    
    //calculate Distance
    duration = pulseIn(echo, HIGH);
    distance = (duration * 0.0343)/2;
    Serial.println(distance);
    
    
    //If Statement(if distance is higher than 30, dont buzz and make LED red)
    if(distance > 30){
    	noTone(buzz);
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);
      
    	break;
      return;
    }
    //Else if stop is true, dont buzz and make LED Blue
    else if(Stop == true){
    	noTone(buzz);
      digitalWrite(green, LOW);
      digitalWrite(red, LOW);
      digitalWrite(blue, HIGH);
      
    	break;
      return;
    }
    //otherwise (No else) make LED Green and buzz using the notes.
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    tone(buzz, notes[i]);
    delay(450);
  }
}
