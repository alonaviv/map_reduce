#ifndef MAPREDUCEFRAMEWORK_H
#define MAPREDUCEFRAMEWORK_H

#include "map_reduce_client.h"
#include <vector>
#include <queue>

typedef std::pair<std::unique_ptr<const k1Base>, std::unique_ptr<const v1Base>> IN_ITEM;
typedef std::pair<std::unique_ptr<k3Base>, std::unique_ptr<v3Base>> OUT_ITEM;

typedef std::vector<IN_ITEM> IN_ITEMS_LIST;
typedef std::list<OUT_ITEM> OUT_ITEMS_LIST;

OUT_ITEMS_LIST runMapReduceFramework(mapReduceBase& mapReduce, IN_ITEMS_LIST& itemsList, unsigned int multiThreadLevel);


typedef std::queue<MapResult> MapResultQueue;

std::unique_ptr<MapResultQueue> execute_map(mapReduceBase& map_reduce_base,
                                            const IN_ITEMS_LIST& input_vector,
                                            std::atomic<size_t >& current_batch_start_index,
                                            size_t batch_size=10);

#endif //MAPREDUCEFRAMEWORK_H
