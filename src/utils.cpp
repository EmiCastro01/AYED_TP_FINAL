#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "../include/utils.hpp"

using namespace std;


configurations_t* load_configurations(const string& filename) {
    cout << "Loading configurations" << endl;
    configurations_t *config = new configurations_t;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        // Eliminar espacios y comas
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        line.erase(remove(line.begin(), line.end(), ','), line.end());

        istringstream iss(line);
        string key, value;

        // Dividir la línea en clave y valor
        size_t pos = line.find(':');
        if (pos != string::npos) {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);

            // Eliminar comillas
            key.erase(remove(key.begin(), key.end(), '"'), key.end());
            value.erase(remove(value.begin(), value.end(), '"'), value.end());

            // Asignar valores a la estructura de configuración
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

    // Imprimir la configuración para verificar
    cout << "Number of routers: " << config->number_of_routers << endl;
    cout << "Terminals per router: " << config->terminals_per_router << endl;
    cout << "Adjacency matrix file: " << config->adjacency_matrix_file << endl;
    cout << "Band width file: " << config->band_width_file << endl;
    cout << "Max page size: " << config->max_page_size << endl;
  return config;
}

