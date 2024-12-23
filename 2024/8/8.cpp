#include <fstream>
#include <iostream>
#include <unordered_map>
#include "8.h"
#include <set>


std::pair<std::pair<int,int>, std::unordered_map<char, std::vector<std::pair<int,int>>>> process_char_grid(const std::string &fname) {
    std::ifstream myfile(fname);
    char c;
    auto n_line = 0;
    auto n_col = 0;
    std::unordered_map<char, std::vector<std::pair<int,int>>> antennas_positions;

    if (myfile.is_open()) {
        while(myfile.get(c)) {
            if (c != '.' && c != '\n') antennas_positions[c].push_back(std::make_pair(n_line, n_col));
            if (c == '\n') {
                n_col = 0;
                n_line++;
            } else n_col++;
        }
        myfile.close();
    } else std::cout << "Unable to open file";
    return std::make_pair(std::make_pair(n_line + 1, n_col), antennas_positions);
}

int count_antinodes(std::pair<int,int> grid_size, std::unordered_map<char, std::vector<std::pair<int,int>>> antennas_positions, bool with_harmonic) {
    std::set<std::pair<int,int>> antinodes_pos;
    for (const auto &[antenna_type, antennas_pos]: antennas_positions) {
        for (auto it = antennas_pos.begin(); it != antennas_pos.end(); ++it) {
            for (auto jt = it + 1; jt != antennas_pos.end(); ++jt) {
                auto x_delta = (*jt).first -(*it).first;
                auto y_delta = (*jt).second -(*it).second;
                auto i = 0;
                if (with_harmonic) {
                    while (true) {
                        auto x_pos = (*jt).first + i * x_delta;
                        auto y_pos = (*jt).second + i * y_delta;
                        if (x_pos < 0 || x_pos >= grid_size.first || y_pos < 0 || y_pos >= grid_size.second) break;
                        antinodes_pos.insert(std::make_pair(x_pos, y_pos));
                        i++;
                    }
                    i = 0;
                    while (true) {
                        auto x_pos = (*it).first - i * x_delta;
                        auto y_pos = (*it).second - i * y_delta;
                        if (x_pos >= 0 && x_pos < grid_size.first && y_pos >= 0 && y_pos < grid_size.second) break;
                        antinodes_pos.insert(std::make_pair(x_pos, y_pos));
                        i--;
                    }
                    
                } else {
                    auto antinode1 = std::make_pair((*jt).first + x_delta, (*jt).second + y_delta);
                    auto antinode2 = std::make_pair((*it).first - x_delta, (*it).second - y_delta);
                    if (antinode1.first >= 0 &&
                        antinode1.first < grid_size.first &&
                        antinode1.second >= 0 && 
                        antinode1.second < grid_size.second)
                        antinodes_pos.insert(antinode1);
                    if (antinode2.first >= 0 &&
                        antinode2.first < grid_size.first &&
                        antinode2.second >= 0 && 
                        antinode2.second < grid_size.second)
                        antinodes_pos.insert(antinode2);
                }
            }
        }
    }
    return antinodes_pos.size();
}
