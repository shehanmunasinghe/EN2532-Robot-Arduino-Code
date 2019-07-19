void comm_handler(){

    comm_bridge.updateBuffer();


    //Motor_PWM_Upper_Limit = 100;

    // WRITE various values into the data structure.
    // comm_bridge.buffer.buttonA = 0;
    // comm_bridge.buffer.buttonB = 0;
    // comm_bridge.buffer.buttonC = 0;
    // comm_bridge.buffer.batteryMillivolts = (uint16_t) 0;

    get_IR_readings(); get_IR_binary_array();

    uint16_t encoded_IR_values = encode_IR_values();
    comm_bridge.buffer.encoded_ADC_readings = encoded_IR_values;

    //comm_bridge.buffer.check_IMU_status_flag = check_IMU_status_flag;

    //Serial2.println(encoded_IR_values);

    // READING the buffer is allowed before or after finalizeWrites().
    // int ledYellow=(comm_bridge.buffer.yellow);
    // int ledGreen=(comm_bridge.buffer.green);
    // int ledRed=comm_bridge.buffer.red;
    // int leftMotor=comm_bridge.buffer.leftMotor;
    // int rightMotor=comm_bridge.buffer.rightMotor;

    tof_right_2 = comm_bridge.buffer.tof_right_2;
    tof_right_1 = comm_bridge.buffer.tof_right_1;
    tof_front = comm_bridge.buffer.tof_front;
    tof_left_1 = comm_bridge.buffer.tof_left_1;
    tof_left_2 = comm_bridge.buffer.tof_left_2;

    Serial2.print("tof_right_2: ");Serial2.print(tof_right_2);Serial2.print("\t");
    Serial2.print("tof_right_1: ");Serial2.print(tof_right_1);Serial2.print("\t");
    Serial2.print("tof_front: ");Serial2.print(tof_front);Serial2.print("\t");
    Serial2.print("tof_left_1: ");Serial2.print(tof_left_1);Serial2.print("\t");
    Serial2.print("tof_left_2: ");Serial2.print(tof_left_2);Serial2.print("\t");
    Serial2.println("");


    IMU_status=comm_bridge.buffer.IMU_status;

    

    // comm_bridge.buffer.leftEncoder = (int16_t) 0;
    // comm_bridge.buffer.rightEncoder = (int16_t) 0;

    // Serial2.print("IMU_status : ");
    // Serial2.print(IMU_status);
    // Serial2.println("");



    // When you are done WRITING, call finalizeWrites() to make modified data available to I2C master.
    comm_bridge.finalizeWrites();
}

void comm_handler_get_tofs(){

    comm_bridge.updateBuffer();



    // get_IR_readings(); get_IR_binary_array();
    // uint16_t encoded_IR_values = encode_IR_values();
    // comm_bridge.buffer.encoded_ADC_readings = encoded_IR_values;


    tof_right_2 = comm_bridge.buffer.tof_right_2;
    tof_right_1 = comm_bridge.buffer.tof_right_1;
    tof_front = comm_bridge.buffer.tof_front;
    tof_left_1 = comm_bridge.buffer.tof_left_1;
    tof_left_2 = comm_bridge.buffer.tof_left_2;

    Serial2.print("tof_right_2: ");Serial2.print(tof_right_2);Serial2.print("\t");
    Serial2.print("tof_right_1: ");Serial2.print(tof_right_1);Serial2.print("\t");
    Serial2.print("tof_front: ");Serial2.print(tof_front);Serial2.print("\t");
    Serial2.print("tof_left_1: ");Serial2.print(tof_left_1);Serial2.print("\t");
    Serial2.print("tof_left_2: ");Serial2.print(tof_left_2);Serial2.print("\t");
    Serial2.println("");


    //IMU_status=comm_bridge.buffer.IMU_status;

    




    // When you are done WRITING, call finalizeWrites() to make modified data available to I2C master.
    comm_bridge.finalizeWrites();
}
