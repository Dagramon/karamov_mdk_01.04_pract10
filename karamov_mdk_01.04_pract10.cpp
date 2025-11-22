#include <iostream>
#include <conio.h>
#include <Windows.h>

DWORD WINAPI Increment(LPVOID iNum)
{
	int iterations = 0;
	int count = 0;
	while (true)
	{
		count++;
		iterations++;

		std::cout << std::endl << "ID = " << GetCurrentThreadId() << " Count iterations = " << iterations << " Priority = " << GetThreadPriority(GetCurrentThread()) << std::endl;

		Sleep(1000);
	};
}
DWORD WINAPI Factorial(LPVOID iNum)
{

	int iterations = 0;
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

		iterations++;

		std::cout << std::endl << "ID = " << GetCurrentThreadId() << " Factorial iterations = " << iterations << " Priority = " << GetThreadPriority(GetCurrentThread()) << std::endl;

		Sleep(1000);
	};
}
DWORD WINAPI Fibonacci(LPVOID iNum)
{
	int iterations = 0;
	int prev = 0;
	int next = 1;
	int res = 0;

	while (true)
	{

		res = prev + next;
		prev = next;
		next = res;

		iterations++;

		std::cout << std::endl << "ID = " << GetCurrentThreadId() << " Fibonacci iterations = " << iterations << " Priority = " << GetThreadPriority(GetCurrentThread()) << std::endl;

		Sleep(1000);
	};
}

DWORD WINAPI Nagruzchik(LPVOID iNum)
{
	while (true)
	{
		std::cout << "Nagruzchik priority = " << GetThreadPriority(GetCurrentThread()) << std::endl;
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

	HANDLE countThread = CreateThread(NULL, 0, Increment, NULL, 0, &idThread1);

	SetThreadPriority(countThread, THREAD_PRIORITY_LOWEST);

	DWORD idThread2;

	HANDLE factorialThread = CreateThread(NULL, 0, Factorial, NULL, 0, &idThread2);

	SetThreadPriority(factorialThread, THREAD_PRIORITY_BELOW_NORMAL);

	DWORD idThread3;

	HANDLE fibonacciThread = CreateThread(NULL, 0, Fibonacci, NULL, 0, &idThread3);

	SetThreadPriority(fibonacciThread, THREAD_PRIORITY_ABOVE_NORMAL);

	DWORD idThread;

	HANDLE nagruzThread = CreateThread(NULL, 0, Nagruzchik, NULL, 0, &idThread);

	SetThreadPriority(nagruzThread, THREAD_PRIORITY_NORMAL);

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
	CloseHandle(duplicatedProcess);

	return 0;
}