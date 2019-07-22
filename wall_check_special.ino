int checkMazeSpecialCondition(){
/*     
    #define WALL_FOLLOW_BOTH              1
    #define WALL_DEAD_END                 2
    #define WALL_LEFT_FREE                3
    #define WALL_LEFT_BLOCKED_FRONT_FREE  4
    #define WALL_ONLY_RIGHT_FREE          5 

*/
    if(tof_left_1 ==0 && tof_right_1 ==0 and tof_front ==0){
        Serial2.println("WALL_TOF_NOT_INITIALIZED");
        return WALL_TOF_NOT_INITIALIZED;
    }else if(tof_left_1 < 200 && tof_right_1 < 200 and tof_front > 360){
        Serial2.println("WALL_FOLLOW_BOTH");
        return WALL_FOLLOW_BOTH;
    }
    else if(tof_left_1 > 200){
        Serial2.println("WALL_LEFT_FREE");
        return WALL_LEFT_FREE;
    }
    else if(tof_front > 440){
        Serial2.println("WALL_LEFT_BLOCKED_FRONT_FREE");
        return WALL_LEFT_BLOCKED_FRONT_FREE;
    }
    else if(tof_right_1 > 200){
        Serial2.println("WALL_ONLY_RIGHT_FREE");
        return WALL_ONLY_RIGHT_FREE;
    }
    else if (tof_left_1 < 200 && tof_right_1 < 200 and tof_front < 100){
        Serial2.println("WALL_DEAD_END");
        return WALL_DEAD_END;
    } else
    {
        Serial2.println("WALL_UNKNOWN_CONDITION");
        return WALL_UNKNOWN_CONDITION;
    }
    
}


