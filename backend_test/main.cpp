#include "aviation_data.h"
#include "trie.h"

int main() {
    std::string jsonFile = "../store/all_data.json";
    Json::Value jsonData = readJsonFile(jsonFile);

    auto start_time = std::chrono::high_resolution_clock::now();
    loadData(jsonData);
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto wall_clock = std::chrono::duration_cast<std::chrono::duration<double>> (curr_time - start_time);
    std::cout << "load took " << wall_clock.count() << " seconds" << std::endl;
    
    std::string input;
    std::cout << "Enter airline or airport to search... ";
    std::getline(std::cin, input);
    word_trie.autocomplete(transformString(input));
    
    //print out vector of autocomplete words
    std::vector<std::string> vec = word_trie.getAutocompleteWords();
    int index = 0;
    std::cout << "-----------Autocompleted results-----------\n";
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << index << ". " << *it << std::endl;
        index++;
        //searchByAirline(*it);
        //searchByAirport(*it);
    }

    int intInput;
    std::cout << "Which # result?: ";
    std::cin >> intInput;
    if(intInput < vec.size() && intInput >= 0) {
        searchByAirline(vec[intInput]);
        searchByAirport(vec[intInput]);
    } else {
        std::cout << "invalid input\n";
    }

    //printUmm(airport_multimap);
    //printUmm(airline_multimap);
    //searchByAirline("SAS");
    //searchByAirport("Sydney Kingsford Smith Airport");
    //searchByAirport("Mc Carran International");

    return 0;
}