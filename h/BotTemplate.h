/*                           BotTemplate.h
  ------------------------------Synopsis------------------------------
    This file defines a simple Robot class with a couple abstract
  factory methods for the end user.

  ------------------------------Warnings------------------------------
	The Assemble(RobotTemplate) and Assemble(RobotTemplate,_RE_vec&) 
  functions returns raw pointers to dynamically allocated objects. 
  The caller of these functions will be responsible for deallocating
  the memory.

  -------------------------Included Libraries-------------------------
    <string> has been included for std::string, which is used to hold 
  the "names" of the robotic extensions.
    <vector> has been included for std::vector, which is used in Robot
  to hold the "robot extensions."

  ----------------------------Type Aliases----------------------------
    The following aliases reside under the Bot_Types namespace.
    std::string has been aliased as _string.
    std::vector<RobotExtensions*> has been aliased as _vec_REptr.
    std::vector<RobotExtensions> has been aliased as _RE_vec.

  -------------------------------Notes--------------------------------
    Because this is just a Abstract Factory and Factory test, no focus
  is given on the Execute() and ExecuteAll() methods.
  
    Unfortunately, a conatiner of raw pointers is used because: 
  1) some kind of pointer is needed as these point to various class
  derivations; 2) smart pointers are resulting in too many head-aches
  like dangling pointers and deleted copy constructors with unique_ptr.
*/
#ifndef BOTTEMPLATE_H
	#define BOTTEMPLATE_H


class RobotExtension;
	//RobotTemplate holds values that represent different combinations
	//   of robotic extensions and not variations of Robot.
enum class RobotTemplate{
	Basic,
	Driller,
	Medusa,
	SuperComputer,
	Armadillo,
	Speedy,
	None
};

#include <vector>
#include <string>
namespace Bot_Types{
   using _string    = std::string;
   using _RE_vec    = std::vector<RobotExtension>;
   using _vec_REptr = std::vector<RobotExtension*>;
};

class Robot;
Robot* Assemble(RobotTemplate=RobotTemplate::None);
Robot* Assemble(RobotTemplate,Bot_Types::_RE_vec&);
	//Don't go with an abstract superclass because there are no
	//   specific derivations;
class Robot{
	public:
		Robot(Bot_Types::_string="");
		Robot(Bot_Types::_RE_vec&,Bot_Types::_string="");
		Robot(const Bot_Types::_vec_REptr&,Bot_Types::_string="");
		~Robot();
		void Execute();
		Bot_Types::_string Name()const;
		//Allow this to be public because the robot's components
		//   should be interchangeable by the user.
		Bot_Types::_vec_REptr __Extensions;
	private:
		Bot_Types::_string    __Name;
};

#endif
