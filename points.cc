#include "points.h"

using namespace std;

int Score::get_score(){
  return score;
}

vector<int> Score::get_initial(){
  vector<int> r = {i_x, i_y};
  return r;
}

vector<int> Score::get_final(){
  vector<int> r = {f_x, f_y};
  return r;
}
