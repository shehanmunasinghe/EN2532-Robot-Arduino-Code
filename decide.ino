void decide(){

  Serial2.print("robot_state ; "); Serial2.println(robot_state);

  switch (robot_state){
    //0
    case STATE_PAUSED:
      Serial2.println("STATE_PAUSED");
      motors_brake();

      while(1){
        Serial2.println("STATE_PAUSED");
        if(digitalRead(38)==0){
          Serial2.println("STATE_DEFAULT_START");
          robot_state = STATE_DEFAULT_START;
          delay(500);
          break;
        }
      }

      break;
    //1
    case STATE_INSIDE_START_BOX:
      Serial2.println("STATE_INSIDE_START_BOX");
      motors_DriveGivenDistance(10);
      robot_state=STATE_LINE_1;
      break;
    //2
    case STATE_LINE_1:
      Serial2.println("STATE_LINE_1");
      //print_IR_readings();
      temp_ir_condition = checkIRSpecialCondition();
      switch (temp_ir_condition)
      {
        // case IR_ALL_BLACK:
        //   motors_brake();
        //   break;
        case IR_90_LEFT:
          /* code */
          motors_DriveGivenDistance(13);
          motors_Turn_90_Left(); /*turn right */
          break;
        case IR_90_RIGHT:
          motors_DriveGivenDistance(13);/*go fwd 13cm */
          motors_Turn_90_Right();  /*turn right */
          break;
        case IR_COIN_BOX:
          //Coin Collect
          //
          motors_brake();
          robot_state = STATE_DETECTED_COIN_BOX_1;
          break;
        default:
          pid_line_follow_step();
          break;
      }
      
      //robot_state=?? To be updated in the PID loop
      print_IR_binary_array();
      break;
    //3
    case STATE_DETECTED_COIN_BOX_1:
      robot_state = STATE_PAUSED; //Change this line
      break;
    //9
    case STATE_LINE_2:
      Serial2.println("STATE_LINE_2");
      if(IMU_status==IMU_RAMP_AHEAD_OR_CLIMB){
        Motor_PWM_Upper_Limit=255;
      }else if(IMU_status==IMU_RAMP_DESCENT)
      {
        //Motor_PWM_Upper_Limit=0;
        motors_brake();
      }else
      {
        Motor_PWM_Upper_Limit=100;
      }
      pid_line_follow_step();
      break;

    case STATE_WALL_MAZE:
      Serial2.println("STATE_WALL_MAZE");

      //temp_ir_condition = checkIRSpecialCondition();
    //   if(temp_ir_condition==IR_NORMAL_LINE){
    //       robot_state=STATE_LINE_4;
    //       break;
    //   }

      temp_wall_condition = checkMazeSpecialCondition();
      switch (temp_wall_condition)
      {
        case WALL_TOF_NOT_INITIALIZED:
            motors_brake();
            delay(2000);
            break;
        case WALL_DEAD_END:
            motors_Turn_180();
            break;
        case WALL_LEFT_FREE:
            while (true)
            { 
              comm_handler_get_tofs();
              if(tof_left_2 >200){
                Serial2.println("tof_left_2 >200");
                break;
              }       
              motors_DriveForward(Motor_PWM_Upper_Limit,Motor_PWM_Upper_Limit);       
            }

            motors_DriveGivenDistance(5);
            motors_Turn_90_Left();
            motors_DriveGivenDistance(36); 
            
            // motors_DriveGivenDistance(18);
            // //delay(1000);
            // motors_Turn_90_Left();
            // //delay(1000);
            // motors_DriveGivenDistance(36); 
            delay(2000);                   
            break;      
        case WALL_LEFT_BLOCKED_FRONT_FREE:
            motors_DriveGivenDistance(40);
            delay(2000);
            break;
        case WALL_ONLY_RIGHT_FREE:
            motors_DriveGivenDistance(18);
            //delay(1000);
            motors_Turn_90_Right();
            //delay(1000);
            motors_DriveGivenDistance(36);    
            delay(2000);
            break;                
        default:
            //case WALL_FOLLOW_BOTH:
            pid_wall_follow_step();
            break;

      }

      break;

    // default:
    //   break;
  }

  //robot_state = robot_next_state;

}

