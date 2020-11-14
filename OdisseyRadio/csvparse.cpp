#include <istream>
#include <string>
#include <istream>
#include <sstream>
#include <bits/stdc++.h>
#include <vector>
#include "csvparse.h"
#define log(x) std::cout<<x<<std::endl;







/**
 * @brief The CSVState enum
 */
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};


csvparse::csvparse()
{

}

/**
  Reads a row and returns it as an element in a vector
 * @brief readCSVRow
 * @param row
 * @return
 */

std::vector<std::string> csvparse::readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}


/**
  Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
 * @brief readCSV
 * @param in
 * @return CSV file in form of a matrix
 */

std::vector<std::vector<std::string>> csvparse::readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}



















