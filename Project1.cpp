#include "Signal.h"
#include <iostream>

// A class with a member function that can be connected to a signal
class MyClass {
public:
    void MyMemberFunction(int value) {
        std::cout << "MyClass::MyMemberFunction was called with value: " << value << std::endl;
    }
};

// A free function that can be connected to a signal
void MyFreeFunction(int value) {
    std::cout << "MyFreeFunction was called with value: " << value << std::endl;
}

// Another free function that can be connected to a signal
void MyOtherFreeFunction(int value) {
    std::cout << "MyOtherFreeFunction was called with value: " << value << std::endl;
}

// Single Threaded Example
void SingleThreadedExample()
{
    std::cout << "Single Threaded Example" << std::endl;
    // Create a signal
    lsmf::signal::Signal<int> signal;

    // Create an object of MyClass
    MyClass myObject;

    // Connect the member function to the signal
    auto connection1 = signal.Connect(&myObject, &MyClass::MyMemberFunction);

    // Connect the free function to the signal
    auto connection2 = signal.Connect(MyFreeFunction);

    // Emit the signal
    signal.Emit(10);
    signal.Update();

    // Disconnect the first connection
    connection1->Disconnect();

    // Connect another free function to the signal
    auto connection3 = signal.Connect(MyOtherFreeFunction);

    // Connect a lambda function to the signal
    auto connection4 = signal.Connect([](int value)
        {
            std::cout << "Lambda function was called with value: " << value << std::endl;
        });

    // Emit the signal again
    signal.Emit(20);
    signal.Update();

    // Disconnect all connections
    signal.DisconnectAll();

    // Emit the signal again
    signal.Emit(30);
    signal.Update();

    std::cout << "Single Threaded Ended" << std::endl;
}

// Multi Threaded Example
void MultiThreadedExample()
{
    std::cout << "Multi Threaded Example" << std::endl;

    // Create a jthread
    std::jthread signalThread;

    // Create a signal in the jthread
    lsmf::signal::Signal<int> signal(signalThread);

    // Create an object of MyClass
    MyClass myObject;

    // Connect the member function to the signal
    auto connection1 = signal.Connect(&myObject, &MyClass::MyMemberFunction);

    // Connect the free function to the signal
    auto connection2 = signal.Connect(MyFreeFunction);

    // Emit the signal
    for (int i = 0; i < 10; ++i) {
        signal.Emit(i);
        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Wait for a while to let the signal thread process the emitted values
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Disconnect the first connection
    connection1->Disconnect();

    // Emit the signal again
    signal.Emit(10);

    // Wait for a while to let the signal thread process the emitted value
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Disconnect the second connection
    connection2->Disconnect();

    // End the signal thread
    signal.End();

    std::cout << "Multi Threaded Ended" << std::endl;
}

int main()
{
    SingleThreadedExample();
    MultiThreadedExample();

    return 0;
}