#include "aviation_data.h"
#include "trie.h"

int main() {
    /* Trie* test = new Trie();
    
    test->insert("apple");
    test->insert("apricot");
    test->insert("artichoke");
    test->insert("ant");
    test->insert("airplane");
    test->insert("almond");
    test->insert("armadillo");
    test->insert("alligator");
    test->insert("asparagus");

    std::string word;
    std::cout << "Enter word to autocomplete: ";
    std::cin >> word;
    test->autocomplete(word);

    //print out vector of autocomplete words
    std::vector<std::string> vec = test->getAutocompleteWords();
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }

    delete test;  */

    std::string jsonFile = "../store/all_data.json";
    Json::Value jsonData = readJsonFile(jsonFile);

    auto start_time = std::chrono::high_resolution_clock::now();
    loadData(jsonData);
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto wall_clock = std::chrono::duration_cast<std::chrono::duration<double>> (curr_time - start_time);
    std::cout << "load took " << wall_clock.count() << " seconds" << std::endl;
    
    std::string input;
    std::cout << "Enter word to autocomplete: ";
    std::getline(std::cin, input);
    word_trie.autocomplete(transformString(input));
    
    //print out vector of autocomplete words
    std::vector<std::string> vec = word_trie.getAutocompleteWords();
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }

    //printUmm(airport_multimap);
    //printUmm(airline_multimap);
    //searchByAirline("SAS");
    //searchByAirport("Sydney Kingsford Smith Airport");

    return 0;
}