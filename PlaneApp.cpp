#include <iostream>
#include "PlaneApp.h"
#include <string.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

PlaneComponent::PlaneComponent()//bool isReady)
: Object(++ TOTAL_OBJECTS) //, ready_check(isReady)
{
    cout << "Plane component just created!\n";
}

PlaneComponent::PlaneComponent(int copyId)
:   Object(copyId)
{
    cout << "Plane component just created!\n";
}

PlaneComponent::~PlaneComponent()
{
    cout << "PlaneComponent to be destroyed!\n";
}
/*
PlaneComponent::PlaneComponent()
{
    cout << "Plane componentjust created!\n";
    //nam = new SString()
}*/

PassengerCompartment::PassengerCompartment()
:   PlaneComponent(),
    internalComp(0),
    comp_i(-1)
{

}

PassengerCompartment::PassengerCompartment(int i)
    //bool isReady
//)
:   PlaneComponent(),//isReady),
    internalComp(0),//new PassengerCompartment(isReady))
    comp_i(i)
{
    cout << "PassengerCompartment just created!\n";
   // this->comp_i = i;
}

PassengerCompartment::PassengerCompartment(const PassengerCompartment& pc)
:   PlaneComponent(pc.id),
    internalComp(NULL)
{
    this->comp_i = pc.comp_i;

    if(pc.internalComp)
        this->internalComp = new PassengerCompartment(*pc.internalComp);
}

PassengerCompartment::~PassengerCompartment()
{
    if(hasInside())
        delete internalComp;

    cout << "PassengerCompartment to be destroyed!\n";
}

PassengerCompartment& PassengerCompartment::operator=(const PassengerCompartment& pc)
{
    //cout << "= called!\n";
    if(this != &pc)
    {
        this->comp_i = pc.comp_i;

        //delete internalComp;
        if(pc.internalComp)
        {
            this->internalComp = new PassengerCompartment(*pc.internalComp);
            //->internalComp->setId(pc.internalComp->getId());
        }
        else
            this->internalComp = 0;
        //internalComp = pc.internalComp;
    }
    return *this;
}


PrivateCompartment::PrivateCompartment()//bool isReady)
:   PlaneComponent()
//: PlaneComponent(isReady)
{
    cout << "PrivateCompartment just created!\n";
}

PrivateCompartment::PrivateCompartment(int copyId)
:   PlaneComponent(copyId)
{
     cout << "PrivateCompartment just created!\n";
}

PrivateCompartment::~PrivateCompartment()
{
    cout << "PrivateCompartment to be destroyed!\n";
}

EquipmentCompartment::EquipmentCompartment()//bool isReady)
:   PrivateCompartment()//isReady)
{
    cout << "Equipment compartment just created!\n";
}

EquipmentCompartment& EquipmentCompartment::operator=(const EquipmentCompartment& EC)
{
    return *this;
}

EquipmentCompartment::EquipmentCompartment(const EquipmentCompartment& oldEq)
:   PrivateCompartment(oldEq.id)
{
    //cout << "Equipment Compartment just created!\n";
    //*this = oldEq; 
}

EquipmentCompartment::~EquipmentCompartment()
{
    cout << "EquipmentCompartment to be destroyed!\n";
}

CargoBay::CargoBay()
:   PrivateCompartment(),
    EqCompartment(new EquipmentCompartment())
{
    cout << "CargoBay just created!\n";
}

CargoBay& CargoBay::operator=(const CargoBay& cB)

{
    //cout << "\nCopy assignment operator of cargo!\n";
    if(this != &cB)
    {
        delete EqCompartment;
        EqCompartment = NULL;

        EqCompartment = new EquipmentCompartment(*cB.EqCompartment);
    }

    return *this;
}

CargoBay::CargoBay(const CargoBay& oldCB)
:   PrivateCompartment(oldCB.id),
    EqCompartment(NULL)
{
    this->EqCompartment = new EquipmentCompartment(*oldCB.EqCompartment);
}

CargoBay::~CargoBay()
{
    delete EqCompartment;

    cout << "CargoBay to be destroyed!\n";
}


Plane::Plane( 
    int cap,
    const char* title,
    int randomCap
            )
