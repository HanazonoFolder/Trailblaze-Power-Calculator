#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>

int main() {
    // Get the current time
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    // Get the current hour and minute
    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;

    // Convert to 12-hour format
    int hour12 = (currentHour > 12) ? (currentHour - 12) : currentHour;
    std::string period = (currentHour >= 12) ? "PM" : "AM";

    // Display the current time
    std::cout << "Current time: " << std::setfill('0') << std::setw(2) << hour12 << ":"
              << std::setfill('0') << std::setw(2) << currentMinute << " " << period << std::endl;

    // Get the remaining Trailblaze power
    int trailblazePower;
    std::cout << "Enter the remaining Trailblaze power: ";
    std::cin >> trailblazePower;

    // Get the target time
    int targetHour, targetMinute;
    std::cout << "Enter the target time (hour minute, 12-hour format): ";
    std::cin >> targetHour >> targetMinute;

    // Convert the target time to 24-hour format
    if (period == "PM") {
        targetHour += 12;
    } else if (hour12 == 12) {
        targetHour = 0;
    }

    // Calculate the time when Trailblaze power will be full
    int minutesToFull = (180 - trailblazePower) * 6;
    int timeDiff = (targetHour * 60 + targetMinute) - (currentHour * 60 + currentMinute);

    if (timeDiff < minutesToFull) {
        int fullMinutes = (currentMinute + minutesToFull) % 60;
        int fullHour = (hour12 + (currentMinute + minutesToFull) / 60) % 12;
        std::string fullPeriod = (currentHour + (currentMinute + minutesToFull) / 60) < 12 ? "PM" : "AM";

        if (fullHour == 0) {
            fullHour = 12;
        }

        std::cout << "Trailblaze power will not be full by the target time." << std::endl;
        std::cout << "It should be full at: " << std::setfill('0') << std::setw(2) << fullHour << ":"
                  << std::setfill('0') << std::setw(2) << fullMinutes << " " << fullPeriod << std::endl;

        // Calculate the Trailblaze power needed to reach the target time
        // int trailblazeNeeded = std::max(0, static_cast<int>(std::ceil(static_cast<double>(minutesToFull - timeDiff) / 6)));

        if (timeDiff <= 0) { //Im hoping someone will able to fix this, i almost lost my mind in here
            std::cout << "There's no need to spend, it's already full." << std::endl;
        }


    } else {
        int trailblazeToSpend = (timeDiff - minutesToFull) / 6;

        std::cout << "You currently have " << trailblazePower << " Trailblaze power." << std::endl;
        std::cout << "To reach 180 Trailblaze power by " << std::setfill('0') << std::setw(2) << targetHour << ":"
                  << std::setfill('0') << std::setw(2) << targetMinute << " ";

        // Display the appropriate period for the target time based on the computer clock
        std::string targetPeriod = (currentHour + (timeDiff - minutesToFull) / 60) >= 12 ? "PM" : "AM";
        std::cout << targetPeriod;

        std::cout << ", you need to spend " << trailblazeToSpend << " Trailblaze power." << std::endl;
    }

    return 0;
}
