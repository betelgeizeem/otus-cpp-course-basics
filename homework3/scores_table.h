#pragma once 
#include <string> 
#include <map> 

class Scores_table
{
public:
    int show();
    int add(const std::string& username, std::size_t value);
    int clear();
    int read();
private:
    std::string filename = "high_scores.txt";
    std::map<std::string, size_t> chart;
    bool chart_ready = false;
};