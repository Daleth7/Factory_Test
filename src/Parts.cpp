/*                             Parts.cpp
  ------------------------------Synopsis------------------------------
    This file defines the functions declared in Parts.h. In each of 
  the defined constructors, there are string and number literals 
  specific to each part. All measurements are in the metric system mks.

  ------------------------------Warnings------------------------------
	The Build(PartType) function returns a raw pointer to a 
  dynamically allocated object. The caller of this function will be
  responsible for deallocating the memory.

  -------------------------Included Libraries-------------------------
    <cmath> has been included for the pow(double,double) function in 
  the various Execute functions.

  From Parts.h:
    <string> has been included for std::string, which is used to hold 
  the new "names" of the robotic parts.

  ----------------------------Type Aliases----------------------------
    std::string has been aliased as _string from the Parts.h file.

  -------------------------------Notes--------------------------------
    Because this is just a Abstract Factory and Factory test, no focus
  is given on the specific execution procedures the parts use.
*/
#include "Parts.h"
RobotPart* Build(PartType requested){
	switch(requested){
		case PartType::Claw:            return new Claw();
		case PartType::Drill:           return new Drill();
		case PartType::SmartPlate:      return new SmartPlate();
		case PartType::SmartBar:        return new SmartBar();
		case PartType::Motor:           return new Motor();
		case PartType::Servo:           return new Servo();
		case PartType::UltrasonicSensor:return new UltrasonicSensor();
		case PartType::LightSensor:     return new LightSensor();
		case PartType::Monitor:         return new Monitor();
		case PartType::Antenna:         return new Antenna();
		case PartType::HUBBlock:        return new HUBBlock();
		case PartType::Microcontroller: return new Microcontroller();
		default:                        return nullptr;
	}
}

/*********************************************************************
                              RobotPart
*********************************************************************/
RobotPart::Connection_t RobotPart::ConnectionType()const
	{return __Connection;}
const RobotPart::_string& RobotPart::Name()const
	{return Name__;}
RobotPart::RobotPart(_string newname, Connection_t newCtype):
	__Connection(newCtype),
	Name__(newname)
{}
RobotPart::~RobotPart(){}
/*********************************************************************
                               Claw
*********************************************************************/
Claw::Claw():RobotPart("Claw",Wire){}
void Claw::Execute(){
	/*Close Claw*/
}
/*********************************************************************
                               Drill
*********************************************************************/
Drill::Drill():RobotPart("Drill",Wire){}
void Drill::Execute(){
	/*Spin Drill*/
}
void Drill::Stop(){
	/*Stop spinning drill*/
}
/*********************************************************************
                             SmartPlate
*********************************************************************/
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
	if(
		fabs(__current_temperature__ - __heat_rating__) 
			< pow(10,-sigfig)
	) throw "Error. Surpassed heat rating of smart plate.";
}
double SmartPlate::CurrentTemp()const
	{return __current_temperature__;}
double SmartPlate::HardRate()const
	{return __hardness_rating__;}
double SmartPlate::HeatRate()const
	{return __heat_rating__;}
double SmartPlate::StiffRate()const
	{return __stiffness__;}
/*********************************************************************
                              SmartBar
*********************************************************************/
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
	/*keep track of temperature and deflection of bar by measuring
	   load from gravity
	  */
	if(fabs(__current_temperature__ - __heat_rating__) < pow(10,-sigfig))
		throw "Error. Surpassed heat rating of smart bar.";
}
double SmartBar::CurrentTemp()const
	{return __current_temperature__;}
double SmartBar::HardRate()const
	{return __hardness_rating__;}
double SmartBar::HeatRate()const
	{return __heat_rating__;}
double SmartBar::StiffRate()const
	{return __stiffness__;}
double SmartBar::Deflection()const
	{return __deflection__;}
/*********************************************************************
                               Motor
*********************************************************************/
Motor::Motor():RobotPart("Motor",Gear){}
void Motor::Execute(){
	/*Turn on motor*/
}
void Motor::Stop(){
	/*Turn off motor*/
}
/*********************************************************************
                               Servo
*********************************************************************/
Servo::Servo():RobotPart("Servo",Gear){}
void Servo::Execute(){
	/*Turn on Servo*/
}
void Servo::Stop(){
	/*Turn off Servo*/
}
/*********************************************************************
                           UltrasonicSensor
*********************************************************************/
UltrasonicSensor::UltrasonicSensor():
	RobotPart("UltrasonicSensor",Male_Female),
	__echo_travel__(0.0)
{}
void UltrasonicSensor::Execute(){
	/*Send signal and calculate time taken to bounce back*/
}
double UltrasonicSensor::Read()const{return __echo_travel__;}
/*********************************************************************
                             LightSensor
*********************************************************************/
LightSensor::LightSensor():
	RobotPart("LightSensor",Male_Female),
	__lux__(0.0)
{}
void LightSensor::Execute(){
	/*Measure brightness of environment*/
}
double LightSensor::Read()const{return __lux__;}
/*********************************************************************
                              Monitor
*********************************************************************/
Monitor::Monitor():RobotPart("Monitor",Wire){}
void Monitor::Execute(){
	/*Switch on monitor*/
}
void Monitor::Print(_string message, bool clearscreen){
	/*Display message and/or clear screen*/
}
/*********************************************************************
                               Antenna
*********************************************************************/
Antenna::Antenna():RobotPart("Antenna",Wire){}
void Antenna::Execute(){
	/*Read signal according to set frequency and store in __data___*/
}
long unsigned int Antenna::Read()const{return __data___;}
/*********************************************************************
                              HUBBlock
*********************************************************************/
HUBBlock::HUBBlock():RobotPart("HUB Block",Independent){}
void HUBBlock::Execute(){}
/*********************************************************************
                            Microcontroller
*********************************************************************/
Microcontroller::Microcontroller():
	RobotPart("Microcontroller", Male_Female)
{}
void Microcontroller::Execute(){
	/*Execute program typed in this block*/
}
void Microcontroller::_Abort(){
	/*Abort current thread and throw some error code number*/
}
