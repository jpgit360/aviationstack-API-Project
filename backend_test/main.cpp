#include "aviation_data.h"
#include "trie.h"

int main() {
    Trie* test = new Trie();
    
    test->insert("race");
    test->insert("racecar");
    delete test; 



    /*std::string jsonFile = "../store/all_data.json";
    Json::Value jsonData = readJsonFile(jsonFile);

    auto start_time = std::chrono::high_resolution_clock::now();
    loadData(jsonData);
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto wall_clock = std::chrono::duration_cast<std::chrono::duration<double>> (curr_time - start_time);
    std::cout << "load took " << wall_clock.count() << " seconds" << std::endl;
 */
    //printUmm(airport_multimap);
    //printUmm(airline_multimap);
    //searchByAirline("SAS");
    //searchByAirport("Sydney Kingsford Smith Airport");

    return 0;
}