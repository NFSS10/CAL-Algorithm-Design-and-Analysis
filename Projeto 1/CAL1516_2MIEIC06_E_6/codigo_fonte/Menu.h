/** @file Menu.h
*  @brief Menu that will work as a tool to the user interact with the city database
*/

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include "City.h"
#include <fstream>

#define MAX_ATTEMPTS 5

/** @class AttemptLimitExceeded
*  @brief The class AttemptLimitExceeded is used when the user exceeds the limit of inputs
*/
class AttemptLimitExceeded {
private:
	std::string reason; ///< @var std::string reason
public:
	/**
	*  @brief Constructor of the AttemptLimitExceeded class
	* @param reason a string argument related to the reason of the exception
	*/
	AttemptLimitExceeded(std::string reason);

	/** @brief Gets the reason of the AttemptLimitExceeded exception
	*  @return A string with the reason
	*/
	std::string getReason() const;
};

/** @class Menu
*  @brief The Menu class has the city database that we want to interact
*/
class Menu {
private:
	City *city; ///< @var City *city
public:
	/**
	*  @brief Constructor of a Menu class
	* @param city a City that the user want to interact
	*/
	Menu(City *city);

	/**
	*  @brief Used to get a numeric value between two bounds from user input. When the limite MAX_ATTEMPTS
	* is exceeded the function throws an exception.
	* @param maximumBound is the max value of the bound
	* @param minimumBound is the min value of the bound
	* @return an integer between the min and the max bound
	*/
	static int inputChoice(int maximumBound, int minimumBound = 1);

	/**
	*  @brief Gets a string introduced by the user
	* @return A string with the input
	*/
	static std::string getString();

	/**
	*  @brief Gets a integer introduced by the user
	* @return A integer with the input
	*/
	static int getNumber();

	/**
	*  @brief Gets the id of the vertex destination of each item introduced by the user 
	* @return void
	*/
	void addItemsDestination();

	/**
	*  @brief Adds the items to be distributed by the truck
	* @return void
	*/
	void LoadToTruck();

	/**
	*  @brief Adds the items to be distributed by the trucks
	* @return void
	*/
	void LoadToTrucks();

	/**
	*  @brief Removes a vertex to simulate a road under construction that the truck cannot pass
	* @return void
	*/
	void roadUnderConstruction();

	/**
	*  @brief Gets all the articulation points and show it
	* @return void
	*/
	void getArticulationPoints();

	/**
	*  @brief Starts the áuxiliary menu to interact with the city database
	* @return void
	*/
	void startAuxMenu();

	/**
	*  @brief Starts the main menu to interact with the city database
	* @return void
	*/
	void start();
};

#endif /* MENU_H_ */
