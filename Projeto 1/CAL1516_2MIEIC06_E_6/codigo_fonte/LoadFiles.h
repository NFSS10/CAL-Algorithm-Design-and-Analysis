/** @file LoadFiles.h
*  @brief The LoadFiles file is resposible to laoad the database 
*/
#ifndef LOADFILES_H_
#define LOADFILES_H_


#include "City.h"
#include "Graph.h"
#include <fstream>
#include <sstream>

/** @class LoadFileException
*  @brief The class LoadFileException is used when the file cannot be loaded
*/
class LoadFileException {
private:
	std::string reason; ///< @var std::string reason
public:
	/**
	*  @brief Constructor of the LoadFileException class
	* @param reason a string argument related to the reason of the exception
	*/
	LoadFileException(std::string reason);

	/** @brief Gets the reason of the LoadFileException exception
	*  @return A string with the reason
	*/
	std::string getReason() const;
};

/** @class LoadFiles
*  @brief The LoadFiles class is resposible to load all the database from the files
*/
class LoadFiles {
private:
	City *city; ///< @var City* city
	std::ifstream items; ///< @var ifstream items
	std::ifstream trucks; ///< @var ifstream trucks
	std::ifstream map1; ///< @var ifstream map1
	std::ifstream map2; ///< @var ifstream map2
	std::ifstream map3; ///< @var ifstream map3

	/**
	*  @brief Gets a string from the item ifstream
	* @return The loaded string
	*/
	std::string loadItemString();

	/**
	*  @brief Gets a string from the truck ifstream
	* @return The loaded string
	*/
	std::string loadTruckString();

	/**
	*  @brief Gets an integer from the item ifstream
	* @return The loaded integer
	*/
	int loadItemInt();

	/**
	*  @brief Gets an integer from the truck ifstream
	* @return The loaded integer
	*/
	int loadTruckInt();

	/**
	*  @brief Gets a double from the item ifstream
	* @return The loaded double
	*/
	double loadNumberDouble();

	/**
	*  @brief Gets all the items and trucks from the files
	* @return A pointer to the loaded company
	*/
	Company* loadCompany();

	/**
	*  @brief Get an item from the database files
	* @see loadCompany()
	* @return A pointer to a item
	*/
	Item *loadItem();

	/**
	*  @brief Get a truck from the database files
	* @see loadCompany()
	* @return A pointer to a truck
	*/
	Truck* loadTrucks();

	/**
	*  @brief Gets a graph map from the files to the city
	* @return A pointer to a graph
	*/
	Graph<int>* loadGraph();

public:
	/**
	*  @brief Default constructor of a LoadFiles class
	*/
	LoadFiles();

	/**
	*  @brief Destructor of the LoadFiles class
	*/
	~LoadFiles();

	/**
	*  @brief Gets the city from a file
	* @param items the string with the filename of the items
	* @param trucks the string with the filename of the trucks and the city name
	* @param map the string with the filename of the map
	* @return Pointer to a City
	*/
	City* load(std::string items, std::string trucks, std::string map);

};


#endif /* CITY_H_ */
