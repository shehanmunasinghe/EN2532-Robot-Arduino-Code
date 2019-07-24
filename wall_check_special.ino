int checkMazeSpecialCondition(){
/*     
    #define WALL_FOLLOW_BOTH              1
    #define WALL_DEAD_END                 2
    #define WALL_LEFT_FREE                3
    #define WALL_LEFT_BLOCKED_FRONT_FREE  4
    #define WALL_ONLY_RIGHT_FREE          5 

*/
    if(tof_left_1 ==0 && tof_right_1 ==0 && tof_front ==0){
        Serial2.println("WALL_TOF_NOT_INITIALIZED");
        return WALL_TOF_NOT_INITIALIZED;
    }else if(tof_left_1 < 200 && tof_right_1 < 200 && tof_front > 150){
        Serial2.println("WALL_FOLLOW_BOTH");
        return WALL_FOLLOW_BOTH;
    }
    else if(tof_left_1 > 200){
        Serial2.println("WALL_LEFT_FREE");
        if (tof_left_2<=200){
            motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2); 
        }
        else{
            return WALL_LEFT_FREE;
        }
        
    }
    else if(tof_front > 440){
        Serial2.println("WALL_LEFT_BLOCKED_FRONT_FREE");
        return WALL_LEFT_BLOCKED_FRONT_FREE;
    }
    else if(tof_right_1 > 200){
        Serial2.println("WALL_ONLY_RIGHT_FREE");
        return WALL_ONLY_RIGHT_FREE;
    }
    else if (tof_left_1 < 200 && tof_right_1 < 200 && tof_front < 150){
        Serial2.println("WALL_DEAD_END");
        return WALL_DEAD_END;
    } else
    {
        Serial2.println("WALL_UNKNOWN_CONDITION");
        return WALL_UNKNOWN_CONDITION; 
    }
    
}

int test_wallfollow2(){
    get_ToF_Measurements();print_tof_readings();
    if (tof_left_1<200){
        if (tof_front>120){pid_wall_follow_left_step();}
        else{motors_Turn_90_Right();}
    }
    else{
        while(1){
        if (tof_left_2<120){
            
            motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2); 
        }
        else{
            motors_DriveGivenDistance(4);
            delay(1000);
            motors_Turn_90_Left();
			delay(1000); 
            break;
        }
        }
    }



}


