void decide(){

  Serial2.print("robot_state ; "); Serial2.println(robot_state);

  switch (robot_state){
    //0
    /*     case STATE_PAUSED:
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

      break; */
    //1
    case STATE_INSIDE_START_BOX:
      Serial2.println("STATE_INSIDE_START_BOX");
      motors_DriveGivenDistance(10);
      robot_state=STATE_LINE_1;
      break;
    //2
    case STATE_LINE_1:
      Serial2.println("STATE_LINE_1");
      test_line_follow(); //Inside this function, it will move to Coin Collect state  //robot_state=?? To be updated inside the line follow function
      break;
    //3
    case STATE_DETECTED_COIN_BOX_1:
      robot_state = STATE_PAUSED; //Change this line
      break;

    //9
    /*case STATE_LINE_2:
      Serial2.println("STATE_LINE_2");
      
      get_IR_readings();get_IR_binary_array();
      print_IR_binary_array();

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
      break; */

    /*     case STATE_WALL_MAZE:
      Serial2.println("STATE_WALL_MAZE");

      //temp_ir_condition = checkIRSpecialCondition();
      //   if(temp_ir_condition==IR_NORMAL_LINE){
      //       robot_state=STATE_LINE_4;
      //       break;
      //}

      temp_wall_condition = checkMazeSpecialCondition();
      switch (temp_wall_condition)
      {
        
      }

      break; */

    // default:
    //   break;
  }


}

