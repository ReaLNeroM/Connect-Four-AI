#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Board.h"

const int windowSize = 2000;

const double radius = 100;
const int boardX = 7;
const int boardY = 6;
const int AITrials = 50000;
const int longest = boardX + boardY;

int main(){
	sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "It Works!");
	window.setFramerateLimit(60);

	Board b(boardY, boardX);
	sf::SoundBuffer buffer;
	buffer.loadFromFile("Move.ogg");
	sf::Sound sound;
	sound.setBuffer(buffer);

	while (window.isOpen()){
		sf::Event event;
		auto mouseLocation = sf::Mouse::getPosition(window);

		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
			} else if(event.type == sf::Event::MouseButtonPressed){
				if(event.mouseButton.button == sf::Mouse::Left){
					int getX = -1;
					int prev = 0;
					for(int i = 0; i < boardX; i++){
						double mostX = (boardX - 1.0) / (double) boardX * windowSize + 2.0 * radius;
						double pX = (double) i / boardX * windowSize + (windowSize - mostX) / 2.0 + 2.0 * radius;

						if(i + 1 == boardX){
							pX = windowSize;
						}

						if(prev <= mouseLocation.x and mouseLocation.x <= pX){
							getX = i;
							break;
						}

						prev = pX;
					}

					if(getX == -1){
						std::cerr << "ERROR: Out of Bounds Click\n";
						return -1;
					}

					b.addPiece(getX);
					sound.play();
				}
			}
		}

		if(b.checkWin() != 0){
			std::cout << "Win for player #" << b.checkWin() << "!\n";
			return 0;
		}

		b.render(window, windowSize, radius);
		b.getAIMove(AITrials);

		window.display();

	}

	return 0;
}
