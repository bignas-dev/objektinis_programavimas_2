/**
 * @file test_vector.cpp
 * @brief Catch2 unit testai Vector konteineriui
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Vector.h"
#include <stdexcept>

TEST_CASE("Vector Constructors", "[Vector][constructors]") {
    
    SECTION("Default Constructor") {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 0);
        REQUIRE(v.empty() == true);
    }
    
    SECTION("Constructor with Size") {
        Vector<int> v(5, 42);
        REQUIRE(v.size() == 5);
        REQUIRE(v.capacity() == 5);
        for (size_t i = 0; i < 5; ++i) {
            REQUIRE(v[i] == 42);
        }
    }
    
    SECTION("Copy Constructor") {
        Vector<int> v1{1, 2, 3, 4, 5};
        Vector<int> v2(v1);
        REQUIRE(v2.size() == 5);
        REQUIRE(v2 == v1);
        
        // Modify original - copy should not change
        v1.push_back(6);
        REQUIRE(v1.size() == 6);
        REQUIRE(v2.size() == 5);
    }
    
    SECTION("Move Constructor") {
        Vector<int> v1{1, 2, 3, 4, 5};
        size_t original_size = v1.size();
        Vector<int> v2(std::move(v1));
        REQUIRE(v2.size() == original_size);
        REQUIRE(v1.size() == 0);
        REQUIRE(v1.empty() == true);
    }
    
    SECTION("Initializer List Constructor") {
        Vector<int> v{10, 20, 30, 40, 50};
        REQUIRE(v.size() == 5);
        REQUIRE(v[0] == 10);
        REQUIRE(v[4] == 50);
    }
}

TEST_CASE("Vector Capacity", "[Vector][capacity]") {
    
    SECTION("size() and capacity()") {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 0);
        
        v.push_back(1);
        REQUIRE(v.size() == 1);
        REQUIRE(v.capacity() == 1);
        
        v.push_back(2);
        REQUIRE(v.size() == 2);
        REQUIRE(v.capacity() == 2);
        
        v.push_back(3);
        REQUIRE(v.size() == 3);
        REQUIRE(v.capacity() == 4);  // Doubled
    }
    
    SECTION("empty()") {
        Vector<int> v;
        REQUIRE(v.empty() == true);
        
        v.push_back(1);
        REQUIRE(v.empty() == false);
        
        v.clear();
        REQUIRE(v.empty() == true);
        REQUIRE(v.size() == 0);
    }
    
    SECTION("reserve()") {
        Vector<int> v;
        v.reserve(100);
        REQUIRE(v.capacity() >= 100);
        REQUIRE(v.size() == 0);
    }
    
    SECTION("shrink_to_fit()") {
        Vector<int> v;
        for (int i = 0; i < 100; ++i) {
            v.push_back(i);
        }
        REQUIRE(v.capacity() >= 100);
        
        v.clear();
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() >= 100);
        
        v.shrink_to_fit();
        REQUIRE(v.capacity() == 0);
    }
}

TEST_CASE("Vector Element Access", "[Vector][access]") {
    
    SECTION("operator[]") {
        Vector<int> v{10, 20, 30, 40, 50};
        REQUIRE(v[0] == 10);
        REQUIRE(v[2] == 30);
        REQUIRE(v[4] == 50);
        
        v[2] = 99;
        REQUIRE(v[2] == 99);
    }
    
    SECTION("at() with bounds checking") {
        Vector<int> v{1, 2, 3};
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(2) == 3);
        
        REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
        REQUIRE_THROWS_AS(v.at(100), std::out_of_range);
    }
    
    SECTION("front() and back()") {
        Vector<int> v{1, 2, 3, 4, 5};
        REQUIRE(v.front() == 1);
        REQUIRE(v.back() == 5);
        
        v.front() = 10;
        v.back() = 50;
        REQUIRE(v.front() == 10);
        REQUIRE(v.back() == 50);
    }
    
    SECTION("data()") {
        Vector<int> v{1, 2, 3, 4, 5};
        int* ptr = v.data();
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr[0] == 1);
        REQUIRE(ptr[4] == 5);
    }
}

TEST_CASE("Vector Modifiers", "[Vector][modifiers]") {
    
    SECTION("push_back() and pop_back()") {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        
        REQUIRE(v.size() == 3);
        REQUIRE(v.back() == 3);
        
        v.pop_back();
        REQUIRE(v.size() == 2);
        REQUIRE(v.back() == 2);
        
        v.pop_back();
        v.pop_back();
        REQUIRE(v.empty() == true);
    }
    
    SECTION("clear()") {
        Vector<int> v{1, 2, 3, 4, 5};
        REQUIRE(v.size() == 5);
        
        v.clear();
        REQUIRE(v.size() == 0);
        REQUIRE(v.empty() == true);
    }
    
    SECTION("insert()") {
        Vector<int> v{1, 2, 3, 4, 5};
        v.insert(2, 99);  // Insert at position 2
        REQUIRE(v.size() == 6);
        REQUIRE(v[2] == 99);
        REQUIRE(v[3] == 3);  // Original element shifted
    }
    
    SECTION("erase()") {
        Vector<int> v{1, 2, 3, 4, 5};
        v.erase(2);  // Erase element at position 2
        REQUIRE(v.size() == 4);
        REQUIRE(v[2] == 4);  // Next element shifted
    }
}

TEST_CASE("Vector Assignment Operators", "[Vector][assignment]") {
    
    SECTION("Copy Assignment") {
        Vector<int> v1{1, 2, 3, 4, 5};
        Vector<int> v2;
        v2 = v1;
        REQUIRE(v2 == v1);
        REQUIRE(v2.size() == 5);
    }
    
    SECTION("Move Assignment") {
        Vector<int> v1{1, 2, 3, 4, 5};
        Vector<int> v2;
        v2 = std::move(v1);
        REQUIRE(v2.size() == 5);
        REQUIRE(v1.size() == 0);
    }
    
    SECTION("Self Assignment") {
        Vector<int> v{1, 2, 3};
        v = v;  // Should not crash
        REQUIRE(v.size() == 3);
    }
}

TEST_CASE("Vector Comparison Operators", "[Vector][comparison]") {
    
    SECTION("operator==") {
        Vector<int> v1{1, 2, 3};
        Vector<int> v2{1, 2, 3};
        Vector<int> v3{1, 2, 4};
        
        REQUIRE(v1 == v2);
        REQUIRE(!(v1 == v3));
    }
    
    SECTION("operator!=") {
        Vector<int> v1{1, 2, 3};
        Vector<int> v2{1, 2, 3};
        Vector<int> v3{1, 2, 4};
        
        REQUIRE(!(v1 != v2));
        REQUIRE(v1 != v3);
    }
}

TEST_CASE("Vector Iterators", "[Vector][iterators]") {
    
    SECTION("begin() and end()") {
        Vector<int> v{1, 2, 3, 4, 5};
        int sum = 0;
        for (auto it = v.begin(); it != v.end(); ++it) {
            sum += *it;
        }
        REQUIRE(sum == 15);
    }
    
    SECTION("Range-based for loop") {
        Vector<int> v{1, 2, 3, 4, 5};
        int sum = 0;
        for (int val : v) {
            sum += val;
        }
        REQUIRE(sum == 15);
    }
}

TEST_CASE("Vector Memory Reallocation Counting", "[Vector][performance]") {
    
    SECTION("Count reallocations for 100M elements") {
        Vector<int> v;
        size_t reallocations = 0;
        size_t old_capacity = 0;
        
        for (int i = 0; i < 100000000; ++i) {
            if (v.capacity() != old_capacity) {
                reallocations++;
                old_capacity = v.capacity();
            }
            v.push_back(i);
        }
        
        REQUIRE(v.size() == 100000000);
        // Should be around 27-28 reallocations (log2(100M) ≈ 27)
        REQUIRE(reallocations < 35);
        REQUIRE(reallocations > 20);
    }
}
