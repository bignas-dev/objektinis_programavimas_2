/**
 * @file test_vector_iterators.cpp
 * @brief Vector iteratorių testai
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Vector.h"
#include <algorithm>

TEST_CASE("Vector Iterators", "[Vector][iterators]") {
    
    SECTION("begin and end") {
        Vector<int> v{1, 2, 3, 4, 5};
        REQUIRE(v.begin() != nullptr);
        REQUIRE(v.end() != nullptr);
        REQUIRE(v.end() - v.begin() == 5);
    }
    
    SECTION("iterator increment") {
        Vector<int> v{10, 20, 30, 40, 50};
        auto it = v.begin();
        
        REQUIRE(*it == 10);
        ++it;
        REQUIRE(*it == 20);
        ++it;
        REQUIRE(*it == 30);
    }
    
    SECTION("iterator dereference") {
        Vector<int> v{100, 200, 300};
        auto it = v.begin();
        
        *it = 999;
        REQUIRE(v[0] == 999);
    }
    
    SECTION("iterator comparison") {
        Vector<int> v{1, 2, 3};
        auto it1 = v.begin();
        auto it2 = v.begin();
        auto it3 = v.end();
        
        REQUIRE(it1 == it2);
        REQUIRE(it1 != it3);
    }
    
    SECTION("range-based for loop") {
        Vector<int> v{1, 2, 3, 4, 5};
        int sum = 0;
        
        for (int val : v) {
            sum += val;
        }
        
        REQUIRE(sum == 15);
    }
    
    SECTION("iterator arithmetic") {
        Vector<int> v{10, 20, 30, 40, 50};
        
        REQUIRE(*(v.begin() + 2) == 30);
        REQUIRE(*(v.end() - 1) == 50);
    }
    
    SECTION("std::sort with iterators") {
        Vector<int> v{5, 2, 8, 1, 9};
        std::sort(v.begin(), v.end());
        
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 5);
        REQUIRE(v[3] == 8);
        REQUIRE(v[4] == 9);
    }
    
    SECTION("std::find with iterators") {
        Vector<int> v{10, 20, 30, 40, 50};
        auto it = std::find(v.begin(), v.end(), 30);
        
        REQUIRE(it != v.end());
        REQUIRE(*it == 30);
        
        auto not_found = std::find(v.begin(), v.end(), 100);
        REQUIRE(not_found == v.end());
    }
}
