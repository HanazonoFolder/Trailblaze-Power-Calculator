#include <iostream>
#include <string.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int main () {

    std::cout << "Welcome to HSR Trailblaze Power Calculator (TPC)" << std::endl;
    int selection;
    std::cout << "Please select your options:" << std::endl << "0. Calculate Trailblaze to be full!"
              << std::endl << "1. Target time, Trailblaze Power Spend!" << std::endl << "Select: ";
    std::cin >> selection;

    if (selection == 0) {

        int trailblaze_power_left;
        int trailblaze_power_maximum = 180;
        int trailblaze_power_cooldown = 360;
        int solution;
        int answer;

        std::cout << "Trailblaze Power Left: ";
        std::cin >> trailblaze_power_left;

    if (trailblaze_power_left < 180) {
        solution = trailblaze_power_maximum - trailblaze_power_left;
        answer = solution * trailblaze_power_cooldown;

        int hours = std::abs(answer) / 3600; // Get the number of hours
        int minutes = (std::abs(answer) % 3600) / 60; // Get the number of minutes
        int seconds = (std::abs(answer) % 3600) % 60; // Get the number of seconds

        std::cout << endl << "Will take: "<< std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << endl;
        
        // Get the current time
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        std::tm* localTime = std::localtime(&currentTime_t);

        
        // Calculate the future time
        auto futureTime = currentTime + std::chrono::seconds(answer);
        std::time_t futureTime_t = std::chrono::system_clock::to_time_t(futureTime);
        std::tm* futureLocalTime = std::localtime(&futureTime_t);

        // Display the current time
        std::cout << endl << "Full in: " << std::put_time(localTime, "%I:%M:%S %p") << std::endl;

        // Get the updated current time
        currentTime = std::chrono::system_clock::now();
        currentTime_t = std::chrono::system_clock::to_time_t(currentTime);
        localTime = std::localtime(&currentTime_t);

        // Display the future time
        std::cout << endl << "Current time: " << std::put_time(futureLocalTime, "%I:%M:%S %p") << std::endl;
        
    }
    else {
        std::cout << "Invalid Way Above the 180" << endl;
        return 1;
    }
    }
    if (selection == 1) {
    // Get current time
    std::time_t currentTime = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&currentTime);

    // Display current time in 12-hour format with AM/PM
    std::cout << endl << "Current time: ";
    std::cout << std::put_time(timeinfo, "%I:%M:%S ");

    // Determine AM/PM based on the current time
    if (timeinfo->tm_hour < 12) {
        std::cout << "AM";
    } else {
        std::cout << "PM";
    }

    std::cout << std::endl;

    // Get remaining trailblazer power
    int remainingPower;
    std::cout << endl << "Trailblaze Power Left: ";
    std::cin >> remainingPower;

    // Get target time
    std::cout << endl << "Enter target time (in 12-hour format with AM/PM): ";
    std::string targetTimeString;
    std::cin >> targetTimeString;

    std::tm targetTime = *timeinfo; // Initialize with current time
    std::istringstream iss(targetTimeString);
    iss >> std::get_time(&targetTime, "%I:%M %p");

    // Calculate time when power reaches 180
    int cooldownPeriod = 6; // Cooldown period in minutes
    int timeToFull = (180 - remainingPower) * cooldownPeriod;

    std::time_t fullTime = currentTime + timeToFull * 60;

    // Display time when power reaches 180
    std::cout << endl << "Full in: ";
    std::cout << std::put_time(std::localtime(&fullTime), "%I:%M:%S %p") << std::endl;

    // Calculate trailblaze power to spend
    std::time_t targetTimeInSeconds = std::mktime(&targetTime);
    std::time_t remainingTimeInSeconds = targetTimeInSeconds - currentTime;
    int remainingTimeMinutes = remainingTimeInSeconds / 60;

    int trailblazeToSpend = std::floor(remainingTimeMinutes / 6.0) - (180 - remainingPower);

    if (targetTimeInSeconds <= fullTime) {
        std::cout << endl << "No need to spend, target time is earlier or equal to the full power time." << std::endl;
    } else {
        std::cout << endl << "Trailblaze power to spend: " << trailblazeToSpend << std::endl;

        // Calculate the time when remaining trailblaze power reaches zero
        int timeToZeroPower = remainingPower / 6;
        std::time_t zeroPowerTime = currentTime + timeToZeroPower * 60;
        std::cout << endl << "Time when power reaches zero: ";
        std::cout << std::put_time(std::localtime(&zeroPowerTime), "%I:%M:%S %p") << std::endl;
    }
    
    }
    std::cout << endl << "Press any key to exit...";
    std::cin.ignore(); // Wait for user to press enter

    // Platform-specific command to wait for a key press
    #ifdef _WIN32
        system("pause");
    #elif __linux__
        system("read -n1 -r -p \"Press any key to exit...\" key");
    #endif

    return 0;
    
}