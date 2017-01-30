/*
The programme is written by Mrinmoy sarkar.
 It is a project for RMA Robotic Competetion ROBORACE 2013
 */
//all header file
#include<Servo.h>
#include<EEPROM.h>
#include<LiquidCrystal.h>

// all variable
byte Check_point_No = 100;//the variable will store the last restart check point number
boolean enter_switch = false;//set true if want to enter the switch zone
int Light_sensor_data[9];  //to store the sensor value
double distance;//to store the distance of any object
double threshold_distance = 5;//distance from the destination box
double box_stand_distance = 30;//distance from the box stand
double switch_box_distance = 30;//distance from the magic box
//buzzer pin
int buzzer_pin = 21;
//all sensor input pin
int total_sensor = 9;//no of sensors
int white[9] = {866,876,918,923,946,910,543,274,362};//referance for white or black
int left1 = 0;
int left2 = 1;
int middle = 2;
int right2 = 3;
int right1 = 4;
int right_back = 5;
int back_left= 6;
int back_middle = 7;
int back_right = 8;

//motor control pin
int right_motor_forward = 4;
int right_motor_backward = 5;
int left_motor_forward = 2;
int left_motor_backward = 3;
//servo pin
int pick_servo1 = 11;//diner servo
int pick_servo2 = 12;//bamer servo
int grab_servo = 10;
int switch_servo = 14;
//sonor pin
int sonor_input_pin = 15;
int sonor_trigger_pin = 16;
//servo object
Servo pick_servoA;//diner servo
Servo pick_servoB;//bamer servo
Servo Grab_servo;
Servo Switch_servo;
int griping_angle_resulotion = 70;
int griping_angle = 5;
int picking_angle = 90;
int pick_angle_resulotion = 50;
int switch_resulution = 80;
int switching_angle = 5;

int calibrate_switch = 30;

int temp_val=0;

void setup()
{
  pinMode(calibrate_switch,INPUT);
  pinMode(buzzer_pin,OUTPUT);

  pinMode(left_motor_forward,OUTPUT);
  pinMode(left_motor_backward,OUTPUT);
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);

  pinMode(sonor_input_pin,INPUT);
  pinMode(sonor_trigger_pin,OUTPUT); 

  pick_servoA.attach(pick_servo1);
  pick_servoB.attach(pick_servo2);
  Grab_servo.attach(grab_servo);
  Switch_servo.attach(switch_servo);

  delay(5);
  //int cali_switch = digitalRead(calibrate_switch);
  delay(5); 
  // white_forward = EEPROM.read(1)*4;
  // white_backward = EEPROM.read(2)*4;
 // if((white_forward == 0 && white_backward == 0)||(white_forward == 1020 && white_backward == 1020)||cali_switch == HIGH)
  {
    //calibrate_sensor();
    // EEPROM.write(1,(byte)white_forward/4);
    // EEPROM.write(2,(byte)white_backward/4);
  }

  Serial.begin(9600);
  //for(int i=0;i<total_sensor;i++)
    //Serial.println(white[i]);
  //Serial.println("************");
  release_box();
  delay(200);
}
void tem_f()
{
  while(temp_val==3);
  distance = get_distance();
  Serial.println(distance);
  if(distance < 25)
  {
    stop_motor();
    delay(1000);
    if(temp_val==0)
    {
      grab_box();
      temp_val = 1;
    }
    go_backward();
    delay(3000);
    stop_motor();
    temp_val = 3;
    delay(30);
  }
  else
  {
    go_forward();
    if(temp_val==1)
    {
      release_box();
      temp_val=0;
    }
    delay(30);
  }
  delay(300);
}

