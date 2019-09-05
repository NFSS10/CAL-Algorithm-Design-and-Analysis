#include "menu.h"


Menu::Menu(City * city)
{
	this->city = city;
}

int Menu::inputChoice(int maximumBound, int minimumBound)
{
	int returnValue;
	bool firstTime = true;
	int attempts = 0;

	do
	{
		if (attempts >= MAX_ATTEMPTS)
			throw AttemptLimitExceeded("The attempt limit was exceeded when typing a number.");

		if (!firstTime)
			std::cout << "Please type a number between " << minimumBound << " and " << maximumBound << "." << std::endl;
		if (!(std::cin >> returnValue))
			std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		++attempts;
		firstTime = false;

		if (returnValue == 0)
			return -1;

	} while (returnValue < minimumBound || returnValue > maximumBound);

	return returnValue;
}

std::string Menu::getString()
{
	std::string value;

	std::getline(std::cin, value);
	std::cin.clear();

	return value;
}

int Menu::getNumber()
{
	int returnValue = -1;
	bool canExit = false;
	do
	{
		if (!(std::cin >> returnValue))
			std::cin.clear();
		else
			canExit = true;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (!canExit);

	return returnValue;
}

AttemptLimitExceeded::AttemptLimitExceeded(std::string reason)
{
	this->reason = reason;
}

std::string AttemptLimitExceeded::getReason() const {
	return this->reason;
}

void Menu::addItemsDestination()
{
	system("CLS");
	const size_t MENU_OPTIONS = city->getMap()->getVertexSet().size();
	size_t depositItems = city->getCompany()->getAllItems().size();

	//show all available destinations
	std::cout << "Available destinations: " << endl;
	city->getMap()->ShowVertexID();

	int option = -1;
	do {
		std::cout << "Choose a Deposit destination: ";
		option = Menu::getNumber();
		try {
			if (city->getMap()->vertexExists(option))
				city->getCompany()->setDeposit(option);
			else
				option = -1;
		}
		catch (Company::EqualGarageDepositLocation &r)
		{
			std::cout << r.getError() << std::endl;
			option = -1;
		}
	} while (option == -1);

	option = -1;
	do {
		std::cout << "Choose a Garage destination: ";
		option = Menu::getNumber();
		try {
			if (city->getMap()->vertexExists(option))
				city->getCompany()->setGarage(option);
			else
				option = -1;
		}
		catch (Company::EqualGarageDepositLocation &r)
		{
			std::cout << r.getError() << std::endl;
			option = -1;
		}
	} while (option == -1);


	size_t counter = 0;
	while (counter < depositItems)
	{
		option = -1;
		do
		{
			std::cout << "Choose a destination to the item " << (counter + 1) << ": ";

			option = Menu::getNumber();

			if (city->getMap()->vertexExists(option))
				city->getCompany()->getAllItems()[counter]->setDestination(option);
			else
				option = -1;

		} while (option == -1);

		counter++;
	}

	if (!city->checkConnection())
	{
		std::cout << std::endl << "----------There is no connection.----------" << endl;
		exit(-1);
	}

	std::cout << endl << "-----------------ALL ITEMS HAVE A DESTINATION-----------------" << endl;
}

void Menu::LoadToTruck()
{
	system("CLS");
	std::cout << "Transferring items to truck..... ";
	//std::this_thread::sleep_for(2s); //"adormece 2 segundos
	std::cout << "COMPLETE." << std::endl;

	vector<Item *> depositItems = city->getCompany()->getAllItems();
	vector<Truck *> fleet = city->getCompany()->getVehicleFleet();

	//Putting all items on the first truck
	for (size_t i = 0; i < depositItems.size(); i++)
		city->getCompany()->loadTruck(depositItems[i], fleet[0]);


	vector<int> shortest;
	shortest = city->shortestPath(fleet[0]);
	if (shortest.size() == 0)
	{
		std::cout << endl << "There is no possible way to deliver those items(no connection)." << endl;
		exit(0);
	}

	std::cout << "----Shortest Path----" << endl;
	for (size_t j = 0; j < shortest.size(); j++)
		std::cout << j << ". " << shortest[j] << endl;

	ofstream fic;
	fic.open("caminho.txt");
	for (size_t j = 0; j < shortest.size(); j++)
		fic << shortest[j] << endl;
	fic.close();

	system("GraphViewer.exe");
	fleet[0]->deliveryItems();
}


void Menu::LoadToTrucks()
{
	system("CLS");
	std::cout << "Transferring items to trucks..... ";
	//std::this_thread::sleep_for(2s); //"adormece 2 segundos
	std::cout << "COMPLETE." << std::endl;

	vector<Truck *> fleet = city->getCompany()->getVehicleFleet();
	vector<Item *> itemsBetween = city->itemsInPathDG();

	for (size_t i = 0; i < itemsBetween.size(); i++)
		city->getCompany()->loadTruck(itemsBetween[i], fleet[fleet.size() - 1]);

	vector<Item *> depositItems = city->getCompany()->getAllItems();

	//Putting all items on the trucks
	for (size_t k = 0; k < fleet.size() - 1; k++)
		for (size_t i = 0; i < depositItems.size(); i++)
			city->getCompany()->loadTruck(depositItems[i], fleet[k]);

	int truck_counter = 0;
	for (size_t i = 0; i < fleet.size(); i++)
		if (fleet[i]->getItemsToDistribute().size() != 0)
			truck_counter++;

	vector<vector<int>> shortest(truck_counter);

	for (size_t i = 0; i < shortest.size(); i++)
		shortest[i] = city->shortestPath(fleet[i]);


	for (size_t i = 0; i < shortest.size(); i++)
		if (shortest[i].size() == 0)
		{
			std::cout << std::endl << "There is no possible way to deliver those items(no connection) in truck " << i + 1 << "." << std::endl;
			exit(0);
		}

	for (size_t j = 0; j < shortest.size(); j++)
	{
		system("CLS");
		std::cout << "----Shortest Path for truck " << j + 1 << "----" << endl;

		ofstream fic;
		fic.open("caminho.txt");
		for (size_t i = 0; i < shortest[j].size(); i++)
		{
			std::cout << i << ". " << shortest[j][i] << std::endl;
			fic << shortest[j][i] << endl;
		}

		fic.close();
		cout << "\n\nPress any key to see other truck\n";
		system("GraphViewer.exe");

	}

	for (size_t k = 0; k < fleet.size(); k++)
		fleet[k]->deliveryItems();
}

void Menu::getArticulationPoints()
{
	system("CLS");
	city->getMap()->resetVisited();
	Vertex<int> *deposit = city->getMap()->getVertex(city->getCompany()->getDeposit());
	city->getMap()->findArt(deposit);
	system("PAUSE");
}

void Menu::roadUnderConstruction()
{
	system("CLS");

	//show all available destinations
	std::cout << "Available destinations: " << endl;
	city->getMap()->ShowVertexID();

	int vertexID1;
	int vertexID2;
	do {
		std::cout << "Enter two vertex ID (Negative number to exit):" << std::endl;
		std::cout << "1. Vertex ID: ";
		vertexID1 = Menu::getNumber();
		if (vertexID1 < 0)
			return;
		std::cout << "2. Vertex ID: ";
		vertexID2 = Menu::getNumber();
		if (vertexID2 < 0)
			return;
		if (city->getMap()->removeEdge(vertexID1, vertexID2))
			std::cout << "Edge removed with success!" << std::endl;
		else
			std::cout << "There is no Edge between the typed vertex IDs!" << std::endl;
	} while (true);
}

void Menu::startAuxMenu()
{
	do
	{
		system("CLS");
		std::cout << std::endl;
		std::cout << " 1 - Remove any edge to simulate a road under construction." << std::endl;
		std::cout << " 2 - Show all articulation points." << std::endl;
		std::cout << " 3 - Continue." << std::endl;
		std::cout << " ";
		int option;

		try
		{
			option = Menu::inputChoice(3, 1);

			switch (option)
			{
			case 1:
			{
				roadUnderConstruction();
				break;
			}
			case 2:
			{
				getArticulationPoints();
				break;
			}
			case 3:
			{
				return;
			}
			}
		}
		catch (AttemptLimitExceeded &e)
		{
			std::cout << e.getReason() << std::endl;
		}
	} while (true);
}

void Menu::start()
{
	addItemsDestination();
	startMenuStringMatcher();
	startAuxMenu();
	//start algorithm
	cout << std::endl << "Calculating best way between vertex's..." << endl;
	city->getMap()->floydWarshallShortestPath();
	do {
		std::vector<Item *> items = city->getCompany()->getAllItems();
		std::cout << "Items in deposit to get destributed:" << std::endl;
		for (size_t i = 0; i < items.size(); i++)
			std::cout << "Item " << i + 1 << " - Destination: " << items[i]->getDestination() << " - Bill Number: " << items[i]->getBillNumber() << std::endl;

		int numberOfFleet = city->getCompany()->getVehicleFleet().size();

		std::cout << std::endl;
		std::cout << " 1 - Load to One Truck" << std::endl;
		if (numberOfFleet > 1)
			std::cout << " 2 - Load to Trucks" << std::endl;
		std::cout << " 0 - Exit" << std::endl;
		std::cout << " ";
		int option;

		try
		{
			if (numberOfFleet > 1)
				option = Menu::inputChoice(2, 0);
			else
				option = Menu::inputChoice(1, 0);

			switch (option)
			{
			case 1:
			{
				std::cout << "Loading items to truck." << std::endl;
				LoadToTruck();
				break;
			}
			case 2:
			{
				std::cout << "Loading items to trucks." << std::endl;
				LoadToTrucks();
				break;
			}
			case -1:
			{
				exit(0);
			}
			}
		}
		catch (AttemptLimitExceeded &e)
		{
			std::cout << e.getReason() << std::endl;
		}

	} while (city->getCompany()->getAllItems().size() != 0);

}

void Menu::stringMatching()
{
	std::vector<Item *> items = city->getCompany()->getAllItems();

	bool secondTime = false;
	std::string toSearch;
	do {
		if (secondTime)
			std::cout << "Bad Input!\n>> ";
		std::cout << "Who do you want to find?\n>> ";
		toSearch = getString();
		secondTime = true;
	} while (toSearch.length() == 0);

	std::cout << "Using KMP algorithm..." << std::endl;
	clock_t time_i = clock();
	bool exist = false;
	int aux = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		if ((aux = matcher::kmp(items[i]->getRecipientName(), toSearch)))
		{
			std::cout << items[i]->getRecipientName() << " found. Item number " << i + 1 << std::endl;
			exist = true;
		}
	}
	if (!exist)
		std::cout << "No one was found using KMP algorithm\n";
	std::cout << "Wasted time searching using KMP algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;


	std::cout << "Using find algorithm of the std..." << std::endl;
	time_i = clock();
	exist = false;
	aux = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		if ((aux = items[i]->getRecipientName().find(toSearch)) != std::string::npos)
		{
			std::cout << items[i]->getRecipientName() << " found. Item number " << i + 1 << std::endl;
			exist = true;
		}
	}
	if (!exist)
		std::cout << "No one was found using find algorithm\n";
	std::cout << "Wasted time searching using find algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;


	std::cout << "Using Bruteforce..." << std::endl;
	time_i = clock();
	aux = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		if ((aux = matcher::searchBruteF(items[i]->getRecipientName(), toSearch)) != -1)
		{
			std::cout << items[i]->getRecipientName() << " found. Item number " << i + 1 << std::endl;
			exist = true;
		}
	}
	if (!exist)
		std::cout << "No one was found using bruteforce\n";
	std::cout << "Wasted time searching using brute force method: " << (clock() - time_i)/ (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;

	system("PAUSE");
}

