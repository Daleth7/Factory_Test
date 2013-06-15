/*                           Extensions.cpp
  ------------------------------Synopsis------------------------------
    This file defines the functions declared in Extensions.h. In each
  of the defined constructors, there is a string literal.

  ------------------------------Warnings------------------------------
	The Build(ExtensionType) and Build(ExtensionType,v_RP_vec&)
  functions returns raw pointers to dynamically allocated objects. The
  caller of these functions will be responsible for deallocating the
  memory.

  -------------------------Included Libraries-------------------------
    <string> has been included for std::string to hold the new "names"
  of the robotic extensions.

  ----------------------------Type Aliases----------------------------
    The following aliases reside under the RE_Types namespace from
  Extensions.h.
    std::string has been aliased as _string.
    std::vector<RobotPart*> has been aliased as _vec_RPptr.
    std::vector<const RobotPart*> has been aliased as _vec_Con_RPptr.
    std::vector<RobotPart> has been aliased as _RP_vec.
    std::vector<RobotPart::Connection_t> has been aliased as
  _RP_Con_vec.

  -------------------------------Notes--------------------------------
    Because this is just a Abstract Factory and Factory test, no focus
  is given on the specific execution procedures in Execute() and
  ExecuteAll().
*/
#include "Extensions.h"

RobotExtension* Build(ExtensionType Etype){
	switch(Etype){
		case ExtensionType::Frame:        return new Frame();
		case ExtensionType::Chassis:      return new Chassis();
		case ExtensionType::SensorModule: return new SensorModule();
		case ExtensionType::DrillArm:     return new DrillArm();
		case ExtensionType::GrabbingArm:  return new GrabbingArm();
		case ExtensionType::Joint:        return new Joint();
		case ExtensionType::DriverWheel:  return new DriverWheel();
		case ExtensionType::BRAIN:        return new BRAIN();
		default:                          return nullptr;
	}
}

using namespace RE_Types;

RobotExtension* Build(ExtensionType Etype, _RP_vec& new_parts){
	RobotExtension* toreturn = Build(Etype);
	toreturn->Attach(new_parts);
	return toreturn;
}
/*********************************************************************
                            RbotExtension
*********************************************************************/
RobotExtension::RobotExtension():
	RE_Name__("HUB")
{
	PartsList__.push_back(Build(PartType::HUBBlock));
	Link__.push_back(RobotPart::Wire);
	Link__.push_back(RobotPart::Snap);
	Link__.push_back(RobotPart::Gear);
	Link__.push_back(RobotPart::Male_Female);
}
RobotExtension::RobotExtension(_string newname):
	RE_Name__(newname)
{}
RobotExtension::~RobotExtension(){
	for(
		auto iter(PartsList__.begin());
		iter != PartsList__.end();
		++iter
	){
		delete (*iter);
		(*iter) = nullptr;
	}
}
_string RobotExtension::Name()const
	{return RE_Name__;}
_vec_Con_RPptr RobotExtension::PartsList()const{
	_vec_Con_RPptr toreturn;
	for(
		auto iter(PartsList__.begin());
		iter != PartsList__.end();
		++iter
	) toreturn.push_back(*iter);
	return toreturn;
}
_RP_Con_vec RobotExtension::LinkList()const
	{return Link__;}
