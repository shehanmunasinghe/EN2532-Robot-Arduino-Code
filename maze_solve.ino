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
			// while (true)
			// { 
			// 	// comm_handler_get_tofs();
			// 	get_ToF_Measurements();
			// 	if(tof_left_2 >200){
			// 		Serial2.println("tof_left_2 >200");
			// 		motors_brake();
			// 		delay(1000);
			// 		break;
			// 	}       
			// 	// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2);       
			// 	motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);       
			// 	// pid_wall_follow_right_step();

			// }

			// motors_DriveGivenDistance(4); 
			// delay(100);
			// motors_Turn_90_Left();
			// delay(100);

			// motors_DriveGivenDistance(36); 
			// if(tof_front>410){
			// 	motors_DriveGivenDistance(36); 
			// }else
			// {
			// 	motors_DriveGivenDistance(tof_front/10 -2);
			// }

			//delay(2000);                   
			break;      
		case WALL_LEFT_BLOCKED_FRONT_FREE:
			// motors_brake();delay(1000);
			motors_DriveGivenDistance(5);
			// motors_DriveGivenDistance(40);
			motors_brake();delay(1000);
			clear_wall_follow_pid_variables();
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
			wall_align_left(2000);delay(1000);
			while (true)
			{ 
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
			wall_align_left(2000);delay(1000);
			motors_Turn_90_Right();
			wall_align_left(2000);delay(1000);
			// if(tof_front>410){
			// 	motors_DriveGivenDistance(36); 
			// }else
			// {
			// 	motors_DriveGivenDistance(tof_front/10 - 2);
			// }
			
			motors_DriveGivenDistance(10);

			delay(2000);                   
			break;          

		case WALL_FOLLOW_BOTH:
			//case WALL_FOLLOW_BOTH:
			pid_wall_follow_both_step();
			break;

		case WALL_DEAD_END:
			// motors_Turn_180();
			if(tof_right_1>tof_left_1){
				motors_Turn_90_Right();
				// get_ToF_Measurements();
				// motors_DriveGivenDistance(10-(tof_front/10));
				motors_Turn_90_Right();
			}else
			{
				motors_Turn_90_Left();
				// get_ToF_Measurements();
				// motors_DriveGivenDistance(10-(tof_front/10));
				motors_Turn_90_Left();				
			}
			
			delay(1000);
			break;

		default:
			Serial2.print("Unhandled Condition");
			Serial2.println(temp_wall_condition);
			motors_brake();
			delay(5000);
			break;

	}
}

bool test_wall_maze_2(){

	// get_IR_readings();get_IR_binary_array();
	// temp_ir_condition = checkIRSpecialCondition();

	// if(temp_ir_condition==IR_COIN_BOX | temp_ir_condition==IR_NORMAL_LINE){
	// 	print_IR_binary_array();
	// 	Serial2.println("End of Maze Detected");		
	// 	motors_brake();
	// 	return 0;
	// }

    get_ToF_Measurements();print_tof_readings();
	temp_wall_condition = checkMazeSpecialCondition_2();

	switch (temp_wall_condition){
		case WALL_LEFT_FREE:
			while(true){
				get_ToF_Measurements();
				if (tof_left_2<150){
					motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);             
					// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2); 
				}
				else{
					motors_DriveGivenDistance(3);
					motors_brake();
					delay(1000);
					motors_Turn_90_Left();
					//motors_brake();
					delay(1000); 
					motors_DriveGivenDistance(23);
					break;
				}
			}
			clear_wall_follow_pid_variables();
			break;
		case WALL_ONLY_RIGHT_FREE:
			while(true){
				get_ToF_Measurements();
				if (tof_right_2<150){
					motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);             
					// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2); 
				}
				else{
					motors_DriveGivenDistance(3);
					motors_brake();
					delay(1000);
					motors_Turn_90_Right();
					//motors_brake();
					delay(1000);
					wall_align_left(100);
					delay(100);
					motors_DriveGivenDistance(23);
					break;
				}
			}
			clear_wall_follow_pid_variables();
			break;

		case WALL_DEAD_END:
			// motors_Turn_180();
			if(tof_right_1>tof_left_1){
				motors_Turn_90_Right();
				// get_ToF_Measurements();
				// motors_DriveGivenDistance(10-(tof_front/10));

				delay(1000);
				//motors_brake();
				motors_Turn_90_Right();
				delay(1000);

			}else
			{
				motors_Turn_90_Left();
				// get_ToF_Measurements();
				// motors_DriveGivenDistance(10-(tof_front/10));
				delay(1000);
				//motors_brake();
				motors_Turn_90_Left();
				delay(1000);				
			}
			
			delay(1000);
			clear_wall_follow_pid_variables();
			wall_align_left(2000);
			break;
			
		default:
			pid_wall_follow_left_step_2();
			break;
	}

	return 1;

	// if(tof_left_1>200){ //LEFT
    //     while(true){
	// 		get_ToF_Measurements();
	// 		if (tof_left_2<150){
	// 			motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);             
	// 			// motors_DriveForward(MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW/2); 
	// 		}
	// 		else{
	// 			motors_DriveGivenDistance(4);
	// 			delay(1000);
	// 			motors_Turn_90_Left();
	// 			delay(1000); 
	// 			motors_DriveGivenDistance(20);
	// 			break;
	// 		}
    //     }
    // }else {
    //     if (tof_front>120){
	// 		pid_wall_follow_left_step_2();
	// 	}else{
	// 		motors_Turn_90_Right();
	// 	}
    // }



}