: 
    passCapacity(cap),
    nRooms(randomCap),
    desc(new SString("[Plane]")),
    plTitle(new SString(title)),
    cargo(new CargoBay()),//true)),
   // eqCompartment(new EquipmentCompartment*[3])
    room(new PassengerCompartment*[nRooms])
{
    //int x;
    //1cout << "Type x to continue;\n\n" << randomCap;
    
    //cin >> x;
    for(int i = 0; i < 3; i ++)
        eqCompartment[i] = new EquipmentCompartment();
    
    for(int i = 0; i < nRooms; i++)
        room[i] = new PassengerCompartment(i+1);
    
    int generateInternals = rand() % nRooms + 1;

    for(int i = 0 ; i < generateInternals; i++)
        room[i]->setInCompartment();
    //room[0]->setInCompartment();
    cout << endl;
    //plTitle->print();
}

Plane::Plane(const Plane& oldPlane)
:   Object(oldPlane.id),
    passCapacity(oldPlane.passCapacity),
    nRooms(oldPlane.nRooms),
    desc(new SString()),
    plTitle(new SString()),
    cargo(new CargoBay()),
    room(new PassengerCompartment*[nRooms])
{
    
    *this->desc = *oldPlane.desc;
    this->desc->setId(oldPlane.desc->getId());
    
    *this->plTitle = *oldPlane.plTitle;
    this->plTitle->setId(oldPlane.plTitle->getId());

    *this->cargo = *oldPlane.cargo;
    this->cargo->setId(oldPlane.cargo->getId());

    for(int i = 0; i < 3; i++)
    {
        this->eqCompartment[i] = new EquipmentCompartment();
        //this->eqCompartment[i] = new EquipmentCompartment(*oldPlane.eqCompartment[i]);
        *this->eqCompartment[i] = *oldPlane.eqCompartment[i];

        this->eqCompartment[i]->setId(oldPlane.eqCompartment[i]->getId());
    }

    for(int i = 0; i < nRooms; i++)
    {
        this->room[i] = new PassengerCompartment();

        *this->room[i] = *oldPlane.room[i];
        this->room[i]->setId(oldPlane.room[i]->getId());

        if(oldPlane.room[i]->hasInside())
            this->room[i]->setIdOfinternalComp(oldPlane.room[i]->getInComp()->getId());
        //this->room[i]->setIdOfinternalComp(oldPlane.room[i])
        //this->room[i]->setId(oldPlane.room[i]->getId());
        //this->room[i]->getInComp()->setId(oldPlane.room[i]->getInComp()->getId());
    }

}

Plane::Plane()
:   Object(++TOTAL_OBJECTS),
    passCapacity(-1),
    nRooms(-1),
    desc(NULL),
    plTitle(NULL),//new SString()),
    cargo(NULL),//new CargoBay()),
    room(NULL)
{

}

Plane::~Plane()
{
    delete desc;
    delete plTitle;
    delete cargo;

    //delete [] eqCompartment;
    for(int i = 0; i < 3; i++)
        delete  eqCompartment[i];

    //delete [] eqCompartment;

    for(int i = 0; i < nRooms; i++)
        delete room[i];

    delete [] room;

    cout << "Plane to be destroyed!\n";
}


/* End of Concstructors / Destructors 
 * Start of functions, setters , getters
*/

/* Function of PlaneComponent */
SString* PlaneComponent::toString()
{
    SString* title = Object::toString();

    title->concat(",PlaneComponent");

    return title;
}

SString* PlaneComponent::toString(SString* ss)
{
    ss = Object::toString(ss);

    ss->concat(" [PlaneComponent] ");
        
    return ss; 
}

/* Functions of PassengerCompartment */
SString* PassengerCompartment::toString()
{
    SString* title = PlaneComponent::toString();
    title->concat(",PassengerCompartment");

    return title;
}

SString* PassengerCompartment::toString(SString* ss)
{
    SString* title = ss;

    if(hasInside())
    {
        title->concat(",internalCompartment,PassengerCompartment");
        return title;
    }
    
    title->concat(",PassengerCompartment");
    //title->concat(",PassengerComponent");
    return title;
}

