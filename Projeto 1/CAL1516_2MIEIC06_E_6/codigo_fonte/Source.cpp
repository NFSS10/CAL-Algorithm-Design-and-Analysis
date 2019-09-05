/**
* @file Source.cpp
* @author  Jorge Ferreira, Nuno Silva, Pedro Lima
* @version 1.0
*
* @section DESCRIPTION
* Freight Company project, version 1
*/

#include "City.h"
#include "Menu.h"
#include "LoadFiles.h"

int main() {

	City *city = new City();
	std::cout << " 1 - Load from file" << std::endl;
	std::cout << " 0 - Exit" << std::endl;
	std::cout << " ";
	int option;

	try
	{
		option = Menu::inputChoice(1, 0);

		if (option == -1) {
			std::cout << "Exiting." << std::endl;
			return 0;
		}
	}
	catch (AttemptLimitExceeded &e)
	{
		std::cout << e.getReason() << std::endl;
		std::cout << "Exiting." << std::endl;
		return 1;
	}

	if (option == 1) {
		try
		{
			std::cout << "Filename of Items (default: .txt): ";
			std::string items = Menu::getString();
			std::cout << "Filename of Trucks (default: .txt): ";
			std::string trucks = Menu::getString();
			std::cout << "Filename of Map (default: .txt): ";
			std::string map = Menu::getString();
			LoadFiles lf;

			try
			{
				city = lf.load(items, trucks, map);
			}
			catch (LoadFileException &l)
			{
				std::cout << l.getReason() << std::endl;
				std::cout << "Exiting." << std::endl;
				return 1;
			}
		}
		catch (AttemptLimitExceeded &e)
		{
			std::cout << e.getReason() << std::endl;
			std::cout << "Exiting." << std::endl;
			return 1;
		}
	}

	Menu menu(city);
	menu.start();

	delete city;

	return 0;
}