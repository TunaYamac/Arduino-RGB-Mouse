const int kirmizi = D1;
const int yesil = D2;
const int mavi = D3;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT); 
  pinMode(mavi, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(kirmizi, HIGH);   
  delay(1000);                       
  digitalWrite(mavi, HIGH);    
  delay(1000);            
  digitalWrite(yesil, HIGH);   
  delay(1000);                       
  digitalWrite(kirmizi, LOW);    
  delay(1000);            
  digitalWrite(mavi, LOW);   
  delay(1000);
  digitalWrite(kirmizi, HIGH);
  delay(1000);                       
  digitalWrite(kirmizi, LOW); 
  delay(1000); 
  digitalWrite(yesil, LOW);
  }
                                   
