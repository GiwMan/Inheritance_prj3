#include <iostream>
//#include "Object.h"
#include "PlaneApp.h"
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

#define CHARS_TO_CHANGE 15

using namespace std;

void clone_encrypt_and_print(Object& obj)
{   // Cloe object
    Object* clone_Obj = obj.clone();

    SString *sObj , *sClone, *desc;
    // desc is used to temporarily hold
    // description when toString is called
    // for every object
    // When it is used then i call clear()
    // to erase it's context in order to reuse it
    desc = new SString;

    //((Plane&)obj).toString(desc)->print();

    sObj = new SString(*obj.toString(desc));

    desc->clear();

    //cout << "\nCloned:\n";
    sClone = new SString(*clone_Obj->toString(desc));    

    desc->clear();

   // sClone->print();
    
    // Check equality
    if(obj.equal(*clone_Obj))
        cout <<"\nEqual\n";
    else
        cout << "\nNot equal!\n";
    // Check if they are identical
    if(obj.identical(*clone_Obj))
        cout <<"Identical\n";
    else
        cout << "Not identical\n"; 

    // Start Updating Strings at random places
    srand(time(NULL));

    int nCharsChange = CHARS_TO_CHANGE;
    // if bigger number then pick a random number smaller than 
    // String's size
    if( nCharsChange > sClone->length())
        nCharsChange = rand() % sClone->length();
     // find Pos in SString
    int pos = rand() %(sClone->length() + 1);

    // Loop untill nCharsChange = 0
    while(nCharsChange > 0)
    {   // Get a random char from string
        char temp = sClone->at(pos);
        // Update char at another position

        pos = rand() % (sClone->length() + 1);
        sClone->updateAt(pos,temp);
        // find another pos
        pos = rand() % (sClone->length() + 1);
        // Decrease counter 
        nCharsChange--;
    }

    cout << "\nAfter making:  Cloned: \n";
    sClone->print();
    cout << endl;

    // Concat string object with cloned
    cout << "Concat string object with cloned and print it:" << endl;
    sObj->concat(sClone);  
    sObj->print();

    cout << "\n\nLength is " << sObj->length() << endl;

    cout << "\n\nMiddle char :";

    if(sObj->length() % 2 != 0) 
        cout << sObj->at(sObj->length() / 2);
    else
    {   char s = sObj->at((sObj->length() / 2)-1);

        if(s == '\n')
        {
            cout << " new line char!";
            cout << s << ", ";
        }else
            cout << s << ", ";
        cout <<sObj->at((sObj->length() / 2)+1) << endl;
    }
    
    delete sClone;
    delete desc;
    delete sObj;
    // Destroying cloned object
    cout << "\n--------Destroying cloned object------------\n\n";
    delete clone_Obj;
    cout << "\n------------ End of destructor messages for cloned!-----------\n";
}

int main(int argc, char** argv)
{
    char* p;
    errno = 0;
    // convert char** to int
    long arg = strtol(argv[1],&p,10);

    if(*p != '\0' || errno != 0)
        return 1;

    //if(arg < INT_MIN || arg > INT_MAX)
       // return 1;
    int capacity = arg;

    arg = strtol(argv[2],&p,10);

    if(*p != '\0' || errno != 0)
        return 1;
    int randCap = arg;

    // Create a Plane with desc :[Plane]
    Plane *plane = new Plane(capacity,"Boeing 445",randCap);
    // Array of 3 Employees
    
    Employee *E[TOTAL_EMPLOYES];    
    /**
     * SecurityE = 0
     * MaintenanceE = 1
     * CleaningE = 2<<
     * TOTAL_EMPLOYES = 3
    */
    E[SecurityE] = new SecurityEmployee("Mixalis");
    E[MaintenanceE] = new MaintenanceEmployee("Giannis");
    E[CleaningE] = new CleaningEmployee("Giwrgos");
    // Plane process
    plane->process(E);

    //clone_encrypt_and_print(*E[SecurityE]);
    //clone_encrypt_and_print(*E[CleaningE]);

    clone_encrypt_and_print(*plane);

    delete plane;

    for(int i = 0; i < 3; i++)
        delete E[i];

   return 0;
}