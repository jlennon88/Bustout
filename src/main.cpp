#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#pragma warning(pop)

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout");

	const sf::Color clearColor = { 0x77, 0x77, 0x77, 0xFF };

	bool shouldClose = false;
	while (!shouldClose)
	{
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == sf::Event::Closed)
				shouldClose = true;
		}

		window.clear(clearColor);

		window.display();
	}

	return 0;
}