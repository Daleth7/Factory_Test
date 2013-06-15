/*                          BotTemplate.cpp
  ------------------------------Synopsis------------------------------
    This file defines the functions declared in BotTemplate.h. In each
  of the defined constructors, there is a string literal.
  
  ------------------------------Warnings------------------------------
	The Assemble(RobotTemplate) and Assemble(RobotTemplate,_RE_vec&) 
  functions returns raw pointers to dynamically allocated objects. The
  caller of these functions will be responsible for deallocating the
  memory.

  -------------------------Included Libraries-------------------------
    <string> has been included for std::string to hold the new "names"
  of the robotic extensions.
  
  ----------------------------Type Aliases----------------------------
    The following aliases reside under the Bot_Types namespace from
  BotTemplate.h.
    std::string has been aliased as _string.
    std::vector<RobotExtensions*> has been aliased as _vec_REptr.
    std::vector<RobotExtensions> has been aliased as _RE_vec.
  
  -------------------------------Notes--------------------------------
    Because this is just a Abstract Factory and Factory test, no focus
  is given on the specific execution procedures in Execute().
*/
#include "Extensions.h"
#include "BotTemplate.h"

using namespace Bot_Types;

Robot* Assemble(RobotTemplate choice){
	_vec_REptr catalyst;
	_string newname;
	switch(choice){
		case RobotTemplate::Basic:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::DrillArm),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::None)
			};
			newname = "Basic";
			break;
		case RobotTemplate::Driller:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::DrillArm),
				Build(ExtensionType::DrillArm),
				Build(ExtensionType::DrillArm),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel)
			};
			newname = "Driller";
			break;
		case RobotTemplate::Medusa:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::Frame),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel)
			};
			newname = "Medusa";
			break;
		case RobotTemplate::SuperComputer:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::SensorModule)
			};
			newname = "Super Computer";
			break;
		case RobotTemplate::Armadillo:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::Frame),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::Chassis),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::GrabbingArm),
				Build(ExtensionType::Joint),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel)
			};
			newname = "Armadillo";
			break;
		case RobotTemplate::Speedy:
			catalyst = {
				Build(ExtensionType::Frame),
				Build(ExtensionType::BRAIN),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::SensorModule),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::Joint),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel),
				Build(ExtensionType::DriverWheel)
			};
			newname = "Speedy";
			break;
		default:	return new Robot("Default");
	}
	return new Robot(catalyst,newname);
}
Robot::Robot(_string newname):
	__Extensions({
		Build(ExtensionType::None),
		Build(ExtensionType::None),
		Build(ExtensionType::None),
		Build(ExtensionType::None),
		Build(ExtensionType::None),
		Build(ExtensionType::None),
		Build(ExtensionType::None)
	}),
	__Name(newname)
{}
Robot::Robot(_RE_vec& newextensions,_string newname):
	__Name(newname)
{
	for(
		auto iter = newextensions.begin(); 
		iter != newextensions.end(); 
		++iter
	) __Extensions.push_back(&(*iter));
}
Robot::Robot(const _vec_REptr& newextensions,_string newname):
	__Extensions({newextensions}),
	__Name(newname)
{}
Robot::~Robot(){
	for(
		auto iter = __Extensions.begin(); 
		iter != __Extensions.end(); 
		++iter
	){
		delete (*iter);
		(*iter) = nullptr;
	}
}
void Robot::Execute(){
	for(
		auto iter = __Extensions.begin(); 
		iter != __Extensions.end(); 
		++iter
	) (*iter)->Execute();
}
_string Robot::Name()const
	{return __Name;}
