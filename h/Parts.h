/*                    Parts.h
  --------------------Synopsis--------------------
    This file declares various classes of robotic
  parts whose only member variables are their
  names, types of connection, and miscellaneous, 
  part-specific data variables.
  
  --------------------Warnings--------------------
    To add new classes of robotic parts requires--
  besides adding the class declaration--that:
    1) the new class derive publicly from the
	  abstract class RobotPart and override its
	  virtual methods which are listed below in 
	  the Classes section.
    2) within PartType, a new enumeration value 
	  whose name be the same as the new class.
    3) within Build(PartType), a new case in the
      switch-case statement return an allocated
	  object of the new class.
    4) the new class be documented in the Classes
      section below.
	  
	The Build(PartType) function returns a raw
  pointer to a dynamically allocated object. The
  caller of this function will be responsible for
  deallocating the memory.

  ---------------Included Libraries---------------
    <string> has been included for std::string,
  which is used to hold the "names" of the robotic
  parts.
    <vector> has been included for std::vector,
  which is used specifically in Microcontroller
  for holding its "data."
  
  ------------------Type Aliases------------------
    std::string and std::vector have been aliased
  with the using keyword so that "string" and 
  "vector" may be used.
  
  ------------------Enumerations------------------
    PartType is a strongly typed enumeration that
  represents each type of robotic part available.
  All PartType values have the same name as the
  type of robotic part.
  
    RobotPart::Connection_t is an enumeration
  within the abstract class RobotPart that
  represents the different types of connections
  that "links" parts together. Available
  RobotPart::Connection_t values are:
    -Connection_t::Wire
    -Connection_t::Snap
    -Connection_t::Gear
    -Connection_t::Male_Female
    -Connection_t::Independent
    -Connection_t::None
  
  ----------------Global Functions----------------
    Build(PartType) returns a new part of type
  RobotPart* that points to a dynamically
  allocated space. The function's caller will be
  responsible for deallocating the allocated 
  space. This function has the default value
  PartType::None.
  
  --------------------Classes---------------------
*/ 
#ifndef PARTS_H
	#define PARTS_H
	
#include <string>
#include <vector>
	//All measurements follow the metric system kms
using std::string;
using std::vector;

class RobotPart;

enum class PartType{
	Claw,
	Drill,
	SmartPlate,
	SmartBar,
	Motor,
	Servo,
	UltrasonicSensor,
	LightSensor,
	Monitor,
	Antenna,
	HUBBlock,
	Microcontroller,
	None
};

RobotPart* Build(PartType=PartType::None);
	//Create an abstract classification for robot parts
class RobotPart{
	public:
		//Arbitrary naming system for types of connections
		enum Connection_t{
			Wire,
			Snap,
			Gear,
			Male_Female,
			Independent,
			None
		};
			//Return type of connection for comparison
		Connection_t ConnectionType()const;
		const string& Name()const;
			//Execute machine instructions in part's controller
		virtual void Execute() = 0;
			//Make virtual to avoid problems
		virtual ~RobotPart();
	protected:
		Connection_t __Connection;
		string Name__;
			//Initialize name of part and its connection type
		RobotPart(string, Connection_t=Independent);
};
	//Various parts
struct Claw: public RobotPart{
	Claw();
	void Execute();
};
struct Drill: public RobotPart{
	Drill();
	void Execute();
	void Stop();
	private:
		double __hardness_rating__;
};
struct SmartPlate: public RobotPart{
	SmartPlate();
	void Execute();
	double CurrentTemp()const;
	double HardRate()const;
	double HeatRate()const;
	double StiffRate()const;
	private:
		double
			__hardness_rating__,
			__stiffness__,
			__heat_rating__,
			__current_temperature__
		;
};
struct SmartBar: public RobotPart{
	SmartBar();
	void Execute();
	double CurrentTemp()const;
	double HardRate()const;
	double HeatRate()const;
	double StiffRate()const;
	double Deflection()const;
		double
			__hardness_rating__,
			__stiffness__,
			__heat_rating__,
			__current_temperature__,
			__deflection__
		;
};
struct Motor: public RobotPart{
	Motor();
	void Execute();
	void Stop();
};
struct Servo: public RobotPart{
	Servo();
	void Execute();
	void Stop();
};
struct UltrasonicSensor: public RobotPart{
	UltrasonicSensor();
	void Execute();
	double Read()const;
	private:
		double __echo_travel__;
};
struct LightSensor: public RobotPart{
	LightSensor();
	void Execute();
	double Read()const;
	private:
		double __lux__;
};
struct Monitor: public RobotPart{
	Monitor();
	void Execute();
	void Print(string,bool=false);
};
struct Antenna: public RobotPart{
	Antenna();
	void Execute();
	long unsigned int Read()const;
	double frequency;
	private:
			//data in bitarray recieved from signal
		long unsigned int __data___;
};
struct HUBBlock: public RobotPart{
	HUBBlock();
	void Execute();
};
struct Microcontroller: public RobotPart{
	Microcontroller();
	void Execute();
	void _Abort();
	private:
		vector<unsigned short> __data__;
		template<typename T>
			struct DataManager{
				T __idata__;
				void Input(T newdata){
					/*Do stuff*/
				}
				T Output()const{
					/*do w/e stuff*/
					return __idata__;
				}
				/*Functions for managing the data*/
		};
};

#endif