#ifndef EXTENSIONS_H
	#define EXTENSIONS_H
	
#include <list>
#include <string>

using std::list;
using std::string;
	
class RobotPart;

enum class ExtensionType{
	Framework,
	Chassis,
	SensorModule,
	DrillArm,
	GrabbingArm,
	Joint,
	DriverWheel
};

class RobotExtensions{
	public:
		virtual void CreateDefault() = 0;
		virtual void AddtoPartsList();
		virtual void PrintPartsList();
		virtual void PrintLinkList();
		virtual string Name()const;
		virtual void Attach(const list<RobotPart*>&);
		RobotExtensions* Build(ExtensionType, const list<RobotPart*>&);
			//Call CreateDefault and AddtoPartsList
		explicit RobotExtensions();
		virtual ~RobotExtensions();
	protected:
		list<RobotPart*> PartsList__;
		list<RobotPart::Connection_t> Link__;
		string RE_Name__;
};
struct Frame: public RobotExtensions{
	Frame(const list<RobotPart*>& = {});
	virtual ~Frame();
	virtual void CreateDefault();
};
struct Chassis: public RobotExtensions{
	Chassis(const list<RobotPart*>& = {});
	virtual ~Chassis();
	virtual void CreateDefault();
};
struct SensorModule: public RobotExtensions{
	SensorModule(const list<RobotPart*>& = {});
	virtual ~SensorModule();
	virtual void CreateDefault();
};
struct DrillArm: public RobotExtensions{
	DrillArm(const list<RobotPart*>& = {});
	virtual ~DrillArm();
	virtual void CreateDefault();
};
struct GrabbingArm: public RobotExtensions{
	GrabbingArm(const list<RobotPart*>& = {});
	virtual ~GrabbingArm();
	virtual void CreateDefault();
};
struct Joint: public RobotExtensions{
	Joint(const list<RobotPart*>& = {});
	virtual ~Joint();
	virtual void CreateDefault();
};
struct DriverWheel: public RobotExtensions{
	DriverWheel(const list<RobotPart*>& = {});
	virtual ~DriverWheel();
	virtual void CreateDefault();
};
struct BRAIN: public RobotExtensions{
	BRAIN(const list<RobotPart*>& = {});
	virtual ~BRAIN();
	virtual void CreateDefault();
};
	
#endif