#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

vector<string> splitOnSpaces(const string &input)
{
    std::istringstream stream(input);
    return {istream_iterator<string>(stream), istream_iterator<string>()};
}

int main()
{
    string line;
    ifstream myfile("data.tsv");
    vector<int> team1Locations;
    vector<int> team2Locations;
    int result = 0;

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            int i = 0;
            vector<string> locations = splitOnSpaces(line);
            for (const auto &location : locations)
            {
                i % 2 == 0 ? team1Locations.push_back(stoi(location)) : team2Locations.push_back(stoi(location));
                i++;
            }
        }
        myfile.close();
        sort(team1Locations.begin(), team1Locations.end());
        sort(team2Locations.begin(), team2Locations.end());
        for (unsigned int i = 0; i < team1Locations.size(); i++)
        {
            result += abs(team1Locations[i] - team2Locations[i]);
        }
        cout << result;
    }

    else
        cout << "Unable to open file";

    return 0;
}
