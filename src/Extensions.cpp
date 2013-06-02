#include "Parts.h"
#include "Extensions.h"

RobotExtensions::RobotExtensions():
	RE_Name__("HUB")
{
	PartsList__.push_back(Build(PartType::HUBBlock));
	Link__.push_back(RobotPart::Wire);
	Link__.push_back(RobotPart::Snap);
	Link__.push_back(RobotPart::Gear);
	Link__.push_back(RobotPart::Male_Female);
}
RobotExtensions::RobotExtensions(string newname):
	RE_Name__(newname)
{}
RobotExtensions::~RobotExtensions(){}
string RobotExtensions::Name()const{return RE_Name__;}
vector<Botpart> RobotExtensions::PartsList()const{}//return PartsList__;}
vector<RobotPart::Connection_t> RobotExtensions::LinkList()const{return Link__;}
void RobotExtensions::Attach(const vector<Botpart>& newparts){
	if(newparts.size() < 1)	return;
	PartsList__.resize(PartsList__.size() + newparts.size());
	for(auto part___ = newparts.begin(); part___ != newparts.end(); part___++){
		if(Link__.empty())	break;
		for(auto alink__ = Link__.begin(); alink__ != Link__.end(); alink__++){
			if((*alink__) == (*part___)->ConnectionType()){
				PartsList__.push_back(*part___);
				Link__.erase(alink__);
				break;
			}
		}
	}
}
void RobotExtensions::AppendPart(PartType newtype,const int max){
	switch(newtype){
		case PartType::Claw:
			for(int i=0; i<max; ++i){
				newpart = Build(PartType::Claw);
				PartsList__.push_back(Botpart(newpart));
			}
			break;
		case PartType::Drill:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Drill));
			break;
		case PartType::SmartPlate:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::SmartPlate));
			break;
		case PartType::Motor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Motor));
			break;
		case PartType::Servo:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Servo));
			break;
		case PartType::UltrasonicSensor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::UltrasonicSensor));
			break;
		case PartType::LightSensor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::LightSensor));
			break;
		case PartType::Monitor:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Monitor));
			break;
		case PartType::Antenna:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Antenna));
			break;
		case PartType::Microcontroller:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::Microcontroller));
			break;
		default:
			for(int i=0; i<max; ++i)	PartsList__.push_back(Build(PartType::HUBBlock));
			break;
	}
}
inline void RobotExtensions::AppendLink(RobotPart::Connection_t newcon, const int max){
	for(int i=0; i<max; ++i)	Link__.push_back(newcon);
}
inline void RobotExtensions::ExecuteAll(){
	for(auto iter = PartsList__.begin(); iter != PartsList__.end(); ++iter)	(*iter)->Execute();
}

RobotExtensions* Build(ExtensionType Etype, const vector<Botpart>& new_parts){
	switch(Etype){
		case ExtensionType::Frame:        return new Frame(new_parts);
		case ExtensionType::Chassis:      return new Chassis(new_parts);
		case ExtensionType::SensorModule: return new SensorModule(new_parts);
		case ExtensionType::DrillArm:     return new DrillArm(new_parts);
		case ExtensionType::GrabbingArm:  return new GrabbingArm(new_parts);
		case ExtensionType::Joint:        return new Joint(new_parts);
		case ExtensionType::DriverWheel:  return new DriverWheel(new_parts);
		default:                          return nullptr;
	}
}

Frame::Frame(const vector<Botpart>& newparts):
	RobotExtensions("Frame")
{
	CreateDefault();
	Attach(newparts);
}
void Frame::CreateDefault(){
	AppendPart(PartType::SmartBar,minimum_bars_need);
	AppendLink(RobotPart::Male_Female,minimum_mf);
	AppendLink(RobotPart::Snap,minimum_snap);
}
void Frame::Execute(){try{ExecuteAll();}catch(...){}}

Chassis::Chassis(const vector<Botpart>& newparts):
	RobotExtensions("Chassis")
{
	CreateDefault();
	Attach(newparts);
}
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
	try{ExecuteAll();}catch(...){}
}

SensorModule::SensorModule(const vector<Botpart>& newparts):
	RobotExtensions("Sensor Module")
{
	CreateDefault();
	Attach(newparts);
}
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
	try{ExecuteAll();}catch(...){}
}

DrillArm::DrillArm(const vector<Botpart>& newparts):
	RobotExtensions("Drill Arm")
{
	CreateDefault();
	Attach(newparts);
}
void DrillArm::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Drill,minimum_drills);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void DrillArm::Execute(){try{ExecuteAll();}catch(...){}}

GrabbingArm::GrabbingArm(const vector<Botpart>& newparts):
	RobotExtensions("Grabbing Arm")
{
	CreateDefault();
	Attach(newparts);
}
void GrabbingArm::CreateDefault(){
//	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Claw,minimum_claws);
//	AppendPart(PartType::SmartBar,minimum_bars);
//	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void GrabbingArm::Execute(){try{ExecuteAll();}catch(...){}}

Joint::Joint(const vector<Botpart>& newparts):
	RobotExtensions("Joint")
{
	CreateDefault();
	Attach(newparts);
}
void Joint::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendPart(PartType::Motor,minimum_motors);
	AppendPart(PartType::Servo,minimum_servos);
	AppendLink(RobotPart::Wire,minimum_wire);
}
void Joint::Execute(){try{ExecuteAll();}catch(...){}}

DriverWheel::DriverWheel(const vector<Botpart>& newparts):
	RobotExtensions("Driver Wheel")
{
	CreateDefault();
	Attach(newparts);
}
void DriverWheel::CreateDefault(){
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendPart(PartType::Servo,minimum_servos);
	AppendLink(RobotPart::Wire,minimum_wire);
}
void DriverWheel::Execute(){try{ExecuteAll();}catch(...){}}

BRAIN::BRAIN(const vector<Botpart>& newparts):
	RobotExtensions("BRAIN")
{
	CreateDefault();
	Attach(newparts);
}
void BRAIN::CreateDefault(){
	AppendPart(PartType::Microcontroller,minimum_mcontroller);
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void BRAIN::Execute(){ExecuteAll();}
