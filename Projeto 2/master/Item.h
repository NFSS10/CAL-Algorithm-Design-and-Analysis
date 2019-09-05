/** @file Item.h
*  @brief Item to get distributed
*/
#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include <string>


/** @class Item
*  @brief The class Item that has all the components of the item like his destination, volume, value bill number and the recipient name
*/
class Item {
private:
	std::string recipient_name; ///< @var std::string recipient_name
	int destination; ///< @var int destination
	int billNumber; ///< @var int billNumber
	double value; ///< @var double value
	double volume; ///< @var double volume

public:
	/**
	*  @brief Constructor of the Item class
	* @param recipient_name name of the recipiente of the item
	* @param destination id of the vertex of destination
	* @param billNumber billNumber of the item
	* @param value Value of the item
	* @param volume Volume of the item
	*/
	Item(std::string recipient_name, int destination, int billNumber, double value, double volume);

	/**
	*  @brief Gets the name of the recipient
	* @return A string with the name of the recipient
	*/
	std::string getRecipientName() const;

	/**
	*  @brief Gets the destination id of the vertex
	* @return A integer with the destination
	*/
	int getDestination() const;

	/**
	*  @brief Gets the bill number of the item
	* @return A integer with the bill number
	*/
	int getBillNumber() const;

	/**
	*  @brief Gets the value of the item
	* @return A double with the value
	*/
	double getValue() const;

	/**
	*  @brief Gets the volume of the item
	* @return A double with the volume
	*/
	double getVolume() const;

	/**
	*  @brief Changes the value of the item
	* @param value a double with the update value
	* @return void
	*/
	void setValue(double value);

	/**
	*  @brief Changes the volume of the item
	* @param volume a double with the update volume
	* @return void
	*/
	void setVolume(double volume);

	/**
	*  @brief Changes the destination of the item
	* @param destination a integer with the update destination
	* @return void
	*/
	void setDestination(int destination);

	/**
	* @brief To check if a item is equal to another item
	* @param t1 the item that we want to compare with
	* @return true if the item we want to check is equal to the t1
	*/
	bool operator==(Item *t1);

	/**
	* @brief To check if a item is smaller than another item
	* @param t1 the item that we want to compare with
	* @return true if the item we want to check is smaller then t1
	*/
	bool operator<(Item *t1);

};
#endif /*ITEM_H_ */
