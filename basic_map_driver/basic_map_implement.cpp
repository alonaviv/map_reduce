#include "../map_reduce_client.h"

class MyK1Base: public k1Base
{
public:
    int key;
    bool operator<(const k1Base &other) const override {return true;}
    explicit MyK1Base(int key): key(key){};
};

class MyV1Base: public v1Base
{
public:
    int value;
    explicit MyV1Base(int value): value(value){};
};


class MyK2Base: public k2Base
{
public:
    int key;
    bool operator<(const k2Base &other)const override {return true;}
    explicit MyK2Base(int key): key(key){};
};

class MyV2Base: public v2Base
{
public:
    int value;
    explicit MyV2Base(int value): value(value){};
};


class MyMapReduceBase: public MapReduceBase
{
public:
    std::pair<k2Base, v2Base> Map(k1Base const key, v1Base const val) override const
    {
        return std::make_pair(MyK2Base(key.int))
    }

};