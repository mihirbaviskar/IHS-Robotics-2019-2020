void forward(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,speed); //mrp
    motor(RIGHTMOTOR,speed);
    msleep(time);
}
void back(int speed, int time){ //in msleep time
    motor(LEFTMOTOR,speed); //mrp or motor
    motor(RIGHTMOTOR,speed);
    msleep(time);
}
void moveSpaceShip(int speed, int finalPos){ // negetive for down 
    curPos = get_servo_position(int port);
    while (curPos < finalPos){  //placement inequality
        set_servo_position(port, curPos+1);
        msleep(10);
    }
}
void moveSweeper(int speed, int time){  // sweeper is a motor, negetive for down
    motor(SWEEPERMOTOR,speed);
    msleep(time);
}
void pipefollowSwitch(double time) {
    double initialTime = seconds();

    while (seconds() <= initialTime + time) {
        if (BUTTONSENSOR == 1)) {
            motor(LEFTMOTOR, 100);
            motor(RIGHTMOTOR, 90);
        } else {
            motor(LEFTMOTOR, 85);
            motor(RIGHTMOTOR, 100);        
        }
    }
}
