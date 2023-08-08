#include "mainwindow.h"
#include "aviation_data.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::string jsonFile = "C:/Users/jfpth/OneDrive/Desktop/aviationstack API Project/all_data.json";
    Json::Value jsonData = readJsonFile(jsonFile);

    auto start_time = std::chrono::high_resolution_clock::now();
    loadData(jsonData);
    auto curr_time = std::chrono::high_resolution_clock::now();
    auto wall_clock = std::chrono::duration_cast<std::chrono::duration<double>> (curr_time - start_time);
    std::cout << "load took " << wall_clock.count() << " seconds" << std::endl;

    //printUmm(airport_multimap);
    //printUmm(airline_multimap);
    searchByAirline("SAS");
    //searchByAirport("Sydney Kingsford Smith Airport");

    return a.exec();
}
