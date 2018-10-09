#include "../map_reduce_client.h"

class myK1: public k1Base
{
public:
    int key;
    bool operator<(const k1Base &other) const override {return true;}
    explicit myK1(int key): key(key){};
    std::ostream& print(std::ostream& os) const override {os << "<K1: key=" << key << ">"; return os;}
};

class myV1: public v1Base
{
public:
    int value;
    explicit myV1(int value): value(value){};
    std::ostream& print(std::ostream& os) const override {os << "<V1: key=" << value << ">"; return os;}

};


class myK2: public k2Base
{
public:
    int key;
    bool operator<(const k2Base &other)const override {return true;}
    explicit myK2(int key): key(key){};
    std::ostream& print(std::ostream& os) const override {os << "<K2: key=" << key << ">"; return os;}

};

class myV2: public v2Base
{
public:
    int value;
    explicit myV2(int value): value(value){};
    std::ostream& print(std::ostream& os) const override {os << "<V2: key=" << value << ">"; return os;}
    ~myV2() override {std::cout << "Destructing myV2!" << std::endl;}
    myV2(){std::cout << "Constructing myV2!" << std::endl;}
};



class myMapReduceBase: public mapReduceBase
{
public:
     MapResult Map(const k1Base& key, const v1Base& val) override
    {

        auto my_key = dynamic_cast<const myK1&>(key);
        auto my_value = dynamic_cast<const myV1&>(val);

        return {std::unique_ptr<const k2Base>(new myK2(my_key.key + 1)),
                std::unique_ptr<const v2Base>(new myV2(my_value.value + 1))};
    }
};