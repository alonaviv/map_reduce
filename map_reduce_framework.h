#ifndef MAPREDUCEFRAMEWORK_H
#define MAPREDUCEFRAMEWORK_H

#include "map_reduce_client.h"
#include <vector>

typedef std::pair<k1Base, v1Base> IN_ITEM;
typedef std::pair<k3Base, v3Base> OUT_ITEM;

typedef std::vector<IN_ITEM> IN_ITEMS_LIST;
typedef std::list<OUT_ITEM> OUT_ITEMS_LIST;

OUT_ITEMS_LIST runMapReduceFramework(MapReduceBase& mapReduce, IN_ITEMS_LIST& itemsList, unsigned int multiThreadLevel);

#endif //MAPREDUCEFRAMEWORK_H
