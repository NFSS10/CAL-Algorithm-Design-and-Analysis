/** @file City.h
*  @brief Database of the program that will have the graph map
*/
#ifndef CITY_H_
#define CITY_H_

#include "Graph.h"
#include <string>
#include "Company.h"

/** @class City
*  @brief The City class has all the database that we want to interact
*/
class City {
private:
	std::string name; ///< @var std::string name
	Graph<int>* map; ///< @var Graph* map
	Company* company; ///< @var Company* company

public:
	/**
	*  @brief Constructor of a City class
	* @param name the name of the city
	* @param map the graph map of the city
	* @param company An Company that will have the trucks to distribute the itens
	*/
	City(std::string name, Graph<int>* map, Company* company);

	/**
	*  @brief Default constructor of a City class
	*/
	City();

	/**
	*  @brief Changes the name of the city
	* @param name a string of the new name of the city
	* @return void
	*/
	void setName(std::string name);

	/**
	*  @brief Gets the name of the city
	* @return A string with the name of the city
	*/
	std::string getName();

	/**
	*  @brief Gets the map of the city
	* @return A graph that have all the vertex's and edge's of the city
	*/
	Graph<int>* getMap();

	/**
	*  @brief Changes the map of the city
	* @param map a graph of the new map of the city
	* @return void
	*/
	void setMap(Graph<int>* map);

	/**
	*  @brief Gets the company responsible for the delivery of items
	* @return The object Company of the city
	*/
	Company* getCompany();

	/**
	*  @brief Changes the company responsible for the delivery of items of the city
	* @param company the new company that will delivery the items of the city
	* @return void
	*/
	void setCompany(Company* company);


	/**
	*  @brief Gets the shortest way to deliver the items
	* @param truck the truck that will deliver the items
	* @return A vector with the ids of the vertex of the best way to deliver the items
	*/
	vector<int> shortestPath(Truck *truck);

	/**
	* @brief Verify if all items of repository are in the vector passed by argument
	* @param v Vector with vertex identifiers
	* @return A boolean that assumes true value if vector contains all items identifiers otherwise return false
	*/
	bool thereIsPath(vector<int> v);

	/**
	* @brief Check the connection between depository and all items destination and garage
	* @return A boolean that assumes true as value if there is connection
	*/
	bool checkConnection();

	/**
	* @brieft Function used to get all the items between Deposit and Garage
	* @return A vector with those items between shortest path
	*/
	vector<Item *> itemsInPathDG();
};

#endif /* CITY_H_ */