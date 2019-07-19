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
    Serial2.println("checkIRSpecialCondition");
    // get_IR_binary_array();

    //Serial2.println();
    //Serial2.print("L "); Serial2.print(array_sum(irBinaryValue,8,15));
    //Serial2.print("    R ");Serial2.println(array_sum(irBinaryValue,0,7));
    
    if(array_sum(irBinaryValue,0,15)<2) //Detect  All black
    {
      Serial2.println("IR_ALL_BLACK");
      return IR_ALL_BLACK;
    }
    else if(array_sum(irBinaryValue,0,15)>8 and array_sum(irBinaryValue,0,15)<14) //Detect coin
    {
      Serial2.println("IR_COIN_BOX");
      return IR_COIN_BOX;
    }
    else if(array_sum(irBinaryValue,0,15)>=14) //Detect all white
    {
      // motors_DriveGivenDistance(13);
      // motors_Turn_90_Right(); /*turn right */
      return IR_ALL_WHITE;
    }
    else if(array_sum(irBinaryValue,0,7)>=6) //Detect Right Turn
    {
      Serial2.println("Right");
      return IR_90_RIGHT;
    }
    else if(array_sum(irBinaryValue,8,15)>=6) //Detect Left Turn
    {
      // motors_DriveGivenDistance(13);
      // motors_Turn_90_Left(); /*turn left */
      Serial2.println("Left");
      return IR_90_LEFT;
    }
    else
    {
      return IR_NORMAL_LINE;
    }
    
    //debug_IR(irValue);
    //delay(2000);
    
}

void check_45()
{ 
  int color=1;
  for(int i=0; i<16; i= i+1){
            irValue[i]= analogRead(i);        // reads the values of the ir panel
        }
 
  for (int i=0; i<16 ; i=i+1){
    if (irValue[i]>=450){   //THRESHOLD = 450
      irBinaryValue[i]= 1;
      Serial2.print(irBinaryValue[i]);
      //Serial2.print(" ");
      }
    else{
      irBinaryValue[i]= 0;
      Serial2.print(irBinaryValue[i]);
      }
  }

  if(8<=array_sum(irBinaryValue,0,15)<=14)
  {
    fortyJunc(color);
  }
  else
  {
    return;
  }
  
}
void fortyJunc(int color)
{  
  //012 => BGR => centre, right, left
  if(color==0)
  {
    motors_DriveGivenDistance(15);
  }
  else if(color==1)
  {
    motors_Turn_45_Right();
    motors_DriveGivenDistance(15);
  }
  else if(color==2)
  {
    motors_Turn_45_Left();
    motors_DriveGivenDistance(15);
  }
  else
  {
    motors_DriveGivenDistance(15);
    //return;
  }
  

}