SString* PassengerCompartment::toString(SString* ss, int i)
{
    SString* number = new SString(comp_i);

        if(hasInside())
        {
            ss = PlaneComponent::toString(ss);
            
            ss->concat("[PassengerCompartment - ");
            ss->concat(number->getString());
            ss->concat(" / with internalCompartment] ");

            delete number;

            return ss;
        }
        else
        {
            ss = PlaneComponent::toString(ss);

            ss->concat("[PassengerCompartment - ");
            ss->concat(number->getString());
            ss->concat("] ");

            delete number;

            return ss;
        }  
}

void PassengerCompartment::setInCompartment()
{
    if(!internalComp) 
    {
        internalComp = new PassengerCompartment(1);
    }     
}

 void PassengerCompartment::setIdOfinternalComp(int Id)
 {
    if(hasInside()) 
        internalComp->setId(Id);
    else
        ;
 }

bool PassengerCompartment::hasInside()
{
    return internalComp != NULL;
}

PassengerCompartment* PassengerCompartment::getInComp()
{
    if(!internalComp)
    {
        //cout << "\nfirst instance !\n";
        return internalComp;
    }
    else
    {
        //cout << "\nprevious instance!\n";
        
        return internalComp;
    }
}

int PassengerCompartment::getNumberOfComp() 
{
    return comp_i;
}

SString* PrivateCompartment::toString()
{
    SString* temp = PlaneComponent::toString();

    temp->concat(",PrivateCompartment");

    return temp;
}

SString* PrivateCompartment::toString(SString* ss)
{
    ss = PlaneComponent::toString(ss);

    ss->concat(" [PrivateCompartment]");

    return ss;

}

SString* EquipmentCompartment::toString()
{
    SString* temp = PrivateCompartment::toString();
    temp->concat("EquipmentCompartment");

    return temp;
}

SString* EquipmentCompartment::toString(SString* ss)
{
    //SString* title = ss;
    ss = PrivateCompartment::toString(ss);
    ss->concat(" [EquipmentCompartment] ");
    //title->concat("EquipmentCompartment");

    return ss;
}

SString* EquipmentCompartment::toString(SString* ss, int i)
{
    SString* number = new SString(i+1);

    ss = PrivateCompartment::toString(ss);

    ss->concat(" [EquipmentCompartment - ");
    ss->concat(number->getString()); 
    ss->concat("] ");

    delete number;

    return ss;
   
}

SString* CargoBay::toString()
{
    SString* temp = EqCompartment->toString();

    temp->concat("CargoBay");

    return temp;
}

SString* CargoBay::toString(SString* ss)
{
    ss = PrivateCompartment::toString(ss);

    ss->concat(" [CargoBay - ");
    ss = EqCompartment->toString(ss);
    ss->concat("] ");

    return ss;
}

EquipmentCompartment* CargoBay::getECompartment()
{
    return EqCompartment;
}

bool CargoBay::hasEquipment()
{
    return EqCompartment != NULL;
}

void CargoBay::setECompartment(EquipmentCompartment* eq)
{
    if(!hasEquipment())
        *EqCompartment = *eq;
}

void Plane::setTitle(const char* s)
{
    if(plTitle == NULL)
        plTitle = new SString(s);
    else
    {
        plTitle->clear();
        plTitle->setString(s);
    }
}

void Plane::setCapacity(int Cap)
{
    passCapacity = Cap;
}

void Plane::setRooms(int n)
{
    nRooms = n;
}

void Plane::setDesc(const char* x)
{
    if(desc == NULL)
        desc = new SString(x);
    else
    {
        desc->clear();
        desc->setString(x);
    }
}

SString* Plane::getTitle()
{
    return plTitle;
}

SString* Plane::getDesc()
{
    return desc;
}

SString* Plane::toString(SString* ss)
{
    SString *capacity = new SString(getCapacity()),
            *nComponents = new SString(nRooms);


    ss = Object::toString(ss);

        //ss->concat("[");
    ss->concat(desc->getString());
    ss->concat(" /\n");

    ss = plTitle->toString(ss);//ss->concat(plTitle);

      // Concat with Plane desc
    ss->concat(" /\n[Plane::passCapacity - "); 
    ss->concat(capacity->getString());
    ss->concat(" ] /\n[Plane::nRooms - ");
    ss->concat(nComponents->getString());
    ss->concat(" ] /\n");

        
        // Call CargoBay::toString
    ss = cargo->toString(ss);
    ss->concat(" /\n");

       // cout << "ss in plane = "<<endl;
        //ss->print();
    for(int i = 0; i < 3; i++)
    {
        ss = eqCompartment[i]->toString(ss,i);
        ss->concat(" /\n");
    }

    for(int i = 0; i < getRooms(); i++)
    {
        ss = room[i]->toString(ss,i);
        if(i != getRooms() - 1)
            ss->concat(" /\n");
    }

    delete capacity;
    delete nComponents;

    return ss;
}

