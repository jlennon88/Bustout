#include <SFML/Graphics.hpp>

constexpr int MainWindowWidth = 800;
constexpr int MainWindowHeight = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(MainWindowWidth, MainWindowHeight), "Bustout");
	window.setVerticalSyncEnabled(true);

	sf::View uiView = window.getView();
	sf::View worldView = window.getView();
	worldView.setCenter(0.0f, 0.0f);
	worldView.setSize(
		{
			 static_cast<float>(MainWindowWidth),
			-static_cast<float>(MainWindowHeight),
		}
	);

	const sf::Color clearColor = { 0x55, 0x55, 0x55, 0xFF };

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


		// draw scene
		window.setView(worldView);
		
		
		// draw ui
		window.setView(uiView);

		
		const auto mousePos = sf::Mouse::getPosition(window);
		
		window.display();
	}

	return 0;
}