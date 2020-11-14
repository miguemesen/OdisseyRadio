
#pragma once
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <string>

class csvparse
{
public:

    csvparse(const csvparse&) = delete;

    static csvparse& Get()
    {
        static csvparse instance;
        return instance;
    }

    static std::vector<std::vector<std::string>> myReadCsv(){return Get().Internal();}

private:

    std::vector<std::vector<std::string>> Internal()
    {
        std::ifstream ip("/home/migue/Desktop/fma_metadata/raw_tracks1.csv");
        return readCSV(ip);
    }

    std::vector<std::vector<std::string>> readCSV(std::istream &in);
    std::vector<std::string> readCSVRow(const std::string &row);
    csvparse();
};