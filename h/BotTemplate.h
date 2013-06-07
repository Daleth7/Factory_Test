#ifndef BOTTEMPLATE_H
	#define BOTTEMPLATE_H

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class RobotExtension;

enum class RobotTemplate{
	Basic,
	Driller,
	Medusa,
	SuperComputer,
	Armadillo,
	Speedy,
	None
};
struct Robot{
//	Robot(const vector<unique_ptr<RobotExtension>>& ={});
	void Execute();
	vector<unique_ptr<RobotExtension>> __extensions;
};
Robot* Assemble(RobotTemplate=RobotTemplate::None);

#endif