SString* Plane::toString()
{
    desc = Object::toString(desc);

    SString *number = new SString(passCapacity),
            *nComps = new SString(nRooms);//*title = plTitle->toString(),//plTitle->toString(),
            //*number = new SString(passCapacity);
    desc->concat(" contains : \n");

    desc->concat(plTitle->toString(plTitle)->getString());

    desc->concat("/\n");

    desc->concat("[Plane::passCapacity] [");
    desc->concat(number->getString());//s.c_str());
    desc->concat("]");

    desc->concat("/\n");

    desc->concat("[Plane::nRooms] [");
    desc->concat(nComps->getString());//s.c_str());
    desc->concat("]");

    desc->concat("/\n");

    desc = cargo->toString(desc);//->print();

    desc->concat("/\n");


    for(int i = 0 ; i < 3; i++)
        desc = eqCompartment[i]->toString(desc);    

    for(int i = 0; i < nRooms; i++)
        desc = room[i]->toString(desc);

    delete number;
    delete nComps;

    cout << endl;

    return desc;
}

int Plane::getCapacity()
{
    return passCapacity;
}

int Plane::getRooms()
{
    return nRooms;
}

CargoBay* Plane::getCargoArea()
{
    return cargo;
}

EquipmentCompartment* Plane::getEquipmentArea(int i)
{
    return eqCompartment[i];
}

PassengerCompartment* Plane::getPassengersArea(int i)
{
    return room[i];
}

void Plane::print()
{
    if(desc != NULL)
    {
        cout << "\n----------Printing Plane's Description---------\n";

        desc->print();

        cout <<" -------------------------------------- \n";
    }
}


void CargoBay::process(Employee& e)
{
    e.workOn(*this);
}

void EquipmentCompartment::process(Employee& e)
{
    e.workOn(*this);
}

void PassengerCompartment::process(Employee& e)
{
    e.workOn(*this);
}


void Plane::process(Employee& e)
{
    e.workOn(*this);
    //c
}

void Plane::process(Employee *E[3])
{
    // Security workOn and report
    process(*E[SecurityE]);
    E[SecurityE]->report();
    // Maintenance workOn and report
    process(*E[MaintenanceE]);
    E[MaintenanceE]->report();
    // Cleaner workOn and report
    process(*E[CleaningE]);
    E[CleaningE]->report();
    // Cargo Bay is ready
    cargo->ready_check(0);
    // Equipment Compartment is ready
    for(int i = 0; i < 3; i ++)
        eqCompartment[i]->ready_check(i);
    // Passenger Compartment is ready
    for(int i = 0; i < nRooms; i++)
        room[i]->ready_check(i);

    cout << "\nJob is done!\n   Plane ready to take off!\n\n";
}

Employee::Employee() : Object(++TOTAL_OBJECTS)
{
    cout << "Employee just created!\n";
}

Employee::Employee(int copyId)
:   Object(copyId),
    name(NULL)
{
     cout << "Employee just created!\n";
}

Employee::Employee(const char* x)
:   Object(++TOTAL_OBJECTS),
    name(new SString(x)) 
{
    cout << "Employee just created!\n";
}

Employee::Employee(SString* nam, int copyId)
:   Object(copyId),
    name(new SString(*nam))
{
     cout << "Employee just created!\n";
}

Employee::Employee(const Employee& oldE)
{
    if(name != NULL)
    {
        delete name;
    }

    name = new SString(*oldE.name);
}

Employee::~Employee()
{
    delete name;

    cout << "Employee to be destroyed!\n";
}

SecurityEmployee::SecurityEmployee()
 : Employee()
{
    cout << "SecurityEmployee just created!\n";
}

SecurityEmployee::SecurityEmployee(const char* x)
:   Employee(x)
{
    cout << "SecurityEmployee just created!\n";
}

