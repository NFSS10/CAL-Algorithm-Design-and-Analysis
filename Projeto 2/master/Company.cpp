/*
 * Company.c
 *
 */
#include "Company.h"
#include <cmath>

Company::Company()
{
	this->deposit = 0;
	this->garage = 0;
}

Company::Company(int deposit, int garage)
{
	if (deposit == garage)
		throw(EqualGarageDepositLocation("Deposit and Garage have the same location"));

	this->deposit = deposit;
	this->garage = garage;
}

int Company::getDeposit() const
{
	return deposit;
}

int Company::getGarage() const
{
	return garage;
}

std::vector<Truck *> Company::getVehicleFleet() const
{
	return vehicle_fleet;
}

std::vector<Item *> Company::getAllItems() const
{
	return allItems;
}

void Company::setDeposit(int location)
{
	if (location == this->garage)
		throw(EqualGarageDepositLocation("Deposit and Garage have the same location!"));
	this->deposit = location;
}

void Company::setGarage(int location)
{
	if (location == this->deposit)
		throw(EqualGarageDepositLocation("Deposit and Garage have the same location!"));
	this->garage = location;
}

void Company::addItemToDeposit(Item *di)
{
	allItems.push_back(di);
}

void Company::addTruck(Truck * truck)
{
	vehicle_fleet.push_back(truck);
}

bool Company::loadTruck(Item *di,Truck *truck)
{
  //find the item in deposit and put it into truck
	for(size_t i = 0; i < allItems.size();i++)
		if(di == allItems[i])
		{
			if (truck->addItem(di))
			{
				allItems.erase(allItems.begin() + i);
				break;
			}
		  else 
			  return false;
		}
	return true;
}

Company::EqualGarageDepositLocation::EqualGarageDepositLocation(std::string error)
{
	this->error = error;
}

std::string Company::EqualGarageDepositLocation::getError() const
{
	return error;
}

