void clear_line_follow_pid_variables(){
    Serial2.println("Clearing PID variables for line_follow");
    lf_prev_error=0;
    lf_error=0;
    lf_diff_speed=0;
    lf_right_speed=0;lf_left_speed=0;
}
 

 
void pid_line_follow_step(){    

    //check_45();
    // get_IR_readings();

    //checkIRSpecialCondition();


    avg_ir_pos= get_IR_Position();//Serial2.println(avg_ir_pos);
    


    if(avg_ir_pos==-1){
        lf_error = lf_prev_error;
    }else{
        lf_error = avg_ir_pos - 8;    // lf_error as signed integer   //Serial2.println(lf_error);
    }
    
    lf_cum_error+=lf_error;
    lf_diff_speed= lf_Kp*lf_error + lf_Kd*(lf_error-lf_prev_error) + lf_Ki * lf_cum_error;  
    lf_prev_error = lf_error;
    
    if (lf_diff_speed>0){
        lf_left_speed= lf_base_speed-lf_diff_speed;
        lf_right_speed=lf_base_speed;
    }else
    {
        lf_left_speed=lf_base_speed;
        lf_right_speed= lf_base_speed+lf_diff_speed;
    }
    
   

    motors_DriveForward( lf_left_speed, lf_right_speed); 

    //Serial2.print(lf_right_speed);Serial2.print("<=>");Serial2.print(left_speed);
    //encodePrint();
    //debug_Line_Follow(avg_ir_pos,lf_error,lf_left_speed,lf_right_speed);

}