void RobotExtension::Attach(_RP_vec& newparts){
	if(newparts.size() < 1)	return;
	PartsList__.resize(PartsList__.size() + newparts.size());
	for(
		_RP_vec::iterator part___ = newparts.begin();
		part___ != newparts.end();
		++part___
	){
	//Check for available links and the one that matches the new
	//   part's own
		if(Link__.empty())	break;
		for(
			auto alink__ = Link__.begin();
			alink__ != Link__.end();
			++alink__
		){
			if((*alink__) == part___->ConnectionType()){
				PartsList__.push_back(&*part___);
				Link__.erase(alink__);
				break;
			}
		}
	}
}
void RobotExtension::AppendPart(PartType newtype,const int max){
	switch(newtype){
		case PartType::Claw:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Claw));
			break;
		case PartType::Drill:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Drill));
			break;
		case PartType::SmartPlate:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::SmartPlate));
			break;
		case PartType::Motor:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Motor));
			break;
		case PartType::Servo:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Servo));
			break;
		case PartType::UltrasonicSensor:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(
					Build(PartType::UltrasonicSensor)
				);
			break;
		case PartType::LightSensor:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::LightSensor));
			break;
		case PartType::Monitor:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Monitor));
			break;
		case PartType::Antenna:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::Antenna));
			break;
		case PartType::Microcontroller:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(
					Build(PartType::Microcontroller)
				);
			break;
		default:
			for(int i=0; i<max; ++i)
				PartsList__.push_back(Build(PartType::HUBBlock));
			break;
	}
}
inline void RobotExtension::AppendLink(
	RobotPart::Connection_t newcon,
	const int max
){
	for(int i=0; i<max; ++i)	Link__.push_back(newcon);
}
inline void RobotExtension::ExecuteAll(){
	for(
		auto iter = PartsList__.begin();
		iter != PartsList__.end();
		++iter
	){
		if((*iter) != nullptr)
			(*iter)->Execute();
	}
}
/*********************************************************************
                               Frame
*********************************************************************/
Frame::Frame():
	RobotExtension("Frame")
{CreateDefault();}
Frame::Frame(_RP_vec& newparts):
	RobotExtension("Frame")
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
/*********************************************************************
                               Chassis
*********************************************************************/
Chassis::Chassis():
	RobotExtension("Chassis")
{CreateDefault();}
Chassis::Chassis(_RP_vec& newparts):
	RobotExtension("Chassis")
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
	advance(
		end,
		minimum_plates_needed+minimum_bars_need
			+minimum_monitors_need+1
	);
	advance(iter,minimum_plates_needed+minimum_bars_need);
	const auto itercopy=iter;
	try{ExecuteAll();}catch(...){}
}
/*********************************************************************
                            SensorModule
*********************************************************************/
SensorModule::SensorModule():
	RobotExtension("Sensor Module")
{CreateDefault();}
SensorModule::SensorModule(_RP_vec& newparts):
	RobotExtension("Sensor Module")
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
/*********************************************************************
                              DrillArm
*********************************************************************/
DrillArm::DrillArm():
	RobotExtension("Drill Arm")
{CreateDefault();}
DrillArm::DrillArm(_RP_vec& newparts):
	RobotExtension("Drill Arm")
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
/*********************************************************************
                              GrabbingArm
*********************************************************************/
GrabbingArm::GrabbingArm():
	RobotExtension("Grabbing Arm")
{CreateDefault();}
GrabbingArm::GrabbingArm(_RP_vec& newparts):
	RobotExtension("Grabbing Arm")
{
	CreateDefault();
	Attach(newparts);
}
void GrabbingArm::CreateDefault(){
	AppendPart(PartType::SmartPlate,minimum_plates);
	AppendPart(PartType::Claw,minimum_claws);
	AppendPart(PartType::SmartBar,minimum_bars);
	AppendLink(RobotPart::Male_Female,minimum_mf);
}
void GrabbingArm::Execute(){try{ExecuteAll();}catch(...){}}
/*********************************************************************
                               Joint
*********************************************************************/
Joint::Joint():
	RobotExtension("Joint")
{CreateDefault();}
Joint::Joint(_RP_vec& newparts):
	RobotExtension("Joint")
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
/*********************************************************************
                             DriverWheel
*********************************************************************/
DriverWheel::DriverWheel():
	RobotExtension("Driver Wheel")
{CreateDefault();}
DriverWheel::DriverWheel(_RP_vec& newparts):
	RobotExtension("Driver Wheel")
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
/*********************************************************************
                               BRAIN
*********************************************************************/
BRAIN::BRAIN():
	RobotExtension("BRAIN")
{CreateDefault();}
BRAIN::BRAIN(_RP_vec& newparts):
	RobotExtension("BRAIN")
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