void loop()
{
  delay(1000);
  L_turn();
  check_sensor_data();
  delay(10000);
 
  //delay(1000);
  //stop_motor();
   //calibrate_sensor();
 // for(int i=0;i<total_sensor;i++)
   // Serial.println(white[i]);
  //Serial.println("************");
  // Check_point_No = EEPROM.read(0);
  switch(Check_point_No)
  {
  case 255:
    {
      //EEPROM.write(0,1);
      break;
    }
  case 1:
    {
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,2);
      break;
    }
  case 2:
    {
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,3);
      break;
    }
  case 3:
    {
      getout_from_checkpoint();     
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,4);
      break; 
    }
  case 4:
    {
      getout_from_checkpoint();
      flow_line();
      blow_buzzer(20);
      getout_from_checkpoint();
      flow_line();
      blow_buzzer(20);  
      //EEPROM.write(0,5);
      break;
    }
  case 5:
    {
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,6);
      break;
    }
  case 6:
    {
      getout_from_checkpoint();
      flow_line();
      pickbox_and_cometo_the_track();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,7);
      break;
    }
  case 7:
    {
      getout_from_checkpoint();
      flow_line();
      if(enter_switch)
      {
        enter_switch_zone();
        flow_line();
        //EEPROM.write(0,9);
        blow_buzzer(20);
        break;
      }
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,8);
      break;
    }
  case 8:
    {
      getout_from_checkpoint();
      flow_line();
      getout_from_checkpoint();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,9);
      break;
    }
  case 9:
    {
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,10);
      break;
    }
  case 10:
    {
      getout_from_checkpoint();
      flow_line();
      L_turn();
      flow_line();
      blow_buzzer(20);
      //EEPROM.write(0,11);
      break;
    }
  case 11:
    {
      getout_from_checkpoint();
      while(1);
      {
        distance = get_distance();
        if(distance < threshold_distance)
        {
          stop_motor();
          keep_box();
          release_box();
          break;
        }
        else
        {
          special_flow_line();
        }
      }
      blow_buzzer(200);
      //EEPROM.write(0,100);
      break;
    }
  }
}

void enter_switch_zone()
{
  boolean left = false;
  while(1)
  {
    getout_from_checkpoint();
    get_sensor_data();
    if(Light_sensor_data[back_middle] == 0 && (Light_sensor_data[back_left] == 0 || Light_sensor_data[back_right] == 0))
    {
      stop_motor();
      if(Light_sensor_data[back_right] == 1)
      {
        left = true;
      }
      break;
    }
    else
    {
      special_flow_line();
    }
  }
  if(left == true)
  {
    int i = 0;
    while(1)
    {
      go_left();
      get_sensor_data();
      if(Light_sensor_data[right1] == 0)
      {
        i = 1;
      }
      else if(i == 1 && Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
      {
        stop_motor();
        break;
      }
    }
    while(1)
    {
      distance = get_distance();
      if(distance < switch_box_distance)
      {
        stop_motor();
        switch_box();
        break;
      }
      else
      {
        special_flow_line();
      }
    }
    flow_line();
    blow_buzzer(20);
    getout_from_checkpoint();
    flow_line();
    while(1)
    {
      get_sensor_data();
      if(Light_sensor_data[back_left] == 0 && Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 0)
      {
        stop_motor();
        break;
      }
      else
      {
        back_sensor_flowline();
      }
    }
    while(1)
    {
      go_left();
      get_sensor_data();
      if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
      {
        stop_motor();
        break;
      }
    }
  }
  if(left == false)
  {
    int i = 0;
    while(1)
    {
      go_right();
      get_sensor_data();
      if(Light_sensor_data[left1] == 0)
      {
        i = 1;
      }
      else if(i == 1 && Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
      {
        stop_motor();
        break;
      }
    }
    while(1)
    {
      distance = get_distance();
      if(distance < switch_box_distance)
      {
        stop_motor();
        switch_box();
        break;
      }
      else
      {
        special_flow_line();
      }
    }
    flow_line();
    blow_buzzer(20);
    getout_from_checkpoint();
    flow_line();
    while(1)
    {
      get_sensor_data();
      if(Light_sensor_data[back_left] == 0 && Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 0)
      {
        stop_motor();
        break;
      }
      else
      {
        back_sensor_flowline();
      }
    }
    while(1)
    {
      go_right();
      get_sensor_data();
      if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
      {
        stop_motor();
        break;
      }
    }
  }
}

void switch_box()
{
  for(int i=0; i< switch_resulution;i++)
  {
    Switch_servo.write(switching_angle+i);
    delay(5);
  }
  delay(200);
  for(int i=0; i< switch_resulution;i++)
  {
    Switch_servo.write(switching_angle+switch_resulution-i);
    delay(5);
  }
}

void back_sensor_flowline()
{
  get_sensor_data();
  if(Light_sensor_data[back_left] == 1 && Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 1)
  {
    go_forward();
  }
  else if(Light_sensor_data[back_left] == 0)
  {
    go_left();
  }
  else if( Light_sensor_data[back_right] == 0)
  {
    go_right();
  }
}
void pickbox_and_cometo_the_track()
{
  int count = 0;
  getout_from_checkpoint();
  while(1)
  {
    get_sensor_data();
    if(Light_sensor_data[back_left] == 0 && Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 0)
    {
      if(count <=3)
      {
        count++;
        continue;
      }
      stop_motor();
      break;
    }
    else
    {
      special_flow_line();
    }
  }
  count = 0;
  while(1)
  {
    go_u_left();
    get_sensor_data();
    if(Light_sensor_data[right1] == 0)
    {
      count = 7;
    }
    else if(count == 7 && Light_sensor_data[left1]==1 && Light_sensor_data[left2]==1 && Light_sensor_data[middle]==0 && Light_sensor_data[right2]==1 && Light_sensor_data[right1]==1)
    {
      stop_motor();
      break;
    }
  }
  count = 0;
  while(1)
  {
    distance = get_distance();
    if(distance < box_stand_distance)
    {
      stop_motor();
      break;
    }
    else
    {
      special_flow_line();
    }
  }
  release_box();
  delay(50);
  grab_box();
  delay(50);
  pick_box();
  while(1)
  {
    get_sensor_data();
    if(Light_sensor_data[back_left] == 0 && Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 0)
    {
      stop_motor();
      break;
    }
    else
    {
      special_bacK_lineflow();
    }
  }
  while(1)
  {
    go_u_right();
    get_sensor_data();
    if(Light_sensor_data[left1] == 0)
    {
      count = 7;
    }
    else if(count == 7 && Light_sensor_data[left1]==1 && Light_sensor_data[left2]==1 && Light_sensor_data[middle]==0 && Light_sensor_data[right2]==1 && Light_sensor_data[right1]==1)
    {
      stop_motor();
      break;
    }
  }
}

void special_bacK_lineflow()
{
  get_sensor_data();
  if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
  {
    go_backward();
  }
  else if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 0 && Light_sensor_data[middle] == 0)
  {
    go_backleft();
  }
  else if(Light_sensor_data[right1] == 1 && Light_sensor_data[right2] == 0 && Light_sensor_data[middle] == 0)
  {
    go_backright();
  }
}
void special_flow_line()
{
  get_sensor_data();
  if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
  {
    go_forward();
  }
  else if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 0 && Light_sensor_data[middle] == 0)
  {
    go_left();
  }
  else if(Light_sensor_data[right1] == 1 && Light_sensor_data[right2] == 0 && Light_sensor_data[middle] == 0)
  {
    go_right();
  }
}

