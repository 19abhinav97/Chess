#include<vector>

using namespace std;
class Score{
  int i_x;
  int i_y;
  int f_x;
  int f_y;
  int score;
public:
  Score(int i_x, int i_y, int f_x, int f_y, int score) : i_x{i_x}, i_y{i_y}, f_x{f_x}, f_y{f_y}, score{score} {}
  int get_score();
  std::vector<int> get_initial();
  std::vector<int> get_final();
};
