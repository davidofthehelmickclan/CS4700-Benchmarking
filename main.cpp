#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

const int REPS = 100;

int fib(int n)
{
	if (n <= 2)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}

int main()
{
	int total;
	int n;
	cin >> n;
	vector<std::chrono::microseconds> time;
	std::chrono::microseconds dur;
	for (int i = 0; i < REPS; ++i)
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
	cout << "Time to find number was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl;
	
	return 0;
}