void flow_line()
{
  int count = 0;
  while(1)
  {
    get_sensor_data();
    if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
    {
      go_forward();
    }
    else if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 0 && Light_sensor_data[middle] == 0)
    {
      go_left();
    }
    else if(Light_sensor_data[right1] == 1 && Light_sensor_data[right2] == 0 && Light_sensor_data[middle] == 0)
    {
      go_right();
    }
    else if(Light_sensor_data[left1] == 0 && Light_sensor_data[left2] == 0 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 0 && Light_sensor_data[right1] == 0)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
    else if(Light_sensor_data[left1] == 0 && Light_sensor_data[left2] == 0 && Light_sensor_data[middle] == 0 && Light_sensor_data[right1] == 1)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
    else if(Light_sensor_data[left1] == 1  && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 0 && Light_sensor_data[right1] == 0)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
  }
}

void L_turn()
{
  while(1)
  {
    get_sensor_data();
    if(Light_sensor_data[left1] == 0 && Light_sensor_data[right1]==1)
    {
      left_L_turn();
      break;
    }
    else if(Light_sensor_data[left1] == 1 && Light_sensor_data[right1]==0)
    {
      right_L_turn();
      break;
    }
  }
}

void getout_from_checkpoint()
{
  int count = 0;
  while(1)
  {
    go_forward();
    get_sensor_data();
    if(Light_sensor_data[left1] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right1] == 1)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }  
  }
}

void blow_buzzer(int delay_time)
{
  digitalWrite(buzzer_pin,HIGH);
  delay(delay_time);
  digitalWrite(buzzer_pin,LOW);
}

void pick_box()
{
  for(int i = 0; i < pick_angle_resulotion; i++)
  {
    pick_servoA.write(picking_angle+i);
    pick_servoB.write(100-i);
    delay(20);
  }
}
void keep_box()
{
  for(int i = 0; i < pick_angle_resulotion; i++)
  {
    pick_servoA.write(picking_angle + pick_angle_resulotion - i);
    pick_servoB.write(50 + i);
    delay(20);
  }
}
void grab_box()
{
  for(int i = 0; i<griping_angle_resulotion; i++)
  {
    Grab_servo.write(griping_angle+i);
    delay(2);
  }
}

