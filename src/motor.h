#ifndef motor
#define motor

/*Motor Status*/
enum motorMovement
{
    GO_FORWARD, 
    GO_BACKWARD, 
    TURN_LEFT,   //Full Spin 
    TURN_RIGHT,  //Full Spin
    ROTATE_ON_LEFT_FWD, //Spins only a single wheel
    ROTATE_ON_LEFT_BWD, //Spins only a single wheel
    ROTATE_ON_RIGHT_FWD, //Spins only a single wheel
    ROTATE_ON_RIGHT_BWD, //Spins only a single wheel
    STOP_ALL
};

/*Directions that the wheels spin in using dWrite*/
enum wheelSpinDirection
{
    SPIN_R_FORWARD, 
    SPIN_R_BACK, 
    SPIN_L_FORWARD, 
    SPIN_L_BACK,
    STOP_L,
    STOP_R,

};

/*Pin Defines*/
#define motorLeftPWM 15
#define motorLeftA 0
#define motorLeftB 2
#define motorRightPWM 18
#define motorRightA 5
#define motorRightB 4

/*Motor Defines*/
#define MOTOR_PWM 125 //Microseconds

/*Motor Functions*/
void initMotors();
void moveMotors(int motorMovement);
void wSD(int wheelSpinDirection);

#endif