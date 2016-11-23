/*Single button digital combination lock code
Written By Chris Bean, 11/22/2016
*/
int button = 6;
boolean unlock = 0;
byte butPress = 0; //counter for button presses

long butTimer = 0; //long press button timer
long longPressTime = 1000; //set button hold time to 1 second

unsigned long prev, interval = 1000; //set reset time

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(6, INPUT_PULLUP);
  digitalWrite(8, LOW); //My button gets it low signal from pin 8, you do not need this line
}

void loop() {
  unsigned long now = millis();
  if (unlock == 1) { //bit to actuate lock (if lock "switch" is "flipped on")
    Serial.println("command unlockSol"); //for debugging/serial monitor
    unlockSol(); //run unlock command
    unlock = 0; //flip unlock "switch" back off
    Serial.println(unlock); //for debugging/serial monitor
  }
  if (digitalRead(button) == LOW) { //if button is pressed
    delay(30); //debouce button (so that one press only increases button counter one time)
    butTimer = now; //set button timer start time
    prev = now; //set start time for counter reset timer
    butPress = butPress + 1; //increase button counter by 1
    Serial.println(butPress);//for debugging/serial monitor
    while (digitalRead(button) == LOW) {} //wait for button release to finish code
  }
  else if ((butPress == 4) && (now - butTimer > longPressTime)) { //if button is held longer than 1 second
    unlock = 1; //Set bit to call unlock function (flip lock "switch" on)
    Serial.println(unlock);//for debugging/serial monitor
  }
  if (now - prev > interval) { //calculate time since button was pressed
    butPress = 0; //Reset counter if button is not pressed for one second
  }
}

void unlockSol() { //code to actuate lock
  Serial.println("unlockSol");
  digitalWrite(3, HIGH); //Turn LED on
  delay(1000 * 2); //Set LED on-time
  digitalWrite(3, LOW);
}
