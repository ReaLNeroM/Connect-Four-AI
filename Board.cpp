#include "Board.h"
#include <iostream>

Board::Board(){
	boardY = 0, boardX = 0;
	bestMoveY = -1, bestMoveX = -1;
	added = 0;
}
Board::Board(int y, int x){
	boardY = y, boardX = x;
	bestMoveY = -1, bestMoveX = -1;
	added = 0;

	for(int i = 0; i < boardY; i++){
		b.push_back(std::vector<int>(boardX));
	}
}

Board::Board(Board& oldB){
	boardY = oldB.boardY, boardX = oldB.boardX;
	bestMoveY = -1, bestMoveX = -1;
	added = oldB.added;
	b = std::vector<std::vector<int>>(boardY);

	for(int i = 0; i < boardY; i++){
		b[i] = std::vector<int>(boardX);
		for(int j = 0; j < boardX; j++){
			b[i][j] = oldB.b[i][j];
		}
	}
}

int Board::checkWin(){
	if(added == boardY * boardX){
		return -1;
	}

	for(int i = 0; i < boardY; i++){
		int extent = 0;
		int prev = 0;

		for(int j = 0; j < boardX; j++){
			if(b[i][j] != prev){
				extent = 1;
				prev = b[i][j];
			} else if(b[i][j] == prev){
				extent++;
			}

			if(extent >= 4 and prev != 0){
				return prev;
			}
		}
	}

	for(int i = 0; i < boardX; i++){
		int extent = 0;
		int prev = 0;

		for(int j = 0; j < boardY; j++){
			if(b[j][i] != prev){
				extent = 1;
				prev = b[j][i];
			} else if(b[j][i] == prev){
				extent++;
			}

			if(extent >= 4 and prev != 0){
				return prev;
			}
		}
	}

	for(int sum = -boardX - boardY; sum < boardX + boardY; sum++){
		int extent = 0;
		int prev = 0;
		for(int i = 0; i < boardY; i++){
			int j = sum - i;
			if(j < 0 or boardX <= i){
				continue;
			}

			if(b[i][j] != prev){
				extent = 1;
				prev = b[i][j];
			} else if(b[i][j] == prev){
				extent++;
			}

			if(extent >= 4 and prev != 0){
				return prev;
			}
		}
	}

	for(int sum = -boardX - boardY; sum < boardX + boardY; sum++){
		int extent = 0;
		int prev = -1;
		for(int i = 0; i < boardY; i++){
			int j = sum + i;
			if(j < 0 or boardX <= i){
				continue;
			}

			if(b[i][j] != prev){
				extent = 1;
				prev = b[i][j];
			} else if(b[i][j] == prev){
				extent++;
			}

			if(extent >= 4 and prev != 0){
				return prev;
			}
		}
	}

	return 0;
}

bool Board::addPiece(int x){
	for(int i = 0; i < boardY; i++){
		if(b[i][x] == 0){
			b[i][x] = added % 2 + 1;
			added++;
			bestMoveY = bestMoveX = -1;
			return true;
		}
	}


	return false;
}

void Board::render(sf::RenderWindow &window, const int& windowSize, const double& radius){
	sf::RectangleShape board(sf::Vector2f(windowSize, windowSize));

	window.draw(board);

	for(int i = 0; i < boardY; i++){
		for(int j = 0; j < boardX; j++){
			sf::CircleShape circ(radius, 100);
			circ.setFillColor(sf::Color(100, 100, 100));

			double mostY = (boardY - 1.0) / (double) boardY * windowSize + 2.0 * radius;
			double mostX = (boardX - 1.0) / (double) boardX * windowSize + 2.0 * radius;
			double pY = ((boardY - 1 - i) + 0.5) * (windowSize / boardY);
			double pX = (j + 0.5) * (windowSize / boardX);
			circ.setPosition(sf::Vector2f(pX - radius, pY - radius));
			
			if(b[i][j] == 1){
				circ.setFillColor(sf::Color(255, 0, 0));
			} else if(b[i][j] == 2){
				circ.setFillColor(sf::Color(0, 0, 0));
			} else if(i == bestMoveY and j == bestMoveX){
				circ.setFillColor(sf::Color(0, 0, 255));
			}

			window.draw(circ);
		}
	}
}

void Board::AImove(const int& trials){
	std::vector<std::thread> vt;
	Board vb[boardX];

	double bestMoveValue = -1.0;

	for(int i = 0; i < boardX; i++){
		vb[i] = Board(*this);

		if(vb[i].addPiece(i)){
			vt.push_back(std::thread(&Board::updateBoardValue, std::ref(vb[i]), trials));
		} else {
			vb[i].boardValue = 1.0;
		}
	}

	for(auto& th : vt){
		th.join();
	}


	std::cout << "Value of moves: ";
	for(int i = 0; i < boardX; i++){
		std::cout << 1.0 - vb[i].boardValue << ' ';
		if(1.0 - vb[i].boardValue > bestMoveValue){
			bestMoveValue = 1.0 - vb[i].boardValue;
			bestMoveX = i;
		}
	}
	std::cout << '\n';

	addPiece(bestMoveX);
	for(int i = 0; i < boardY; i++){
		if(b[i][bestMoveX] == 0){
			bestMoveY = i;
			break;
		}
	}
}

void Board::updateBoardValue(const int& trials){
	double wins = 0.0;


	for(int trial = 0; trial < trials; trial++){
		Board cp(*this);

		while(!cp.checkWin()){
			int x = std::rand() % boardX;

			cp.addPiece(x);
		}

		int winner = cp.checkWin();

		if(winner == added % 2 + 1){
			wins += 1;
		}
	}

	boardValue = wins / (double) trials;
}
