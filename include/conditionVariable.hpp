#include <iostream>
#include <atomic>
#include <condition_variable>
#include <mutex>

std::condition_variable cv;
std::atomic<bool> running(true);
std::mutex mtx;
void waitForEnter()
{
    std::unique_lock<std::mutex> lock(mtx);
    std::cin.get();
    running = false;
    cv.notify_all();
}