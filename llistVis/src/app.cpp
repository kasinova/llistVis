#include "..\include\app.h"
#include <iostream>
#include "..\include\util.h"
App::App() : llist(assets), gui(&assets,&llist)
{
	window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Linked List Visualizer");
	window.setView(sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT)));
	
	//load assets
	assets.addTex("node", "../assets/node.png");
}

int App::run(int minFPS)
{
	//overall clock of game
	sf::Clock clock;
	//holds return value of elapsed clock time when calling clock.restart()
	sf::Time timeSinceLastUpdate;
	//fixed time of minFPS
	sf::Time TimePerFrame = sf::seconds(1.f / minFPS);

	while (window.isOpen())
	{
		if (processEvents())//true means user is on console so come back with a 0 second dt
		{
			clock.restart();
			timeSinceLastUpdate = sf::Time::Zero;
		}
		else
		{
			timeSinceLastUpdate = clock.restart();
		}
		//enters only if dt is greater than minFPS
		while (timeSinceLastUpdate > TimePerFrame) //lag would cause a greater dt so run "catch-up" updates 
		{
			timeSinceLastUpdate -= TimePerFrame; //hack away at big dt
			update(TimePerFrame); //use fixed minFPS for update
		}
		update(timeSinceLastUpdate);
		draw();
	}
	return 0;
}

bool App::processEvents()
{
	//when user prompts for input, app is suspended
	bool inputLag = false;

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::Resized)
		{
			window.setView(sf::View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(event.size.width, event.size.height)));
			SCREEN_WIDTH = event.size.width;
			SCREEN_HEIGHT = event.size.height;
			gui.updateButtonPositions(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		}
		if (gui.processEvent(event, window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			inputLag = true;
		}
	
	}
	return inputLag;
}
void App::update(sf::Time dt)
{
	gui.update(dt);
	llist.update(dt);

}
void App::draw()
{
	window.clear(sf::Color(128,128,128,255));

	llist.draw(window);
	gui.draw(window);
	window.display();
}