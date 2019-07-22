void init_TOFs(){

    //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
    pinMode(TOF1_XSHUT, OUTPUT);
    pinMode(TOF2_XSHUT, OUTPUT);
    pinMode(TOF3_XSHUT, OUTPUT);
    pinMode(TOF4_XSHUT, OUTPUT);
    pinMode(TOF5_XSHUT, OUTPUT);

    Wire.begin();

    Serial2.println("Initializing TOFs");

    Serial2.println("Setting Addresses");
    //Setting Addresses
    pinMode(TOF1_XSHUT, INPUT);delay(20);
    TOF_sensor_1.init();delay(10);
    Serial2.print("Sensor 1 ok");
    TOF_sensor_1.setAddress(TOF1_ADDR);delay(100);

    pinMode(TOF2_XSHUT, INPUT);delay(20);
    TOF_sensor_2.init();delay(10);
    Serial2.print("Sensor 2 ok");
    TOF_sensor_2.setAddress(TOF2_ADDR);delay(100);

    pinMode(TOF3_XSHUT, INPUT);delay(20);
    TOF_sensor_3.init();delay(10);
    Serial2.print("Sensor 3 ok");
    TOF_sensor_3.setAddress(TOF3_ADDR);delay(100);

    pinMode(TOF4_XSHUT, INPUT);delay(20);
    TOF_sensor_4.init();delay(10);
    Serial2.print("Sensor 4 ok");
    TOF_sensor_4.setAddress(TOF4_ADDR);delay(100);

    pinMode(TOF5_XSHUT, INPUT);delay(100);
    TOF_sensor_5.init();delay(10);
    Serial2.print("Sensor 5 ok"); 
    TOF_sensor_5.setAddress(TOF5_ADDR);delay(100);

    delay(100);


    //Setting Timeouts for sensors
    TOF_sensor_1.setTimeout(500);
    TOF_sensor_2.setTimeout(500);
    TOF_sensor_3.setTimeout(500);
    TOF_sensor_4.setTimeout(500);
    TOF_sensor_5.setTimeout(500);

    Serial2.println("TOFs  - startContinuous");
    //Start taking measurements continuously
    TOF_sensor_1.startContinuous();
    TOF_sensor_2.startContinuous();
    TOF_sensor_3.startContinuous();
    TOF_sensor_4.startContinuous();
    TOF_sensor_5.startContinuous();
  
}




void get_ToF_Measurements(){
    tof_right_1=TOF_sensor_1.readRangeContinuousMillimeters();
    tof_right_2=TOF_sensor_2.readRangeContinuousMillimeters() -15; // Offset Correction for rear sensors
    tof_left_2=TOF_sensor_3.readRangeContinuousMillimeters() -20; // Offset Correction for rear sensors
    tof_left_1=TOF_sensor_4.readRangeContinuousMillimeters();
    tof_front=TOF_sensor_5.readRangeContinuousMillimeters();


}