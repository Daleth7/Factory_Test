/*                    Parts.h
  --------------------Synopsis--------------------
    This file declares various classes of robotic
  parts whose only member variables are their
  names, types of connection, and miscellaneous, 
  part-specific data variables.
  
  --------------------Warnings--------------------
    To add new classes of robotic parts requires--
  besides adding the class definition--that:
    1) the new class derive publicly from the
	  abstract class RobotPart and override its
	  virtual methods which are listed below.
    2) within PartType, a new enumeration value 
	  have the same name as the new class.
    3) within the Build(PartType) implementation,
      a new case in the switch-case statement 
	  return an allocated object of the new class.
	  
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
  
  ----------------------Notes---------------------
    The subclasses of RobotPart originally had no
  private members, which is why they are all
  structs.
*/ 
#ifndef PARTS_H
	#define PARTS_H
	
#include <string>

//PartType is a strongly typed enumeration that
//  represents each type of robotic part available.
//  All PartType values have the same name as the
//  type of robotic part.
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
	//Prototype RobotPart, so Build(PartType) is shown first
class RobotPart;
	//Build(PartType) returns a new part of type
	//  RobotPart* that points to a dynamically
	//  allocated space. The function's caller will be
	//  responsible for deallocation.
RobotPart* Build(PartType=PartType::None);
	//Create an abstract classification for robot parts
class RobotPart{
	public:
		using string=std::string;
	//RobotPart::Connection_t is an enumeration
	//  that represents the different types of
    //  connections "linking" parts together.
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
			//Execute machine instructions in part's chip
		virtual void Execute() = 0;
			//Make virtual to avoid problems
		virtual ~RobotPart();
	protected:
			//Initialize name of part and its connection type
		RobotPart(string, Connection_t=Independent);
	private:
		Connection_t __Connection;
		string Name__;
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
#include <vector>
struct Microcontroller: public RobotPart{
	Microcontroller();
	void Execute();
	void _Abort();
	private:
		std::vector<unsigned short> __data__;
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

#endif //end PARTS_H