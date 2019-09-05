/*
 * DepositItem.c
 *
 */
#include "Item.h"

Item::Item(std::string client_name, int destination, int billNumber, double value, double volume)
{
	this->recipient_name = client_name;
	this->destination = destination;
	this->billNumber = billNumber;
	this->value = value;
	this->volume = volume;
}

std::string Item::getRecipientName() const
{
	return recipient_name;
}

int Item::getDestination() const
{
	return destination;
}

int Item::getBillNumber() const
{
	return billNumber;
}

double Item::getValue() const
{
	return value;
}

double Item::getVolume() const
{
	return volume;
}

void Item::setValue(double value)
{
	this->value = value;
}

void Item::setVolume(double volume)
{
	this->volume = volume;
}

void Item::setDestination(int destination)
{
	this->destination = destination;
}

bool Item::operator==(Item *t1)
{
   return ((value == t1->getValue()) && (volume == t1->getVolume()) && (billNumber == t1->getBillNumber()) && (recipient_name == t1->getRecipientName()) && (destination == t1->getDestination()));
}

bool Item::operator<(Item *t1)
{
	if (destination < t1->getDestination())
		return true;
	else
		if (destination == t1->getDestination())
			if (billNumber < t1->getBillNumber())
				return true;

	return false;
}






