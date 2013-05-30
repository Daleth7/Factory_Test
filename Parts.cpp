#include "Parts.h"

#include <string>

using std::string;

typedef RobotPart::Connection_t Connection_t;

RobotPart::RobotPart(string newname, Connection_t newCtype):
	Name__(newname),
	__Connection(newCtype)
{}
RobotPart::~RobotPart(){}
RobotPart::Connection_t ConnectionType()const{return __Connection;}
const RobotPart::string& Name()const{return Name__;}
	//Various parts
Claw::Claw():RobotPart("Claw",Wire){}
Claw::~Claw(){}
void Claw::Execute(){
	/*Close Claw*/
}

Drill::Drill():RobotPart("Drill",Wire){}
Drill::~Drill(){}
void Drill::Execute(){
	/*Spin Drill*/
}
void Drill::Stop(){
	/*Stop spinning drill*/
}

SmartPlate::SmartPlate():
	RobotPart("Smart Plate",Snap),
	__current_temperature__(0.0),
	__hardness_rating__(65.0),
	__heat_rating__(500.0),
	__stiffness__(66672.3324)
{}
SmartPlate::~SmartPlate(){}
void SmartPlate::Execute(){
	int sigfig(0);
	/*Track temperature and count number of significant digits*/
	if(fabs(__current_temperature__ - __heat_rating__) < pow(10,-sigfig))	
		throw "Error. Surpassed heat rating of smart plate.";
}
double SmartPlate::CurrentTemp()const{return __current_temperature__;}
double SmartPlate::HardRate()const{return __hardness_rating__;}
double SmartPlate::HeatRate()const{return __heat_rating__;}
double SmartPlate::StiffRate()const{return __stiffness__;}

SmartBar::SmartBar():
	RobotPart("Smart Bar"),
	__current_temperature__(0.0),
	__hardness_rating__(60.0),
	__heat_rating__(500.0),
	__stiffness__(4448.2216),
	__deflection__(0.0)
{}
SmartBar::~SmartBar(){}
void SmartBar::Execute(){
	int sigfig(0);
	/*keep track of temperature and deflection of bar by measuring loads from gravity*/
	if(fabs(__current_temperature__ - __heat_rating__) < pow(10,-sigfig))
		throw "Error. Surpassed heat rating of smart bar.";
}
double SmartBar::CurrentTemp()const{return __current_temperature__;}
double SmartBar::HardRate()const{return __hardness_rating__;}
double SmartBar::HeatRate()const{return __heat_rating__;}
double SmartBar::StiffRate()const{return __stiffness__;}
double SmartBar::Deflection()const{return __deflection__;}

Motor::Motor():RobotPart("Motor",Gear){}
Motor::~Motor(){}
Motor::Connection_t ConnectionType()const{return __Connection;}
const Motor::string& Name()const{return Name__;}
void Motor::Execute(){
	/*Turn on motor*/
}
void Motor::Stop(){
	/*Turn off motor*/
}

Servo::Servo():RobotPart("Servo",Gear){}
Servo::~Servo(){}
void Servo::Execute(){
	/*Turn on Servo*/
}
void Servo::Stop(){
	/*Turn off Servo*/
}

UltrasonicSensor::UltrasonicSensor():
	RobotPart("UltrasonicSensor",Male_Male_Female),
	__echo_travel__(0.0)
{}
UltrasonicSensor::~UltrasonicSensor(){}
void UltrasonicSensor::Execute(){
	/*Send signal and calculate time taken to bounce back*/
}
double UltrasonicSensor::Read()const{return __echo_travel__;}

LightSensor::LightSensor():
	RobotPart("LightSensor",Male_Male_Female),
	__lux__(0.0)
{}
LightSensor::~LightSensor(){}
void LightSensor::Execute(){
	/*Measure brightness of environment*/
}
double LightSensor::Read()const{return __lux__;}

Monitor::Monitor():RobotPart("Monitor",Wire){}
Monitor::~Monitor(){}
void Monitor::Execute(){
	/*Switch on monitor*/
}
void Monitor::Print(string message, bool clearscreen){
	/*Display message and/or clear screen*/
}

Antenna::Antenna():RobotPart("Antenna",Wire){}
Antenna::~Antenna(){}
void Antenna::Execute(){
	/*Read signal according to set frequency and store in __data___*/
}
long unsigned int HUBBlock::Read()const{return __data___;}

HUBBlock::HUBBlock():RobotPart("HUB Block",Independent){}
HUBBlock::~HUBBlock(){}
void HUBBlock::Execute(){}

Microcontroller::Microcontroller():RobotPart("Microcontroller", Male_Female){}
Microcontroller::~Microcontroller(){}
void Microcontroller::Execute(){
	/*Execute program typed in this block*/
}
void MicroController::_Abort(){
	/*Abort current thread and throw some code*/
}