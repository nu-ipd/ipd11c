# Configuration for building example C programs.
cmake_minimum_required(VERSION 3.10)
project(ipd11c C)
include(.ipd/cmake/CMakeLists.txt)

add_c_test_program(test_graph
        test/test_graph.c
        src/graph.c
        ASAN)

add_c_test_program(test_graph_search
        test/test_graph_search.c
        src/graph.c
        src/graph_search.c
        ASAN)

add_c_test_program(ipd11c-2
        exercise/ipd11c-2.c
        src/graph.c
        ASAN)