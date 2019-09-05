/*
* Graph.h
*/
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <map>

using namespace std;

#define RADIUS 6371
#define PI  3.14159265358

template <class T> class Edge;
template <class T> class Graph;

const int NOT_VISITED = 0;
const int BEING_VISITED = 1;
const int DONE_VISITED = 2;
const int INT_INFINITY = INT_MAX;

/*
* ================================================================================================
* Class Vertex
* ================================================================================================
*/
template <class T>
class Vertex {
	T info;
	double x;
	double y;
	double z;
	int num;
	int low;
	T parent_id;
	vector<Edge<T>  > adj;
	bool visited;
	bool processing;
	int indegree;
	int dist;
	int parents;
public:

	Vertex(T in, double latitude, double longitude);
	friend class Graph<T>;

	void addEdge(Vertex<T> *dest, double w, int id);
	bool removeEdgeTo(Vertex<T> *d, int *index);

	vector<Edge<T> > getAdjEdges() const;
	T getInfo() const;
	void setInfo(T info);

	int getDist() const;
	int getIndegree() const;

	void increaseParents();
	int getParents();


	Vertex* path;
};


template <class T>
struct vertex_greater_than {
	bool operator()(Vertex<T> * a, Vertex<T> * b) const {
		return a->getDist() > b->getDist();
	}
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d,int *index) {
	d->indegree--; //adicionado do exercicio 5
	typename vector<Edge<T> >::iterator it = adj.begin();
	typename vector<Edge<T> >::iterator ite = adj.end();
	while (it != ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

//atualizado pelo exercício 5
template <class T>
Vertex<T>::Vertex(T in, double latitude, double longitude) : info(in), visited(false), processing(false), indegree(0), dist(0) {
	path = NULL;

	this->x = RADIUS * cos(latitude*(PI / 180)) * cos(longitude*(PI / 180));
	this->y = RADIUS * cos(latitude*(PI / 180)) * sin(longitude*(PI / 180));
	this->z = RADIUS * sin(latitude*(PI / 180));
	this->parents = 0;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w, int id) {
	Edge<T> edgeD(dest, w, id);
	adj.push_back(edgeD);
}

template<class T>
vector<Edge<T> > Vertex<T>::getAdjEdges() const
{
	return adj;
}

template<class T>
void Vertex<T>::increaseParents()
{
	parents++;
}

template<class T>
int Vertex<T>::getParents()
{
	return parents;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
int Vertex<T>::getDist() const {
	return this->dist;
}


template <class T>
void Vertex<T>::setInfo(T info) {
	this->info = info;
}

template <class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}




/* ================================================================================================
* Class Edge
* ================================================================================================
*/
template <class T>
class Edge {
	int id;
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w, int identifier);

	int getID() const;
	Vertex<T>* getDest() const;
	double getWeight() const;

	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, int identifier) : dest(d), weight(w), id(identifier) {}

template <class T>
int Edge<T>::getID() const
{
	return id;
}

template<class T>
Vertex<T>* Edge<T>::getDest() const
{
	return dest;
}

template<class T>
double Edge<T>::getWeight() const
{
	return weight;
}


/* ================================================================================================
* Class Graph
* ================================================================================================
*/
template <class T>
class Graph {

	std::map<int, std::string> map;

	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();
	void getPathTo(Vertex<T> *origin, list<T> &res);

	double ** W;   //weight
	double ** P;   //path

	int counter = 1;

public:
	bool addVertex(const T &in, double latitude, double longitude);
	bool addEdge(const T &sourc, const T &dest, int id, double w = 0);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;

	bool vertexExists(const T info);
	Vertex<T>* getVertex(const T &v) const;
	int getVertexIndex(const T &v) const;
	double ** getW() const;
	double ** getP() const;
	void resetIndegrees();
	vector<Vertex<T>*> getSources() const;
	int getNumCycles();
	vector<T> topologicalOrder();
	vector<T> getPath(const T &origin, const T &dest);
	void unweightedShortestPath(const T &v);
	bool isDAG();
	void ShowVertexID();
	void resetVisited();

	void addToMap(int i, std::string s);
	std::map<int, std::string> getMap() const;

	void findArt(Vertex<T> *v);

	void floydWarshallShortestPath();
	double edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
};


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
void Graph<T>::addToMap(int i, std::string s)
{
	map.insert(std::pair<int, std::string >(i, s));
}

template<class T>
std::map<int, std::string> Graph<T>::getMap() const
{
	return map;
}

template <class T>
bool Graph<T>::vertexExists(const T info)
{
	for (size_t i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == info)
			return true;

	return false;
}

template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template <class T>
double ** Graph<T>::getW() const
{
	return W;
}

template <class T>
double ** Graph<T>::getP() const
{
	return P;
}

template <class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template <class T>
bool Graph<T>::addVertex(const T &in, double latitude, double longitude) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in, latitude, longitude);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v = *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1 = vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e = vertexSet.end();
			for (; it1 != it1e; it1++) {
				int index;
				(*it1)->removeEdgeTo(v,&index);
			}

			typename vector<Edge<T> >::iterator itAdj = v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje = v->adj.end();
			for (; itAdj != itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, int id, double w) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS = NULL, *vD = NULL;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (vD == NULL || vS == NULL)
		return false;

	vD->indegree++;

	w = sqrt((pow(vS->x - vD->x, 2) + (pow(vS->y - vD->y, 2)) + (pow(vS->z - vD->z, 2))));

	vS->addEdge(vD, w, id);
	vD->increaseParents();

	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS = NULL;
	Vertex<T> *vD = NULL;

	while (found != 2 && it != ite) {
		if ((*it)->info == sourc)
		{
			vS = *it; found++;
		}
		if ((*it)->info == dest)
		{
			vD = *it; found++;
		}
		it++;
	}
	if (found != 2)
		return false;

	vD->indegree--;

	int index = 0;
	bool ret = (vS->removeEdgeTo(vD,&index));
	bool test = true;

	if (ret) {
		for (size_t i = 0; i < vertexSet.size(); i++)
		{
			if (vertexSet[i]->info == dest)
			{
				for (size_t j = 0; j < vertexSet[i]->getAdjEdges().size(); j++)
					if (vertexSet[i]->getAdjEdges()[j].getDest()->info == sourc)
					{
						test = false;
						break;
					}
			}
			if (!test)
				break;
		}
		if (test)
			map.erase(index);
	}

	return ret;
}

