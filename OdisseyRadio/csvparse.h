#pragma once
#include <iostream>
#include <vector>

class csvparse
{
public:
    std::vector<std::vector<std::string>> readCSV(std::istream &in);
    std::vector<std::string> readCSVRow(const std::string &row);
    csvparse();
};

