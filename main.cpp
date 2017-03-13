#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;

const int FREPS = 1000;

int fib(int n)
{
	if (n <= 2)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

int callFib()
{
	int total;
	int n;
	cout << "running Fibonacci, please input number" << endl;
	cin >> n;
	vector<std::chrono::microseconds> time;
	std::chrono::microseconds dur;
	for (int i = 0; i < FREPS; ++i)
	{
		auto start = std::chrono::steady_clock::now();
		total = fib(n);
		auto end = std::chrono::steady_clock::now();
		dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		time.push_back(dur);
	}
	long long average = 0;
	for (int i = 0; i < time.size(); ++i)
		average += time[i].count();
	average = average / time.size();
	cout << "Fibonacci number " << n << " is " << total << endl;
	cout << "Time to find number was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl << endl;

	return 0;
}

#define INF INT_MAX //Infinity

const int sz = 10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly
vector<vector<pair<int, int> > > a; //Adjacency list
vector<int> dis; //Stores shortest distance
vector<bool> vis; //Determines whether the node has been visited or not
const int DREPS = 1000;

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

int callDijkstra() //Driver Function for Dijkstra SSSP
{
	int n, m;//Number of vertices
	ifstream fin;
	cout << "Runing Dijkstra" << endl;
	fin.open("matrix.txt");
	cout << "Enter number of vertices in the graph\n";
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
	cout << "Enter source for Dijkstra's SSSP algorithm\n";
	int source;
	cin >> source;
	vector<std::chrono::microseconds> time;
	for (int i = 0; i < DREPS; ++i)
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
	for (int i = 0; i < DREPS; ++i)
		average += time[i].count();
	average = average / time.size();
	cout << "Source is: " << source << ". The shortest distance to every other vertex from here is: \n";
	for (int i = 0; i < n; i++)//Printing final shortest distances from source
	{
		cout << "Vertex: " << i << " , Distance: ";
		dis[i] != INF ? cout << dis[i] << "\n" : cout << "-1\n";
	}
	cout << "Average time to find solution is " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl << endl;
	return 0;
}

const int SREPS = 1000;

void Merge(vector<int>& A, int beg, int mid, int fin, vector<int>& B)
{
	int i = beg;
	int j = mid;
	for (int k = beg; k < fin; ++k)
	{
		if (i < mid && (j >= fin || A[i] <= A[j]))
		{
			B[k] = A[i];
			++i;
		}
		else
		{
			B[k] = A[j];
			++j;
		}
	}
}

void SplitMerge(vector<int>& B, int beg, int fin, vector<int>& A)
{
	if (fin - beg < 2)
		return;
	int mid = (beg + fin) / 2;
	SplitMerge(A, beg, mid, B);
	SplitMerge(A, mid, fin, B);
	Merge(B, beg, mid, fin, A);
}

int callMerge()
{
	int input;
	vector<int> base;
	ifstream fin;
	cout << "running MergeSort" << endl;
	fin.open("input.txt");
	while (fin >> input)
		base.push_back(input);
	fin.close();
	vector<int> sort;
	vector<int> work;
	vector<std::chrono::microseconds> time;
	for (int i = 0; i < SREPS; ++i)
	{
		sort = base;
		work = sort;
		auto start = std::chrono::steady_clock::now();
		SplitMerge(work, 0, sort.size(), sort);
		auto end = std::chrono::steady_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		time.push_back(dur);
	}
	for (int i = 0; i < sort.size(); ++i)
		cout << sort[i] << endl;
	long long average = 0;
	for (int i = 0; i < time.size(); ++i)
		average += time[i].count();
	average = average / time.size();
	cout << "Time to sort numbers was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl << endl;

	return 0;
}

int main()
{
	callFib();
	callDijkstra();
	callMerge();
}