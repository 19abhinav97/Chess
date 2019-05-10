#include "board.h"
#include "ai_level_1.h"
#include "ai_level_2.h"
#include "ai_level_3.h"
#include "ai_level_4.h"
#include "board_impl.h"
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	Board board;

  // New
	int rows;
	int columns;
	int n_players;
	cout << "Enter the number of rows, column and players" << endl;
	cin >> rows >> columns >> n_players;
	b.init(rows, columns, n_players);

	string player1, player2;

	cout << "Enter the name of the players" << endl;
	cin >> player1 >> player2;
	cout << board; // TextDisplay of the board

	int whitewin = 0;
	int blackwin = 0;
	int whitemove = 0;
	int blackmove = 0;
	Colour c_piece = Colour::White;

	string input_string;
	cin >> input_string;

	if (!strcmp(input_string, "Setup")) {
		string s;
		while (cin >> s) {
			if (s == '+') {
				Position first;
				PieceType second;
				Colour colour;
				cin >> first;
				cin >> second;
				cin >> colour;
				b.setPiece(first, second, colour);
				colour = colour::Black;
				cout << b;
			}
			if (s == '-') {
				Position first;
				Colour colour;
				cin >> first;
				b.removePiece(first);
				cout << b;
			} 
			if (s == '=') {
				Colour colour;
				cin >> colour;
				c_piece = colour;
			}
			if (!strcmp(s, "Done")) {
				if (board.isValidBoard()) {
					break;
				} else {
					continue;
				}
			}
			cout << board;
		}
	}
	if (!strcmp(input_string, "play")) {
		if (strcmp(player1, "human") == 0) {
			auto human_cont = std::make_unique<TextControllerImpl> ();
		}
		if (strcmp(player2, "computer1") == 0) {
			auto ai_lev = std::make_unique<AILevel1Impl> ();
		}
		if (strcmp(player2, "computer2") == 0) {
			auto ai_lev = std::make_unique<AILevel2Impl> ();
		}
		if (strcmp(player2, "computer3") == 0) {
			auto ai_lev = std::make_unique<AILevel3Impl> ();
		}
		if (strcmp(player2, "computer4") == 0) {
			auto ai_lev = std::make_unique<AILevel4Impl> ();
		}
		while(!board.isCheckmate() && !board.isStalemate()){
			player1->doPlayNextMove(&board);
			player2->doPlayNextMove(&board);
		}

	}
}

