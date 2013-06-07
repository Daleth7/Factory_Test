#include "Extensions.h"
#include "BotTemplate.h"

#include <iterator>
using std::make_move_iterator;
using std::begin;
using std::end;

Robot* Assemble(RobotTemplate choice){
	auto RE_Build = [](ExtensionType new_etype=ExtensionType::None)
		{return unique_ptr<RobotExtension>(Build(new_etype));};
	vector<unique_ptr<RobotExtension>> toreturn;
	switch(choice){
		case RobotTemplate::Basic:
//			toreturn.push_back(RE_Build(ExtensionType::Frame));
/*			toreturn.push_back(RE_Build(ExtensionType::Chassis));
			toreturn.push_back(RE_Build(ExtensionType::BRAIN));
			toreturn.push_back(RE_Build(ExtensionType::SensorModule));
			toreturn.push_back(RE_Build(ExtensionType::DrillArm));
			toreturn.push_back(RE_Build(ExtensionType::GrabbingArm));
			toreturn.push_back(RE_Build(ExtensionType::GrabbingArm));
			toreturn.push_back(RE_Build(ExtensionType::DriverWheel));
			toreturn.push_back(RE_Build(ExtensionType::DriverWheel));
			toreturn.push_back(RE_Build(ExtensionType::DriverWheel));
			toreturn.push_back(RE_Build(ExtensionType::DriverWheel));
*/			break;
/*			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::DrillArm),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build()
			});
		case RobotTemplate::Driller:
			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::DrillArm),
				RE_Build(ExtensionType::DrillArm),
				RE_Build(ExtensionType::DrillArm),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel)
			});
		case RobotTemplate::Medusa:
			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel)
			});
		case RobotTemplate::SuperComputer:
			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::SensorModule)
			});
		case RobotTemplate::Armadillo:
			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::Chassis),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::GrabbingArm),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel)
			});
		case RobotTemplate::Speedy:
			return new Robot({
				RE_Build(ExtensionType::Frame),
				RE_Build(ExtensionType::BRAIN),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::SensorModule),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::DriverWheel),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint),
				RE_Build(ExtensionType::Joint)
			});
*/		default:	return new Robot();
	}
}/*
Robot::Robot(const vector<unique_ptr<RobotExtension>>& newextensions){
	if(newextensions.size()>0)	__extensions = newextensions;
	else{
		for(size_t i=0; i<7; ++i)
			__extensions.push_back(unique_ptr<RobotExtension>(Build()));
	}
}*/
void Robot::Execute(){
	for(auto iter = __extensions.begin(); iter != __extensions.end(); ++iter)
		(*iter)->Execute();
}
