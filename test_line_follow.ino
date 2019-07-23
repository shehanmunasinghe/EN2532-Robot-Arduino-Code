void test_line_follow_1(){
	get_IR_readings();get_IR_binary_array();
	print_IR_binary_array();

	temp_ir_condition = checkIRSpecialCondition();

	switch (temp_ir_condition)
	{
		// case IR_ALL_BLACK:
		//   motors_brake();
		//   break;
		case IR_90_LEFT:
			motors_DriveGivenDistance(11);
			motors_Turn_90_Left(); /*turn left */
			delay(100);

			break;

		case IR_90_RIGHT:
			motors_DriveGivenDistance(11);/*go fwd 11cm */
			motors_Turn_90_Right();  /*turn right */
			delay(100);
			break;

		case IR_COIN_BOX:
			//Move to Coin Collect state
			robot_state = STATE_DETECTED_COIN_BOX_1;
			break;

		default:
			pid_line_follow_step();
			break;
	}
}

// void test_line_follow_2(){
// 	get_IR_readings();get_IR_binary_array();
// 	print_IR_binary_array();

// 	temp_ir_condition = checkIRSpecialCondition();

// 	switch (temp_ir_condition)
// 	{
// 		// case IR_ALL_BLACK:
// 		// case IR_90_LEFT:
// 		// case IR_90_RIGHT:

// 		case IR_COIN_BOX:
// 			//Move to next state
// 			robot_state = STATE_DETECTED_Y_JUNCTION;
// 			break;

// 		default:
// 			pid_line_follow_step();
// 			break;
// 	}
// }

bool test_line_follow_3(){
	get_IR_readings();get_IR_binary_array();
	print_IR_binary_array();

	temp_ir_condition = checkIRSpecialConditionInsideCoinArea();

	if(temp_ir_condition==IR_COIN_BOX){
		motors_brake();
		return 0;
	}else
	{
		pid_line_follow_step();
		return 1;
	}

}

bool test_line_follow_4(){
	get_IR_readings();get_IR_binary_array();
	print_IR_binary_array();

	temp_ir_condition = checkIRSpecialCondition();

	switch (temp_ir_condition)
	{
		// case IR_ALL_BLACK:
		//   motors_brake();
		//   break;
		case IR_90_LEFT:
			motors_DriveGivenDistance(11);
			motors_Turn_90_Left(); /*turn left */
			delay(100);

			break;

		case IR_90_RIGHT:
			motors_DriveGivenDistance(11);/*go fwd 11cm */
			motors_Turn_90_Right();  /*turn right */
			delay(100);
			break;

		default:
			pid_line_follow_step();
			break;
	}

}