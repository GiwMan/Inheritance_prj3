#include <iostream>
#include <sstream>
#include <string.h>
#include "Object.h"

int TOTAL_OBJECTS;

using namespace std;

// Default Constructor of Object
/*Object::Object()
{
    cout << "Object created!\n";
}*/
// Paramerized constructor
Object::Object(int k) 
: id(k)
{
    cout <<"Object just created!" << endl;
}
// Destructor of Object
Object::~Object()
{
    cout << "Object to be destroyed!\n";
}

/* Object functions */
int Object::getId()
{
    return id;
}

void Object::setId(int k)
{
    id = k;
}


SString* Object::toString()
{
    SString* name = new SString("Object, id= "); //= new SString("Object,id = ");
    // Create a SString of our id
    SString* number = new SString(id);    
    //Find the size of name + id
    //int lenOfString = name->length() + number->length();
    // Allocate some space for str initialization
    //SString* title = new SString(lenOfString,id);
    // Concat name with string(id)
    name->concat(number->getString());
    // Title is now fixed
    //title->concat(name->getString());
    //title->concat(",");

    // Free allocated space
    //delete name;
    delete number;
    //TOTAL_Oreturn BJECTS--;
    return name;
}

SString* Object::toString(SString* ss)
{
    if(ss != NULL)
    {
        SString* number = new SString(id);

        ss->concat("[Object] [");
        //ss->concat("[");
        ss->concat(number->getString());
        ss->concat("] ");

        delete number;

        return ss;
    }
    else
    {
        ss->setString("[Object] [id] [");

        SString* number = new SString(id);

        ss->concat(number->getString());
        ss->concat("] ");

        delete number;

        return ss;
    }
    
}

bool Object::equal(Object& obj)
{
    if(obj.getId() == getId())
        return true;
    else
        return false;
}

bool Object::identical(Object& obj)
{
    if(&obj == this)
        return true;
    else
        return false;
}

// Default Constructor of SString
SString::SString()
{
    cout << "SString just created!\n ";
    //str = new char[strlen("") + 1];
    str = NULL;
    //strcpy(str,"");
}

SString::SString(const char*x)
: Object(++TOTAL_OBJECTS)
{
    str = new char[strlen(x)+1];
    strcpy(str,x);

    cout << "String just created!\n";

    //cout << str << endl;
}
// Paramerized constructor
SString::SString(const char* x,int k)
: Object(k)
{
    str = new char[strlen(x)+1];
    strcpy(str,x);
    //cout << "String just created!\n";
}

SString::SString(int size, int ID)
: Object(ID)
{
    str = new char(size+1);
    strcpy(str,"");
}

SString::SString(int id)
:   Object(++TOTAL_OBJECTS)
{ // Convert id to String
    string s;
    stringstream ss;
    ss << id;
    s = ss.str();

    str = new char[strlen(s.c_str()) + 1];
    strcpy(str,s.c_str());
}

SString::SString(const SString& oldSS)
:   Object(++TOTAL_OBJECTS),
    str(NULL)
{
    //cout << "copy constructor is called\n";
    str = new char[strlen(oldSS.str)+1];
    strcpy(str,oldSS.str);
    
}

SString& SString::operator=(const SString& oldS)
{
    //cout << "\nCopy assignment operator!\n";

    if(this != &oldS)
    {
        delete [] str;

        str = new char[strlen(oldS.str) + 1];

        strcpy(str,oldS.str);
    }

    return *this;
}
// Destructor of SString
SString::~SString()
{
    cout << "SString to be destroyed!\n";

    delete [] str;

    str = NULL;
}


const char* SString::getString()
{
    return str;
}

void SString::setString(const char*x)
{
    //str = NULL;
    delete [] str;
    str = NULL;

    str = new char[strlen(x)+1];
    strcpy(str,x);
}

int SString::length()
{
    if( str != NULL)
        return strlen(str);
    else 
        return 0;
}

void SString::clear()
{
    if(str != NULL)
    {
        delete [] str;

        str = NULL;
    }
}

void SString::concat(SString* add)
{
    if(str != NULL)
    {

        char* temp = new char[strlen(str) + add->length() + 1];
        strcpy(temp,str);
        strcat(temp,add->getString());

        delete [] str;
        str = NULL;

        str = new char[strlen(temp) + 1];
        strcpy(str,temp);

        delete [] temp;

    }else
        setString(add->getString());
}

void SString::concat(const char* add)
{   // Hold in temp the value of str
    // and make space for str+add 
    //cout << "add = " << add << endl;
    //print();
    //cout << "ime stin concat!\n";
    if( str != NULL)
    {
        //cout << "mpike sto != \n";
        char* temp = new char[strlen(str) + strlen(add) + 1];
        strcpy(temp,str);
        strcat(temp,add);

        delete [] str;
        str = NULL;

        str = new char[strlen(temp) + 1];
        
        strcpy(str,temp);

        delete [] temp;
        temp = NULL;
    }
    else 
    {
        //cout << "mpike sto == \n";
        setString(add);
    }
}

char SString::at(int pos)
{
    if( str != NULL)
        return str[pos];
    else 
        return ' ';
}

void SString::updateAt(int pos,char c)
{
    if( str != NULL)
        str[pos] = c;
    else
        cout << "There is an empty string!\n";
}

void SString::print()
{
    cout << str << endl;
}


bool SString::equal(Object& obj) 
{
    if(Object::equal(obj))
    {
        SString& temp = (SString&) obj;
       
        if(strcmp(temp.getString(),str) == 0)
            return true;
    }
    return false;
}

bool SString::identical(Object& objAddress) 
{
    return Object::identical(objAddress);    
}

Object* SString::clone()
{
    SString* cloned = new SString();

    *cloned = *this;

    return cloned;
}

SString* SString::toString() 
{   // temp has the value of Object::toString
    SString* temp = new SString("[Object] [id] ");

    SString *title = Object::toString(temp); //Object::toString();

    //title = temp;//Object::toString(temp);//new SString(*Object::toString());
    
    title->concat(",str = ");
    title->concat(str);
    title->concat(",String");

    //title->print();

    return title;
}


SString* SString::toString(SString* ss) 
{   // temp has the value of Object::toString

    if(ss->getString() != NULL) 
    {
        ss = Object::toString(ss);
        ss->concat(" [String] contains: ");
        ss->concat(" [String:str - ");
        ss->concat(str);
        ss->concat("] ");

        return ss;
    }
    else
    {
        //cout <<  " mpike!\n";
        //ss = new SString("[String]");

        //SString* temp = NULL;
        ss = Object::toString(ss);

        ss->concat("[String] ");
        ss->concat(" [String::str - ");
        ss->concat(str);
        ss->concat("] ");
        
        return ss;

    }
}