void wall_align_left(int timeout){
	Serial2.println("wall_align_left");

    unsigned long start_time=millis();

	get_ToF_Measurements();
	if(tof_left_1<tof_left_2){
		while (true)
		{
			get_ToF_Measurements();
			if(tof_left_1<tof_left_2){
				motorL_Drive(90,255);
				
				//motorR_brake();
			}else
			{
				motors_brake();
				Serial2.println("return");
				return;
			}

			unsigned long current_time=millis();
			if((current_time-start_time)>timeout){
				Serial2.println("Timeout");
				motors_brake();
				return; 
			}

		}
		
	}else{
		while (true)
		{
			get_ToF_Measurements();
			if(tof_left_1>tof_left_2){
				motorR_Drive(90,255);
				
				//motorL_brake();
			}else
			{
				motors_brake();
				Serial2.println("return");
				return;
			}

			unsigned long current_time=millis();
			if((current_time-start_time)>timeout){
				Serial2.println("Timeout");
				motors_brake();
				return; 
			}

		}		
	}
	
	
	// while (true)
	// {
	// 	get_ToF_Measurements();
	// 	if(tof_left_1<tof_left_2){
	// 		motorL_Drive(50,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);
	// 		motorR_brake();
	// 	}else if(tof_left_1>tof_left_2){
	// 		motorR_Drive(50,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);
	// 		motorL_brake();
	// 		// motors_brake();
	// 	}else
	// 	{
	// 		motors_brake();
	// 		Serial2.println("return");
	// 		return;
	// 	}
		
		// unsigned long current_time=millis();
        // if((current_time-start_time)>timeout){
        //     Serial2.println("Timeout");
        //     motors_brake();
        //     return; 
        // }
		
	// }

    // while (true){
    //     get_ToF_Measurements();
    //     wf_error = tof_left_1 - tof_left_2;

    //     if(wf_error>-3 && wf_error <+3){
	// 		motors_brake();
    //         break;
    //     }

    //     wf_diff_speed= 1*wf_error + 10*(wf_error-wf_prev_error);
    //     wf_prev_error=wf_error;


    //     // motorL_Drive(-wf_diff_speed,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);
    //     // motorR_Drive(+wf_diff_speed,MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW);
	// 	motorL_Drive(-wf_diff_speed,80);
    //     motorR_Drive(+wf_diff_speed,80);


    //     Serial2.print("tof_left_1: ");Serial2.print(tof_left_1);Serial2.print(",  ");Serial2.print("tof_left_2: ");Serial2.print(tof_left_2);Serial2.print(",  ");
    //     Serial2.print("wf_error:  ");Serial2.print(wf_error); Serial2.print(",  ");


    //     unsigned long current_time=millis();
    //     if((current_time-start_time)>timeout){
    //         Serial2.println("Timeout");
    //         motors_brake();
    //         return; 
    //     }

    // }

  return;
 }