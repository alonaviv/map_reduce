#include <memory>
#include <atomic>
#include "map_reduce_framework.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

std::unique_ptr<MapResultQueue> execute_map(mapReduceBase& map_reduce_base,
                                            const IN_ITEMS_LIST& input_vector,
                                            std::atomic<size_t >& current_batch_start_index,
                                            size_t batch_size)
{
    LOG(INFO) << "Starting map phase ";

    LOG(INFO) << "Creating queue";
    MapResultQueue* thread_map_result_queue = new MapResultQueue;

    while(current_batch_start_index.load() < input_vector.size())
    {
        size_t current_index = current_batch_start_index.fetch_add(batch_size);
        size_t end_of_current_batch = current_index + batch_size < input_vector.size() - 1 ?
                                      current_index + batch_size - 1 : input_vector.size() - 1;

        for (current_index; current_index <= end_of_current_batch; current_index++)
        {
            auto &key = *(input_vector[current_index].first);
            auto &value = *(input_vector[current_index].second);
            LOG(INFO) << "Running map function on key=" << key << ", value=" << value;
            thread_map_result_queue->emplace(map_reduce_base.Map(key, value));
        }
    }

    LOG(INFO) << "Finished map phase";
    return std::unique_ptr<MapResultQueue>(thread_map_result_queue);
};

OUT_ITEMS_LIST runMapReduceFramework(mapReduceBase &mapReduce, IN_ITEMS_LIST &itemsList, unsigned int multiThreadLevel)
{
    return OUT_ITEMS_LIST();
}


