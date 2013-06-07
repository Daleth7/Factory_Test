/*                  Extensions.h
  --------------------Synopsis--------------------
    This file defines the various robot extensions
  that are made of various robot parts. In this
  file is a factory method called CreateDefault().
  
  --------------------Warnings--------------------
    To add new classes of robotic extensions 
  requires--besides adding the class definition--
  that:
    1) the new class derive publicly from the
	  abstract class RobotExtension and override 
	  its virtual methods which are listed below.
    2) within ExtensionType, a new enumeration 
	  value have the same name as the new class.
    3) within the Build(ExtensionType) 
	  implementation, a new case in the switch-
	  case statement return an allocated object 
	  of the new class.
	  
	The Build(ExtensionType) function returns a 
  raw pointer to a dynamically allocated object. 
  The caller of this function will be responsible
  for deallocating the memory.

  ---------------Included Libraries---------------
    <string> has been included for std::string,
  which is used to hold the "names" of the robotic
  extensions.
    <vector> has been included for std::vector,
  which is used in RobotExtension to hold the 
  "robot parts."
  
  ------------------Type Aliases------------------
    std::string and std::vector have been aliased
  with the using keyword so that "string" and 
  "vector" may be used.
  
  ----------------------Notes---------------------
    Because this is just a Abstract Factory and
  Factory test, no focus is given on the Execute()
  and ExecuteAll() methods.
*/
#ifndef EXTENSIONS_H
	#define EXTENSIONS_H

#include "Parts.h"

#include <vector>
#include <string>

enum class ExtensionType{
	Frame,
	Chassis,
	SensorModule,
	DrillArm,
	GrabbingArm,
	Joint,
	DriverWheel,
	BRAIN,
	None
};

class RobotExtension;
	//Build specific extensions based on type
	//  and appends any additional parts from
	//  second parameter
RobotExtension* Build(
	ExtensionType=ExtensionType::None,
	const std::vector<RobotPart>& ={}
);
	//Cannot figure how to keep this 
	//   inside the class
using std::vector;
class RobotExtension{
	public:
		using string=std::string;
			//Add the parts specific to each 
			//   subclass to the PartsList__
			//   container
		virtual void CreateDefault() = 0;
			//Calls ExecuteAll() and specific
			//  instructions
		virtual void Execute() = 0;
		vector<RobotPart> PartsList()const;
		vector<RobotPart::Connection_t> 
			LinkList()const;
		string Name()const;
		void Attach(const vector<RobotPart>&);
		explicit RobotExtension();
		virtual ~RobotExtension();
	protected:
			//Protect to disallow random naming
		RobotExtension(string);
			//For use in overridden CreateDefault()
			//   calls; takes in type of part and
			//   the number of that part to append.
		void AppendPart(
			PartType=PartType::None,
			const int=0
		);
			//Similar to above function but for 
			//   link types
		void AppendLink(
			RobotPart::Connection_t
				=RobotPart::Connection_t::None,
			const int=0
		);
			//For use in overriden Execute() calls
		void ExecuteAll();
	private:
		vector<RobotPart> PartsList__;
		vector<RobotPart::Connection_t> Link__;
		string RE_Name__;
};

class Frame: public RobotExtension{
	public:
		Frame(const vector<RobotPart>& = {});
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_bars_need = 10,
			minimum_mf=minimum_bars_need,
			minimum_snap=minimum_mf/2
		;
};
class Chassis: public RobotExtension{
	public:
		Chassis(const vector<RobotPart>& = {});
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_plates_needed=50,
			minimum_bars_need=7,
			minimum_monitors_need=3,
			minimum_snap=minimum_plates_needed,
			minimum_wire=minimum_plates_needed/2
		;
		string __message;
};
class SensorModule: public RobotExtension{
	public:
		SensorModule(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_plates=4,
			minimum_servos=1,
			minimum_lsensors=16,
			minimum_ussensors=4,
			minimum_mcontroller=2,
			minimum_monitor=1,
			minimum_mf=1,
			minimum_gear=1
		;
};
class DrillArm: public RobotExtension{
	public:
		DrillArm(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_drills=3,
			minimum_bars=2,
			minimum_plates=6,
			minimum_mf=1
		;
};
class GrabbingArm: public RobotExtension{
	public:
		GrabbingArm(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_claws=1,
			minimum_bars=2,
			minimum_plates=6,
			minimum_mf=1
		;
};
class Joint: public RobotExtension{
	public:
		Joint(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_plates=6,
			minimum_bars=2,
			minimum_motors=4,
			minimum_servos=4,
			minimum_wire=2
		;
};
class DriverWheel: public RobotExtension{
	public:
		DriverWheel(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_bars=2,
			minimum_servos=1,
			minimum_wire=1
		;
};
class BRAIN: public RobotExtension{
	public:
		BRAIN(
			const vector<RobotPart>& = {}
		);
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_mcontroller=4,
			minimum_plates=5,
			minimum_mf=minimum_mcontroller/2
		;
};

#endif
