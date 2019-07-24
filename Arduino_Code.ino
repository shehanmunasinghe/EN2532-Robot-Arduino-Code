/*--------------------------------Pin Definitions--------------------------------*/

//EncRight
#define Motor1_INA 24//D5
#define Motor1_INB 25//D7
#define Motor1_PWM 11//D6
//EncLeft
#define Motor2_INA 26//D2
#define Motor2_INB 27//D4
#define Motor2_PWM 12//D3

#define Motor1_Encoder1 2//A2
#define Motor1_Encoder2 3//A3
#define Motor2_Encoder1 18//A5 //A4
#define Motor2_Encoder2 19//A4 //A5

#define Servo1_PWM 8
#define Servo2_PWM 7
#define Servo3_PWM 6
#define Servo4_PWM 5
#define Servo5_PWM 4

#define TOF1_XSHUT 34           
#define TOF2_XSHUT 33           
#define TOF3_XSHUT 32           
#define TOF4_XSHUT 31           
#define TOF5_XSHUT 30   

#define TOF1_ADDR 0x2A
#define TOF2_ADDR 0x2B
#define TOF3_ADDR 0x2C
#define TOF4_ADDR 0x2D
#define TOF5_ADDR 0x2E

#define MPU6050_ADDR 0x68
/*--------------------------------Constant Definitions--------------------------------*/

//STATES
#define STATE_PAUSED                      0
#define STATE_DEFAULT_START               1 //STATE_INSIDE_START_BOX  //STATE_WALL_MAZE  //1//STATE_INSIDE_START_BOX            //

#define STATE_INSIDE_START_BOX                  1
#define STATE_LINE_1                            2
#define STATE_LINE_1B                           102
#define STATE_DETECTED_COIN_BOX_1               3
#define STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_1    4
#define STATE_DETECTED_Y_JUNCTION               5
#define STATE_SELECTED_Y_PATH                   6
#define STATE_DETECTED_COIN_BOX_2               7
#define STATE_LINE_FOLLOW_UNTIL_Y_JUNCTION_2    8
#define STATE_LINE_2                            9
#define STATE_RAMP_CLIMB                        10
#define STATE_RAMP_TOP                          11
#define STATE_RAMP_DESCEND                      12
#define STATE_LINE_3                            13
#define STATE_WALL_MAZE                         14
#define STATE_LINE_4                            15
#define STATE_DETECTED_WATER_JUNCTION           16
#define STATE_SELECTED_WATER_PATH               17
#define STATE_DETECTED_WATER_TANK               18
#define STATE_RETURNED_TO_WATER_JUNCTION        19
#define STATE_DETECTED_END_BOX                  20


//IMU STATES
#define IMU_RAMP_AHEAD_OR_CLIMB           1
#define IMU_RAMP_DESCENT                  2 

//IR Special Conditions
#define IR_NORMAL_LINE           0
#define IR_ALL_BLACK             1
#define IR_ALL_WHITE             2
#define IR_90_RIGHT              3
#define IR_90_LEFT               4
#define IR_COIN_BOX              5

//Wall Special Conditions
#define WALL_FOLLOW_BOTH              1
#define WALL_DEAD_END                 2
#define WALL_LEFT_FREE                3
#define WALL_LEFT_BLOCKED_FRONT_FREE  4
#define WALL_ONLY_RIGHT_FREE          5
#define WALL_UNKNOWN_CONDITION        6
#define WALL_TOF_NOT_INITIALIZED      7


//DEBUG Messages
#define DEBUG_IR_ARRAY 						          1
#define DEBUG_TOFS 						            	2
#define DEBUG_STATE_TRANSITION		      		3
#define DEBUG_CHECK_IR_SPECIAL_CONDITION  	4
#define DEBUG_CHECK_MAZE_SPECIAL_CONDITION	5

//Motor PWM Limits
#define MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW 	60
#define MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW 	65

//Coin Detected Colors
#define COIN_COLOR_RED          1
#define COIN_COLOR_GREEN        2
#define COIN_COLOR_BLUE         3

//IMU
#define IMU_GOING_LEVEL       0
#define IMU_GOING_UP          1
#define IMU_GOING_DOWN        2
/*--------------------------------Libraries------------------------------------------*/
#include <Encoder.h>
#include <Servo.h>

#include <Wire.h>
#include <VL53L0X.h>

/*--------------------------------Global Objects--------------------------------*/


Encoder EncRight(Motor1_Encoder1, Motor1_Encoder2);
Encoder EncLeft(Motor2_Encoder1, Motor2_Encoder2);

Servo servo1,servo2,servo3,servo4,servo5;

VL53L0X TOF_sensor_1;VL53L0X TOF_sensor_2;VL53L0X TOF_sensor_3;VL53L0X TOF_sensor_4;VL53L0X TOF_sensor_5;

/*--------------------------------Global Variables - General--------------------------------*/

int irValue[16]= {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int irBinaryValue[16]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

uint16_t tof_right_2 ;
uint16_t tof_right_1 ;
uint16_t tof_front  ;
uint16_t tof_left_1 ;
uint16_t tof_left_2 ;

uint8_t robot_state=0;

uint8_t Motor_PWM_Upper_Limit;

uint8_t IMU_status;

bool button_pressed=false;

int temp_ir_condition=0;int temp_wall_condition=0;

char debug_buffer[5];

int detected_coin_color;

int16_t IMU_AcX,IMU_AcY,IMU_AcZ,IMU_Tmp,IMU_GyX,IMU_GyY,IMU_GyZ;
double IMU_x,IMU_y,IMU_z;

#define IMU_minVal -1600
#define IMU_maxVal -700
/*--------------------------------Global Variables - Wall Follow--------------------------------*/
int wf_base_speed = MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW;//= Motor_PWM_Upper_Limit;

int wf_prev_error=0;int wf_error=0; int wf_cum_error=0;
int wf_diff_speed;
int wf_right_speed;int wf_left_speed;

// const int wf_Kp=1.5,wf_Kd=90,wf_Ki=0.2;
const int wf_Kp=2,wf_Kd=90,wf_Ki=0.2;
const int wfR_Kp=5,wfR_Kd=10,wfR_Ki=0.2;
const int wfL_Kp=5,wfL_Kd=20,wfL_Ki=0.2;

/*--------------------------------Global Variables - Line Follow--------------------------------*/
// int lf_base_speed = Motor_PWM_Upper_Limit/2;
// const int lf_Kp=20,lf_Kd=5;//lf_Ki=0.2;
int lf_base_speed = MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;
const int lf_Kp=45,lf_Kd=100,lf_Ki=0.5;

int lf_prev_error=0;int lf_error=0; int lf_cum_error=0;
int lf_diff_speed;
int lf_right_speed;int lf_left_speed;

int avg_ir_pos=0;
/*--------------------------------Setup-----------------------------------------------*/

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  
  init_motors();
  init_IR();
  init_Servos();
  init_TOFs();

  init_IMU();

  robot_state = STATE_DEFAULT_START;

  // Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_WALL_FOLLOW;
	Motor_PWM_Upper_Limit=MOTOR_PWM_UPPER_LIMIT_LINE_FOLLOW;

}

/*--------------------------------Loop-----------------------------------------------*/

void loop(){
	// test_wall_maze();

  //  test_line_follow_1();
  // pid_line_follow_step();
  
  decide();

  // get_IR_readings();
  // get_IR_binary_array();
  // print_IR_readings();
  // print_IR_binary_array();

  // get_ToF_Measurements();print_tof_readings();
  // check_IMU_status();
}