void Menu::approximateStringMatching()
{
	std::vector<Item *> items = city->getCompany()->getAllItems();
	
	bool secondTime = false;
	std::string toSearch;
	do {
		if (secondTime)
			std::cout << "Bad Input!\n>> ";
		std::cout << "Who do you want to find?\n>> ";
		toSearch = getString();
		secondTime = true;
	} while (toSearch.length() == 0);

	std::cout << "Using approximate string matching algorithm..." << std::endl;
	clock_t time_i = clock();
	bool exist = false;
	int aux = 0;
	for (size_t i = 0; i < items.size(); i++)
	{
		if ((aux = matcher::numApproximateStringMatching(items[i]->getRecipientName(), toSearch)) < 6)
		{
			std::cout << items[i]->getRecipientName() << " found. Item number " << i + 1 << std::endl;
			exist = true;
		}
	}
	if (!exist)
		std::cout << "No one was found using approximate string matching algorithm\n";
	std::cout << "Wasted time searching using approximate string matching algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;

	system("PAUSE");
}

std::vector<int> getRoadsToID(City *city, int id)
{
	std::vector<int> ret;
	std::vector<Vertex<int> *> v = city->getMap()->getVertexSet();

	for (size_t i = 0; i < v.size(); i++)
		for (size_t j = 0; j < v[i]->getAdjEdges().size(); j++)
			if ((v[i]->getInfo() == id) || (v[i]->getAdjEdges()[j].getDest()->getInfo() == id))
				ret.push_back(v[i]->getAdjEdges()[j].getID());

	return ret;
}

