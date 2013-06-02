#ifndef EXTENSIONS_H
	#define EXTENSIONS_H

#include "Parts.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

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

class RobotExtensions{
	public:
		virtual void CreateDefault() = 0;
		virtual void Execute() = 0;
		vector<RobotPart> PartsList()const;
		vector<RobotPart::Connection_t> LinkList()const;
		string Name()const;
		void Attach(const vector<RobotPart>&);
			//Call CreateDefault and AddtoPartsList
		explicit RobotExtensions();
		virtual ~RobotExtensions();
	protected:
			//Protect to disallow random naming of parts
		RobotExtensions(string);
		vector<RobotPart> PartsList__;
		vector<RobotPart::Connection_t> Link__;
		string RE_Name__;
			//For use in overridden CreateDefault() calls
		void AppendPart(PartType=PartType::None,const int=0);
		void AppendLink(
			RobotPart::Connection_t=RobotPart::Connection_t::None,
			const int=0
		);
			//For use in overriden Execute() calls
		void ExecuteAll();
};

RobotExtensions* Build(
	ExtensionType=ExtensionType::None,
	const vector<RobotPart>& ={}
);

class Frame: public RobotExtensions{
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
class Chassis: public RobotExtensions{
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
class SensorModule: public RobotExtensions{
	public:
		SensorModule(const vector<RobotPart>& = {});
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
class DrillArm: public RobotExtensions{
	public:
		DrillArm(const vector<RobotPart>& = {});
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
class GrabbingArm: public RobotExtensions{
	public:
		GrabbingArm(const vector<RobotPart>& = {});
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
class Joint: public RobotExtensions{
	public:
		Joint(const vector<RobotPart>& = {});
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
class DriverWheel: public RobotExtensions{
	public:
		DriverWheel(const vector<RobotPart>& = {});
		void CreateDefault();
		void Execute();
	private:
		static const int
			minimum_bars=2,
			minimum_servos=1,
			minimum_wire=1
		;
};
class BRAIN: public RobotExtensions{
	public:
		BRAIN(const vector<RobotPart>& = {});
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
