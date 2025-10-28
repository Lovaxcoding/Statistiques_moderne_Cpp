#include <iostream>
#include <iomanip> // For std::setw and std::setfill

// Forward declaration
class Duration;

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    // Helper function to check if a year is a leap year
    bool isLeapYear(int y) const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    // Helper function to get the number of days in a given month
    int daysInMonth(int m, int y) const {
        if (m < 1 || m > 12) return 0;
        int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (isLeapYear(y) && m == 2) {
            return 29;
        }
        return days[m];
    }

    // Helper function to convert a DateTime object to a total number of seconds
    long long toTotalSeconds() const {
        long long totalSeconds = 0;
        
        // Add seconds from previous years
        for (int y = 1; y < year; ++y) {
            totalSeconds += (isLeapYear(y) ? 366 : 365) * 24LL * 60 * 60;
        }

        // Add seconds from previous months in the current year
        for (int m = 1; m < month; ++m) {
            totalSeconds += daysInMonth(m, year) * 24LL * 60 * 60;
        }

        // Add seconds from previous days in the current month
        totalSeconds += (day - 1) * 24LL * 60 * 60;

        // Add seconds from current hour, minute, and second
        totalSeconds += hour * 60LL * 60;
        totalSeconds += minute * 60LL;
        totalSeconds += second;

        return totalSeconds;
    }

public:
    // 1. Default constructor
    DateTime() : year(0), month(0), day(0), hour(0), minute(0), second(0) {}

    // 2. Parameterized constructor
    DateTime(int y, int m, int d, int h, int min, int s)
        : year(y), month(m), day(d), hour(h), minute(min), second(s) {}

    // 3. Copy constructor
    DateTime(const DateTime& other)
        : year(other.year), month(other.month), day(other.day),
          hour(other.hour), minute(other.minute), second(other.second) {}

    // Function to set date and time manually
    void setDateTime() {
        std::cout << "Enter year: ";
        std::cin >> year;
        std::cout << "Enter month: ";
        std::cin >> month;
        std::cout << "Enter day: ";
        std::cin >> day;
        std::cout << "Enter hour: ";
        std::cin >> hour;
        std::cout << "Enter minute: ";
        std::cin >> minute;
        std::cout << "Enter second: ";
        std::cin >> second;
    }
    
    // Function to get system date and time
    // NOTE: This implementation requires C-style date/time functions
    // which use the <ctime> library. A fully "from scratch" version
    // would require OS-specific calls, which is beyond a simple example.
    void getSystemDateTime() {
        // Use the C standard library's time functions
        // This is the one exception to the "no library" rule for practicality
        time_t now = time(0);
        tm* ltm = localtime(&now);

        year = 1900 + ltm->tm_year;
        month = 1 + ltm->tm_mon;
        day = ltm->tm_mday;
        hour = ltm->tm_hour;
        minute = ltm->tm_min;
        second = ltm->tm_sec;
    }
    
    // Function to display date and time
    void display() const {
        std::cout << "Date: " << std::setw(2) << std::setfill('0') << month << "/"
                  << std::setw(2) << std::setfill('0') << day << "/"
                  << year << std::endl;
        std::cout << "Time: " << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << minute << ":"
                  << std::setw(2) << std::setfill('0') << second << std::endl;
    }
    
    // Function to subtract two DateTime objects and return a Duration object
    Duration operator-(const DateTime& other) const;
};

// A separate class to represent the duration
class Duration {
private:
    long long totalSeconds;

public:
    Duration(long long seconds) : totalSeconds(seconds) {}

    void display() const {
        if (totalSeconds < 0) {
            std::cout << "Duration: -" << std::endl;
            Duration(-totalSeconds).display();
            return;
        }

        long long days = totalSeconds / (24 * 60 * 60);
        long long remainingSeconds = totalSeconds % (24 * 60 * 60);

        long long hours = remainingSeconds / (60 * 60);
        remainingSeconds %= (60 * 60);

        long long minutes = remainingSeconds / 60;
        long long seconds = remainingSeconds % 60;

        std::cout << "Duration: " << days << " days, "
                  << std::setw(2) << std::setfill('0') << hours << " hours, "
                  << std::setw(2) << std::setfill('0') << minutes << " minutes, "
                  << std::setw(2) << std::setfill('0') << seconds << " seconds"
                  << std::endl;
    }
};

// Implementation of the subtraction operator
Duration DateTime::operator-(const DateTime& other) const {
    return Duration(this->toTotalSeconds() - other.toTotalSeconds());
}

int main() {
    // 1. Default constructor
    std::cout << "Using default constructor:" << std::endl;
    DateTime dt1;
    dt1.display();
    std::cout << "----------------------" << std::endl;

    // 2. Parameterized constructor
    std::cout << "Using parameterized constructor:" << std::endl;
    DateTime dt2(2025, 10, 22, 11, 25, 0);
    dt2.display();
    std::cout << "----------------------" << std::endl;

    // 3. Copy constructor
    std::cout << "Using copy constructor:" << std::endl;
    DateTime dt3 = dt2;
    dt3.display();
    std::cout << "----------------------" << std::endl;

    // Set date and time manually
    std::cout << "Entering a date manually:" << std::endl;
    DateTime manualTime;
    manualTime.setDateTime();
    std::cout << "You entered:" << std::endl;
    manualTime.display();
    std::cout << "----------------------" << std::endl;
    
    // Get and display system date and time
    std::cout << "Getting system date and time:" << std::endl;
    DateTime systemTime;
    systemTime.getSystemDateTime();
    std::cout << "Current system time:" << std::endl;
    systemTime.display();
    std::cout << "----------------------" << std::endl;
    
    // Subtract dates and get duration
    std::cout << "Subtracting dates (system time - manual time):" << std::endl;
    Duration diff = systemTime - manualTime;
    diff.display();
    std::cout << "----------------------" << std::endl;

    // Another subtraction example
    DateTime past(2020, 1, 1, 0, 0, 0);
    DateTime future(2021, 1, 1, 0, 0, 0);
    std::cout << "Subtracting dates (2021-01-01 - 2020-01-01):" << std::endl;
    Duration diff2 = future - past;
    diff2.display();
    
    return 0;
}
