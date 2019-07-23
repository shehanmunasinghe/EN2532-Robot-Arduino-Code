//turn_left
//turn_right
//T junction(box)
int array_sum(int array[],int start,int last)
{
  int sum=0;
  for(start;start<=last;start++)
  {
    sum+=array[start];
  }
  return sum;
}

int checkIRSpecialCondition(){
    // Serial2.println("checkIRSpecialCondition");
    // get_IR_binary_array();

    //Serial2.println();
    //Serial2.print("L "); Serial2.print(array_sum(irBinaryValue,8,15));
    //Serial2.print("    R ");Serial2.println(array_sum(irBinaryValue,0,7));
    
    if(array_sum(irBinaryValue,0,15)>=14){ //Detect all white T Junction
		Serial2.println("IR_ALL_WHITE");
		return IR_ALL_WHITE;
    }else if(array_sum(irBinaryValue,0,15)>=7 ) {
		motors_brake();
		get_IR_readings();get_IR_binary_array();
		delay(100);
     
		if (array_sum(irBinaryValue,2,13)>=7 && array_sum(irBinaryValue,0,1)<2 && array_sum(irBinaryValue,14,15)<2){    
			//Detect coin box
			Serial2.println("IR_COIN_BOX");
			return IR_COIN_BOX;
		}else if(array_sum(irBinaryValue,0,7)>=7 && irBinaryValue[15]==0 && array_sum(irBinaryValue,0,1)>=1) //Detect Right Turn
		{
			Serial2.println("Right");
			return IR_90_RIGHT; 
		}
		else if(array_sum(irBinaryValue,8,15)>=7 && irBinaryValue[0]==0 && array_sum(irBinaryValue,14,15)>=1) //Detect Left Turn
		{
		// motors_DriveGivenDistance(13);
		// motors_Turn_90_Left(); Turn left
		Serial2.println("Left");
		return IR_90_LEFT;
		} 
    }
    /* else if((array_sum(irBinaryValue,2,7)>=3 && array_sum(irBinaryValue,8,13)>=3)  && array_sum(irBinaryValue,0,1)<2 && array_sum(irBinaryValue,14,15)<2 ) //Detect coin box
    {

      Serial2.println("IR_COIN_BOX");
      return IR_COIN_BOX;
    }
    else if(array_sum(irBinaryValue,0,7)>=7 && irBinaryValue[15]==0 && array_sum(irBinaryValue,0,1)>=1) //Detect Right Turn
    {
      Serial2.println("Right");
      return IR_90_RIGHT; 
    }
    else if(array_sum(irBinaryValue,8,15)>=7 && irBinaryValue[0]==0 && array_sum(irBinaryValue,14,15)>=1) //Detect Left Turn
    {
      //motors_DriveGivenDistance(13);
      //motors_Turn_90_Left(); Turn left
      Serial2.println("Left");
      return IR_90_LEFT;
    } */
    else if(array_sum(irBinaryValue,0,15)<2) //Detect  All black
    {
      Serial2.println("IR_ALL_BLACK");
      return IR_ALL_BLACK;
    }
    else
    {
      return IR_NORMAL_LINE;
    }
    
    //debug_IR(irValue);
    //delay(2000);
    
}

int checkIRSpecialConditionInsideCoinArea(){

  if(array_sum(irBinaryValue,0,15)>=7 ) { 		
		// if (array_sum(irBinaryValue,2,13)>=7 && array_sum(irBinaryValue,0,1)<2 && array_sum(irBinaryValue,14,15)<2)
		if (array_sum(irBinaryValue,2,13)>=7 )
		{    //Detect coin box
			Serial2.println("IR_COIN_BOX");
			return IR_COIN_BOX;
		}else
		{
			return	IR_NORMAL_LINE;
		}
		
      
    }
    else
    {
      	return IR_NORMAL_LINE;
    }
    
}
