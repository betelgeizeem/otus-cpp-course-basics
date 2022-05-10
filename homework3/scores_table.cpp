#include "scores_table.h"

#include <fstream>
#include <iostream>

int Scores_table::show()
{   
    // if the chart is not ready, read it from file
    if (!chart_ready)
    {
        auto failed = read();
        if (failed)
            return -1;
    }
    
    std::cout << "High scores table:" << std::endl;
    for (auto& [username, score] : chart)
        std::cout << username << "\t" << score << std::endl;

    return 0;
}

int Scores_table::read()
{
    // open file
    std::ifstream in_file{filename, std::ios::in};
    if (!in_file.is_open()) 
    {
        std::cout << "Failed to open file for read: " << filename << std::endl;
        std::cout << "Creating new file... ";
        if (clear())
            return -1;
        else 
        {
            std::cout << "OK" << std::endl;
            return 0;
        }
    }

    // read file to std::map<name, score>
    while (true) 
    {
        std::string username;
        int high_score = 0;

        in_file >> username;
        
        if (username.empty()) break;
        
        in_file >> high_score;

        in_file.ignore();

        if (chart.find(username) == std::end(chart))
            chart[username] = high_score;
        else if (chart[username] > high_score)
            chart[username] = high_score;

        if (in_file.fail()) 
            break;
    }

    // chart is ready to use
    chart_ready = true;

    return 0;
}

int Scores_table::add(const std::string& username, std::size_t value)
{   
    if (!chart_ready)
    {
        auto failed = read();
        if (failed)
            failed = clear();
        if (failed)
            return -1;
    }

    // replace or append data to map
    if (chart.find(username) == std::end(chart) || chart[username] > value)
            chart[username] = value;

    // write map to file
    std::ofstream file{filename};
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file for write: " << filename << std::endl;
        return -1;
    }

    for (auto& [name, value] : chart)
        file << name << " " << value << std::endl;

    return 0;
}

int Scores_table::clear()
{   
    // open and trunc file
    std::ofstream file{filename, std::ofstream::out | std::ofstream::trunc};
    if (!file.is_open()) 
    {
        std::cout << "Failed to open file " << filename << std::endl;
        return -1;
    }

    // clear map and set flag to true
    chart.clear();
    chart_ready = true;

    return 0;
}