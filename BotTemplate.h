#ifndef BOTTEMPLATE_H
	#define BOTTEMPLATE_H

#include <list>
#include <memory>

using std::list;
using std::unique_ptr;

class RobotExtensions;

enum class RobotTemplate{
	Basic,
	Driller,
	Medusa,
	SuperComputer,
	Armadillo,
	Speedy,
	None
};
Robot* Assemble(RobotTemplate=RobotTemplate::None);
struct Robot{
	Robot();
	Robot(const list<unique_ptr<RobotExtensions>>&={});
	void Execute();
	list<unique_ptr<RobotExtensions>> __extensions;
};

#endif