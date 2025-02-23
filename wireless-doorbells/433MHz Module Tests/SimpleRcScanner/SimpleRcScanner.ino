// https://github.com/sui77/SimpleRcScanner/tree/master

#define SAMPLESIZE 500

static unsigned int timings[SAMPLESIZE];
static unsigned int pos = 0;
static unsigned long lastTime = 0;

static int receiverPin = 21;
static int interruptPin = 0;
static int led_pin = 25;

void setup() {
  interruptPin = digitalPinToInterrupt(receiverPin);
  Serial.begin(115200); 
  delay(5000);
  Serial.println("hello");
  attachInterrupt(interruptPin, handleInterrupt, CHANGE);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
    for (int i = 6; i>0; i--) {
      Serial.print(i);
      Serial.print("... ");
      delay(900);
      digitalWrite(led_pin, HIGH);
      delay(100);
      digitalWrite(led_pin, LOW);
    }
    Serial.println();
      
    detachInterrupt(interruptPin);
  
    int finalstate = digitalRead(receiverPin);
    
    char s = Serial.read();
    
    for (unsigned int i = pos + finalstate; i< SAMPLESIZE; i++) {
      Serial.print( timings[i] );
      Serial.print(",");
    }
 
    for (unsigned int i = 0; i < pos; i++) {
      Serial.print( timings[i] );
      Serial.print(",");
    }

    Serial.println("");
    Serial.println("Reset your Arduino to scan again...");

    while(true) {} 
  
}

void handleInterrupt() {
  const long time = micros();
  timings[pos] = time - lastTime;
  lastTime = time;
  if (++pos > SAMPLESIZE-1) {
    pos = 0;
  }
}