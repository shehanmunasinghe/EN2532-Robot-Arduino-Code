void init_Servos(){
    servo1.attach(Servo1_PWM);
    servo2.attach(Servo2_PWM);
    servo3.attach(Servo3_PWM);
    servo4.attach(Servo4_PWM);
    servo5.attach(Servo5_PWM);

    coin_arm_rest_position();
    water_arm_rest_position();
}

/*--------------------------------Servo Test Functions-----------------------------------------------*/

void test_servo_1(){
    int pos=0;
    while (true)
    {
        int pos=0;

        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
            for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            servo1.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        Serial2.println("OK");
    }
    
}

void test_servo_2(){
    int pos=0;
    while (true)
    {
        int pos=0;

        for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            servo2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
            for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            servo2.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15ms for the servo to reach the position
        }
        Serial2.println("OK");
    }
    
}

/*--------------------------------Servo High Level Functions-----------------------------------------------*/

void water_arm_rest_position(){
    servo1.write(0);
}

void water_arm_active_position(){
    servo1.write(150);
}

void coin_arm_rest_position(){
    servo2.write(30);
}

void coin_arm_pickup_position(){
    servo2.write(180);
}