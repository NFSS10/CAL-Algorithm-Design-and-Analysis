/*
 * Truck.c
 *
 */

#include "Truck.h"

Truck::Truck(double truck_load)
{
	this->truck_load = truck_load;
	this->stowage = 0;
}

double Truck::getTruckLoad() const
{
	return truck_load;
}

double Truck::getStowage() const
{
	return stowage;
}

std::vector<Item *> Truck::getItemsToDistribute() const
{
	return itemsToDistribute;
}

bool Truck::operator==(const Truck *t1)
	{
	if((t1->getTruckLoad() != truck_load) || (t1->getStowage() != stowage) || (t1->getItemsToDistribute().size() != itemsToDistribute.size()))
		return false;
	else
	{
		for(size_t i = 0;i < t1->getItemsToDistribute().size();i++)
			if(!(t1->getItemsToDistribute()[i] == itemsToDistribute[i]))
				return false;
	}
	return true;
	}

bool alreadyHasItem(Item *di,Truck *truck)
{
	std::vector<Item *> aux = truck->getItemsToDistribute();
	for (size_t i = 0; i < aux.size(); i++)
		if (di->getDestination() == aux[i]->getDestination())
			return true;
	return false;
}

bool Truck::addItem(Item *di)
{
	if ((this->stowage + di->getVolume()) <= truck_load)
	{
		if(!alreadyHasItem(di,this))
			itemsToDistribute.push_back(di);
		this->stowage += di->getVolume();
		return true;
	}
	return false;
}

void Truck::deliveryItems()
{
	this->stowage = 0;
	itemsToDistribute.clear();
}