SecurityEmployee::SecurityEmployee(const SecurityEmployee& oldSec)
:   Employee(oldSec.id)
{
    name = new SString();
    *this->name = *oldSec.name;
    name->setId(oldSec.name->getId());
    //name->setId(oldSec.name->getId());
    //this->id = oldSec.id;
}

SecurityEmployee::~SecurityEmployee()
{
    cout << "SecurityEmployee to be destroyed!\n";
}

MaintenanceEmployee::MaintenanceEmployee()
:   Employee()
{
    cout << "MaintnenanceEmployee just created!\n";
}

MaintenanceEmployee::MaintenanceEmployee(const MaintenanceEmployee& oldMain)
:   Employee(oldMain.id)
{
    name = new SString();
    *this->name = *oldMain.name;
    name->setId(oldMain.name->getId());
    //this->id = oldSec.id;
}

MaintenanceEmployee::MaintenanceEmployee(const char* x)
:   Employee(x)
{
    cout << "MaintenanceEmployee just created!\n";
}

MaintenanceEmployee::~MaintenanceEmployee()
{
    cout << "MainenanceEmployee to be destroyed!\n";
}

CleaningEmployee::CleaningEmployee()
{
    cout << "CleaningEmployee just created!\n";
}

CleaningEmployee::CleaningEmployee(const char* x)
:   Employee(x)
{
    cout << "CleaningEmployee just created!\n";
}

CleaningEmployee::CleaningEmployee(const CleaningEmployee& oldClean)
:   Employee(oldClean.id)
{
    name = new SString();
    *this->name = *oldClean.name;
    name->setId(oldClean.name->getId());
   // this->id = oldSec.id;
}

CleaningEmployee::~CleaningEmployee()
{
    cout << "CleaningEmployee to be destroyed!\n";
}



/* ----------------------------------- */

/* Functions of Employee.h */


void SecurityEmployee::workOn(PassengerCompartment& area)
{
    cout << "Security checks PassengerCompartment!\n";

    if(area.hasInside())
        cout << "Security checks internal Compartment!n";
}

void SecurityEmployee::workOn(EquipmentCompartment& area)
{
    cout << "Security checks EquipmentCompartment!\n";
}

void SecurityEmployee::workOn(CargoBay& area)
{
    cout << "\nSecurity checks CargoBay!\n";

    if(area.hasEquipment())
        cout << "Security checks EquipmentCompartment of CargoBay\n";
}

void SecurityEmployee::workOn(Plane& plane)
{
    // Working in CargoBay
    workOn(*plane.getCargoArea());
    // Working in EquipmentCompartment
    for(int i = 0; i < 3; i++)
        workOn(*plane.getEquipmentArea(i));
    // Working in PassengerCompartment
    for(int i = 0 ; i < plane.getRooms(); i++)
        workOn(*plane.getPassengersArea(i));
}

void MaintenanceEmployee::workOn(PassengerCompartment& area)
{

}

void MaintenanceEmployee::workOn(EquipmentCompartment& area)
{
     cout << "MaintenanceEmployee maintains EquipmentCompartment!\n";
}

void MaintenanceEmployee::workOn(CargoBay& area)
{
     cout << "\nMaintenanceEmployee maintains CargoBay!\n";

     if(area.hasEquipment())
         cout << "MaintenanceEmployee maintains EquipmentCompartment in CargoBay!\n";
}

void MaintenanceEmployee::workOn(Plane& plane)
{
    // Working in CargoBay
    workOn(*plane.getCargoArea());
    // Working in EquipmentCompartment
    for(int i = 0; i < 3; i++)
        workOn(*plane.getEquipmentArea(i));
    // Working in PassengerCompartment
    //for(int i = 0 ; i < plane.getRooms(); i++)
        //workOn(*plane.getPassengersArea(i));
}

void CleaningEmployee::workOn(PassengerCompartment& area)
{
    cout << "CleaningEmployee is cleaning PassengerCompartment\n";

    if(area.hasInside())
        cout << "CleaningEmployee is cleaning internal PassengerCompartment\n";
}

void CleaningEmployee::workOn(EquipmentCompartment& area)
{

}

void CleaningEmployee::workOn(CargoBay& area)
{
    cout << "\nCleaningEmployee is cleaning CargoBay\n";
}

