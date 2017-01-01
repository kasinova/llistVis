#ifndef APP_H
#define APP_H

#include "SFML\Graphics.hpp"
#include "assetManager.h"
#include "GUI.h"
//debug
#include "llist.h"

class App
{
public:
	App();
	int run(int minFPS);
private:
	bool processEvents();
	void update(sf::Time dt);
	void draw();

	AssetManager assets;
	sf::RenderWindow window;
	GUI gui;
	//debug
	LList llist;
};

#endif