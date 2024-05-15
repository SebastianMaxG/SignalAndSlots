// Project1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Signal.h"
#include <string>

class MyClass
{
public:
	void RecieveSignal(std::string message)
	{
		std::cout << "Received class message: " << message << std::endl;
	}

private:

};

class SignalClass
{
public:
	void operator()(std::string message)
	{
		std::cout << "Received functionclass message: " << message << std::endl;
	}
};

class Blob
{
public:
	void RecieveSignal(std::string message)
	{
		std::cout << "Blob is hungry" << message << std::endl;
	}

	void RecieveSignal2(int number, bool isTrue)
	{
		if (isTrue)
			std::cout << "Blob is hungry" << number << " " << isTrue << std::endl;
		else
			std::cout << "Blob is not hungry" << number << " " << isTrue << std::endl;
	}

private:

};

std::jthread Signal1Thread;
std::jthread Signal2Thread;

dae::signal:: Signal<std::string> signal{Signal1Thread};
dae::signal:: Signal<int, bool> signal2{Signal2Thread};



void RecieveSignal(std::string message)
{
	std::cout << "Received message: " << message << std::endl;
}
void ReceiveSignal2(std::string message)
{
	std::cout << "Received message2: " << message << std::endl;
}

void RecieveSignal3(int number, bool isTrue)
{
	if (isTrue)
		std::cout << "Received message: " << number << " " << isTrue << std::endl;
	else
		std::cout << "Received message: " << number << " " << isTrue << std::endl;
}



MyClass myClass{};

int main()
{
	Blob blob{};

	auto c1 = signal.Connect(RecieveSignal);
	auto c2 = signal.Connect(ReceiveSignal2);
	signal.Connect(SignalClass{});
	{
		MyClass myClass{};
		auto c3 = signal.Connect<MyClass>(&myClass, &MyClass::RecieveSignal);
		signal.Emit(std::string("Hello World"));
		c1->Disconnect();
	}
		signal.Emit(std::string("Hello World 2"));

	auto c4 = signal2.Connect(RecieveSignal3);
	auto c5 = signal2.Connect<Blob>(&blob, &Blob::RecieveSignal2);

	signal2.Emit(5, true);

	signal2.Emit(10, false);

	for (int i = 0; i < 50; i+=5)
	{
		if (i == 10)
			c4->Pause();
		if (i == 20)
			c4->Resume();
		signal2.Emit(i, true);
	}

	//wait a bit
	std::this_thread::sleep_for(std::chrono::seconds(1));

	signal.End();
	Signal1Thread.join();
	signal2.End();
	Signal2Thread.join();
    //std::cout << "Hello World!\n";
}


int retMax(int n1, int n2)
{
    return (n1 > n2) ? n1 : n2;
}
//
//int main()
//{
//    //declare two function pointers
//    int (*ptrMaxFunctin)(int, int);
//    int (*ptrMaxFunctin2)(int, int);
//
//    //assign function address to pointer
//    ptrMaxFunctin = retMax;
//
//    // assign NULL to function pointer
//    ptrMaxFunctin2 = NULL;
//
//    if (ptrMaxFunctin2 == NULL)
//    {
//        printf("ptrMaxFunctin2 has not been assigned yet.\n");
//    }
//
//    if (ptrMaxFunctin2 != ptrMaxFunctin)
//    {
//        printf("ptrMaxFunctin2 and ptrMaxFunctin do not point to the same function.\n");
//    }
//    else
//    {
//        printf("ptrMaxFunctin2 and ptrMaxFunctin point to the same function.\n");
//    }
//
//    ptrMaxFunctin2 = retMax;
//
//    if (ptrMaxFunctin2 == ptrMaxFunctin)
//    {
//        printf("ptrMaxFunctin2 and ptrMaxFunctin point to the same function.\n");
//    }
//    else
//    {
//        printf("ptrMaxFunctin2 and ptrMaxFunctin do not point to the same function.\n");
//    }
//
//    int qty1 = 20, qty2 = 50;
//
//    printf("Max of %d and %d is : %d \n", qty1, qty2, (*ptrMaxFunctin)(qty1, qty2));
//    return 0;
//}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
