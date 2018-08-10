#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Chrono>
#include <ratio>
#include <iostream>
#include <string>
#include "Ball.h"

using std::cout;
using std::endl;
using std::string;
//using namespace std::chrono;

int main()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	unsigned int mainWidth = desktop.width, mainHeight = desktop.height;
	cout << "window width = " << mainWidth << "\nwindow height = " << mainHeight << endl;
	sf::RenderWindow mainWindow(sf::VideoMode(mainWidth, mainHeight), "Pong");

	float screenRatioWidthToHeight = mainWidth / mainHeight;
	float screenMultiplier = mainWidth / 100;

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

	//duration of time between updates: 1 second / 60 = 0.016 seconds = 16 milliseconds
	//1 second = 1000 milliseconds
	//1 / 60 * 1000 = duration between updates in milliseconds
	std::chrono::seconds oneSecond(1);
	std::chrono::milliseconds oneMillisecond(1);
	std::chrono::milliseconds timeBetweenPhysicsUpdates(16); //16 milliseconds between physics updates (60 updates a second)
	std::chrono::milliseconds timeBetweenFrameUpdates(16); //16 milliseconds between frame draws (60 updaes per second)

	std::cout << "Time between physics updates: " << timeBetweenPhysicsUpdates.count() << " milliseconds (should be: " << int(1.0 / 60.0 * 1000) << ")"
		<< std::endl;

	std::cout << "Time between frame updates: " << timeBetweenFrameUpdates.count() << " milliseconds (should be: " << int(1.0 / 60.0 * 1000) << ")"
		<< std::endl;

	std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point lastTime = currentTime;
	std::chrono::steady_clock::time_point updateCounterTime = currentTime + oneSecond;
	std::chrono::steady_clock::time_point updatePhysicsTime = currentTime + timeBetweenPhysicsUpdates;
	std::chrono::steady_clock::time_point updateFrameTime = currentTime + timeBetweenFrameUpdates;

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

	float initialX = 0.01f, initialY = 0.01f;
	//Ball ballObj(0, 0, initialX, initialY);
	Ball ballObj(initialX, initialY);

	sf::CircleShape ballSprite;
	ballSprite.setOutlineColor(sf::Color::White);
	ballSprite.setFillColor(sf::Color::White);
	ballSprite.setRadius(1.f);
	ballSprite.setScale(screenMultiplier * 2, screenMultiplier * 2);
	ballSprite.setOrigin(ballSprite.getRadius(), ballSprite.getRadius());

	//initialize the ball in the middle of the screen
	ballSprite.setPosition(mainWindow.getSize().x / 2 - ballSprite.getScale().x / 2, mainWindow.getSize().y / 2 - ballSprite.getScale().y / 2);

	while (mainWindow.isOpen())
	{
		//cout << "-----------------\nNew cycle!" << endl;
		//update time
		lastTime = currentTime;
		currentTime = std::chrono::steady_clock::now();

		//check if physics need to be updated
		if (currentTime >= updatePhysicsTime)
		{
			cout << "Time to update physics!" << endl;
			updatePhysicsTime = currentTime + timeBetweenPhysicsUpdates;

			//update physics stuff here
			//get delta time
			std::chrono::duration<float, std::ratio<1, 1000>> diff = (currentTime - lastTime);
			float deltaTime = diff.count();
			cout << "dT = " << deltaTime << endl;
			//update ball motion data using delta time
			ballObj.update(deltaTime);
			//update ball position on screen based on physics calculations
			ballSprite.setPosition(ballSprite.getPosition().x + ballObj.getDeltaX(), ballSprite.getPosition().y + ballObj.getDeltaY());


			++physicsUpdateCounter;
		}

		//check if phys counter needs updating
		//check if fps counter needs updating
		if (currentTime >= updateCounterTime)
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

			updateCounterTime = currentTime + oneSecond;
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
		if (currentTime >= updateFrameTime)
		{
			++frameUpdateCounter;
			updateFrameTime = currentTime + timeBetweenFrameUpdates;
			mainWindow.clear();
			//draw stuff here
			
			//debug stuff
			mainWindow.draw(physCounterText);
			mainWindow.draw(frameCounterText);

			//game stuff
			mainWindow.draw(ballSprite);

			mainWindow.display();
		}
	}
	return 0;
}