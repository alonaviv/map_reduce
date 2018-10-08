#include <memory>
#include <atomic>
#include "map_reduce_framework.h"
#include "easylogging++.h"
#include <iostream>

INITIALIZE_EASYLOGGINGPP

std::unique_ptr<MapResultQueue> execute_map(mapReduceBase& map_reduce_base,
                                            IN_ITEMS_LIST& input_vector,
                                            std::atomic<unsigned int>& next_batch_index,
                                            unsigned int batch_size)
{
    LOG(INFO) << "Starting execute_map ";
    LOG(INFO) << "Creating queue";
    MapResultQueue* thread_map_result_queue = new MapResultQueue;

    while(next_batch_index.load() < input_vector.size())
    {
        LOG(INFO) << "In loop. next_batch_index=" << next_batch_index.load();
        unsigned int current_index = next_batch_index.fetch_add(batch_size);
        LOG(INFO) << "Got current index = " << current_index << ". Current vector size is " << input_vector.size();
        if(current_index < input_vector.size())
        {
            auto &key = *(input_vector[current_index].first);
            auto &value =  *(input_vector[current_index].second);
            LOG(INFO) << "Running map function on key=" << key << ", value=" << value;
            thread_map_result_queue -> emplace(map_reduce_base.Map(key, value));
            LOG(INFO) << "Ran map. result is " << *(thread_map_result_queue->front().first) << " " <<
                      *(thread_map_result_queue -> front().second);
        }
    }
    LOG(INFO) << "Finished loop. Now next batch index is " << next_batch_index.load();
    LOG(INFO) << "Ending execute_map ";
    return std::unique_ptr<MapResultQueue>(thread_map_result_queue);

};

OUT_ITEMS_LIST runMapReduceFramework(mapReduceBase &mapReduce, IN_ITEMS_LIST &itemsList, unsigned int multiThreadLevel)
{
    return OUT_ITEMS_LIST();
}


