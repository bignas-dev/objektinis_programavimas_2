/**
 * @file test_vector_std.cpp
 * @brief Vector vs std::vector funkcionalumo palyginimo testai
 * 
 * Šie testai patikrina ar Vector elgiasi taip pat kaip std::vector
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../Vector.h"
#include <vector>

TEST_CASE("Vector matches std::vector behavior", "[Vector][compatibility]") {
    
    SECTION("push_back sequence") {
        Vector<int> v_custom;
        std::vector<int> v_std;
        
        for (int i = 0; i < 100; ++i) {
            v_custom.push_back(i);
            v_std.push_back(i);
        }
        
        REQUIRE(v_custom.size() == v_std.size());
        REQUIRE(v_custom.capacity() >= v_std.size());
        
        for (size_t i = 0; i < v_std.size(); ++i) {
            REQUIRE(v_custom[i] == v_std[i]);
        }
    }
    
    SECTION("copy constructor") {
        std::vector<int> v_std{1, 2, 3, 4, 5};
        Vector<int> v_custom{1, 2, 3, 4, 5};
        
        std::vector<int> v_std_copy = v_std;
        Vector<int> v_custom_copy(v_custom);
        
        REQUIRE(v_custom_copy.size() == v_std_copy.size());
        for (size_t i = 0; i < v_std_copy.size(); ++i) {
            REQUIRE(v_custom_copy[i] == v_std_copy[i]);
        }
    }
    
    SECTION("assignment operator") {
        std::vector<int> v_std{1, 2, 3};
        Vector<int> v_custom{1, 2, 3};
        
        std::vector<int> v_std_assign;
        Vector<int> v_custom_assign;
        
        v_std_assign = v_std;
        v_custom_assign = v_custom;
        
        REQUIRE(v_custom_assign.size() == v_std_assign.size());
        for (size_t i = 0; i < v_std_assign.size(); ++i) {
            REQUIRE(v_custom_assign[i] == v_std_assign[i]);
        }
    }
    
    SECTION("pop_back sequence") {
        std::vector<int> v_std{1, 2, 3, 4, 5};
        Vector<int> v_custom{1, 2, 3, 4, 5};
        
        while (!v_std.empty()) {
            REQUIRE(v_custom.back() == v_std.back());
            v_std.pop_back();
            v_custom.pop_back();
        }
        
        REQUIRE(v_custom.empty() == v_std.empty());
    }
    
    SECTION("insert at position") {
        std::vector<int> v_std{1, 2, 3, 4, 5};
        Vector<int> v_custom{1, 2, 3, 4, 5};
        
        v_std.insert(v_std.begin() + 2, 99);
        v_custom.insert(2, 99);
        
        REQUIRE(v_custom.size() == v_std.size());
        for (size_t i = 0; i < v_std.size(); ++i) {
            REQUIRE(v_custom[i] == v_std[i]);
        }
    }
    
    SECTION("erase at position") {
        std::vector<int> v_std{1, 2, 3, 4, 5};
        Vector<int> v_custom{1, 2, 3, 4, 5};
        
        v_std.erase(v_std.begin() + 2);
        v_custom.erase(2);
        
        REQUIRE(v_custom.size() == v_std.size());
        for (size_t i = 0; i < v_std.size(); ++i) {
            REQUIRE(v_custom[i] == v_std[i]);
        }
    }
    
    SECTION("clear operation") {
        std::vector<int> v_std{1, 2, 3, 4, 5};
        Vector<int> v_custom{1, 2, 3, 4, 5};
        
        v_std.clear();
        v_custom.clear();
        
        REQUIRE(v_custom.size() == v_std.size());
        REQUIRE(v_custom.empty() == v_std.empty());
    }
    
    SECTION("reserve and capacity") {
        std::vector<int> v_std;
        Vector<int> v_custom;
        
        v_std.reserve(1000);
        v_custom.reserve(1000);
        
        REQUIRE(v_custom.capacity() >= 1000);
        REQUIRE(v_std.capacity() >= 1000);
        REQUIRE(v_custom.size() == v_std.size());
    }
    
    SECTION("front and back") {
        std::vector<int> v_std{10, 20, 30, 40, 50};
        Vector<int> v_custom{10, 20, 30, 40, 50};
        
        REQUIRE(v_custom.front() == v_std.front());
        REQUIRE(v_custom.back() == v_std.back());
        
        v_custom.front() = 100;
        v_custom.back() = 500;
        
        REQUIRE(v_custom.front() == 100);
        REQUIRE(v_custom.back() == 500);
    }
    
    SECTION("equality operator") {
        Vector<int> v1{1, 2, 3};
        Vector<int> v2{1, 2, 3};
        Vector<int> v3{1, 2, 4};
        
        std::vector<int> std_v1{1, 2, 3};
        std::vector<int> std_v2{1, 2, 3};
        std::vector<int> std_v3{1, 2, 4};
        
        REQUIRE((v1 == v2) == (std_v1 == std_v2));
        REQUIRE((v1 == v3) == (std_v1 == std_v3));
        REQUIRE((v1 != v3) == (std_v1 != std_v3));
    }
}
