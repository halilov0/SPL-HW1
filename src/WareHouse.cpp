#include <fstream>
#include "WareHouse.h"
#include <iostream>
#include <sstream>
using namespace std;

WareHouse::WareHouse(const string &configFilePath) 
{
    string filePath = configFilePath; // replace with your own file path
    ifstream inputFile(filePath);
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line, '\n'))
        {
            string word;
            stringstream lines(line);
            vector<string> v;
            while (getline(lines, word, ' ')) 
                v.push_back(word);
            for (int i = 0; i < v.size(); i++)
            {
                cout << v[i] << endl;
            }
        }
        inputFile.close();
    }   
}

void WareHouse::start(){}