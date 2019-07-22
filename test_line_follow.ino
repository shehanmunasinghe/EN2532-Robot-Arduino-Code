void test_line_follow(){
	get_IR_readings();get_IR_binary_array();
	print_IR_binary_array();

	temp_ir_condition = checkIRSpecialCondition();

	switch (temp_ir_condition)
	{
		// case IR_ALL_BLACK:
		//   motors_brake();
		//   break;
		case IR_90_LEFT:
			motors_DriveGivenDistance(13);
			motors_Turn_90_Left(); /*turn left */
			break;

		case IR_90_RIGHT:
			motors_DriveGivenDistance(13);/*go fwd 13cm */
			motors_Turn_90_Right();  /*turn right */
			break;

		case IR_COIN_BOX:
		    motors_brake();
      		delay(5000);
			//Coin Collect
			//
			robot_state = STATE_DETECTED_COIN_BOX_1;
			break;

		default:
			pid_line_follow_step();
			break;
	}
}
