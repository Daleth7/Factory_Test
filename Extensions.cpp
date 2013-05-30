#include "Extensions.h"
#include "Parts.h"
	
#include <list>
#include <string>

using std::list;
using std::string;

enum class ExtensionType;
class RobotPart;

RobotExtensions::RobotExtensions(){
	PartsList__.pushback(new HUBBlock());
	Link__.push_back(Wire);
	Link__.push_back(Snap);
	Link__.push_back(Gear);
	Link__.push_back(Male_Female);
	RE_Name = "HUB";
}
RobotExtensions::~RobotExtensions(){
	for(auto part__ = PartsList__.begin(); part__ != PartsList__.end(); part__++)
		delete (*part);
}
string RobotExtensions::Name()const{return RE_Name__;}
void RobotExtensions::Attach(const list<RobotPart*>& newparts){
	PartsList__.resize(PartsList__.size() + newparts.size());
	for(auto part___ = newparts.begin(); part__ != newparts.end(); part___++){
		if(Link__.empty())	break;
		for(auto alink__ = Link__.begin(); alink__ != Link__.end(); alink++){
			if((*alink) == (*part__)->__Connection){
				PartsList__.pushback(*part___);
				Link__.erase(alink);
				break;
			}
		}
	}
}
RobotExtensions* RobotExtensions::RobotExtensions(ExtensionType Etype, const list<RobotPart*>& new_parts){
	switch(Etype){
		case Framework:		return new Frame(new_parts);		break;
		case Chassis:		return new Chassis(new_parts);		break;
		case SensorModule:	return new SensorModule(new_parts);	break;
		case DrillArm:		return new DrillArm(new_parts);		break;
		case GrabbingArm:	return new GrabbingArm(new_parts);	break;
		case Joint:			return new Joint(new_parts);		break;
		case DriverWheel:	return new DriverWheel(new_parts);	break;
		default:			return new RobotExtension();		break;
	}
}


Frame::Frame(const list<RobotPart*>& newparts):
	RE_Name("Frame")
{
	CreateDefault();
	Attach(newparts);
}
Frame::~Frame(){}
void Frame::CreateDefault(){
	const int minimum_bars_need(10);
	for(int i = 0; i < minimum_bars_need; i++){
		PartsList__.push_back(new SmartBar());
		Link__.push_back(Male_Female);
		if(i%2 == 0)	Link__.push_back(Snap);
	}
}

Chassis::Chassis(const list<RobotPart*>& newparts):
	RE_Name("Chassis")
{
	CreateDefault();
	Attach(newparts);
}
Chassis::~Chassis(){}
void Chassis::CreateDefault(){
	const int 
		minimum_plates_needed(50),
		minimum_bars_need(7)
	;
	for(int i = 0; i < minimum_plates_needed; i++){
		PartsList__.push_back(new SmartPlate());
		if(i%2 == 0)	Link__.push_back(Snap);
	}
	for(int i = 0; i < minimum_bars_need; i++){
		PartsList__.push_back(new SmartBar());
		Link__.push_back(Wire);
	}
}

SensorModule::SensorModule(const list<RobotPart*>& newparts):
	RE_Name("Sensor Module")
{
	CreateDefault();
	Attach(newparts);
}
SensorModule::~SensorModule(){}
void SensorModule::CreateDefault(){
	const int
		minimum_plates(4),
		minimum_servos(1),
		minimum_lsensors(16),
		minimum_ussensors(4)
	;
	for(int i=0; i<minimum_plates; i++)
		PartsList__.push_back(new SmartPlate());
	for(int i=0; i<minimum_servos; i++)
		PartsList__.push_back(new Servo());
	for(int i=0; i<minimum_lsensors; i++)
		PartsList__.push_back(new LightSensor());
	for(int i=0; i<minimum_ussensors; i++)
		PartsList__.push_back(new UltrasonicSensor());
	Link__.push_back(Male_Female);
	Link__.push_back(Gear);
}

DrillArm::DrillArm(const list<RobotPart*>& newparts){
	CreateDefault();
	Attach(newparts);
}
DrillArm::~DrillArm(){}
void DrillArm::CreateDefault(){
	const int
		minimum_drills(3),
		minimum_bars(2),
		minimum_plates(6)
	;
	for(int i=0; i<minimum_plates; i++)
		PartsList__.push_back(new SmartPlate());
	for(int i=0; i<minimum_drills; i++)
		PartsList__.push_back(new Drill());
	for(int i=0; i<minimum_bars; i++)
		PartsList__.push_back(new SmartBar());
	Link__.push_back(Male_Female);
}

GrabbingArm::GrabbingArm(const list<RobotPart*>& newparts){
	CreateDefault();
	Attach(newparts);
}
GrabbingArm::~GrabbingArm(){}
void GrabbingArm::CreateDefault(){
	const int
		minimum_claws(1),
		minimum_bars(2),
		minimum_plates(6)
	;
	for(int i=0; i<minimum_plates; i++)
		PartsList__.push_back(new SmartPlate());
	for(int i=0; i<minimum_claws; i++)
		PartsList__.push_back(new Drill());
	for(int i=0; i<minimum_bars; i++)
		PartsList__.push_back(new SmartBar());
	Link__.push_back(Male_Female);
}

Joint::Joint(const list<RobotPart*>& newparts){
	CreateDefault();
	Attach(newparts);
}
Joint::~Joint(){}
void Joint::CreateDefault();

DriverWheel::DriverWheel(const list<RobotPart*>& newparts){
	CreateDefault();
	Attach(newparts);
}
DriverWheel::~DriverWheel(){}
void DriverWheel::CreateDefault();

BRAIN::BRAIN(const list<RobotPart*>& newparts){
	CreateDefault();
	Attach(newparts);
}
BRAIN::~BRAIN(){}
void BRAIN::CreateDefault(){
	const int
		minimum_mcontrollers(4),
		minimum_plates(5)
	;
	for(int i=0; i < minimum_mcontrollers; i++){
		PartsList.push_back(new Microcontrollers());
		Link__.push_back(Male_Female);
		Link__.push_back(Male_Female);
	}
	for(int i=0; i < minimum_plates; i++)
		PartsList.push_back(new SmartPlate());
}