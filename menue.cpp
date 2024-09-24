#include "menue.hpp"

void Menue::runMenue()
{
	std::string choice = "d";

	while (choice != "6") {

		std::cout << std::endl << "MAIN MENUE:" << std::endl;
		std::cout << "1. Game Rules" << std::endl;
		std::cout << "2. Play Game" << std::endl;
		std::cout << "3. Load Previous Game" << std::endl;
		std::cout << "4. Add Command" << std::endl;
		std::cout << "5. Remove Command" << std::endl;
		std::cout << "6. Exit/Save" << std::endl;
		std::cout << std::endl << "Enter Choice:";

		std::cin >> choice;
		handleMenueOption(choice);
	}
}

void Menue::handleMenueOption(std::string choice) {

	if (choice == "1") {
		std::cout << "You'll be presented with a Linux command and several descriptions. Enter the number of the description you think matches the command." << std::endl;
	}
	else if (choice == "2") {
		game->runGame();
	}
	else if (choice == "3") {
		game->loadGame();
	}
	else if (choice == "4") {
		game->addCommand();
	}
	else if (choice == "5") {
		game->removeCommand();
	}
	else if (choice == "6") {
		std::cout << "Exiting!";
		game->exitAndUpdate();
	}
	else {
		std::cout << "That wasn't a choice! Try again!" << std::endl;
	}

}