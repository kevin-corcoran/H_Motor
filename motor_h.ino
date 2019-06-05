class Motor {
public:
  Motor(int control_pin) {
    pin_ = control_pin;
    speed_ = 0;
    max_volt_ = 255;
    
    pin_1_ = 0;
    pin_2_ = 0;
  }

  Motor(int control1, int control2) {
    pin_1_ = control1;
    pin_2_ = control2;
    speed_ = 0;
    max_volt_ = 255;
    
    pin_ = pin_1_; // start in one direction
  }

  void setup() {
    Serial.begin(9600);
    pinMode(pin_, OUTPUT);
    if (pin_1_ != pin_2_) // if they aren't both 0
      pinMode(pin_2_, OUTPUT);
  }

  void loop() {
    int volt = speedToVolt(speed_);
    analogWrite(pin_, volt);
  }

  void toggleDirection() {
    int pin = pin_;
    if (pin_ == pin_1_) {
      pin_ = pin_2_;
      // change speed slowly
      setSpeed(speed_);
    } else {
      pin_ = pin_1_;
      // change speed slowly
      setSpeed(speed_);
    }
    analogWrite(pin, 0);
  }

  /* "Getter" returns speed */
  int getSpeed() {
    return speed_;
  }

  int getMaxVolt() {
    return max_volt_;
  }

  void setSpeed(int speed) {
    if (speed > speed_) {
      slowDown(speed);
    } else if (speed > speed_) {
      speedUp(speed);
    } // else do nothing
  }

  void setMaxVolt(int volt) {
    max_volt_ = volt;
  }

  void printValues() {
    Serial.print("pin_: ");
    Serial.println(pin_);
 
    Serial.print("pin_1_: ");
    Serial.println(pin_1_);
 
    Serial.print("pin_2_: ");
    Serial.println(pin_2_);
    
    Serial.print("speed_: ");
    Serial.println(speed_);
    
    Serial.print("max_volt_: ");
    Serial.println(max_volt_);
 }

private:
  int pin_;
  int speed_;
  int max_volt_; // 255 might be too fast. Should be determined experimentally.
  int pin_1_;
  int pin_2_;

  int speedToVolt(int speed) {
    return map(speed, 0, 9, 0, max_volt_);
  }

  void speedUp(int target_speed) {
    int volt = speedToVolt(speed_); // 0 - 255
    int target_volt = speedToVolt(target_speed);
    for (int v = volt; v < target_volt; v += 1) {
      analogWrite(pin_, v);
    }
    analogWrite(pin_, target_volt);

    speed_ = target_speed;
  }

  void slowDown(int target_speed) {
    int volt = speedToVolt(speed_); // 0 - 255
    int target_volt = speedToVolt(target_speed);
    for (int v = volt; v > target_volt; v -= 1) {
      analogWrite(pin_, v);
    }
    analogWrite(pin_, target_volt);

    speed_ = target_speed;
  }

  void stop() {
    slowDown(0);
  }
};
