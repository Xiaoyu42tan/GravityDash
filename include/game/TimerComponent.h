#ifndef TIMERCOMPONENT_H
#define TIMERCOMPONENT_H

#include <SFML/Graphics.hpp>

#include "BezierTransition.h"
#include "Clock.h"
#include "Event.h"
#include "Game.h"
#include "GameComponent.h"
#include "Settings.h"
#include "Utility.h"
#include "World.h"

#include <functional>

// A GameComponent providing timer functionality, which can be refilled under certain conditions
class TimerComponent : public GameComponent
{
public:
  // Create a timer with the desired time duration (in milliseconds)
  TimerComponent(Game* game, int maxTime);
  // Processes timer related events, such as when a time bonus is collected
  void ProcessEvent(Event& event) override;
  // Update the amount of time remaining, sends out events if the timer is refilled or runs out
  void Update() override;
  // Renders the timer gauge
  void Render(sf::RenderWindow* win) const override;

private:
  // Add or subtracts time from the timer
  void AddTime(int addition);
  // Smoothly vertically moves the arrow position based on `timerRefill`
  void MoveArrow();

private:
  mutable sf::Sprite gauge;             // The sprite for the timer gauge
  mutable sf::RectangleShape timeRect;  // The rectangle used to display how much time is left
  
  mutable sf::Sprite refillArrow;             // The sprite used to display how much time boost has been collected
  sf::Vector2f arrowPos;              // The position of the refill arrow
  bool showArrow = false;             // Whether `refillArrow` is rendered
  BezierTransition<float> arrowYMove; // The transition used to smoothly move the arrow up and down

  int timeRemaining = 0;  // The amount of time left in the timer (in milliseconds)
  const int maxTime = 0;  // The maximum amount of time the timer can hold (in milliseconds)

  std::vector<int> boostCount;  // Count of the TimeBonus pickups in a player's combo
  int timeRefill = 0;           // How much the timer is refilled once it runs out

  bool done = false;  // Whether the timer is done
};

#endif