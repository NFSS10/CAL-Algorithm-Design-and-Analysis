/*
 * Company.cpp
 *
 */
#include "LoadFiles.h"

LoadFileException::LoadFileException(std::string reason) : reason(reason) {}

std::string LoadFileException::getReason() const
{
	return reason;
}

//---------------------------------------------------------------
LoadFiles::LoadFiles():city(NULL){}

LoadFiles::~LoadFiles()
{
	if (items.is_open())
		items.close();

	if (trucks.is_open())
		trucks.close();

	if (map1.is_open())
		map1.close();

	if (map2.is_open())
		map2.close();

	if (map3.is_open())
		map3.close();
}

std::string LoadFiles::loadItemString()
{
	std::string returnString;

	std::getline(items, returnString);

	return returnString;
}

std::string LoadFiles::loadTruckString()
{
	std::string returnString;

	std::getline(trucks, returnString);

	return returnString;
}

int LoadFiles::loadItemInt()
{
	int number = 0;

	items >> number;
	items.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return number;
}

int LoadFiles::loadTruckInt()
{
	int number = 0;

	trucks >> number;
	trucks.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return number;
}

double LoadFiles::loadNumberDouble()
{
	double number;

	items >> number;
	items.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return number;
}

Item * LoadFiles::loadItem()
{
	std::string clientName = loadItemString();
	int billNumber = loadItemInt();
	double value = loadNumberDouble();
	double volume = loadNumberDouble();

	return new Item(clientName, NULL, billNumber, value, volume);
}

Truck* LoadFiles::loadTrucks()
{
	int truckLoad = loadTruckInt();
	
	return new Truck(truckLoad);
}

Company* LoadFiles::loadCompany()
{
	Company *com = new Company();

	while (!items.eof())
		com->addItemToDeposit(loadItem());

	while (!trucks.eof())
		com->addTruck(loadTrucks());

	return com;
}

Graph<int>* LoadFiles::loadGraph()
{
	Graph<int> *graph = new Graph<int>();
	std::string line;
	int idNo;
	double longitude = 0;
	double latitude = 0;

	//read map1
	while (std::getline(map1, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> latitude;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> longitude;

		graph->addVertex(idNo, latitude, longitude);
	}

	//read map3
	int vertexS = 0;
	int vertexD = 0;
	while (std::getline(map3, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> vertexS;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> vertexD;

		graph->addEdge(vertexS, vertexD, idNo);
	}

	//read map2
	std::string roadName;
	std::string two_way;

	while (std::getline(map2, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> idNo;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		std::getline(linestream, roadName, ';');  // read up-to the first ; (discard ;).
		std::getline(linestream, two_way);  // read up-to the first ; (discard ;).
		graph->addToMap(idNo, roadName);

		if (two_way == "True")
		{
			bool test = false;
			//if road got two ways we should add another edge
			for(size_t i = 0; i < graph->getVertexSet().size();i++) {
				if (test == true)
					break;
				std::vector<Edge<int> > adjacents = graph->getVertexSet()[i]->getAdjEdges();
				for (size_t j = 0; j < adjacents.size(); j++){
					if (adjacents[j].getID() == idNo)
					{
						vertexS = adjacents[j].getDest()->getInfo();
						vertexD = graph->getVertexSet()[i]->getInfo();
						graph->addEdge(vertexS, vertexD,idNo);
						test = true;
						break;
					}
					
				}
			}
		}
	}
	
	for (size_t i = 0; i < graph->getVertexSet().size(); i++)
		if (graph->getVertexSet()[i]->getParents() == 0 && graph->getVertexSet()[i]->getAdjEdges().size() == 0) {
			Vertex<int> * v = graph->getVertexSet()[i];
			graph->getVertexSet().erase(graph->getVertexSet().begin() + i);
			delete(v);
		}
	

	return graph;
	
}

City* LoadFiles::load(std::string items, std::string trucks, std::string map)
{
	if (items.find_last_of(".") == string::npos)
		items += ".txt";

	this->items.open(items.c_str(), std::ios::in);
	if (!this->items.is_open())
		throw LoadFileException("Error opening file");

	if (trucks.find_last_of(".") == string::npos)
		trucks += ".txt";

	this->trucks.open(trucks.c_str(), std::ios::in);
	if (!this->trucks.is_open())
		throw LoadFileException("Error opening file");

	std::string map1aux;
	std::string map2aux;
	std::string map3aux;

	size_t pos = map.find_last_of(".");
	if (pos == string::npos)
	{
		map1aux = map + "1.txt";
		map2aux = map + "2.txt";
		map3aux = map + "3.txt";
	}
	else
	{
		map1aux = map;
		map1aux.insert(pos - 1, "1");
		map2aux = map;
		map2aux.insert(pos - 1, "2");
		map3aux = map;
		map3aux.insert(pos - 1, "3");
	}

	this->map1.open(map1aux.c_str(), std::ios::in);
	if (!this->map1.is_open())
		throw LoadFileException("Error opening file!");

	this->map2.open(map2aux.c_str(), std::ios::in);
	if (!this->map2.is_open())
		throw LoadFileException("Error opening file!");

	this->map3.open(map3aux.c_str(), std::ios::in);
	if (!this->map3.is_open())
		throw LoadFileException("Error opening file!");

	std::string name = loadTruckString();
	Graph<int> *graph = loadGraph();

	Company * com = loadCompany();
	
	cout << endl << "LOAD COMPLETE." << endl;
	return new City(name, graph, com);
}
