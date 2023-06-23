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
using namespace std:: this_thread;
using namespace std:: chrono;

int trailblaze_power_left;
int trailblaze_power_maximum = 180;
int trailblaze_power_cooldown = 360;
int solution;
int answer;
int converter;

int main() {
    std::cout << "Trailblaze Power Left: ";
    std::cin >> trailblaze_power_left;

    if (trailblaze_power_left < 180) {
        solution = trailblaze_power_left - trailblaze_power_maximum;
        answer = solution * trailblaze_power_cooldown;

        int hours = std::abs(answer) / 3600; // Get the number of hours
        int minutes = (std::abs(answer) % 3600) / 60; // Get the number of minutes
        int seconds = (std::abs(answer) % 3600) % 60; // Get the number of seconds

        std::cout << endl << "Will take: "<< std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << endl;

        // Get the current time
        time_t currentTime;
        time(&currentTime);
        struct tm* localTime = localtime(&currentTime);

        // Calculate the remaining time
        int remainingSeconds = answer;
        remainingSeconds -= (localTime->tm_hour * 3600);
        remainingSeconds -= (localTime->tm_min * 60);
        remainingSeconds -= localTime->tm_sec;

        // Calculate the future time
        time_t futureTime = currentTime + remainingSeconds;
        struct tm* futureLocalTime = localtime(&futureTime);

        // Display the remaining time
        std::cout << endl << "Full in: " << std::setw(2) << std::setfill('0') << futureLocalTime->tm_hour << ":" << std::setw(2) << std::setfill('0') << futureLocalTime->tm_min << ":" << std::setw(2) << std::setfill('0') << futureLocalTime->tm_sec << endl;
        std::cout << endl << endl << "Program will close in 20sec" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(20));
    }
    else {
        std::cout << "Invalid Way Above the 180" << endl;
        return 1;
    }
    return 0;
}