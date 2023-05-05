/* 
 * Credits to all sources on Google and Youtube, acting as reference to this code below. This code is not 
 * TechValer's own creation. TechValer has referred to different projects and websites to 
 * find an easy code for beginners to get started with PIR sensor and Arduino.
 * TechValer does not claim this code to be its own. TechValer is greatly thankful for original 
 * creaters of this code and also all others who acted as reference. 
 */

/* 
 *  About TechValer
 *  
 *  What comes to mind when you think of tech...hmm, were sure youre thinking of iPhone, 
 *  Alexa, Boston Dynamics robotic dog etc., at least thats what we would have thought of. 
 *  Our point here is, when you look inside this tech...youll find weird boards with 
 *  components attached to it. This stuff is electronics and we at Techvaler deeply appreciate 
 *  this piece of tech. As the name suggests, we are Tech Enthusiasts who know the Worth and 
 *  Potential of these amazing tech stuff! So, check out our website techvaler.com and 
 *  Youtube Channel: Techcafe to find out more.
 */

/*
 * Thanks to Drona Automations Pvt.Ltd for Sponsoring this project!
 */

int Buzz= 8; // Define Bizzer pin
int LED= 9; // Define LED pin
int PIR= 13; // Define PIR pin
int val= 0; // Initializing the value as zero at the beginning
  
void setup() {
  
pinMode(Buzz, OUTPUT);
pinMode(LED, OUTPUT);
pinMode(PIR, INPUT);
Serial.begin(9600);
}

void loop() {

val = digitalRead(PIR); // The value read from PIR pin 3 will be assigned to 'val'
if(val == HIGH){
  digitalWrite(LED, HIGH); // Turn LED ON
  digitalWrite(Buzz, HIGH); // Turn Buzzer ON  
  Serial.println("Movement Detected"); // Print this text in Serial Monitor
}
else 
{
  digitalWrite(LED, LOW);
  digitalWrite(Buzz, LOW);
  Serial.println("Movement not Detected");
}
}