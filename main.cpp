#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

const int REPS = 1000;

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

int main()
{
	int input;
	vector<int> base;
	ifstream fin;
	fin.open("input.txt");
	while (fin >> input)
		base.push_back(input);
	fin.close();
	vector<int> sort;
	vector<int> work;
	vector<std::chrono::microseconds> time;
	for (int i = 0; i < REPS; ++i)
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
	cout << "Time to sort numbers was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl;
}