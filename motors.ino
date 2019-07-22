void init_motors(){
  pinMode(Motor1_INA, OUTPUT);
  pinMode(Motor1_INB, OUTPUT);
  pinMode(Motor1_PWM, OUTPUT);
  pinMode(Motor2_INA, OUTPUT);
  pinMode(Motor2_INB, OUTPUT);
  pinMode(Motor2_PWM, OUTPUT);
}

/*--------------------------------Encoder Feedback Turns-----------------------------------------------*/

void motorL_TurnRevolutions(int desired_revos){
  //Left Motor
  Serial2.println("motorL_TurnRevolutions");

  resetLeftEncoder();

  int current_pos=0;
  int prev_error=0; int error=0;
  int Kp=3,Kd=2;
  int motor_pwm;

  unsigned long start_time=millis();
  int timeout=abs(desired_revos)*3; //Assume a single revo takes ~1 millisecond. Timeout is 3 times that

  while (true)
  {
    current_pos=EncLeft.read();
    error= desired_revos-current_pos;
    motor_pwm= Kp*error + Kd*(error-prev_error); 
    prev_error = error;

    if(error<3 && error>-3){
      //Stop
      Serial2.println("EXIT");
      motorL_Drive(0,Motor_PWM_Upper_Limit);
      break;
    }

    motorL_Drive(motor_pwm,Motor_PWM_Upper_Limit);
    
    debug_Encoder_Turn( current_pos,  error, motor_pwm);

  
    unsigned long current_time=millis();
    if((current_time-start_time)>timeout){
      Serial2.println("Timeout");
      motorL_Drive(0,Motor_PWM_Upper_Limit);
      return; 
    }
  }
  return;
}

void motorR_TurnRevolutions(int desired_revos){
  //Right Motor
  Serial2.println("motorR_TurnRevolutions");

  resetRightEncoder();

  int current_pos=0;
  int prev_error=0; int error=0;
  int Kp=3,Kd=2;
  int motor_pwm;

  unsigned long start_time=millis();
  int timeout=abs(desired_revos)*3; //Assume a single revo takes ~1 millisecond. Timeout is 3 times that

  while (true)
  {
    current_pos=-EncRight.read();
    error= desired_revos-current_pos;
    motor_pwm= Kp*error + Kd*(error-prev_error); 
    prev_error = error;

    if(error<3 && error>-3){
      //Stop
      Serial2.println("EXIT");
      motorR_Drive(0,Motor_PWM_Upper_Limit);
      break;
    }

    motorR_Drive(motor_pwm,Motor_PWM_Upper_Limit);
    
    debug_Encoder_Turn( current_pos,  error, motor_pwm);

    unsigned long current_time=millis();
    if((current_time-start_time)>timeout){
      Serial2.println("Timeout");
      motorR_Drive(0,Motor_PWM_Upper_Limit);
      return; 
    }
  }
  return;

}

void motors_L_R_TurnRevolutions(int desired_revos_L,int desired_revos_R){
  Serial2.print("motors_L_R_TurnRevolutions   "); Serial2.print(desired_revos_L);Serial2.println(desired_revos_R);
  resetLeftEncoder();resetRightEncoder();

  int current_pos_L=0;
  int prev_error_L=0; int error_L=0;
  int Kp_L=3,Kd_L=2;
  int motor_pwm_L;

  int current_pos_R=0;
  int prev_error_R=0; int error_R=0;
  int Kp_R=3,Kd_R=2;
  int motor_pwm_R;

  unsigned long start_time=millis();
  int timeout=abs(desired_revos_L)*3+abs(desired_revos_R)*3; //Assume a single revo takes ~1 millisecond. Timeout is 3 times that

  while (true)
  {
    current_pos_L=EncLeft.read();
    error_L= desired_revos_L-current_pos_L;
    motor_pwm_L= Kp_L * error_L + Kd_L*(error_L-prev_error_L); 
    prev_error_L = error_L;

    current_pos_R=-EncRight.read();
    error_R= desired_revos_R-current_pos_R;
    motor_pwm_R= Kp_R * error_R + Kd_R*(error_R-prev_error_R); 
    prev_error_R = error_R;

    if(error_L<10 && error_L>-10){
      motorL_Drive(0,Motor_PWM_Upper_Limit);
    }else{
      motorL_Drive(motor_pwm_L,Motor_PWM_Upper_Limit);
    }
    if(error_R<10 && error_R>-10){
      motorR_Drive(0,Motor_PWM_Upper_Limit);
    }else{
      motorR_Drive(motor_pwm_R,Motor_PWM_Upper_Limit);
    }
    

    if(error_L<10 && error_L>-10 && error_R<10 && error_R>-10){
      break;
    }

    
    // Serial2.print("Left:  ");Serial2.print("current_pos_L: ");Serial2.print(current_pos_L); Serial2.print(",  ");Serial2.print("error_L: ");Serial2.print(error_L); Serial2.print(",  ");Serial2.print("motor_pwm_L: ");Serial2.print(motor_pwm_L); Serial2.print(",  ");
    // Serial2.print("Right: ");Serial2.print("current_pos_R: ");Serial2.print(current_pos_R); Serial2.print(",  ");Serial2.print("error_R: ");Serial2.print(error_R); Serial2.print(",  ");Serial2.print("motor_pwm_R: ");Serial2.print(motor_pwm_R); Serial2.print(",  ");
    // Serial2.println("");

    unsigned long current_time=millis();
    if((current_time-start_time)>timeout){
      Serial2.println("Timeout");
      //motorL_Drive(0,Motor_PWM_Upper_Limit);
      motors_brake();
      return; 
    }

  }

  return;

}



