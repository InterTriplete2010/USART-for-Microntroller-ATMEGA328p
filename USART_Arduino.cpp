void setup() 
{

  Serial.begin(9600); //initialize serial communication at a 9600 baud rate

}

void loop() {

 
  if (Serial.available() > 0) 
  {
  

     Serial.print("I received: ");

    Serial.println(Serial.read());

}

}
