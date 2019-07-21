void print_IR_readings(){
    START_DEBUG_MESSAGE(DEBUG_IR_ARRAY);
    for (int i=0; i<16 ; i=i+1){
        Serial2.print(irValue[i]);Serial2.print("  ");
    }
    Serial2.println("");
}
void print_IR_binary_array(){
    for (int i=0; i<16 ; i=i+1){
        Serial2.print(irBinaryValue[i]);Serial2.print("  ");
    }
    Serial2.println(" ");
}

void print_tof_readings(){
    // get_ToF_Measurements();

    Serial.print(tof_right_2);
    Serial.print(",  ");
    Serial.print(tof_right_1);
    Serial.print(",  ");
    Serial.print(tof_front);
    Serial.print(",  ");
    Serial.print(tof_left_1);
    Serial.print(",  ");
    Serial.print(tof_left_2);
    Serial.print(" \n  ");
    //delay(100);  
}

void debug_Wall_Follow(uint16_t tof_left1,uint16_t tof_left2,uint16_t tof_front, int error,int left_speed,int right_speed){

    Serial2.print("L1: ");Serial2.print(tof_left1);
    Serial2.print(",  ");
    Serial2.print("L2: ");Serial2.print(tof_left2);
    Serial2.print(",  ");
    Serial2.print("F: ");Serial2.print(tof_front);
    Serial2.print(",  ");
    Serial2.print("Error: ");Serial2.print(error);
    Serial2.print(",  ");
    Serial2.print("left: ");Serial2.print(left_speed);
    Serial2.print(",  ");
    Serial2.print("right: ");Serial2.print(right_speed);
    Serial2.print(" \n  ");
    
}

void debug_Line_Follow(int avg_ir_pos, int error,int left_speed,int right_speed){

    Serial2.print("avg_ir_pos: ");Serial2.print(avg_ir_pos);
    Serial2.print(",  ");
    Serial2.print("error: ");Serial2.print(error);
    Serial2.print(",  ");
    Serial2.print("left_speed: ");Serial2.print(left_speed);
    Serial2.print(",  ");
    Serial2.print("right_speed: ");Serial2.print(right_speed);
    Serial2.print(",  ");
    Serial2.print(" \n  ");
    
}

void debug_Encoder_Turn(int current_pos, int error,int motor_pwm){

    Serial2.print("current_pos: ");Serial2.print(current_pos);
    Serial2.print(",  ");
    Serial2.print("error: ");Serial2.print(error);
    Serial2.print(",  ");
    Serial2.print("motor_pwm: ");Serial2.print(motor_pwm);
    Serial2.print(",  ");
    Serial2.print(" \n  ");
    
}

/*--------------------------------Serial Print - Special Functions-----------------------------------------------*/

void START_DEBUG_MESSAGE(int messageType){
    Serial2.print("#");//Serial2.print(messageType);Serial2.print(" ");
    //sprintf(debug_buffer, "#%03d ",messageType);
    sprintf(debug_buffer, "%03d",messageType);
    Serial2.print (debug_buffer);
    Serial2.print(" ");
}
