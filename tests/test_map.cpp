#include "catch.hpp"

#include "../basic_map_driver/basic_map_implement.cpp"
#include "../map_reduce_framework.h"
#include "../map_reduce_client.h"
#include "../easylogging++.h"

#include <atomic>
#include <iostream>

void _emplace_pairs(IN_ITEMS_LIST& in_items, unsigned int num_of_pairs)
{
    for(unsigned i = 0; i < num_of_pairs; i++)
    {
        in_items.emplace_back(std::unique_ptr<const k1Base>(new myK1(i+1)),
                std::unique_ptr<const v1Base>(new myV1(i+2)));
    }

}

void _test_pair_results(std::unique_ptr<MapResultQueue> &res, unsigned int num_of_pairs)
{
    for (unsigned int i=0; i < num_of_pairs; i++)
    {
        LOG(INFO) << "Testing result pair #" << i;
        auto pair = std::move(res -> front());
        res -> pop();

        auto result_key_ptr = std::move(pair.first);
        auto result_key = dynamic_cast<myK2 const *>(result_key_ptr.get());
        result_key_ptr.release();
        REQUIRE(result_key->key == i + 2);


        auto result_value_ptr = std::move(pair.second);
        auto result_value = dynamic_cast<myV2 const *>(result_value_ptr.get());
        result_value_ptr.release();
        REQUIRE(result_value->value == i + 3);
    }
}

TEST_CASE("execute_map functionality tests, single thread")
{
    LOG(INFO) << "Starting a test";
    myMapReduceBase map_reduce_base;
    IN_ITEMS_LIST in_items;
    std::atomic<unsigned int> vector_index(0);


    SECTION("use execute_map with one pair and a dummy index counter")
    {
        _emplace_pairs(in_items, 1);
        auto res = execute_map(map_reduce_base, in_items, vector_index);
        _test_pair_results(res, 1);
        REQUIRE(vector_index.load() == 10);
    }

    SECTION("use execute_map with a few pairs, running a single fetch loop")
    {
        _emplace_pairs(in_items, 9);
        auto res = execute_map(map_reduce_base, in_items, vector_index);
        _test_pair_results(res, 9);
        REQUIRE(vector_index.load() == 10);
    }
}