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

int trailblaze_power_left;
int trailblaze_power_maximum = 180;
int trailblaze_power_cooldown = 360;
int solution;
int answer;
int converter;

int main() {

    while (true) {

        std::cout << endl << "Trailblaze Power Left: ";
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

            // Display the updated current time
            //std::cout << "Updated current time: " << std::put_time(localTime, "%I:%M:%S %p") << std::endl;

            // Display the future time
            std::cout << endl << "Current time: " << std::put_time(futureLocalTime, "%I:%M:%S %p") << std::endl;
            
        }
        else {
            std::cout << "Invalid Way Above the 180" << endl;
            return 1;
        }
        

        std::cout << endl << "Would you like to continue? Yes or No?" << endl << endl;
        string choices;
        std::cin >> choices;

        if (choices == "yes" || choices == "Yes" || choices == "y") {
            std::cout << endl << "You wish to continue" << endl << endl;
        }
        else if (choices == "no" || choices == "No" || choices == "n") {
            std::cout << endl << "You wish to stopped" << endl << endl;
            break;
            return 1;
        }
        else {
            std::cout << endl << "[Error] Looks like you put something other than yes and no." << endl;
        }
    }
    return 0;
}
