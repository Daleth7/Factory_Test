#include "Extensions.h"
#include "BotTemplate.h"

#include <list>
#include <memory>

using std::list;
using std::unique_ptr;

Robot* Assemble(RobotTemplate choice){
	switch(choice){
		case RobotTemplate::Basic:
			return new Robot({
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
					Build(ExtensionType::DriverWheel)
				});
		case RobotTemplate::Driller:
			return new Robot({	
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
				});
		case RobotTemplate::Medusa:
			return new Robot({	
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
				});
		case RobotTemplate::SuperComputer:
			return new Robot({
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
				});
		case RobotTemplate::Armadillo:
			return new Robot({	
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
				});
		case RobotTemplate::Speedy:
			return new Robot({	
					Build(ExtensionType::Frame),
					Build(ExtensionType::BRAIN), 
					Build(ExtensionType::SensorModule),
					Build(ExtensionType::SensorModule),
					Build(ExtensionType::DriverWheel), 
					Build(ExtensionType::DriverWheel), 
					Build(ExtensionType::DriverWheel),
					Build(ExtensionType::DriverWheel),
					Build(ExtensionType::Joint),
					Build(ExtensionType::Joint),
					Build(ExtensionType::Joint),
					Build(ExtensionType::Joint)
				});
		default:	return new Robot();
	}
}
Robot::Robot():
	__extensions({Build(), Build(), Build(), Build(), Build(), Build(), Build()})
{}
Robot::Robot(const list<unique_ptr<RobotExtensions>>& newextensions):
	__extensions(newextensions)
{}
void Robot::Execute(){
	for(auto iter = __extensions.begin(); iter != __extensions.end(); ++iter)
		(*iter)->Execute();
}