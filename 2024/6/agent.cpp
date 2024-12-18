#include "agent.h"
#include "iostream"

tuple<vector<vector<char>>, pair<int,int>, pair<int,int>> process_char_grid(const string &fname) {
  ifstream myfile(fname);
  string line;
  auto line_counter = 0;
  vector<vector<char>> charGrid;
  auto agent_pos = make_pair(-1, -1);
  auto direction = make_pair(-1, -1);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      vector<char> line_v;
      for (auto it = line.begin(); it != line.end(); ++it) {
        if (*it == 'v') direction = Direction::DOWN;
        else if (*it == '>') direction = Direction::RIGHT;
        else if (*it == '<') direction = Direction::LEFT;
        else if (*it == '^') direction = Direction::UP;
        if (*it == 'v' || *it == '>' || *it == '<' || *it == '^') {
            agent_pos = make_pair(line_counter, distance(line.begin(), it));
            line_v.push_back('1');
        } else line_v.push_back(*it);
      }
      charGrid.push_back(line_v);
      line_counter++;
    }
    myfile.close();
  }
  else
    cout << "Unable to open file";
  return make_tuple(charGrid, agent_pos, direction);
}

Agent::Agent(pair<int, int> startPosition, pair<int, int> startDirection, vector<vector<char>> grid)
  : position(startPosition), direction(startDirection), grid(grid) {}

void Agent::run_through() {
  auto stuck_in_a_loop = false;
  while (! stuck_in_a_loop) {
    auto nextChar = _look_ahead();
    while (nextChar == '#' || nextChar == '*') {
      _turn_right();
      nextChar = _look_ahead();
    }
    if (nextChar == '&') break;
    stuck_in_a_loop = _stuck_in_a_loop(nextChar);
    n_loops += stuck_in_a_loop;
    _move_forward();
    _update_visited();
  }
}

void Agent::look_for_loops() {
  while (true) {
    auto nextChar = _look_ahead();
    while (nextChar == '#' || nextChar == '*') {
      _turn_right();
      nextChar = _look_ahead();
    }
    if (nextChar == '&') break;
    auto current_position = position;
    auto current_direction = direction;
    auto current_grid = grid;
    auto blocker_pos = _put_blocker();
    run_through();
    position = current_position;
    direction = current_direction;
    grid = current_grid;
    _move_forward();
    _update_visited();
  }
}

void Agent::_move_forward() {
    position = _get_next_position();
}

void Agent::_turn_right() {
    if (direction == Direction::UP) direction = Direction::RIGHT;
    else if (direction == Direction::RIGHT) direction = Direction::DOWN;
    else if (direction == Direction::DOWN) direction = Direction::LEFT;
    else if (direction == Direction::LEFT) direction = Direction::UP;
}

const pair<int, int> Agent::_get_next_position() const{
  return {position.first + direction.first, position.second + direction.second};
}

char Agent::_look_ahead() {
  const auto futur_position = _get_next_position();
  if (futur_position.first == grid.size() || 
  futur_position.second == grid[0].size() ||
  futur_position.first == -1 ||
  futur_position.second == -1) return '&';
  else {
    return grid[futur_position.first][futur_position.second];
  }
}

void Agent::_update_visited() {
  auto current_char = &grid[position.first][position.second];
  if (*current_char == '.') {
    n_visited++;
    *current_char = '1';
  } else (*current_char)++;
}

pair<int,int> Agent::_put_blocker() {
  const auto futur_position = _get_next_position();
  auto next_char = &grid[futur_position.first][futur_position.second];
  if (*next_char == '.') *next_char = '*';
  return futur_position;
}

bool Agent::_stuck_in_a_loop(char c) {
  if (c == '4') return true;
  return false;
}