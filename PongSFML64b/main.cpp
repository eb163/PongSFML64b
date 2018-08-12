#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ratio>
#include <iostream>
#include <string>
#include "PhysObj.h"
#include "Ball.h"

using std::cout;
using std::endl;
using std::string;

int main()
{
	sf::Clock mainClock; //start internal sfml clock
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	unsigned int mainWidth = desktop.width, mainHeight = desktop.height;
	cout << "window width = " << mainWidth << "\nwindow height = " << mainHeight << endl;
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Pong");

	float screenRatioWidthToHeight = mainWidth / mainHeight;
	float screenMultiplier = mainWidth / 100;
	sf::Vector2f screenScale(screenMultiplier, screenMultiplier);

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");

	short TEXT_SIZE = screenMultiplier;

	//temporary start screen for now
	string pauseStr = "Press any key to continue...";
	sf::Text pauseText;
	pauseText.setString(pauseStr);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setOutlineColor(sf::Color::White);
	//need to center it by resetting origin
	pauseText.setPosition(mainWindow.getSize().x / 2.0f, mainWindow.getSize().y / 2.0f);
	pauseText.setFont(font);
	pauseText.setCharacterSize(TEXT_SIZE * 4);

	bool paused = true;
	while (paused)
	{
		sf::Event eventQue;
		while (mainWindow.pollEvent(eventQue))
		{
			switch (eventQue.type)
			{
			case sf::Event::Closed:
				paused = false;
				mainWindow.close();
				break;
			case sf::Event::MouseButtonReleased:
			case sf::Event::KeyReleased:
			case sf::Event::JoystickButtonReleased:
				paused = false;
				break;
			}
		}
		mainWindow.clear();
		mainWindow.draw(pauseText);
		mainWindow.display();
	}

	/////////////////////////////////////////////////////////////////////////////////
	//MAIN GAME
	/////////////////////////////////////////////////////////////////////////////////
	mainClock.restart(); //reset clock
	sf::Time currentTime;
	sf::Time physUpdateTimeCounter = sf::milliseconds(0);
	sf::Time grphUpdateTimeCounter = sf::milliseconds(0);
	sf::Time oneSecondCounter = sf::seconds(0);
	sf::Time timeAtPrevCycle = sf::seconds(0);
	sf::Time deltaTime;
	sf::Time timeBetweenPhysUpdates = sf::milliseconds(16);
	sf::Time oneSecond = sf::seconds(1);
	sf::Time timeBetweenGrphUpdates = sf::milliseconds(16);
	//duration of time between updates: 1 second / 60 = 0.016 seconds = 16 milliseconds
	//1 second = 1000 milliseconds
	//1 / 60 * 1000 = duration between updates in milliseconds

	int physicsUpdateCounter = 0; //tracks how many times physics is updated
	string physCounterStr;
	sf::Text physCounterText;
	physCounterText.setString(physCounterStr);
	physCounterText.setFillColor(sf::Color::White);
	physCounterText.setOutlineColor(sf::Color::White);
	physCounterText.setPosition(0, 0);
	physCounterText.setFont(font);
	physCounterText.setCharacterSize(TEXT_SIZE);

	int frameUpdateCounter = 0;
	string frameCounterStr;
	sf::Text frameCounterText;
	frameCounterText.setString(frameCounterStr);
	frameCounterText.setFillColor(sf::Color::White);
	frameCounterText.setOutlineColor(sf::Color::White);
	frameCounterText.setPosition(0, TEXT_SIZE);
	frameCounterText.setFont(font);
	frameCounterText.setCharacterSize(TEXT_SIZE);


	//creating the ball (sprite and physical object are merged in one class)
	float initialX = 10.0f, initialY = 10.0f;
	sf::Vector2f ballStartPos(mainWindow.getSize().x / 2, mainWindow.getSize().y / 2);
	Ball ballObj(sf::Vector2f(initialX, initialY), sf::Color::White, 1.0f, screenScale, ballStartPos);

	//creating the paddle
	sf::RectangleShape paddleSprite;
	paddleSprite.setOutlineColor(sf::Color::White);
	paddleSprite.setFillColor(sf::Color::White);
	paddleSprite.setSize(sf::Vector2f(7, 1));
	paddleSprite.setScale(screenMultiplier * 2, screenMultiplier * 2);
	paddleSprite.setOrigin(paddleSprite.getSize().x / 2, paddleSprite.getSize().y / 2);

	//initialize the paddle located arbitrarily at the bottom of the screen
	paddleSprite.setPosition(mainWindow.getSize().x / 2, mainWindow.getSize().y * 0.8);

	//creating some basic walls to test collision detection
	sf::RectangleShape wallSprite;
	wallSprite.setOutlineColor(sf::Color::Red);
	wallSprite.setFillColor(sf::Color::Red);
	wallSprite.setSize(sf::Vector2f(100, 1));
	wallSprite.setScale(screenMultiplier * 2, screenMultiplier * 2);
	wallSprite.setOrigin(wallSprite.getSize().x / 2, wallSprite.getSize().y / 2);

	sf::RectangleShape wall1 = wallSprite, wall2 = wallSprite, wall3 = wallSprite, wall4 = wallSprite;
	wall1.setPosition(mainWindow.getSize().x / 2, 0); //top wall
	wall2.setRotation(90); wall2.setPosition(mainWindow.getSize().x, mainWindow.getSize().y / 2); //right side wall
	wall3.setPosition(mainWindow.getSize().x / 2, mainWindow.getSize().y); //bottom wall
	wall4.setRotation(90); wall4.setPosition(0, mainWindow.getSize().y / 2); //left side wall



	while (mainWindow.isOpen())
	{
		cout << "-----------------\nNew cycle!" << endl;
		//update time
		currentTime = mainClock.getElapsedTime();
		deltaTime = currentTime - timeAtPrevCycle; //get delta time
		cout << "dT = " << deltaTime.asMilliseconds() << endl;
		//update counters
		oneSecondCounter += deltaTime; //used for framerate and phys update stats //temp
		physUpdateTimeCounter += deltaTime; //for updating phys
		grphUpdateTimeCounter += deltaTime; //for updating graphics

		//check if physics need to be updated
		if (physUpdateTimeCounter >= timeBetweenPhysUpdates)
		{
			cout << "Time to update physics!" << endl;
			//update physics stuff here
			//get delta time
			//deltaTime += mainClock.getElapsedTime(); //already updated at start of loop
			cout << "dT = " << deltaTime.asSeconds() << endl;
			//update ball motion data using delta time
			//phys update operates in units of seconds
			ballObj.update(deltaTime.asSeconds());
			//update ball position on screen based on physics calculations
			//can move this into ball.update() member
			ballObj.getSprite().setPosition(ballObj.getSprite().getPosition().x + ballObj.getDeltaX(), 
				ballObj.getSprite().getPosition().y + ballObj.getDeltaY());

			physUpdateTimeCounter = sf::milliseconds(0); //reset counter for phys update time
			++physicsUpdateCounter;
		}

		//check if phys counter needs updating
		//check if fps counter needs updating
		if (oneSecondCounter >= oneSecond)
		{
			physCounterStr = "Physics updates per second: ";
			physCounterStr += std::to_string(physicsUpdateCounter);
			physCounterText.setString(physCounterStr);
			cout << physCounterStr << endl;
			physicsUpdateCounter = 0;

			frameCounterStr = "FPS: ";
			frameCounterStr += std::to_string(frameUpdateCounter);
			frameCounterText.setString(frameCounterStr);
			cout << frameCounterStr << endl;
			frameUpdateCounter = 0;

			oneSecondCounter = sf::seconds(0); //reset counter
		}
		

		//process events
		sf::Event eventQue;
		while (mainWindow.pollEvent(eventQue))
		{
			if (eventQue.type == sf::Event::Closed)
			{
				mainWindow.close();
			}
		}

		//update graphics
		if (grphUpdateTimeCounter >= timeBetweenGrphUpdates)
		{
			++frameUpdateCounter;
			mainWindow.clear();
			//draw stuff here

			//game stuff
			//mainWindow.draw(ballSprite);
			mainWindow.draw(ballObj.getSprite());
			mainWindow.draw(paddleSprite);
			mainWindow.draw(wall1);
			mainWindow.draw(wall2);
			mainWindow.draw(wall3);
			mainWindow.draw(wall4);

			//debug stuff
			mainWindow.draw(physCounterText);
			mainWindow.draw(frameCounterText);

			mainWindow.display();
		}
		timeAtPrevCycle = currentTime;
	}
	return 0;
}