void Menu::stringMatchingAdress()
{
	std::vector<Item *> items = city->getCompany()->getAllItems();

	bool secondTime = false;
	std::string toSearch;
	do {
		if (secondTime)
			std::cout << "Bad Input!\n>> ";
		std::cout << "What road do you want to find?\n>> ";
		toSearch = getString();
		secondTime = true;
	} while (toSearch.length() == 0);

	std::map<int, std::string> m = city->getMap()->getMap();

	bool exist = false;
	std::cout << "Using KMP algorithm..." << std::endl;
	clock_t time_i = clock();
	for (size_t i = 0; i < items.size(); i++)
	{
		//get all the Roads with nodes id equals to ItemID
		std::vector<int> roadsToID = getRoadsToID(city, items[i]->getDestination());
		for (size_t j = 0; j < roadsToID.size(); j++) {
			std::map<int, std::string>::iterator it;
			it = m.find(roadsToID[j]);
			if(it != m.end())
				if (matcher::kmp(it->second, toSearch))
				{
					exist = true;
					std::cout << it->second << " found. Item number " << i + 1 << std::endl;
					break;
				}
		}
	}
	if (!exist)
		std::cout << "No road was found using KMP algorithm\n";
	std::cout << "Wasted time searching using KMP algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;


	exist = false;
	std::cout << "Using find algorithm of the std..." << std::endl;
	time_i = clock();
	for (size_t i = 0; i < items.size(); i++)
	{
		//get all the Roads with nodes id equals to ItemID
		std::vector<int> roadsToID = getRoadsToID(city, items[i]->getDestination());
		for (size_t j = 0; j < roadsToID.size(); j++) {
			std::map<int, std::string>::iterator it;
			it = m.find(roadsToID[j]);
			if (it != m.end())
				if (it->second.find(toSearch) != std::string::npos)
				{
					exist = true;
					std::cout << it->second << " found. Item number " << i + 1 << std::endl;
					break;
				}
		}
	}
	if (!exist)
		std::cout << "No road was found using find algorithm\n";
	std::cout << "Wasted time searching using find algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;


	exist = false;
	std::cout << "Using Bruteforce..." << std::endl;
	time_i = clock();
	for (size_t i = 0; i < items.size(); i++)
	{
		//get all the Roads with nodes id equals to ItemID
		std::vector<int> roadsToID = getRoadsToID(city, items[i]->getDestination());
		for (size_t j = 0; j < roadsToID.size(); j++) {
			std::map<int, std::string>::iterator it;
			it = m.find(roadsToID[j]);
			if (it != m.end())
				if (matcher::searchBruteF(it->second, toSearch) != -1)
				{
					exist = true;
					std::cout << it->second << " found. Item number " << i + 1 << std::endl;
					break;
				}
		}
	}
	if (!exist)
		std::cout << "No road was found using bruteforce\n";
	std::cout << "Wasted time searching using bruteforce: " << (clock() - time_i) /(double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;


	system("PAUSE");
}

void Menu::approximateStringMatchingAdress()
{
	std::vector<Item *> items = city->getCompany()->getAllItems();

	bool secondTime = false;
	std::string toSearch;
	do {
		if (secondTime)
			std::cout << "Bad Input!\n>> ";
		std::cout << "What road do you want to find?\n>> ";
		toSearch = getString();
		secondTime = true;
	} while (toSearch.length() == 0);

	std::map<int, std::string> m = city->getMap()->getMap();

	std::cout << "Using approximate string matching algorithm..." << std::endl;
	clock_t time_i = clock();
	bool exist = false;
	for (size_t i = 0; i < items.size(); i++)
	{
		//get all the Roads with nodes id equals to ItemID
		std::vector<int> roadsToID = getRoadsToID(city, items[i]->getDestination());
		for (size_t j = 0; j < roadsToID.size(); j++) {
			std::map<int, std::string>::iterator it;
			it = m.find(roadsToID[j]);
			if (it != m.end())
			{
				int aux = 0;
				if ((aux = matcher::numApproximateStringMatching(it->second, toSearch)) < 6)
				{
					std::cout << it->second << " found. Item number " << i + 1 << std::endl;
					exist = true;
					break;
				}
			}
		}
	}
	if (!exist)
		std::cout << "No road was found using approximate string matching algorithm\n";
	std::cout << "Wasted time searching using approximate string matching algorithm: " << (clock() - time_i) / (double)(CLOCKS_PER_SEC / TOMILISECONDS) << "ms." << std::endl << std::endl;

	system("PAUSE");
}

void Menu::startMenuStringMatcher()
{
	do
	{
		system("CLS");
		std::cout << std::endl;
		std::cout << " 1 - String Matching (Client Name)" << std::endl;
		std::cout << " 2 - Approximate String Matching (Client Name)" << std::endl;
		std::cout << " 3 - String Matching (Adress Name)" << std::endl;
		std::cout << " 4 - Approximate String Matching (Adress Name)" << std::endl;
		std::cout << " 5 - Continue." << std::endl;
		std::cout << " ";
		int option;

		try
		{
			option = Menu::inputChoice(5, 1);

			switch (option)
			{
			case 1:
			{
				stringMatching();
				break;
			}
			case 2:
			{
				approximateStringMatching();
				break;
			}
			case 3:
			{
				stringMatchingAdress();
				break;
			}
			case 4:
			{
				approximateStringMatchingAdress();
				break;
			}
			case 5:
			{
				return;
			}
			}
		}
		catch (AttemptLimitExceeded &e)
		{
			std::cout << e.getReason() << std::endl;
		}
	} while (true);
}