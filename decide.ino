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
	  delay(100);
      robot_state=STATE_LINE_1;
      break;
    //2
    case STATE_LINE_1:
    	Serial2.println("STATE_LINE_1");
    	// test_line_follow_1();
		while (true)
		{
			if(!test_line_follow_2()){
				robot_state = STATE_LINE_1B;
				break;
			}
		}
    	break;
    case STATE_LINE_1B:
      Serial2.println("STATE_LINE_1B");
		test_line_follow_1();
    	break;	  
    //3
    case STATE_DETECTED_COIN_BOX_1:
		motors_brake();delay(1000);
		//Detect Coin Color
		detected_coin_color=COIN_COLOR_BLUE; //TODO : Write Function to get this from raspberry pi
		Serial2.println("STATE_DETECTED_COIN_BOX_1");
		coin_arm_pickup_position();
		delay(1000);
		motors_DriveGivenDistance(12);
		robot_state=STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_1;
    	break;
		
	case STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_1:
		Serial2.println("STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_1");
		// test_line_follow_2();
		while (true)
		{
			if(!test_line_follow_3()){
				robot_state = STATE_DETECTED_Y_JUNCTION;
				break;
			}
		}

		break;

	case STATE_DETECTED_Y_JUNCTION:
		Serial2.println("STATE_DETECTED_Y_JUNCTION");
		// motors_brake();delay(1000);	

		switch (detected_coin_color){
			case COIN_COLOR_GREEN:
				motors_DriveGivenDistance(13);	
				while (true)
				{
					if(!test_line_follow_3()){
						robot_state = STATE_DETECTED_COIN_BOX_2;
						break;
					}
				}
				break;
			case COIN_COLOR_RED:
				motors_DriveGivenDistance(13);	
				motors_Turn_45_Right();
				//TODO			
				break;
			case COIN_COLOR_BLUE:
				motors_DriveGivenDistance(13);	
				motors_Turn_45_Left();
				// motors_DriveGivenDistance(3);	
				while (true)
				{
					// get_IR_readings();get_IR_binary_array();
					// print_IR_binary_array();
					// pid_line_follow_step();
					if(!test_line_follow_3()){
						robot_state = STATE_DETECTED_COIN_BOX_2;
						break;
					}					
				}	
				break;					
			default:
				break;
		}
		break;

    case STATE_DETECTED_COIN_BOX_2:
		motors_brake();delay(2000);
		Serial2.println("STATE_DETECTED_COIN_BOX_2");
		coin_arm_rest_position();
		motors_DriveGivenDistance(12);
		motors_brake();delay(1000);


		robot_state=STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_2;
    	break;

	case STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_2:
		// motors_brake();
		Serial2.println("STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_2");

		while (true)
		{
			if(!test_line_follow_3()){
				motors_DriveGivenDistance(10);
				if(detected_coin_color==COIN_COLOR_BLUE){
					motors_Turn_45_Left();
				}else if (detected_coin_color==COIN_COLOR_BLUE)
				{
					motors_Turn_45_Right();
				}						
				robot_state = STATE_LINE_2;
				break;
			}
		}

		break;

	case STATE_LINE_2:
		Serial2.println("STATE_LINE_2");
		while (true)
		{
			get_ToF_Measurements_Only_Front();Serial2.print(tof_front);
			if(tof_front<210){
				robot_state=STATE_RAMP_AREA;
				break;
			}
			test_line_follow_2();
		}
		break;

	case STATE_RAMP_AREA:
		Serial2.println("STATE_RAMP_AREA");
		while (true){
			IMU_status=check_IMU_status();
			if(IMU_status==IMU_GOING_UP){
				Motor_PWM_Upper_Limit=130; lf_base_speed=130;
			}else if (IMU_status==IMU_GOING_DOWN)
			{
				Motor_PWM_Upper_Limit=0;lf_base_speed=0;
				get_ToF_Measurements_Only_Front();Serial2.print(tof_front);
				if(tof_front<210){
					robot_state=STATE_LINE_3;
					break;
				}
			}else
			{
				Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW; lf_base_speed=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
			}
			test_line_follow_2();

			//TODO: ADD - code to exit this state when tof_front is blocked
		}
		
		break;

	case STATE_LINE_3:
		motors_brake();
		
		break;

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

