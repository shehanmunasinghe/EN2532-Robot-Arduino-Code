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
		detected_coin_color= COIN_COLOR_GREEN; //COIN_COLOR_BLUE; //TODO : Write Function to get this from raspberry pi
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
			Serial2.println("STATE_LINE_2");
			get_ToF_Measurements_Only_Front();Serial2.print(tof_front);
			if(tof_front<230){
				robot_state=STATE_RAMP_AREA;
				break;
			}
			test_line_follow_2();
		}
		break;

	case STATE_RAMP_AREA:
		Serial2.println("STATE_RAMP_AREA");
		lf_base_speed=130;
		while (true){
			Serial2.println("STATE_RAMP_AREA");
			IMU_status=check_IMU_status();
			if(IMU_status==IMU_GOING_UP){
				Motor_PWM_Upper_Limit=130; 
				lf_base_speed=130;
			}else if (IMU_status==IMU_GOING_DOWN)
			{
				Motor_PWM_Upper_Limit=0;
				lf_base_speed=0;//pid_line_follow_step();
				// delay(50);
				// motors_brake();

				// Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW; lf_base_speed=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
				// test_line_follow_2();
				// get_ToF_Measurements_Only_Front();Serial2.print(tof_front);
				// if(tof_front<210){
				// 	robot_state=STATE_LINE_3;
				// 	break;
				// }
			}else
			{
				Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW; 
				lf_base_speed=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
			}

			// test_line_follow_2();
			if(!test_line_follow_2()){
				Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW; 
				lf_base_speed=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
				robot_state = STATE_LINE_3;
				break;
			}

			//TODO: ADD - code to exit this state when tof_front is blocked
		}
		
		break;

	case STATE_LINE_3:
		Serial2.println("STATE_LINE_3");
		delay(1000);
		// motors_brake();
		while (true)
		{
			Serial2.println("STATE_LINE_3");
			if(!test_line_follow_5()){
				robot_state = STATE_WALL_MAZE;
				break;
			}
		}
		
		break;

	case STATE_WALL_MAZE:
		Serial2.println("STATE_WALL_MAZE");
		motors_brake();delay(2000);
		Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW;
		while (true)
		{
			Serial2.println("STATE_WALL_MAZE");
			if(!test_wall_maze_2()){
				robot_state = STATE_LINE_4;
				break;
			}			
		}
		
		break;

	case STATE_LINE_4:
		Serial2.println("STATE_LINE_4");
		motors_brake();delay(2000);
		Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
		while (true)
		{
			Serial2.println("STATE_LINE_3");
			if(!test_line_follow_2()){
				robot_state = STATE_WALL_MAZE;
				break;
			}
		}

	case STATE_WATER_PATH_1:
		Serial2.println("STATE_WATER_PATH_1");
		while (true)
		{
			Serial2.println("STATE_WATER_PATH_1");
			if(!test_line_follow_2()){
				robot_state = STATE_WATER_PATH_2;
				break;
			}
		}		
		break;
		
	case STATE_WATER_PATH_2:
		Serial2.println("STATE_WATER_PATH_2");
		while (true)
		{
			Serial2.println("STATE_WATER_PATH_2");
			if(!test_line_follow_5()){
				robot_state = STATE_DETECTED_WATER_TANK;
				break;
			}
		}		
		break;		

	case STATE_DETECTED_WATER_TANK:
		Serial2.println("STATE_DETECTED_WATER_TANK");
		motors_DriveGivenDistance(-3);
		motors_brake();delay(1000);
		water_arm_active_position();delay(2000);
		operate_pump();
		water_arm_mid_position();delay(2000);
		motors_Turn_180();
		robot_state=STATE_WATER_PATH_2_RETURN;
		break;

	case STATE_WATER_PATH_2_RETURN:
		Serial2.println("STATE_WATER_PATH_2_RETURN");
		while (true)
		{
			Serial2.println("STATE_WATER_PATH_2_RETURN");
			if(!test_line_follow_7()){
				robot_state = STATE_WATER_PATH_1_RETURN;
				break;
			}
		}		
		break;

	case STATE_WATER_PATH_1_RETURN:
		Serial2.println("STATE_WATER_PATH_1_RETURN");
		while (true)
		{
			Serial2.println("STATE_WATER_PATH_1_RETURN");
			if(!test_line_follow_7()){
				robot_state = STATE_LINE_5;
				break;
			}
		}		
		break;
	
	case STATE_LINE_5:
		Serial2.println("STATE_LINE_5");
		while (true)
		{
			Serial2.println("STATE_LINE_5");
			if(!test_line_follow_6()){
				robot_state = STATE_DETECTED_END_BOX;
				break;
			}
		}		
		break;

	case STATE_DETECTED_END_BOX:
		Serial2.println("STATE_DETECTED_END_BOX");
		motors_DriveGivenDistance(10);
		motors_brake();delay(20000);
		while (1)
		{
			//END
		}
		
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

