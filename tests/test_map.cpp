#include "catch.hpp"

#include "../basic_map_driver/basic_map_implement.cpp"
#include "../map_reduce_framework.h"
#include "../map_reduce_client.h"
#include "../easylogging++.h"

#include <atomic>
#include <iostream>


TEST_CASE("execute_map functionality tests, single thread")
{
    myMapReduceBase map_reduce_base;
    IN_ITEMS_LIST in_items;

    SECTION("use execute_map with one pair and a dummy index counter")
    {
        std::atomic<unsigned int> dummy_index(0);
        in_items.emplace_back(std::unique_ptr<const k1Base>(new myK1(1)), std::unique_ptr<const v1Base>(new myV1(2)));

        auto res = execute_map(map_reduce_base, in_items, dummy_index);


        auto result_key_ptr = std::move(res -> front().first);
        auto result_key = dynamic_cast<myK2 const *>(result_key_ptr.get());
        result_key_ptr.release();
        REQUIRE(result_key -> key == 2);


        auto result_value_ptr = std::move(res -> front().second);
        auto result_value = dynamic_cast<myV2 const *>(result_value_ptr.get());
        result_value_ptr.release();
        REQUIRE(result_value -> value == 3);

    }
}