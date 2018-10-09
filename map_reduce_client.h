#ifndef MAPREDUCECLIENT_H
#define MAPREDUCECLIENT_H

#include <list>
#include <memory>
#include <iostream>

//input key and value.
//the key, value for the map function and the MapReduceFramework
class k1Base {
public:
	virtual ~k1Base(){}
    virtual bool operator<(const k1Base &other) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const k1Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "<k1Base>"; return os;};
};

class v1Base {
public:
	virtual ~v1Base() {}
    friend std::ostream& operator<<(std::ostream& os, const v1Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "<v1Base>"; return os;};
};

//intermediate key and value.
//the key, value for the Reduce function created by the Map function
class k2Base {
public:
	virtual ~k2Base(){}
    virtual bool operator<(const k2Base &other) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const k2Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "<k2Base>"; return os;};
};

class v2Base {
public:
	v2Base(){std::cout << "In v2Base ctor" << std::endl;}
	virtual ~v2Base(){std::cout << "In v2Base dtor" << std::endl;}
    friend std::ostream& operator<<(std::ostream& os, const v2Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "<v2Base>"; return os;};
};

//output key and value
//the key,value for the Reduce function created by the Map function
class k3Base {
public:
	virtual ~k3Base()  {}
    virtual bool operator<(const k3Base &other) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const k3Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "<k3Base>"; return os;};
};

class v3Base {
public:
	virtual ~v3Base() {}
    friend std::ostream& operator<<(std::ostream& os, const v3Base& other) {return other.print(os);}
    virtual std::ostream& print(std::ostream& os) const {os << "v3Base>"; return os;};
};

typedef std::list<v2Base *> V2_LIST;
typedef std::pair<std::unique_ptr<const k2Base>, std::unique_ptr<const v2Base>> MapResult;


class mapReduceBase {
public:
    virtual MapResult Map(const k1Base& key, const v1Base& val) = 0;
    //virtual void Reduce(k2Base * key, const V2_LIST &vals) = 0;
};


#endif //MAPREDUCECLIENT_H
