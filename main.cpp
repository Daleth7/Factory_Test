/** To do
*  -Compact code
*  -Put in labels
**/

#include "Parts.h"
#include "Extensions.h"
#include "BotTemplate.h"

#include <iostream>
#include <memory>

int main(int argc, char* argv[]){
    using std::cout;
    using std::cin;
    using std::endl;
    using std::cerr;
    using std::unique_ptr;
    cout << "\t\tRobot Part Test\n";
    unique_ptr<RobotPart> RP_ptr(Build(PartType::SmartPlate));
    cout << "Part name: " << RP_ptr->Name() << endl << endl;

    cout << "\t\tRobot Extension Test\n";
    unique_ptr<RobotExtension> RE_ptr(Build(ExtensionType::GrabbingArm));
     try{
        cout << "Extension name: "
            << RE_ptr->Name() << '\n';
        if(RE_ptr== nullptr)
            throw std::exception();
        else{
            cout << "Parts list:\n";
            for(auto RE_iter(RE_ptr->PartsList().begin());
            RE_iter != RE_ptr->PartsList().end();
            ++RE_iter)
                cout << '\t' << (*RE_iter)->Name() << '\n';
            RE_ptr->Execute();
            cout << "Successful execution.\n\n";
        }
    }catch(const std::exception& err){cerr << "Null pointer" << endl;}
    catch(...){cerr << "Caught Dangling Pointer" << endl;}
    unique_ptr<RobotExtension> BRAIN_ptr(Build(ExtensionType::BRAIN));
     try{
        cout << "Extension name: "
            << BRAIN_ptr->Name() << '\n';
        if(BRAIN_ptr== nullptr)
            throw std::exception();
        else{
            cout << "Parts list:\n";
/*            for(auto RE_iter(BRAIN_ptr->PartsList().begin());
            RE_iter != BRAIN_ptr->PartsList().end();
            ++RE_iter)
                cout << '\t' << (*RE_iter)->Name() << '\n';
*/            BRAIN_ptr->Execute();
            cout << "Successful execution.\n\n";
        }
    }catch(const std::exception& err){cerr << "Null pointer" << endl;}
    catch(...){cerr << "Caught Dangling Pointer" << endl;}

    cout << "\t\tRobot Test\n";
    unique_ptr<Robot> Rptr(Assemble(RobotTemplate::Medusa));
    try{
        cout << "Robot name: " << Rptr->Name() << '\n';
        if(Rptr == nullptr)
            throw std::exception();
        else{
            cout << "container size: " << Rptr->__Extensions.size() << '\n';
          //  Rptr->Execute();
            cout << "Extensions list:\n";
   /*         for(auto Riter(Rptr->__Extensions.begin());
                Riter != Rptr->__Extensions.end();
                ++Riter){
                cout << '\t' << (*Riter)->Name()
                    << "\n\t\tParts list:\n";
                for(
                    auto REiter((*Riter)->PartsList().begin());
                    REiter != ((*Riter)->PartsList().end());
                    ++REiter
                ) cout << "\t\t\t" << (*REiter)->Name() << '\n';
            }
*/            cout << "Another sucessful execution.\n";
        }
    }catch(const std::exception& err){cerr << "Null pointer" << endl;}
    catch(...){cerr << "Caught Dangling Pointer" << endl;}
}
