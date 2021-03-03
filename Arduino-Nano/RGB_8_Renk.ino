// D1, D2, D3 Kismi calismazsa 1, 2, 3 ile degistirin
const int kirmizi = D1;
const int yesil = D2;
const int mavi = D3;


void setup() {
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT); 
  pinMode(mavi, OUTPUT); 
}

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
                                   
