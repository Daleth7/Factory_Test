#ifndef PARTS_H
	#define PARTS_H
	
#include <string>
#include <list>
	//All measurements follow the metric system kms
using std::string;
using std::list;
	//Create an abstract classification for robot parts
class RobotPart{
	public:
		//Arbitrary naming system for types of connections
		enum Connection_t{
			Wire,
			Snap,
			Gear,
			Male_Female,
			Independent
		};
			//Return type of connection for comparison
		virtual Connection_t ConnectionType()const;
		virtual const string& Name()const;
			//Execute machine instructions in part's controller
		virtual void Execute() = 0;
	protected:
		Connection_t __Connection;
		string Name__;
			//Initialize name of part and its connection type
		RobotPart(string, Connection_t=Independent);
			//Make virtual to avoid problems
		virtual ~RobotPart();
};
	//Various parts
struct Claw: public RobotPart{
	Claw();
	virtual ~Claw();
	virtual void Execute();
};
struct Drill: public RobotPart{
	Drill();
	virtual ~Drill();
	virtual void Execute();
	virtual void Stop();
	private:
		double __hardness_rating__;
};
struct SmartPlate: public RobotPart{
	Drill();
	virtual ~SmartPlate();
	virtual void Execute();
	virtual double CurrentTemp()const;
	virtual double HardRate()const;
	virtual double HeatRate()const;
	virtual double StiffRate()const;
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
	virtual ~SmartBar();
	virtual void Execute();
	virtual double CurrentTemp()const;
	virtual double HardRate()const;
	virtual double HeatRate()const;
	virtual double StiffRate()const;
	virtual double Deflection()const;
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
	virtual ~Motor();
	virtual void Execute();
	virtual void Stop();
};
struct Servo: public RobotPart{
	Servo();
	virtual ~Servo();
	virtual void Execute();
};
struct UltrasonicSensor: public RobotPart{
	UltrasonicSensor();
	virtual ~UltrasonicSensor();
	virtual void Execute();
	virtual double Read()const;
	private:
		double __echo_travel__;
};
struct LightSensor: public RobotPart{
	LightSensor();
	virtual ~LightSensor();
	virtual void Execute();
	virtual bool Read()const;
	private:
		double __lux__;
};
struct Monitor: public RobotPart{
	Monitor();
	virtual ~Monitor();
	virtual void Execute();
	virtual void Print(string,bool=false);
};
struct Antenna: public RobotPart{
	Antenna();
	virtual ~Antenna();
	virtual void Execute();
	virtual long unsigned int Read()const;
	double frequency;
	private:
			//data in bitarray recieved from signal
		long unsigned int __data___;
};
struct HUBBlock: public RobotPart{
	HUBBlock();
	virtual ~HUBBlock();
	virtual void Execute();
};
struct Microcontroller: public RobotPart{
	Microcontroller();
	virtual ~Microcontroller();
	virtual void Execute();
	virtual void _Abort();
	private:
		list<unsigned short> __data__;
		template<typename T>
			struct DataManager{
				T __idata__;
					template<typename T>
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