#include "Parts.h"

unique_ptr<RobotPart> Build(PartType requested){
	switch(requested){
		case PartType::Claw:             return unique_ptr<RobotPart>(new Claw());
		case PartType::Drill:            return unique_ptr<RobotPart>(new Drill());
		case PartType::SmartPlate:       return unique_ptr<RobotPart>(new SmartPlate());
		case PartType::Motor:            return unique_ptr<RobotPart>(new Motor());
		case PartType::Servo:            return unique_ptr<RobotPart>(new Servo());
		case PartType::UltrasonicSensor: return unique_ptr<RobotPart>(new UltrasonicSensor());
		case PartType::LightSensor:      return unique_ptr<RobotPart>(new LightSensor());
		case PartType::Monitor:          return unique_ptr<RobotPart>(new Monitor());
		case PartType::Antenna:          return unique_ptr<RobotPart>(new Antenna());
		case PartType::HUBBlock:         return unique_ptr<RobotPart>(new HUBBlock());
		case PartType::Microcontroller:  return unique_ptr<RobotPart>(new Microcontroller());
		default:                         return nullptr;
	}
}

RobotPart::RobotPart(string newname, Connection_t newCtype):
	__Connection(newCtype),
	Name__(newname)
{}
RobotPart::~RobotPart(){}
RobotPart::Connection_t RobotPart::ConnectionType()const{return __Connection;}
const string& RobotPart::Name()const{return Name__;}

	//Various parts
Claw::Claw():RobotPart("Claw",Wire){}
void Claw::Execute(){
	/*Close Claw*/
}

Drill::Drill():RobotPart("Drill",Wire){}
void Drill::Execute(){
	/*Spin Drill*/
}
void Drill::Stop(){
	/*Stop spinning drill*/
}

SmartPlate::SmartPlate():
	RobotPart("Smart Plate",Snap),
	__hardness_rating__(65.0),
	__stiffness__(66672.3324),
	__heat_rating__(500.0),
	__current_temperature__(0.0)
{}
#include <cmath>
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
	__hardness_rating__(60.0),
	__stiffness__(4448.2216),
	__heat_rating__(500.0),
	__current_temperature__(0.0),
	__deflection__(0.0)
{}
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
void Motor::Execute(){
	/*Turn on motor*/
}
void Motor::Stop(){
	/*Turn off motor*/
}

Servo::Servo():RobotPart("Servo",Gear){}
void Servo::Execute(){
	/*Turn on Servo*/
}
void Servo::Stop(){
	/*Turn off Servo*/
}

UltrasonicSensor::UltrasonicSensor():
	RobotPart("UltrasonicSensor",Male_Female),
	__echo_travel__(0.0)
{}
void UltrasonicSensor::Execute(){
	/*Send signal and calculate time taken to bounce back*/
}
double UltrasonicSensor::Read()const{return __echo_travel__;}

LightSensor::LightSensor():
	RobotPart("LightSensor",Male_Female),
	__lux__(0.0)
{}
void LightSensor::Execute(){
	/*Measure brightness of environment*/
}
double LightSensor::Read()const{return __lux__;}

Monitor::Monitor():RobotPart("Monitor",Wire){}
void Monitor::Execute(){
	/*Switch on monitor*/
}
void Monitor::Print(string message, bool clearscreen){
	/*Display message and/or clear screen*/
}

Antenna::Antenna():RobotPart("Antenna",Wire){}
void Antenna::Execute(){
	/*Read signal according to set frequency and store in __data___*/
}
long unsigned int Antenna::Read()const{return __data___;}

HUBBlock::HUBBlock():RobotPart("HUB Block",Independent){}
void HUBBlock::Execute(){}

Microcontroller::Microcontroller():RobotPart("Microcontroller", Male_Female){}
void Microcontroller::Execute(){
	/*Execute program typed in this block*/
}
void Microcontroller::_Abort(){
	/*Abort current thread and throw some code*/
}