/*--------------------------------Control Individual Motor-----------------------------------------------*/


void motorL_Drive(int motor_pwm, int upper_limit){
  if(motor_pwm>0){
    //Forward
    if(motor_pwm>upper_limit){motor_pwm=upper_limit;}
    digitalWrite(Motor2_INA, HIGH);
    digitalWrite(Motor2_INB, LOW);
    analogWrite(Motor2_PWM, motor_pwm);
  }else if(motor_pwm<0){
    //Backward
    if(motor_pwm< -upper_limit){motor_pwm = upper_limit;}
    digitalWrite(Motor2_INA, LOW);
    digitalWrite(Motor2_INB, HIGH);
    analogWrite(Motor2_PWM, motor_pwm);
  }else
  {
    //Stop
    digitalWrite(Motor2_INA, LOW);
    digitalWrite(Motor2_INB, LOW);
    analogWrite(Motor2_PWM, motor_pwm);
  }
  
}

void motorR_Drive(int motor_pwm, int upper_limit){
  if(motor_pwm>0){
    //Forward
    if(motor_pwm>upper_limit){motor_pwm=upper_limit;}
    digitalWrite(Motor1_INA, LOW);
    digitalWrite(Motor1_INB, HIGH);
    analogWrite(Motor1_PWM, motor_pwm);
  }else if(motor_pwm<0){
    //Backward
    if(motor_pwm< -upper_limit){motor_pwm = upper_limit;}
    digitalWrite(Motor1_INA, HIGH);
    digitalWrite(Motor1_INB, LOW);
    analogWrite(Motor1_PWM, motor_pwm);
  }else
  {
    //Stop
    digitalWrite(Motor1_INA, LOW);
    digitalWrite(Motor1_INB, LOW);
    analogWrite(Motor1_PWM, motor_pwm);
  }
  
}


/*--------------------------------Motor Public Functions-----------------------------------------------*/

void motors_DriveForward(int left_speed,int right_speed) 
{
  if(left_speed<0){left_speed=0;}
  if(right_speed<0){right_speed=0;}
  
  motorL_Drive( left_speed, Motor_PWM_Upper_Limit);
  motorR_Drive( right_speed, Motor_PWM_Upper_Limit);
 
}


/*--------------------------------Motor API Functions-----------------------------------------------*/

void motors_DriveGivenDistance(int distance_cm){
  int revos=61*distance_cm;
  motors_L_R_TurnRevolutions(revos,revos);
}

void motors_Turn_90_Left(){
  motors_L_R_TurnRevolutions(-830,830);
}

void motors_Turn_90_Right(){
  motors_L_R_TurnRevolutions(830,-830);
}

void motors_Turn_45_Left(){
  motors_L_R_TurnRevolutions(-415,415);
}

void motors_Turn_45_Right(){
  motors_L_R_TurnRevolutions(415,-415);
}

void motors_Turn_180(){
  motors_L_R_TurnRevolutions(1660,-1660);
  //OR
  //motors_L_R_TurnRevolutions(-1660,+1660)
}

void motorL_brake(){
  //Left
  digitalWrite(Motor2_INA, LOW);
  digitalWrite(Motor2_INB, LOW);
  analogWrite(Motor2_PWM, 0);
}

void motorR_brake(){
  //Right
  digitalWrite(Motor1_INA, LOW);
  digitalWrite(Motor1_INB, LOW);
  analogWrite(Motor1_PWM, 0);
}

void motors_brake(){
  //Left
  digitalWrite(Motor2_INA, LOW);
  digitalWrite(Motor2_INB, LOW);
  analogWrite(Motor2_PWM, 0);
  //Right
  digitalWrite(Motor1_INA, LOW);
  digitalWrite(Motor1_INB, LOW);
  analogWrite(Motor1_PWM, 0);
}