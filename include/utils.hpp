#pragma once
#include <iostream>

using namespace std;

typedef struct {
    int number_of_routers;
    int terminals_per_router;
    string adjacency_matrix_file;
    string band_width_file;
    int max_page_size;
} configurations_t;
