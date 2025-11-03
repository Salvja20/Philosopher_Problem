/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex fork1;  
std::mutex fork2;  


void philosopher(int id, std::mutex &left_fork, std::mutex &right_fork) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  

        std::cout << "Philosopher " << id << " is thinking...\n";
        
        
        std::lock(left_fork, right_fork);  
        std::lock_guard<std::mutex> guard_left(left_fork, std::adopt_lock);  
        std::lock_guard<std::mutex> guard_right(right_fork, std::adopt_lock); 

        std::cout << "Philosopher " << id << " is eating...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));  

        
        std::cout << "Philosopher " << id << " finished eating and put down both forks.\n";
    }
}

int main() {
    
    std::thread philosopher0(philosopher, 0, std::ref(fork1), std::ref(fork2));
    std::thread philosopher1(philosopher, 1, std::ref(fork2), std::ref(fork1));

    
    philosopher0.join();
    philosopher1.join();

    return 0;
}