void CleaningEmployee::workOn(Plane& plane)
{
    // Working in CargoBay
    workOn(*plane.getCargoArea());
    // Working in EquipmentCompartment
    //for(int i = 0; i < 3; i++)
        //workOn(*plane.getEquipmentArea(i));
    // Working in PassengerCompartment
    for(int i = 0 ; i < plane.getRooms(); i++)
        workOn(*plane.getPassengersArea(i));
}

SString* Employee::toString()
{ // find the path of current object
    SString* temp = name->toString();//new SString(name->getString());//name->toString();

    temp->concat(", Employee");

    return temp;
}

SString* SecurityEmployee::toString()
{
    SString* temp = Employee::toString();
    
    temp->concat(", SecurityEmployee");
    
    return temp;
}

SString* MaintenanceEmployee::toString()
{
    SString* temp = Employee::toString();

    temp->concat(", MaintenanceEmployee");

    return temp;
}

SString* CleaningEmployee::toString()
{
    SString* temp = Employee::toString();

    temp->concat(", CleaningEmployee");

    return temp;
}

SString* Employee::getName()
{
    return name;
}

void SecurityEmployee::report()
{   // Report for Security Employee
    cout << "Plane processed for : ";
    Employee::getName()->print();
    cout << "SecurityEmployee report: Everything OK!\n";
}

void MaintenanceEmployee::report()
{   // Report for Maintenance Employee
    cout << "Plane processed for : ";
    Employee::getName()->print();
    cout << "Maintenance report: Everything OK!\n";
}

void CleaningEmployee::report()
{   // Report for Cleaning Employee
    cout << "Plane processed for : ";
    Employee::getName()->print();
    cout << "Cleaning report: Everything OK!\n";
}


void PassengerCompartment::ready_check(int x)
{
    if(hasInside())
    {
        cout << "   Internal Compartment of Passenger Compartment #" << comp_i <<" is OK!\n";
        if(internalComp->hasInside())
            internalComp->ready_check(comp_i);

        cout << "PassengerCompartment #" << comp_i << " is OK!\n";

        return;
    }

    cout << "PassengerCompartment #" << comp_i << " is OK!\n";
}

void EquipmentCompartment::ready_check(int x)
{
    cout << "Equipment Compartment #"<< x + 1<<" is OK!\n";
}

void CargoBay::ready_check(int x)
{
    // Check of Equipment Compartment in Cargo Bay
    cout << "\nCheck Equipment Compartment of Cargo Bay!\n";
    EqCompartment->ready_check(x);
    // Cargo Bay is ready
    cout << "   Cargo Bay #"<< x + 1<<" is OK!\n";
}


/* toString Functions */

SString* Employee::toString(SString* ss)
{
    //if(ss->getString() == NULL)
    //{
        ss = Object::toString(ss);

        ss->concat(" [Employee]");//contains: ");
        //ss->print();
        //ss = name->toString(ss);
        
        //ss->print();

        return ss;
    //}
}

SString* SecurityEmployee::toString(SString* ss)
{
    //if(ss->getString() == NULL)
    //{
        ss = Employee::toString(ss);

        ss->concat(" [SecurityEmployee] contains : /\n ");

        ss = Employee::getName()->toString(ss);

        return ss;
    //}
}

SString* MaintenanceEmployee::toString(SString* ss)
{
    //if(ss->getString() == NULL)
    //{
        ss = Employee::toString(ss);

        ss->concat(" [MaintenanceEmployee] contains : /\n ");

        ss = Employee::getName()->toString(ss);

        return ss;
    //}
}

SString* CleaningEmployee::toString(SString* ss)
{
    //if(ss->getString() == NULL)
    //{
        ss = Employee::toString(ss);

        ss->concat(" [CleaningEmployee] contains : /\n ");

        ss = Employee::getName()->toString(ss);

        return ss;
    //}
}

/* End of toString
 *  
 * Start of equal 
 */
bool PlaneComponent::equal(Object& obj)
{
    return Object::equal(obj);
}

bool PrivateCompartment::equal(Object& obj)
{
    return PlaneComponent::equal(obj);
}

bool EquipmentCompartment::equal(Object& obj)
{
    return PrivateCompartment::equal(obj);
}

bool CargoBay::equal(Object& obj)
{
    CargoBay& cb = (CargoBay&) obj;

    if(PrivateCompartment::equal(obj))
    {
        if(EqCompartment->equal(*cb.getECompartment()))
            return true;
    }
    return false;
}

