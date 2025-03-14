#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


vector<vector<string>> readCSV(const string &filename) {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file at " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        vector<string> row;

        while (getline(ss, value, ',')) {
            row.push_back(value);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}


void generateHTML(const vector<vector<string>> &table) {
    if (table.size() < 21 || table[0].size() < 2) {
        cerr << "Error: Table does not have enough rows or columns!" << endl;
        return;
    }


    int A5 = stoi(table[5][1]);
    int A20 = stoi(table[20][1]);
    int A15 = stoi(table[15][1]);
    int A7 = stoi(table[7][1]);
    int A13 = stoi(table[13][1]);
    int A12 = stoi(table[12][1]);


    int Alpha = A5 + A20;
    double Beta = static_cast<double>(A15) / A7;
    int Charlie = A13 * A12;


    ofstream htmlFile("output.html");

    htmlFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>Table Output</title>\n";
    htmlFile << "<style> table { border-collapse: collapse; width: 50%; } ";
    htmlFile << "th, td { border: 1px solid black; padding: 8px; text-align: left; } ";
    htmlFile << "th { background-color: #f2f2f2; } </style>\n";
    htmlFile << "</head>\n<body>\n";


    htmlFile << "<h2>Table 1: Original CSV Data</h2>\n<table>\n<tr>";
    for (const auto &header : table[0]) {
        htmlFile << "<th>" << header << "</th>";
    }
    htmlFile << "</tr>\n";

    for (size_t i = 1; i < table.size(); i++) {
        htmlFile << "<tr>";
        for (const auto &col : table[i]) {
            htmlFile << "<td>" << col << "</td>";
        }
        htmlFile << "</tr>\n";
    }
    htmlFile << "</table>\n";

    htmlFile << "<h2>Table 2: Processed Data</h2>\n<table>\n<tr><th>Category</th><th>Value</th></tr>";
    htmlFile << "<tr><td>Alpha</td><td>" << Alpha << "</td></tr>";
    htmlFile << "<tr><td>Beta</td><td>" << Beta << "</td></tr>";
    htmlFile << "<tr><td>Charlie</td><td>" << Charlie << "</td></tr>";
    htmlFile << "</table>\n";

    htmlFile << "</body>\n</html>";
    htmlFile.close();

    cout << "HTML file 'output.html' has been generated successfully!" << endl;
}

int main() {
    string filename = "C:/Users/Acer/OneDrive/Desktop/Assesment Mula tech/Table_Input.csv";
    vector<vector<string>> table = readCSV(filename);

    generateHTML(table);

    return 0;
}

