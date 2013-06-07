#include "BotTemplate.h"
#include "Extensions.h"
#include "Parts.h"

#include <iostream>
#include <memory>
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]){
 //   std::unique_ptr<RobotPart> RP_ptr = Build(PartType::SmartPlate);
    RobotPart* RP_ptr = Build(PartType::SmartPlate);
    RobotExtension* RE_ptr = Build(ExtensionType::GrabbingArm);
    cout << RP_ptr->Name() << endl;
    delete RP_ptr;
//    for(auto iter = RE_ptr->PartsList().begin(); iter != RE_ptr->PartsList().end(); ++iter)
 //       cout << (*iter)->Name() << endl;
     try{
        if(RE_ptr== nullptr)
            cout << "Error" << endl;
        else
            cout<< "Dangling Pointer" << endl;
        //    cout << (*RE_ptr->PartsList().begin())->Name() << endl;
    }catch(std::exception err){cout << "Null pointer" << endl;}
    catch(...){cout << "Caught Dangling Pointer" << endl;}
}
