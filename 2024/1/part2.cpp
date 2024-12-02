#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "utils.h"
#include <algorithm>
#include <unordered_map>
using namespace std;

int main()
{
    string line;
    ifstream myfile("data.tsv");
    std::unordered_map<int, int> team1Counters;
    std::unordered_map<int, int> team2Counters;

    int result = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            int i = 0;
            vector<string> locations = splitOnSpaces(line);
            for (const auto &location : locations)
            {
                i % 2 == 0 ? team1Counters[stoi(location)]++ : team2Counters[stoi(location)]++;
                i++;
            }
        }
        myfile.close();

        for (auto &[key, value] : team1Counters)
        {
            result += key * team2Counters[key] * value;
        }
        cout << result;
    }

    else
        cout << "Unable to open file";

    return 0;
}
