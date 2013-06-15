/*                            Extensions.h
  ------------------------------Synopsis------------------------------
    This file defines the various robot extensions that are made of 
  various robot parts. In this file is a factory method called 
  CreateDefault().

  ------------------------------Warnings------------------------------
    To add new classes of robotic extensions requires--besides adding
  the class definition--that:
    1) the new class derive publicly from the abstract class
	  RobotExtension and override its virtual methods which are listed
	  below.
    2) within ExtensionType, a new enumeration value have the same
	  name as the new class.
    3) within the Build(ExtensionType) implementation, a new case in
	  the switch-case statement return an allocated object of the new
	  class.

	The Build(ExtensionType) and Build(ExtensionType,_RP_vec&) 
  functions returns raw pointers to dynamically allocated objects.
  The caller of these functions will be responsible for deallocating
  the memory.

  -------------------------Included Libraries-------------------------
    <string> has been included for std::string, which is used to hold
  the "names" of the robotic extensions.
    <vector> has been included for std::vector, which is used in
  RobotExtension to hold the "robot parts."

  ----------------------------Type Aliases----------------------------
    The following aliases reside under the RE_Types namespace.
    std::string has been aliased as _string.
    std::vector<RobotPart*> has been aliased as _vec_RPptr.
    std::vector<const RobotPart*> has been aliased as _vec_Con_RPptr.
    std::vector<RobotPart> has been aliased as _RP_vec.
    std::vector<RobotPart::Connection_t> has been aliased as 
  _RP_Con_vec.

  -------------------------------Notes--------------------------------
    Because this is just a Abstract Factory and Factory test, no focus
  is given on the Execute() and ExecuteAll() methods.
  
    Unfortunately, a conatiner of raw pointers is used because: 
  1) some kind of pointer is needed as these point to various class
  derivations; 2) smart pointers are resulting in too many head-aches
  like dangling pointers and deleted copy constructors with unique_ptr.
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
RobotExtension* Build(
	ExtensionType=ExtensionType::None
);
namespace RE_Types{
	using _string         = std::string;
	using _vec_RPptr      = std::vector<RobotPart*>;
	using _vec_Con_RPptr  = std::vector<const RobotPart*>;
	using _RP_vec         = std::vector<RobotPart>;
	using _RP_Con_vec     = std::vector<RobotPart::Connection_t>;
};
	//Specialization for adding additional
	//  parts along with a basic template
RobotExtension* Build(ExtensionType,RE_Types::_RP_vec&);
	//Cannot figure how to keep this
	//   inside the class
class RobotExtension{
	public:
	//Add the parts specific to each
	//   subclass to the PartsList__
	//   container
		virtual void CreateDefault() = 0;
	//Calls ExecuteAll() and specific
	//  instructions
		virtual void Execute() = 0;
		RE_Types::_vec_Con_RPptr PartsList()const;
		RE_Types::_RP_Con_vec LinkList()const;
		RE_Types::_string Name()const;
	//Don't use const, so iterator can be
	//   used instead of const_iterator
		void Attach(RE_Types::_RP_vec&);
		explicit RobotExtension();
		virtual ~RobotExtension();
	protected:
	//Helper functions
	//Protect to disallow random naming
		RobotExtension(RE_Types::_string);
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
	//Member variables
		RE_Types::_vec_RPptr   PartsList__;
		RE_Types::_RP_Con_vec  Link__;
		RE_Types::_string      RE_Name__;
};
	//All subsequent classes have constructors
	//   that only take references instead of
	//   const because they call
	//   RobotExtension::Attach, which does not
	//   take a constant reference
class Frame: public RobotExtension{
	public:
		Frame();
		Frame(RE_Types::_RP_vec&);
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
		Chassis();
		Chassis(RE_Types::_RP_vec&);
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
		RE_Types::_string __message;
};
class SensorModule: public RobotExtension{
	public:
		SensorModule();
		SensorModule(RE_Types::_RP_vec&);
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
		DrillArm();
		DrillArm(RE_Types::_RP_vec&);
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
		GrabbingArm();
		GrabbingArm(RE_Types::_RP_vec&);
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
		Joint();
		Joint(RE_Types::_RP_vec&);
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
		DriverWheel();
		DriverWheel(RE_Types::_RP_vec&);
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
		BRAIN();
		BRAIN(RE_Types::_RP_vec&);
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
