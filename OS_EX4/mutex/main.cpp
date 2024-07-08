#include <iostream>
#include <thread>
#include " MutexImpl.hpp"
#include "Guard.hpp"

// Shared resource
int sharedCounter = 0;

/**
 * @brief Function to be executed by multiple threads. Increments the shared counter.
 */
void incrementCounter() {
    MutexBase& mutex = MutexImpl::getInstance();
    Guard guard(mutex); // Lock the mutex for the scope of this function

    // Critical section: safe access to the shared resource
    for (int i = 0; i < 1000; ++i) {
        ++sharedCounter;
    }

    // Mutex is automatically unlocked when guard goes out of scope
}

int main() {
    // Create multiple threads
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);
    std::thread t3(incrementCounter);

    // Wait for all threads to complete
    t1.join();
    t2.join();
    t3.join();

    // Print the result
    std::cout << "Final counter value: " << sharedCounter << std::endl;

    return 0;
}
