#include <iostream>
#include <conio.h>
#include <Windows.h>

volatile long countIterations = 0;
volatile long factorialIterations = 0;
volatile long fibonacciIterations = 0;

HANDLE countThread;
HANDLE factorialThread;
HANDLE fibonacciThread;
HANDLE nagruzThread;

DWORD WINAPI Increment(LPVOID iNum)
{
	int count = 0;
	while (true)
	{
		count++;
		countIterations++;

	};
}
DWORD WINAPI Factorial(LPVOID iNum)
{
	int number = (rand() % 5) + 1;
	int result = 1;

	while (true)
	{

		do
		{
			result *= number;
			number--;

		} while (number > 0);

		number = rand() % 5;

		factorialIterations++;

	};
}
DWORD WINAPI Fibonacci(LPVOID iNum)
{
	int prev = 0;
	int next = 1;
	int res = 0;

	while (true)
	{

		res = prev + next;
		prev = next;
		next = res;

		fibonacciIterations++;

	};
}

DWORD WINAPI Nagruzchik(LPVOID iNum)
{
	while (true)
	{

	}
}

DWORD WINAPI Print(LPVOID iNum)
{
	while (true)
	{
		system("cls");
		std::cout << "counter ID: " << GetThreadId(countThread) << " iterations: " << countIterations << " priority: " << GetThreadPriority(countThread) << std::endl;
		std::cout << "fibonaci ID: " << GetThreadId(factorialThread) << " iterations: " << factorialIterations << " priority: " << GetThreadPriority(factorialThread) << std::endl;
		std::cout << "factorial ID: " << GetThreadId(fibonacciThread) << " iterations: " << fibonacciIterations << " priority: " << GetThreadPriority(fibonacciThread) << std::endl;
		std::cout << "Nagruzchik priority = " << GetThreadPriority(nagruzThread) << std::endl;
		std::cout << "1 - set counter priority to 2" << std::endl
			<< "2 - set fibonacci priority to 2" << std::endl
			<< "3 - set factorial priority to 2" << std::endl
			<< "t - nagruzit" << std::endl;
		Sleep(1000);
	}
}

int main()
{

	HANDLE currentProcess = GetCurrentProcess();

	HANDLE duplicatedProcess;

	DuplicateHandle(currentProcess, currentProcess, currentProcess, &duplicatedProcess, 0, FALSE, DUPLICATE_SAME_ACCESS);

	SetPriorityClass(duplicatedProcess, NORMAL_PRIORITY_CLASS);

	std::cout << GetPriorityClass(duplicatedProcess);

	srand(time(NULL));

	DWORD idThread1;

	countThread = CreateThread(NULL, 0, Increment, NULL, 0, &idThread1);

	SetThreadPriority(countThread, THREAD_PRIORITY_LOWEST);

	DWORD idThread2;

	factorialThread = CreateThread(NULL, 0, Factorial, NULL, 0, &idThread2);

	SetThreadPriority(factorialThread, THREAD_PRIORITY_BELOW_NORMAL);

	DWORD idThread3;

	fibonacciThread = CreateThread(NULL, 0, Fibonacci, NULL, 0, &idThread3);

	SetThreadPriority(fibonacciThread, THREAD_PRIORITY_ABOVE_NORMAL);

	DWORD idThread;

	nagruzThread = CreateThread(NULL, 0, Nagruzchik, NULL, 0, &idThread);

	SetThreadPriority(nagruzThread, THREAD_PRIORITY_NORMAL);

	DWORD idThreadPrint;

	HANDLE printer = CreateThread(NULL, 0, Print, NULL, 0, &idThreadPrint);

	char selection = 'a';

	do
	{

		selection = _getch();

		switch (selection)
		{
			case '1':
			{
				SetThreadPriority(countThread, THREAD_PRIORITY_HIGHEST);
				break;
			}
			case '2':
			{
				SetThreadPriority(factorialThread, THREAD_PRIORITY_HIGHEST);
				break;
			}
			case '3':
			{
				SetThreadPriority(fibonacciThread, THREAD_PRIORITY_HIGHEST);
				break;
			}
			case 't':
			{
				SetThreadPriority(countThread, THREAD_PRIORITY_IDLE);
				SetThreadPriority(factorialThread, THREAD_PRIORITY_IDLE);
				SetThreadPriority(fibonacciThread, THREAD_PRIORITY_IDLE);

				SetThreadPriority(nagruzThread, THREAD_PRIORITY_TIME_CRITICAL);
				Sleep(3000);

				SetThreadPriority(countThread, THREAD_PRIORITY_LOWEST);
				SetThreadPriority(factorialThread, THREAD_PRIORITY_BELOW_NORMAL);
				SetThreadPriority(fibonacciThread, THREAD_PRIORITY_ABOVE_NORMAL);

				SetThreadPriority(nagruzThread, THREAD_PRIORITY_NORMAL);
				break;
			}
		}

	} while (selection != 'e');

	CloseHandle(countThread);
	CloseHandle(factorialThread);
	CloseHandle(fibonacciThread);
	CloseHandle(nagruzThread);
	CloseHandle(printer);
	CloseHandle(duplicatedProcess);

	return 0;
}