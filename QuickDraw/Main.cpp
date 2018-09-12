#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <cstdlib>
#include <ctime>


int main()

{
	//GAME SETUP


	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Quick Draw", sf::Style::Titlebar | sf::Style::Close);

	//Seed our random number generator
	srand(time(NULL));

	//TIMER
	float signalTimeLowerLimit = 5.0f;
	float signalTimeUpperLimit = 10.0f;
	sf::Time timeTillSignal = sf::seconds(signalTimeLowerLimit);
	sf::Time timeSinceSignal = sf::seconds(0.0f);
	sf::Clock gameClock;

	//button sprite
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("graphics/button.png");
	sf::Sprite buttonSprite;
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(gameWindow.getSize().x / 2 - buttonTexture.getSize().x / 2, gameWindow.getSize().y / 2 - buttonTexture.getSize().y / 2);
	//END GAME SETUP



	// GAME LOOP
	//RUNS EVERY FRAME UNTIL GAME IS CLOSED

	while (gameWindow.isOpen())
	{
		//INPUT
		sf::Event gameEvent;

		while (gameWindow.pollEvent(gameEvent))
		{
			if (gameEvent.type == sf::Event::MouseButtonPressed)
			{
				if (buttonSprite.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y))
				{
					//If we did click it
					int range = (int)(signalTimeUpperLimit - signalTimeLowerLimit);
					float signalSeconds = rand() % range + signalTimeLowerLimit;
					timeTillSignal = sf::seconds(signalSeconds);
				}
			}
			if (gameEvent.type == sf::Event::Closed)
			{
				gameWindow.close();
			}
		}


		//UPDATE
		sf::Time frameTime = gameClock.restart();

		timeTillSignal = timeTillSignal - frameTime;
		if (timeTillSignal.asSeconds() <= 0.0f)
		{
			buttonSprite.setColor(sf::Color::Red);
		}


		//DRAW		
		gameWindow.clear(sf::Color::Black);
		//Draw everything
		gameWindow.draw(buttonSprite);
		//Display contents
		gameWindow.display();
	}
	//Exit Point
	return 0;
}//End of main function