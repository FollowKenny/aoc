#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <sstream>
#include <string>
using namespace std;

inline vector<string> splitOnSpaces(const string &input)
{
    istringstream stream(input);
    return {istream_iterator<string>(stream), istream_iterator<string>()};
}

#endif
