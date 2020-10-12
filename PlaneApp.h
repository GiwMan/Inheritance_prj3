#include <iostream>
#include "Object.h"

enum EnumEmploys{
    SecurityE, // for SecurityEmployee
    MaintenanceE, // for MaintenanceEmployee
    CleaningE,  // for CleaningEmployee
    TOTAL_EMPLOYES  // total Employees in current App
    };

class Employee;

class PlaneComponent : public Object{
public:
    PlaneComponent();
    PlaneComponent(int);
    virtual ~PlaneComponent() = 0;

    virtual void process(Employee&) = 0;
    virtual void ready_check(int) = 0;

    
    bool equal(Object&) override;
    bool identical(Object&) override ;
    virtual Object* clone() = 0;

    SString* toString() override;
    SString* toString(SString*) override;
};

class PassengerCompartment : public PlaneComponent{
private:
    PassengerCompartment *internalComp;
    int comp_i;
public:
    PassengerCompartment();
    PassengerCompartment(int);//bool=false);//,int=0);
    PassengerCompartment(const PassengerCompartment&);
    ~PassengerCompartment();

    PassengerCompartment& operator=(const PassengerCompartment&);
    
    void process(Employee&) override;
    void ready_check(int); 

    SString* toString() override;
    SString* toString(SString*) override;
    SString* toString(SString*,int);

    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;

    void setInCompartment();
    void setIdOfinternalComp(int);
    bool hasInside();
    PassengerCompartment* getInComp();
    int getNumberOfComp();

};

class PrivateCompartment : public PlaneComponent{
//private:
public:
    PrivateCompartment();//bool=false);
    PrivateCompartment(int);
    ~PrivateCompartment();

    virtual void process(Employee&) override = 0;
    virtual void ready_check(int) override = 0;


    SString* toString() override;
    SString* toString(SString*) override;

    bool equal(Object&) override;
    bool identical(Object&) override;
    virtual Object* clone() = 0;
};

class EquipmentCompartment : public PrivateCompartment{
//private:
public:
    EquipmentCompartment();
    EquipmentCompartment(const EquipmentCompartment&);
    EquipmentCompartment& operator=(const EquipmentCompartment&);
    ~EquipmentCompartment();

    void process(Employee&) override;
    void ready_check(int);

    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;

    SString* toString() override;
    SString* toString(SString*) override;
    SString* toString(SString*,int);
};

class CargoBay : public PrivateCompartment{
private:
    EquipmentCompartment* EqCompartment;
public:
    CargoBay();
    CargoBay(const CargoBay&);
    CargoBay& operator=(const CargoBay&);
    ~CargoBay();

    void process(Employee&) override;
    void ready_check(int);

    SString* toString() override;
    SString* toString(SString*) override;

    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;

    bool hasEquipment();
    EquipmentCompartment* getECompartment();
    void setECompartment(EquipmentCompartment*);

};

class Plane : public Object{
private:
    int passCapacity;
    int nRooms;
    SString* desc;
    SString* plTitle;
    CargoBay* cargo;
    EquipmentCompartment *eqCompartment[3];
    PassengerCompartment **room;
public:
    Plane();
    Plane(int,const char*,int);
    Plane(const Plane&);
    ~Plane();

    void process(Employee&);
    void process(Employee*[TOTAL_EMPLOYES]);


    /* setters / getters */

    void setTitle(const char*);
    void setCapacity(int);
    void setRooms(int);
    void setDesc(const char*);

    //int getId();
    SString* getTitle();
    SString* getDesc();
    int getCapacity();
    int getRooms();
    /*Override functions*/
    SString* toString() override;
    SString* toString(SString*) override;

    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;

    CargoBay* getCargoArea();
    EquipmentCompartment* getEquipmentArea(int);
    PassengerCompartment* getPassengersArea(int);

    void print();
};


class Employee : public Object {
protected: 
    SString* name;

    SString* getName();
public:
    Employee();
    Employee(const char*);
    Employee(SString*,int);
    Employee(const Employee&);
    Employee(int);
    virtual ~Employee();

    virtual void workOn(Plane&) = 0;
    virtual void workOn(PassengerCompartment&) = 0;
    virtual void workOn(EquipmentCompartment&) = 0;
    virtual void workOn(CargoBay&) = 0;

    virtual void report() = 0;

    SString* toString() override;
    SString* toString(SString*) override;

    bool equal(Object&) override;
    bool identical(Object&) override;
    virtual Object* clone()  = 0;
    
    //SString* getName();
};

class SecurityEmployee : public Employee {
private:
public:
    SecurityEmployee();
    SecurityEmployee(const char*);
    SecurityEmployee(const SecurityEmployee&);
    ~SecurityEmployee();


    void workOn(Plane&) override;
    void workOn(PassengerCompartment&) override;
    void workOn(EquipmentCompartment&) override;
    void workOn(CargoBay&) override;
    void report() override;

    SString* toString() override;
    SString* toString(SString*) override;
    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;
};

class MaintenanceEmployee : public Employee {
private:
public:
    MaintenanceEmployee();
    MaintenanceEmployee(const char*);
    MaintenanceEmployee(const MaintenanceEmployee&);
    
    ~MaintenanceEmployee();


    void workOn(Plane&) override;
    void workOn(PassengerCompartment&) override;
    void workOn(EquipmentCompartment&) override;
    void workOn(CargoBay&) override;
    void report() override;

    SString* toString() override;
    SString* toString(SString*) override;
    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone();
};

class CleaningEmployee : public Employee {
private:
public:
    CleaningEmployee();
    CleaningEmployee(const char*);
    CleaningEmployee(const CleaningEmployee&);
    ~CleaningEmployee();

    void workOn(Plane&) override;
    void workOn(PassengerCompartment&) override;
    void workOn(EquipmentCompartment&) override;
    void workOn(CargoBay&) override;
    void report() override;

    SString* toString() override;
    SString* toString(SString*) override;
    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone();
};


