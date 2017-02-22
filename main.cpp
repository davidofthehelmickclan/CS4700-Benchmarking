#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
#define INF INT_MAX //Infinity

const int sz = 10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly
vector<vector<pair<int, int> > > a; //Adjacency list
vector<int> dis; //Stores shortest distance
vector<bool> vis; //Determines whether the node has been visited or not
const int REPS = 1000;

void Dijkstra(int source, int n) //Algorithm for SSSP 
{
	for (int i = 0; i<n; i++) //Set initial distances to Infinity
		dis.push_back(INF);
	vis.resize(n, false);
	//Custom Comparator for Determining priority for priority queue (shortest edge comes first)
	class prioritize { public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2) { return p1.second>p2.second; } };
	priority_queue<pair<int, int>, vector<pair<int, int> >, prioritize> pq; //Priority queue to store vertex,weight pairs
	pq.push(make_pair(source, dis[source] = 0)); //Pushing the source with distance from itself as 0
	while (!pq.empty())
	{
		pair<int, int> curr = pq.top(); //Current vertex. The shortest distance for this has been found
		pq.pop();
		int cv = curr.first, cw = curr.second; //'cw' the final shortest distance for this vertex
		if (vis[cv]) //If the vertex is already visited, no point in exploring adjacent vertices
			continue;
		vis[cv] = true;
		for (int i = 0; i<a[cv].size(); i++) //Iterating through all adjacent vertices
			if (!vis[a[cv][i].first] && a[cv][i].second + cw<dis[a[cv][i].first]) //If this node is not visited and the current parent node distance+distance from there to this node is shorted than the initial distace set to this node, update it
				pq.push(make_pair(a[cv][i].first, (dis[a[cv][i].first] = a[cv][i].second + cw))); //Set the new distance and add to priority queue
	}
}

int main() //Driver Function for Dijkstra SSSP
{
	int n, m;//Number of vertices
	ifstream fin;
	fin.open("matrix.txt");
	cout<<"Enter number of vertices in the graph\n";
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; ++i) //Building Graph
	{
		for (int k = 0; k < n; ++k)
		{
			fin >> m; //weight of edge
			if (m != 0)
				a[i].push_back(make_pair(k, m));
		}
	}
	fin.close();
	cout<<"Enter source for Dijkstra's SSSP algorithm\n";
	int source;
	cin >> source;
	vector<std::chrono::microseconds> time;
	for (int i = 0; i < REPS; ++i)
	{
		dis.clear();
		vis.clear();
		auto start = std::chrono::steady_clock::now();
		Dijkstra(source, n);//SSSP from source (Also passing number of vertices as parameter)
		auto end = std::chrono::steady_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		time.push_back(dur);
	}
	long long average = 0;
	for (int i = 0; i < REPS; ++i)
		average += time[i].count();
	average = average / REPS;
	cout << "Source is: " << source << ". The shortest distance to every other vertex from here is: \n";
	for (int i = 0; i < n; i++)//Printing final shortest distances from source
	{
		cout << "Vertex: " << i << " , Distance: ";
		dis[i] != INF ? cout << dis[i] << "\n" : cout << "-1\n";
	}
	cout << "Average time to find solution is " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl;
	return 0;
}