template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			dfs(it->dest, res);
		}
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren = 0;
	inf = v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l = level.front();
		level.pop(); l++;
		int nChildren = 0;
		typename vector<Edge<T> >::iterator it = v1->adj.begin();
		typename vector<Edge<T> >::iterator ite = v1->adj.end();
		for (; it != ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited == false) {
				d->visited = true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren > maxChildren) {
			maxChildren = nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
int Graph<T>::getVertexIndex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return i;
	return NULL;
}


template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++) vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}


template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const {
	vector< Vertex<T>* > buffer;
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->indegree == 0) buffer.push_back(vertexSet[i]);
	}
	return buffer;
}


template <class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}

template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true) numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

template<class T>
vector<T> Graph<T>::topologicalOrder() {
	//vector com o resultado da ordenacao
	vector<T> res;

	//verificar se é um DAG
	if (getNumCycles() > 0) {
		cout << "Ordenacao Impossivel!" << endl;
		return res;
	}

	//garantir que os "indegree" estao inicializados corretamente
	this->resetIndegrees();

	queue<Vertex<T>*> q;

	vector<Vertex<T>*> sources = getSources();
	while (!sources.empty()) {
		q.push(sources.back());
		sources.pop_back();
	}

	//processar fontes
	while (!q.empty()) {
		Vertex<T>* v = q.front();
		q.pop();

		res.push_back(v->info);

		for (unsigned int i = 0; i < v->adj.size(); i++) {
			v->adj[i].dest->indegree--;
			if (v->adj[i].dest->indegree == 0) q.push(v->adj[i].dest);
		}
	}

	//testar se o procedimento foi bem sucedido
	if (res.size() != vertexSet.size()) {
		while (!res.empty()) res.pop_back();
	}

	//garantir que os "indegree" ficam atualizados ao final
	this->resetIndegrees();

	return res;
}



template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest) {

	list<T> buffer;
	Vertex<T>* v = getVertex(dest);

	//cout << v->info << " ";
	buffer.push_front(v->info);
	while (v->path != NULL &&  v->path->info != origin) {
		v = v->path;
		buffer.push_front(v->info);
	}
	if (v->path != NULL)
		buffer.push_front(v->path->info);


	vector<T> res;
	while (!buffer.empty()) {
		res.push_back(buffer.front());
		buffer.pop_front();
	}
	return res;
}


template<class T>
void Graph<T>::unweightedShortestPath(const T &s) {

	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while (!q.empty()) {
		v = q.front(); q.pop();
		for (unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if (w->dist == INT_INFINITY) {
				w->dist = v->dist + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::ShowVertexID()
{
	for (size_t i = 0; i < vertexSet.size(); i++)
		cout << vertexSet[i]->info << endl;
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest) {

	int originIndex = -1, destinationIndex = -1;

	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if (vertexSet[i]->info == origin)
			originIndex = i;
		if (vertexSet[i]->info == dest)
			destinationIndex = i;

		if (originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if (W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if (P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex, destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}


template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if (P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2], index2, res);
	}
}

template<class T>
double Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if (vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for (unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if (vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new double *[vertexSet.size()];
	P = new double *[vertexSet.size()];
	for (unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new double[vertexSet.size()];
		P[i] = new double[vertexSet.size()];
		for (unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i, j);
			P[i][j] = -1;
		}
	}


	for (unsigned int k = 0; k < vertexSet.size(); k++)
		for (unsigned int i = 0; i < vertexSet.size(); i++)
			for (unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem convém considerar essa soma
				if (W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				double val = min(W[i][j], W[i][k] + W[k][j]);
				if (val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}

}

template<class T>
void Graph<T>::resetVisited()
{
	for (size_t k = 0; k < vertexSet.size(); k++)
		vertexSet[k]->visited = false;
}


template<class T>
void Graph<T>::findArt(Vertex<T> *v)
{
	v->visited = true;
	v->low = v->num = counter++;
	for (size_t i = 0; i < v->getAdjEdges().size(); i++) {
		Vertex<T> *w = v->getAdjEdges()[i].getDest();
		if (!w->visited) { // ramo da árvore
			w->parent_id = v->info;
			findArt(w);
			v->low = min(v->low, w->low);
			if (w->low >= v->num)
				std::cout << v->info << "- Ponto de articulacao" << std::endl;
		}
		else
			if (v->parent_id != w->info) //aresta de retorno
				v->low = min(v->low, w->num);
	}
}


#endif /* GRAPH_H_ */
