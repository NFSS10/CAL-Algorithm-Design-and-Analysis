/** @file Company.h
*  @brief The company responsible for the delivery of items of the city
*/
#ifndef COMPANY_H_
#define COMPANY_H_

#include "Truck.h"
#include <vector>
#include "Item.h"

/** @class Company
*  @brief The Company class has a vertex id of the deposit, garage, has the items that
* need to be delivered and the trucks
*/
class Company {
private:
	int deposit; ///< @var int deposit
	int garage; ///< @var int garage
	std::vector<Truck *> vehicle_fleet; ///< @var vector vehicle_fleet
	std::vector<Item *> allItems; ///< @var vector allItems

public:
	/**
	*  @brief Constructor of a Company class
	* @param deposit The vertex id of the deposit
	* @param map The vertex id of the garage
	*/
	Company(int deposit, int garage);

	/**
	*  @brief Default constructor of a Company class
	*/
	Company();

	/**
	*  @brief Gets the vertex id of the deposit of the company
	* @return A integer with the vertex id of the deposit
	*/
	int getDeposit() const;

	/**
	*  @brief Gets the vertex id of the garage of the company
	* @return A integer with the vertex id of the garage
	*/
	int getGarage() const;

	/**
	*  @brief Gets all the trucks of the company
	* @return A vector with all the trucks of the company
	*/
	std::vector<Truck *> getVehicleFleet() const;

	/**
	*  @brief Gets all the items to be delivered
	* @return A vector with all the items that are not in transity yet
	*/
	std::vector<Item *> getAllItems() const;

	/**
	*  @brief Changes the vertex id of the deposit
	* @param location a integer of the new location of the deposit
	* @return void
	*/
	void setDeposit(int location);

	/**
	*  @brief Changes the vertex id of the garage
	* @param location a integer of the new location of the garage
	* @return void
	*/
	void setGarage(int location);

	/**
	*  @brief Adds a new item to be delivered by the company
	* @param di The item to be delivered
	* @return void
	*/
	void addItemToDeposit(Item *di);

	/**
	*  @brief Adds a new truck to the company
	* @param truck The new truck for the company's fleet
	* @return void
	*/
	void addTruck(Truck * truck);

	/**
	*  @brief Finds an item in the deposit and put it into the truck
	* @param di The item that is to be delivered
	* @param truck The truck responsible for the delivery
	* @return True if the item exists, false otherwise
	*/
	bool loadTruck(Item *di, Truck *truck);

	/** @class EqualGarageDepositLocation
	*  @brief The class EqualGarageDepositLocation is used when the user inputs the same garage and deposit location
	*/
	class EqualGarageDepositLocation {
	private:
		std::string error; ///< @var std::string reason
	public:
		/**
		*  @brief Constructor of the EqualGarageDepositLocation class
		* @param error a string argument related to the error of the exception
		*/
		EqualGarageDepositLocation(std::string error);

		/** @brief Gets the error of the EqualGarageDepositLocation exception
		*  @return A string with the error
		*/
		std::string getError() const;
	};
};

#endif /* COMPANY_H_ */
