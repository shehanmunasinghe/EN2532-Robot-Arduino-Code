void clear_wall_follow_pid_variables(){
    Serial2.println("Clearing PID variables for wall_follow");
    wf_prev_error=0;
    wf_error=0;
    wf_diff_speed=0;
    wf_right_speed=0;wf_left_speed=0;

}
 



void pid_wall_follow_both_step(){    

    //PID
    wf_error= tof_left_1 - tof_right_1 ;    // wf_error as signed integer   //Serial2.println(wf_error);
    if(wf_error>-5 && wf_error <+5){
        wf_error=0;
    }
    wf_cum_error+=wf_error;
    wf_diff_speed= wf_Kp*wf_error + wf_Kd*(wf_error-wf_prev_error) + wf_Ki * wf_cum_error;      //Serial2.print("=>"); //Serial2.println(wf_diff_speed);
    
    wf_prev_error = wf_error;

    // wf_right_speed= wf_base_speed+wf_diff_speed;wf_left_speed= wf_base_speed-wf_diff_speed;

    if (wf_diff_speed>0){
        wf_left_speed= wf_base_speed-wf_diff_speed;
        wf_right_speed=wf_base_speed;
    }else
    {
        wf_left_speed=wf_base_speed;
        wf_right_speed= wf_base_speed+wf_diff_speed;
    }

    motors_DriveForward( wf_left_speed, wf_right_speed);

    //debug_Wall_Follow(tof_left_1, tof_left_2 ,tof_front,wf_error,wf_left_speed,wf_right_speed);



}

void pid_wall_follow_right_step(){    

    //PID
    wf_error= tof_right_2 - tof_right_1 ;    // wf_error as signed integer   //Serial2.println(wf_error);
    if(wf_error>-5 && wf_error <+5){
        wf_error=0;
    }
    wf_cum_error+=wf_error;
    wf_diff_speed= wfR_Kp*wf_error + wfR_Kd*(wf_error-wf_prev_error) + wfR_Ki * wf_cum_error;      //Serial2.print("=>"); //Serial2.println(wf_diff_speed);
    
    wf_prev_error = wf_error;

    // wf_right_speed= wf_base_speed+wf_diff_speed;wf_left_speed= wf_base_speed-wf_diff_speed;

    if (wf_diff_speed>0){
        wf_left_speed= wf_base_speed-wf_diff_speed;
        wf_right_speed=wf_base_speed;
    }else
    {
        wf_left_speed=wf_base_speed;
        wf_right_speed= wf_base_speed+wf_diff_speed;
    }

    motors_DriveForward( wf_left_speed, wf_right_speed);

    debug_Wall_Follow(tof_right_1, tof_right_2 ,tof_front,wf_error,wf_left_speed,wf_right_speed);

}

void pid_wall_follow_left_step(){    
    
    //PID
    wf_error= tof_left_1 - tof_left_2 ;    // wf_error as signed integer   //Serial2.println(wf_error);
    if(wf_error>-5 && wf_error <+5){
        wf_error=0;
    }
    wf_cum_error+=wf_error;
    wf_diff_speed= wfL_Kp*wf_error + wfL_Kd*(wf_error-wf_prev_error) + wfL_Ki * wf_cum_error;      //Serial2.print("=>"); //Serial2.println(wf_diff_speed);
    
    wf_prev_error = wf_error;

    // wf_right_speed= wf_base_speed+wf_diff_speed;wf_left_speed= wf_base_speed-wf_diff_speed;

    if (wf_diff_speed>0){
        wf_left_speed= wf_base_speed-wf_diff_speed;
        wf_right_speed=wf_base_speed;
    }else
    {
        wf_left_speed=wf_base_speed;
        wf_right_speed= wf_base_speed+wf_diff_speed;
    }

    motors_DriveForward( wf_left_speed, wf_right_speed);

    debug_Wall_Follow(tof_left_1, tof_left_2 ,tof_front,wf_error,wf_left_speed,wf_right_speed);

}
 

 void wall_align_left(int timeout){

    unsigned long start_time=millis();

    while (true){
        get_ToF_Measurements();
        wf_error = tof_left_1 - tof_left_2;

        if(wf_error>-5 && wf_error <+5){
            break;
        }

        wf_diff_speed= 10*wf_error + 1*(wf_error-wf_prev_error);
        wf_prev_error=wf_error;


        motorL_Drive(-wf_diff_speed,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);
        motorR_Drive(+wf_diff_speed,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);


        Serial2.print("tof_left_1: ");Serial2.print(tof_left_1);Serial2.print(",  ");Serial2.print("tof_left_2: ");Serial2.print(tof_left_2);Serial2.print(",  ");
        Serial2.print("wf_error:  ");Serial2.print(wf_error); Serial2.print(",  ");


        unsigned long current_time=millis();
        if((current_time-start_time)>timeout){
            Serial2.println("Timeout");
            //motorL_Drive(0,Motor_PWM_Upper_Limit);
            motors_brake();
            return; 
        }

    }

  return;
 }