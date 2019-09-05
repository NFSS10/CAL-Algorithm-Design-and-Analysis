/** @file Truck.h
*  @brief Truck that will deliver the items
*/

#ifndef TRUCK_H_
#define TRUCK_H_

#include <vector>
#include "Item.h"

/** @class Truck
*  @brief The Truck class has all a truck_load, a stowage and all the items to be delivered
*/
class Truck {
private:
	double truck_load; ///< @var double truck_load
	double stowage; ///< @var double stowage
	std::vector<Item *> itemsToDistribute; ///< @var vector itemsToDistribute

public:
	/**
	*  @brief Constructor of a Truck class
	* @param truck_load The maximum volume that the truck supports
	*/
	Truck(double truck_load);

	/**
	*  @brief Gets the maximum volume that the truck supports
	* @return A double with the maximum volume that the truck supports
	*/
	double getTruckLoad() const;

	/**
	*  @brief Gets the volume occupied by the items
	* @return A double with the volume occupied by the items
	*/
	double getStowage() const;

	/**
	*  @brief Gets the items that the truck needs to deliver
	* @return A vector with the items to be delivered
	*/
	std::vector<Item *> getItemsToDistribute() const;

	/**
	*  @brief Adds a item to the truck
	* @param di The item to be delivered by the truck
	* @return true if the item was added to the truck, false otherwise
	*/
	bool addItem(Item *di);

	/**
	*  @brief Deletes the item in the vector and decreases the stowage
	* @return void
	*/
	void deliveryItems();

	/**
	* @brief To check if a truck is equal to another truck
	* @param t1 the truck that we want to compare with
	* @return true if the truck we want to check is equal to the t1
	*/
	bool operator==(const Truck  *t1);
};

#endif /* TRUCK_H_*/
