#include "../include/utils.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @brief Parses the json file and stores the configurations.
 *
 * @param filename
 * @return configurations_t*
 */
configurations_t* load_configurations(const string& filename) {
    cout << "Loading configurations .." << endl;
    configurations_t* config = new configurations_t;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        istringstream iss(line);
        string key, value;

        size_t pos = line.find(':'); // pos = amount of chars before :
        if (pos != string::npos) {
            key = line.substr(0, pos); 
            value = line.substr(pos + 1);

            key.erase(remove(key.begin(), key.end(), '"'), key.end()); // remove "
            value.erase(remove(value.begin(), value.end(), '"'), value.end()); 

            if (key == "numberofrouters") {
                config->number_of_routers = stoi(value);
            } else if (key == "terminalsperrouter") {
                config->terminals_per_router = stoi(value);
            } else if (key == "adjacencymatrixfile") {
                config->adjacency_matrix_file = value;
            } else if (key == "bandwidthfile") {
                config->band_width_file = value;
            } else if (key == "maxpagesize") {
                config->max_page_size = stoi(value);
            }
        }
    }

    file.close();

    cout << "Number of routers: " << config->number_of_routers << endl;
    cout << "Terminals per router: " << config->terminals_per_router << endl;

    return config;
}
