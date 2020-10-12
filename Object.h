#include <iostream>


extern int TOTAL_OBJECTS;
class SString;

class Object{
protected:
    int id;
public:
    //Object();
    Object(int=TOTAL_OBJECTS);
    virtual ~Object();

    virtual bool equal(Object&);
    virtual bool identical(Object&);
    virtual Object* clone() = 0;
    virtual SString* toString();
    virtual SString* toString(SString*);
    //virtual SString* toString(SString*, int);
    
    int getId();
    void setId(int);
};


class SString : public Object {
private:
    //int id;
    char* str;
public:
    SString();
    SString& operator=(const SString&);
    SString(const char*);
    SString(const char*,int);
    SString(int,int);
    SString(int); // Convert id to String
    SString(const SString&);
    ~SString();

    bool equal(Object&) override;
    bool identical(Object&) override;
    Object* clone() override;

    SString* toString() override;
    SString* toString(SString*) override;
    //SString* toString(SString*,int) override;

    int length();
    void clear();
    void concat(const char*);
    void concat(SString*);
    char at(int);
    void updateAt(int,char);

    //int getId();
    const char* getString();
    //void setId(int);
    void setString(const char*);

    void print();
};


