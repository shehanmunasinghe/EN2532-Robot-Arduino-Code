void init_IMU(){
    Wire.begin();
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}

uint8_t check_IMU_status(){
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR,14,true);
    IMU_AcX=Wire.read()<<8|Wire.read();
    IMU_AcY=Wire.read()<<8|Wire.read();
    IMU_AcZ=Wire.read()<<8|Wire.read();
    int IMU_xAng = map(IMU_AcX,IMU_minVal,IMU_maxVal,-90,90);
    int IMU_yAng = map(IMU_AcY,IMU_minVal,IMU_maxVal,-90,90);
    int IMU_zAng = map(IMU_AcZ,IMU_minVal,IMU_maxVal,-90,90);

    IMU_x= RAD_TO_DEG * (atan2(-IMU_yAng, -IMU_zAng)+PI);
    IMU_y= RAD_TO_DEG * (atan2(-IMU_xAng, -IMU_zAng)+PI);
    IMU_z= RAD_TO_DEG * (atan2(-IMU_yAng, -IMU_xAng)+PI);

    // Serial.print("AngleX= ");
    // Serial.println(IMU_x);

    // Serial.print("AngleY= ");
    // Serial.println(IMU_y);

    // Serial.print("AngleZ= ");
    // Serial.println(IMU_z);

    // Serial2.println(IMU_y);
    IMU_y=medianFilter_IMU_y.AddValue(IMU_y);
    if (IMU_y<=75){
        Serial2.print("GOING_UP   ");Serial2.println(IMU_y);
        return IMU_GOING_UP;
    }
    else if (IMU_y>85){
        Serial2.print("GOING_DOWN   ");Serial2.println(IMU_y);
        // return GOING_LEVEL;
        return IMU_GOING_DOWN;
    }
    else{
        Serial2.print("GOING_LEVEL    ");Serial2.println(IMU_y);
        return IMU_GOING_LEVEL;
    }

 
}