
 int inclination(){
  #define GOING_UP           0
  #define GOING_LEVEL        1
  #define GOING_DOWN          2
  const int MPU_addr=0x68;
  int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

  int minVal=-1600;
  int maxVal=-700;

  double x;
  double y;
  double z;
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

while(1)
{
    
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();

    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);
    

       x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);



     if (y<=70)
     {
       return GOING_UP;
     }

     else if (70<y<85)
     {
       return GOING_LEVEL;
     }

     else
    {
          return GOING_DOWN;
     }


     Serial2.println("-----------------------------------------");
     delay(400);
}
}
