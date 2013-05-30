#ifndef EXTENSIONS_H
	#define EXTENSIONS_H
	
#include <list>
#include <string>
#include <memory>

using std::list;
using std::string;
using std::unique_ptr;
	
class RobotPart;

enum class ExtensionType{
	Frame,
	Chassis,
	SensorModule,
	DrillArm,
	GrabbingArm,
	Joint,
	DriverWheel,
	None
};

class RobotExtensions{
	public:
		virtual void CreateDefault() = 0;
		virtual void Execute() = 0;
		virtual void AddtoPartsList();
		virtual void PrintPartsList();
		virtual void PrintLinkList();
		virtual string Name()const;
		virtual void Attach(const list<unique_ptr<RobotPart>>&);
			//Call CreateDefault and AddtoPartsList
		explicit RobotExtensions();
		virtual ~RobotExtensions();
	protected:
		list<unique_ptr<RobotPart>> PartsList__;
		list<RobotPart::Connection_t> Link__;
		string RE_Name__;
			//For use in overridden CreateDefault() calls
		void AppendPart(PartType=PartType::None,const int);
		void AppendLink(
			RobotPart::Connection_t=RobotPart::Connection_t::None,
			const int
		);
			//For use in overriden Execute() calls
		void ExecuteAll();
};

RobotExtensions* Build(ExtensionType=ExtensionType::None, const list<unique_ptr<RobotPart>>&);

class Frame: public RobotExtensions{
	public:
		Frame(const list<unique_ptr<RobotPart>>& = {});
		virtual ~Frame();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_bars_need(10),
			minimum_mf(minimum_bars_need),
			minimum_snap(minimum_mf/2)
		;
};
class Chassis: public RobotExtensions{
	public:
		Chassis(const list<unique_ptr<RobotPart>>& = {});
		virtual ~Chassis();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int 
			minimum_plates_needed(50),
			minimum_bars_need(7),
			minimum_monitors_need(3),
			minimum_snap(minimum_plates_needed),
			minimum_wire(minimum_plates_needed/2)
		;
		string __message;
};
class SensorModule: public RobotExtensions{
	public:
		SensorModule(const list<unique_ptr<RobotPart>>& = {});
		virtual ~SensorModule();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_plates(4),
			minimum_servos(1),
			minimum_lsensors(16),
			minimum_ussensors(4),
			minimum_mf(1),
			minimum_gear(1)
		;
};
class DrillArm: public RobotExtensions{
	public:
		DrillArm(const list<unique_ptr<RobotPart>>& = {});
		virtual ~DrillArm();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_drills(3),
			minimum_bars(2),
			minimum_plates(6),
			minimum_mf(1)
		;
};
class GrabbingArm: public RobotExtensions{
	public:
		GrabbingArm(const list<unique_ptr<RobotPart>>& = {});
		virtual ~GrabbingArm();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_claws(1),
			minimum_bars(2),
			minimum_plates(6),
			minimum_mf(1)
		;
};
class Joint: public RobotExtensions{
	public:
		Joint(const list<unique_ptr<RobotPart>>& = {});
		virtual ~Joint();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_plates(6),
			minimum_bars(2),
			minimum_motors(4),
			minimum_servos(4),
			minimum_wire(2)
		;
};
class DriverWheel: public RobotExtensions{
	public:
		DriverWheel(const list<unique_ptr<RobotPart>>& = {});
		virtual ~DriverWheel();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_bars(2),
			minimum_wheels(1),
			minimum_servos(1),
			minimum_wire(1)
		;
};
class BRAIN: public RobotExtensions{
	public:
		BRAIN(const list<unique_ptr<RobotPart>>& = {});
		virtual ~BRAIN();
		virtual void CreateDefault();
		virtual void Execute();
	private:
		static const int
			minimum_mcontroller(4),
			minimum_plates(5),
			minimum_mf(minimum_mcontrollers/2)
		;
};
	
#endif