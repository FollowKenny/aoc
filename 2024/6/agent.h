#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>

using namespace std;

struct Direction {
    static constexpr pair<int, int> UP = {-1, 0};
    static constexpr pair<int, int> DOWN = {1, 0};
    static constexpr pair<int, int> LEFT = {0, -1};
    static constexpr pair<int, int> RIGHT = {0, 1};
};

class Agent {
public:
    int n_visited = 1;
    int n_loops = 0;
    Agent(pair<int, int> startPosition, pair<int, int> startDirection, vector<vector<char>> grid);
    void run_through();
    void look_for_loops();

private:
    pair<int, int> position;      // Current position
    pair<int, int> direction;     // Current direction vector
    vector<vector<char>> grid;    // The grid agent will run through

    void _move_forward();
    void _turn_right();
    const pair<int, int> _get_next_position() const;
    char _look_ahead();
    void _update_visited();
    pair<int,int> _put_blocker();
    bool _stuck_in_a_loop(char c);
};

tuple<vector<vector<char>>, pair<int,int>, pair<int,int>> process_char_grid(const string &fname);

#endif