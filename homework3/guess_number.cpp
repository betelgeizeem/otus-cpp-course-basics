#include "scores_table.h"

#include <iostream>
#include <string>
#include <ctime>


auto const max_value_default = 100;
auto verbose = false;

bool play(int max_value, std::size_t& res_attempts)
{
    std::srand(std::time(nullptr));
    auto my_number = std::rand() % max_value;

    if (verbose)
        std::cout << "D my_number " << my_number << std::endl;

    auto guess = -1;
    auto attempts = 0;

    while (guess != my_number)
    {
        attempts++;

        std::cout << "Enter your guess:" << std::endl;
        std::cin >> guess;

        if (std::cin.fail()) 
        {
		    std::cout << "Bad value!" << std::endl;
		    return false;
	    }
           
        if (guess > my_number)
            std::cout << "less than " << guess << std::endl;
        else 
            std::cout << "greater than " << guess << std::endl;
    }

    std::cout << "You win! Number of attempts: " << attempts << std::endl;

    res_attempts = attempts;
    return true;
}

int main(int argc, char** argv) 
{
    auto max_value = max_value_default;
    Scores_table table; 
    
    // parsing args
	for (auto argn = 1; argn < argc; argn++)
    {
		std::string arg {argv[argn]};
        if (arg == "-table")
            return table.show();
 		if (arg == "-max") 
            max_value = ++argn < argc ? std::stoi(argv[argn]) : max_value;
        if (arg == "-d")
            verbose = true;
	}

    // use -d for testing
    if (verbose)
        std::cout << "D max_value " << max_value << std::endl;

    if (max_value < 1)
    {
        std::cout << "Too small max value, using default: " << max_value_default << std::endl;
        max_value = max_value_default;
    }
    
    // intro words
    std::cout << "Hi! Enter your name, please: ";
    std::string name;
    std::cin >> name;
    std::cout << "Hi, " << name << "! Guess my number from 0 to " << max_value << "!" << std::endl; 
    
    // the game
    std::size_t attempts = 0;
    auto win = play(max_value, attempts);

    // write results to file
    if (win)
        return table.add(name, attempts);

	return 0;
}