#include "bigInt.h"
#include <chrono>
using namespace std;

const int REPS = 100;

//BigInt::Rossi fib(int n)
//{
//	if (n <= 2)
//		return BigInt::Rossi(1);
//	else
//		return fib(n - 1) + fib(n - 2);
//}
//
//int main()
//{
//	BigInt::Rossi total;
//	int n;
//	cin >> n;
//	vector<std::chrono::microseconds> time;
//	std::chrono::microseconds dur;
//	for (int i = 0; i < REPS; ++i)
//	{
//		auto start = std::chrono::steady_clock::now();
//		total = fib(n);
//		auto end = std::chrono::steady_clock::now();
//		dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//		time.push_back(dur);
//	}
//	long long average = 0;
//	for (int i = 0; i < time.size(); ++i)
//		average += time[i].count();
//	average = average / time.size();
//	cout << "Fibonacci number " << n << " is " << total.toStrDec() << endl;
//	cout << "Time to find number was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl;
//	
//	return 0;
//}

int main()
{
	BigInt::Rossi base(1);
	BigInt::Rossi fib1(1);
	BigInt::Rossi fib2(1);
	BigInt::Rossi temp;
	int n;
	cin >> n;
	vector<std::chrono::microseconds> time;
	std::chrono::microseconds dur;
	for (int i = 0; i < REPS; ++i)
	{
		fib1 = base;
		fib2 = base;
		auto start = std::chrono::steady_clock::now();
		for (int i = 2; i < n; ++i)
		{
			temp = fib2;
			fib2 = fib1 + fib2;
			fib1 = temp;
		}
		auto end = std::chrono::steady_clock::now();
		dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		time.push_back(dur);
	}
	long long average = 0;
	for (int i = 0; i < time.size(); ++i)
		average += time[i].count();
	average = average / time.size();
	cout << "Fibonacci number " << n << " is " << fib2.toStrDec() << endl;
	cout << "Time to find number was " << average / 1000000 << " seconds " << (average / 1000) % 1000 << " milliseconds " << average % 1000 << " microseconds" << endl;

	return 0;
}