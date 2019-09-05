/*
* City.c
*
*/
#include "City.h"

City::City(std::string name, Graph<int> *map, Company* company)
{
	this->name = name;
	this->map = map;
	this->company = company;
}

City::City()
{
	this->name = "";
	this->map = NULL;
	this->company = NULL;
}

void City::setName(std::string name)
{
	this->name = name;
}

std::string City::getName()
{
	return name;
}

Graph<int>* City::getMap()
{
	return map;
}

void City::setMap(Graph<int> *map)
{
	this->map = map;
}

Company* City::getCompany()
{
	return company;
}

void City::setCompany(Company* company)
{
	this->company = company;
}

//auxiliar func
double calcDist(vector<Item *> vi,Graph<int>* map,double dist_min)
{
	double dist = 0;
	int i = 0;
	int j = 0;
	for (size_t k = 0; k < (vi.size() - 1); k++)
	{
		i = map->getVertexIndex(vi[k]->getDestination());
		j = map->getVertexIndex(vi[k + 1]->getDestination());
		double tmp = map->getW()[i][j];

		if (((map->getW()[i][j] == INT_INFINITY)) || ((dist + tmp ) > dist_min))
			return -1;
		else dist += map->getW()[i][j];
	}
	//retorna -1 se nao existe caminho possivel entre 2 items da sequencia
	return dist;
}


vector<int> City::shortestPath(Truck *truck)
{
	int garage = company->getGarage();
	int deposit = company->getDeposit();

	double dist_min = INT_INFINITY;
	vector<Item *> minimal_path;

	vector<int> error;

	vector<Item *> vi = truck->getItemsToDistribute();
	std::sort(vi.begin(), vi.end());

	int depositoIndex = map->getVertexIndex(deposit);
	int garageIndex = map->getVertexIndex(garage);
	do {
		double dist = 0;
		//calcula a distancia da garagem ao 1º elemento
		//a garagem e o deposito nao devem fazer parte do vector ja que 
		//iniciamos e terminamos sempre no mesmo sitio
		int firstEleIndex = map->getVertexIndex(vi.front()->getDestination());
		if ((dist = map->getW()[depositoIndex][firstEleIndex]) == INT_INFINITY)
			continue;
		
		//calcula a distancia entre todos os items
		double tmpDist = 0;
		if ((tmpDist = calcDist(vi, map,dist_min)) != -1)
			dist += tmpDist;
		else
			continue;

		//adiciona a distancia do ultimo elemento a garagem
		
		int LastEleIndex = map->getVertexIndex(vi.back()->getDestination());
		if ((tmpDist = map->getW()[LastEleIndex][garageIndex]) != INT_INFINITY)
			dist += tmpDist;
		else
			continue;

		if (dist < dist_min)
		{
			dist_min = dist;
			minimal_path = vi;
		}

	} while (std::next_permutation(vi.begin(), vi.end()));
	
	//se nao houver nenhuma combinacao de items em que haja um caminho possivel
	if (dist_min == INT_INFINITY)
		return error;

	//vector with all nodes ids (intermediate points included)
	vector<int> shortestPath;
	//vector of ids without intermediate ones;
	vector<int> nodsID;
	nodsID.push_back(deposit);
	for (size_t j = 0; j < minimal_path.size(); j++)
		nodsID.push_back(minimal_path[j]->getDestination());
	nodsID.push_back(garage);

	for (size_t i = 0; i < (nodsID.size() - 1); i++)
	{
		int originID = nodsID[i];
		int destID = nodsID[i + 1];
		vector<int> pathOfTwoNodes = map->getfloydWarshallPath(originID, destID);
		//we must delete the last element or we will get 2x each destID
		if(i < (nodsID.size() -2)) //in the last iteration we wont remove of course
		pathOfTwoNodes.pop_back();
		//append pathOfTwoNodes to the end of ShortestPath vector
		shortestPath.insert(shortestPath.end(), pathOfTwoNodes.begin(), pathOfTwoNodes.end());
	}

	return shortestPath;
}

bool City::thereIsPath(vector<int> v)
{
	int paths = 0;
	bool pathToExit = false;
	vector<Item *> allItems = company->getAllItems();
	int garage = company->getGarage();

	//verifica se todos os items sao alcancaveis atraves do deposito
	for (size_t i = 0; i < allItems.size(); i++)
		for (size_t j = 0; j < v.size(); j++)
			if (allItems[i]->getDestination() == v[j])
			{
				paths++;
				break;
			}
	//verifica se a saida é alcancavel
	for (size_t k = 0; k < v.size(); k++)
		if (v[k] == garage)
			pathToExit = true;

	return ((paths == allItems.size()) && pathToExit);//verifica se existe um caminho possivel desde o deposito a todos os outros vertices


}

bool City::checkConnection()
{
	int deposit = company->getDeposit();
	int garage = company->getGarage();

	//faz uma pesquisa em largura
	Vertex<int> *depositV = map->getVertex(deposit);
	vector<int> breadthFirst = map->bfs(depositV);

	return thereIsPath(breadthFirst);
}

vector<Item *> City::itemsInPathDG()
{
	vector<Item *> itemsInPath;
	vector<int> betweenPath = map->getfloydWarshallPath(company->getDeposit(), company->getGarage());

	vector<Item *> depositoryItems = company->getAllItems();
	for(size_t i = 0; i < depositoryItems.size();i++)
		for(size_t j = 0; j < betweenPath.size();j++)
		if(depositoryItems[i]->getDestination() == betweenPath[j])
		{
			itemsInPath.push_back(depositoryItems[i]);
			break;
		}

	return itemsInPath;
}