void release_box()
{
  for(int i = 0; i<griping_angle_resulotion; i++)
  {
    Grab_servo.write(griping_angle + griping_angle_resulotion - i);
    delay(2);
  } 
}

void right_L_turn()
{
  int count = 0;
  while(1)
  {
    go_forward();
    get_sensor_data();
    if(Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_right] == 0)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
  }
  count = 0;
  while(1)
  {
    go_right();
    get_sensor_data();
    if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
  }
}
void left_L_turn()
{
  int count = 0;
  while(1)
  {
    go_forward();
    get_sensor_data();
    if(Light_sensor_data[back_middle] == 0 && Light_sensor_data[back_left] == 0)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
  }
  count = 0;
  while(1)
  {
    go_left();
    get_sensor_data();
    if(Light_sensor_data[left1] == 1 && Light_sensor_data[left2] == 1 && Light_sensor_data[middle] == 0 && Light_sensor_data[right2] == 1 && Light_sensor_data[right1] == 1)
    {
      if(count <= 3)
      {
        count++;
        continue;   
      }
      stop_motor();
      break;
    }
  } 
}
void stop_motor()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,LOW);
}
void go_right()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,HIGH);
  digitalWrite(right_motor_forward,LOW);
}
void go_backright()
{
  digitalWrite(left_motor_backward,HIGH);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,LOW);
}

void go_u_right()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,HIGH);
  digitalWrite(left_motor_forward,HIGH);
  digitalWrite(right_motor_forward,LOW); 
}

void go_left()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,HIGH);
}
void go_backleft()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,HIGH);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,LOW);
}
void go_u_left()
{
  digitalWrite(left_motor_backward,HIGH);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,HIGH);
}
void go_forward()
{
  digitalWrite(left_motor_backward,LOW);
  digitalWrite(right_motor_backward,LOW);
  digitalWrite(left_motor_forward,HIGH);
  digitalWrite(right_motor_forward,HIGH);
}

void go_backward()
{
  digitalWrite(left_motor_backward,HIGH);
  digitalWrite(right_motor_backward,HIGH);
  digitalWrite(left_motor_forward,LOW);
  digitalWrite(right_motor_forward,LOW);
}

double get_distance()
{
  digitalWrite(sonor_trigger_pin,HIGH);
  delayMicroseconds(10);
  digitalWrite(sonor_trigger_pin,LOW);
  int i = pulseIn(sonor_input_pin,HIGH);
  double distance = 0.017 * i;
  delay(3);
  return distance;
}

void get_sensor_data()
{
  for(int i = 0; i < total_sensor; i++)
  {
    Light_sensor_data[i] = analogRead(i);
    if(Light_sensor_data[i] < white[i])
    {
      Light_sensor_data[i] = 0;
    }
    else
    {
      Light_sensor_data[i] = 1;
    }
    delay(1);
  }
}

void check_sensor_data()
{
  get_sensor_data();
  Serial.println("*****************************");
  Serial.println("left1:");
  Serial.println(Light_sensor_data[left1]);
  Serial.println("left2:");
  Serial.println(Light_sensor_data[left2]);
  Serial.println("middle1:");
  Serial.println(Light_sensor_data[middle]);
  Serial.println("right1:");
  Serial.println(Light_sensor_data[right1]);
  Serial.println("right2:");
  Serial.println(Light_sensor_data[right2]);
  Serial.println("right_back:");
  Serial.println(Light_sensor_data[right_back]);
  Serial.println("back_left:");
  Serial.println(Light_sensor_data[back_left]);
  Serial.println("back_middle:");
  Serial.println(Light_sensor_data[back_middle]);
  Serial.println("back_right:");
  Serial.println(Light_sensor_data[back_right]);
  Serial.println("*****************************");
  delay(5000);
}

void calibrate_sensor()
{
  int thresh_value[9];
  blow_buzzer(30);
  delay(10000);
  for(int i = 0; i < total_sensor ; i++)
  {
    thresh_value[i] = analogRead(i);
    delay(5);
  }
  blow_buzzer(30);
  delay(10000);
  for(int i = 0; i < total_sensor ; i++)
  {
    thresh_value[i] += analogRead(i);
    delay(5);
  }
  for(int i = 0; i < total_sensor ; i++)
  {
    white[i] = thresh_value[i]/2;
  }
  blow_buzzer(1000);
}



