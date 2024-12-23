#ifndef ANTENNA_H
#define ANTENNA_H

#include <string>
#include <unordered_map>
#include <vector>

std::pair<std::pair<int,int>, std::unordered_map<char, std::vector<std::pair<int,int>>>> process_char_grid(const std::string &fname);
int count_antinodes(std::pair<int, int> grid_size, std::unordered_map<char, std::vector<std::pair<int,int>>> antennas_positions, bool with_harmonic = false);

#endif