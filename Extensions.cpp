#include "Extensions.h"
#include "Parts.h"
	
#include <list>
#include <string>
#include <memory>

using std::list;
using std::string;
using std::unique_ptr;

RobotExtensions::RobotExtensions():
	RE_Name("HUB")
{
	PartsList__.pushback(new HUBBlock());
	Link__.push_back(RobotPart::Wire);
	Link__.push_back(RobotPart::Snap);
	Link__.push_back(RobotPart::Gear);
	Link__.push_back(RobotPart::Male_Female);
}
RobotExtensions::~RobotExtensions(){}
string RobotExtensions::Name()const{return RE_Name__;}
void RobotExtensions::Attach(const list<unique_ptr<RobotPart>>& newparts){
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
void RobotExtensions::AppendPart(PartType newtype,const int max){
	switch(newtype){
		case PartType::Claw:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Claw());
			break;
		case PartType::Drill:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Drill());
			break;
		case PartType::SmartPlate:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new SmartPlate());
			break;
		case PartType::Motor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Motor());
			break;
		case PartType::Servo:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Servo());
			break;
		case PartType::UltrasonicSensor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new UltrasonicSensor());
			break;
		case PartType::LightSensor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new LightSensor());
			break;
		case PartType::Monitor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Monitor());
			break;
		case PartType::Antenna:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Antenna());
			break;
		case PartType::Microcontroller:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new Microcontroller());
			break;
		default:
			for(int i=0; i<max; ++i)	PartsList__.push_back(new HUBBlock());
			break;
	}
}
inline void RobotExtensions::AppendLink(RobotPart::Connection_t newcon, const int max){
	for(int i=0; i<max; ++i)	Link__.push_back(newcon);
}
inline void RobotExtensions::ExecuteAll(){
	for(auto iter = PartsList__.begin(); iter != PartsList__.end(); ++iter)	(*iter)->Execute();
}

RobotExtensions* RobotExtensions(ExtensionType Etype, const list<unique_ptr<RobotPart>>& new_parts){
	switch(Etype){
		case ExtensionType::Frame:        return new Frame(new_parts);         break;
		case ExtensionType::Chassis:      return new Chassis(new_parts);       break;
		case ExtensionType::SensorModule: return new SensorModule(new_parts);  break;
		case ExtensionType::DrillArm:     return new DrillArm(new_parts);      break;
		case ExtensionType::GrabbingArm:  return new GrabbingArm(new_parts);   break;
		case ExtensionType::Joint:        return new Joint(new_parts);         break;
		case ExtensionType::DriverWheel:  return new DriverWheel(new_parts);   break;
		default:                          return new RobotExtension();         break;
	}
}

Frame::Frame(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Frame")
{
	CreateDefault();
	Attach(newparts);
}
Frame::~Frame(){}
void Frame::CreateDefault(){
	AppendPart(PartType::SmartBar,minimum_bars_need);
	AppendLink(RobotPart::Male_Female,minimum_mf);
	AppendLink(RobotPart::Snap,minimum_snap);
}
void Frame::Execute(){try{ExecuteAll();}catch(...){}}

Chassis::Chassis(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Chassis")
{
	CreateDefault();
	Attach(newparts);
}
Chassis::~Chassis(){}
void Chassis::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates_needed);
	AppendPart(PartType::SmartBar,minimum_bars_need);
	AppendPart(PartType::Monitor,minimum_monitors_need);
	AppendLink(RobotPart::Snap,minimum_snap);
	AppendLink(RobotPart::Wire,minimum_wire);
}
void Chassis::Execute(){
	auto end = PartsList__.begin(),iter = PartsList__.begin();
	advance(end,minimum_plates_needed+minimum_bars_need+minimum_monitors_need+1);
	advance(iter,minimum_plates_needed+minimum_bars_need);
	const auto itercopy=iter;
	try{
		ExecuteAll();
		for(; iter != end; ++iter)
			(*iter)->Print("Status: Good",true);
	}catch(const char* emsg){
		iter = itercopy
		for(; iter != end; ++iter){
			(*iter)->Execute();
			(*iter)->Print("Status: BAD\n"+string(emsg),true);
		}
	}catch(...){}
}

SensorModule::SensorModule(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Sensor Module")
{
	CreateDefault();
	Attach(newparts);
}
SensorModule::~SensorModule(){}
void SensorModule::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Servo,minimum_servos);
	AppendPart(PartType::LightSensor,minimum_lsensors);
	AppendPart(PartType::UltrasonicSensor,minimum_ussensors);
	AppendPart(PartType::Microcontroller,minimum_mcontroller);
	AppendPart(PartType::Monitor,minimum_monitor);
	AppendLink(RobotPart::Male_Female,minimum_mf);
	AppendLink(RobotPart::Gear,minimum_gear);
}
void SensorModule::Execute(){
	auto iter=PartsList__.begin(), end=PartsList__.begin();
	advance(
		iter,
		minimum_plates+minimum_servos
		+minimum_lsensors+minimum_ussensors+minimum_mcontroller
	);
	advance(
		end,
		minimum_plates+minimum_servos+minimum_lsensors
		+minimum_ussensors+minimum_mcontroller+minimum_monitor
	);
	const auto itercopy = iter;
	try{
		ExecuteAll();
		for(; iter != end; ++iter)
			(*iter)->Print("Status: Good",true);
	}catch(const char* emsg){
		iter = itercopy
		for(; iter != end; ++iter){
			(*iter)->Execute();
			(*iter)->Print("Status: BAD\n"+string(emsg),true);
		}
	}catch(...){}
}

DrillArm::DrillArm(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Drill Arm")
{
	CreateDefault();
	Attach(newparts);
}
DrillArm::~DrillArm(){}
void DrillArm::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Drill,minimum_drills);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void DrillArm::Execute(){try{ExecuteAll();}catch(...){}}

GrabbingArm::GrabbingArm(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Grabbing Arm")
{
	CreateDefault();
	Attach(newparts);
}
GrabbingArm::~GrabbingArm(){}
void GrabbingArm::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Drill,minimum_claws);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void GrabbingArm::Execute(){try{ExecuteAll();}catch(...){}}

Joint::Joint(const list<unique_ptr<RobotPart>>& newparts):	
	RE_Name("Joint")
{
	CreateDefault();
	Attach(newparts);
}
Joint::~Joint(){}
void Joint::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendPart(PartType::Motor,minimum_motors);
	AppendPart(PartType::Servo,minimum_servos);
	AppendLink(RobotPart::Wire,minimum_wire);
}
void Joint::Execute(){try{ExecuteAll();}catch(...){}}

DriverWheel::DriverWheel(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("Driver Wheel")
{
	CreateDefault();
	Attach(newparts);
}
DriverWheel::~DriverWheel(){}
void DriverWheel::CreateDefault(){
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendPart(PartType::Wheel,minimum_wheels);
	AppendPart(PartType::Servo,minimum_servos);
	AppendLink(RobotPart::Wire,minimum_wire);
}
void DriverWheel::Execute(){try{ExecuteAll();}catch(...){}}

BRAIN::BRAIN(const list<unique_ptr<RobotPart>>& newparts):
	RE_Name("BRAIN")
{
	CreateDefault();
	Attach(newparts);
}
BRAIN::~BRAIN(){}
void BRAIN::CreateDefault(){
	AppendPart(PartType::Microcontroller,minimum_mcontroller);
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void BRAIN::Execute(){ExecuteAll();}