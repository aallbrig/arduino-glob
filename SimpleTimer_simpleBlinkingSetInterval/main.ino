    #include <SimpleTimer.h>
    #include <Servo.h> 

    #define ledPin1 6
    #define ledPin2 5
    #define ledPin3 7
    int pos = 0;
    // the timer object
    SimpleTimer timer;

    // a function to be executed periodically
    void repeatMe (int pin) {
      Serial.print("Uptime (s): ");
      Serial.println(millis() / 1000);
      digitalWrite(pin, !digitalRead(pin));
    }

    void setup() {
      // Generate function pointer to repeatMe
      Serial.begin(9600);
      timer.setInterval(1000, repeatMe, ledPin1));
      timer.setInterval(1200, repeatMe, ledPin2));
      timer.setInterval(1800, repeatMe, ledPin3));
      pinMode(ledPin1, OUTPUT);
      pinMode(ledPin2, OUTPUT);
      pinMode(ledPin3, OUTPUT);
    }

    void loop() {
      timer.run();
    }
