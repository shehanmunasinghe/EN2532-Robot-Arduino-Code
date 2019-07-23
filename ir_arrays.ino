void init_IR(){
  for(int i=0; i<16; i=i+1){
    pinMode(i, INPUT);
  }

}

void get_IR_readings(){
  for(int i=0; i<16; i= i+1){
      irValue[i]= analogRead(i);        // reads the values of the ir panel
  }
}

void get_IR_binary_array(){
  for (int i=0; i<16 ; i=i+1){
    irBinaryValue[i]= (irValue[i]>=200) ;
  }
}

uint16_t encode_IR_values(){
  uint16_t encoded_value = 0;
  for(int i=0; i<16; i++){
    //encoded_value |= (irValue[i] >200 )<< i;
    encoded_value |= irBinaryValue[i]<< i;
  }
  return encoded_value;
}


int get_IR_Position(){      // Gets average position in IR

  //Threshold IR readings
  for (int i=0; i<16 ; i=i+1){
    if (irValue[i]>=200){   //THRESHOLD = 200
      irValue[i]= 1;
      }
    else{
      irValue[i]= 0;
      }
  }

  //Get average IR position
  int avg_pos= 0;
  for(int i=0; i<16; i=i+1){
    if (irValue[i]==1){
      avg_pos += (i+1);}
  }
  int num_pos=0;
  for(int i=0; i<16; i=i+1){
    if (irValue[i]==1){
      num_pos += 1;}
  }

   return avg_pos/num_pos;
}
 