bool PassengerCompartment::equal(Object& obj)
{
    PassengerCompartment& pc = (PassengerCompartment&) obj;
    if(PlaneComponent::equal(obj))
    { // if there is an internal Comp then check id's
        if( hasInside() && comp_i == pc.comp_i)
        {
            if(internalComp->equal(*pc.getInComp()))
                return true;
            else
                return false;
        // if not then retun true
        }
        return true;
    }
    return false;
}

bool Plane::equal(Object& obj)
{
    if(Object::equal(obj))
    {
        Plane& p = (Plane&) obj;
        //cout << "perase!\n";
        if(passCapacity == p.passCapacity)
        {
            //cout << "same capacity!\n";
            if(nRooms == p.nRooms)
            {
                //cout << "same nRooms\n";
                if(desc->equal(*p.getDesc()))//strcmp(desc->getString(),p.desc->getString()) == 0)
                {
                   // cout << "same description!\n";
                    if(plTitle->equal(*p.getTitle()))//strcmp(plTitle->getString(),p.plTitle->getString()) == 0)
                    {
                       // cout << "same title!\n";
                        if(cargo->equal(*p.getCargoArea()))
                        {
                            //cout << "same cargo area!\n";
                            for(int i = 0; i < 3; i++)
                            {
                                if(eqCompartment[i]->equal(*p.getEquipmentArea(i)))
                                {
                                    //cout << "same eqCompartment #" << i+1 << endl;
                                }else{
                                    return false;
                                }
                            }

                            for(int i = 0; i < nRooms; i++)
                            {
                                if(room[i]->equal(*p.getPassengersArea(i)))
                                {
                                   // cout << "same passenger compartment #" << i+1<<endl;
                                }else
                                {
                                    return false;
                                }
                            }
                            return true;
                        }else
                        {
                            return false;
                        }
                    }else
                    {
                        return false;
                    }
                }else
                {
                    return false;
                }
            }else
            {
                return false;
            }
        }else
        {
            return false;
        }
    }else
    {
        //cout << "diaforetika id!\n";
        return false;
    }
    //return true;
}

bool Employee::equal(Object& obj)
{
    if(Object::equal(obj))
    {
        Employee& e = (Employee&) obj;
        
        if( name->equal(*e.name) )
            return true;
        
    }
    return false;
}

bool SecurityEmployee::equal(Object& obj)
{
    return Employee::equal(obj);
}

bool MaintenanceEmployee::equal(Object& obj)
{
    return Employee::equal(obj);
}

bool CleaningEmployee::equal(Object& obj)
{
    return Employee::equal(obj);
}

/* End of equal
 *  
 * Start of identical 
*/
bool PlaneComponent::identical(Object& obj)
{
    return Object::identical(obj);
}

bool PrivateCompartment::identical(Object& obj)
{
    return PlaneComponent::identical(obj);
}

bool EquipmentCompartment::identical(Object& obj)
{
    return PrivateCompartment::identical(obj);
}

bool CargoBay::identical(Object& obj)
{
    return PrivateCompartment::identical(obj);
}

bool PassengerCompartment::identical(Object& obj)
{
    return PlaneComponent::identical(obj);
}

bool Plane::identical(Object& obj)
{
    return Object::identical(obj);
}

bool Employee::identical(Object& obj)
{
    return Object::identical(obj);
}

bool SecurityEmployee::identical(Object& obj)
{
    return Employee::identical(obj);
}

bool MaintenanceEmployee::identical(Object& obj)
{
    return Employee::identical(obj);
}

bool CleaningEmployee::identical(Object& obj)
{
    return Employee::identical(obj);
}

/* End of identical
 *  
 * Start of clone
*/
Object* EquipmentCompartment::clone()
{
    return new EquipmentCompartment(*this);
}

Object* CargoBay::clone()
{
    return new CargoBay(*this);
}

Object* PassengerCompartment::clone()
{
    return new PassengerCompartment(*this);
}


Object* Plane::clone()
{
    return new Plane(*this);
}

Object* SecurityEmployee::clone()
{
    return new SecurityEmployee(*this);
}

Object* MaintenanceEmployee::clone()
{
    return new MaintenanceEmployee(*this);
}

Object* CleaningEmployee::clone()
{
    return new CleaningEmployee(*this);
}

