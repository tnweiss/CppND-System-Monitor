#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long totalSeconds) { 
    long hours = totalSeconds/3600;
    long minutes = (totalSeconds % 3600)/60;
    long seconds = totalSeconds % 60;
    
    string hours_str = hours > 9 ? std::to_string(hours) : "0" + std::to_string(hours);
    string minutes_str = minutes > 9 ? std::to_string(minutes) : "0" + std::to_string(minutes);
    string seconds_str = seconds > 9 ? std::to_string(seconds) : "0" + std::to_string(seconds);

    return hours_str + ":" + minutes_str + ":" + seconds_str; 
}