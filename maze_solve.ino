void test_wall_maze(){
	get_ToF_Measurements();print_tof_readings();
	temp_wall_condition = checkMazeSpecialCondition();
	switch (temp_wall_condition){
		// case WALL_TOF_NOT_INITIALIZED:
		// 	motors_brake();
		// 	delay(2000);
		// 	break;
		// case WALL_DEAD_END:
		// 	motors_Turn_180();
		// 	break;
		case WALL_LEFT_FREE:
			while (true)
			{ 
				// comm_handler_get_tofs();
				get_ToF_Measurements();
				if(tof_left_2 >200){
					Serial2.println("tof_left_2 >200");
					motors_brake();
					delay(1000);
					break;
				}       
				// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2);       
				motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);       
				// pid_wall_follow_right_step();

			}

			// motors_DriveGivenDistance(5);
			delay(1000);
			motors_Turn_90_Left();
			delay(1000);
			motors_DriveGivenDistance(36); 

			delay(2000);                   
			break;      
		case WALL_LEFT_BLOCKED_FRONT_FREE:
			// motors_brake();delay(1000);
			motors_DriveGivenDistance(5);
			// motors_DriveGivenDistance(40);
			delay(1000);
			while (true)
			{ 
				// comm_handler_get_tofs();
				get_ToF_Measurements();
				if(tof_right_1 <200 && tof_right_2 <200){
					motors_brake();
					Serial2.println("tof_right_1 <200 && tof_right_2 <200");				
					delay(1000);
					break;
				}       
				// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2);       
				pid_wall_follow_left_step();

			}
			motors_brake();delay(2000);                   
			break;  

		case WALL_ONLY_RIGHT_FREE:
			while (true)
			{ 
				// comm_handler_get_tofs();
				get_ToF_Measurements();
				if(tof_right_2 >200){
					Serial2.println("tof_right_2 >200");
					motors_brake();
					delay(1000);
					break;
				}       
				//motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2);       
				motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);       
				// pid_wall_follow_left_step();

			}

			// motors_DriveGivenDistance(5);
			delay(1000);
			motors_Turn_90_Right();
			delay(1000);
			motors_DriveGivenDistance(36); 

			delay(2000);                   
			break;          

		case WALL_FOLLOW_BOTH:
			//case WALL_FOLLOW_BOTH:
			pid_wall_follow_both_step();
			break;

		default:
			Serial2.print("Unhandled Condition");
			Serial2.println(temp_wall_condition);
			break;

	}
}