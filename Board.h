#include <vector>
#include <SFML/Graphics.hpp>
#include <thread>

class Board {
	std::vector<std::vector<int>> b;
	int added;
	int boardY, boardX;
	int bestMoveY, bestMoveX;
	double boardValue;

public:
	Board();
	Board(int, int);
	Board(Board&);
	Board(Board *b) : Board(*b){}
	int checkWin();
	bool addPiece(int);
	void render(sf::RenderWindow&, const int&, const double&);
	void getAIMove(const int&);
	void updateBoardValue(const int&);
};
