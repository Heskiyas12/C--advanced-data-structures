#include "game.hpp"
#include <string>

Game::Game() {
	commandList->loadCsv("commands.csv");
}

void Game::addCommand() {

	std::string inCommand, inDescription;

	std::cout << std::endl << "Enter command you want to add:";
	std::cin >> inCommand;
	std::cin.ignore(256, '\n');  //get rid of the newline at end of input, (getline is space delimited and leaves it in cin)

	std::cout << std::endl << "Enter command description:";
	std::getline(std::cin, inDescription);

	commandList->insert(inCommand, "\"" + inDescription + "\"");

	std::cout << std::endl;
	commandList->printList();

	std::cout << std::endl << "Added the command to the list!" << std::endl << std::endl;
};

void Game::removeCommand() {

	//commandList->loadCsv("commands.csv");
	commandList->printList();

	std::string rmCommand;

	std::cout << std::endl << "Enter command to remove from choice list:";
	std::cin >> rmCommand;

	commandList->deleteNode(rmCommand);
	commandList->printList();
	std::cout << std::endl << "Removed the command if it was in the list!" << std::endl;

};

void Game::runGame() {

	//commandList->loadCsv("commands.csv");
	//commandList->printList();  //this is for testing only: The linkedList works!

	std::cout << std::endl << "Confirm username choice:";
	std::cin >> username;

	int numQuestions = 0;
	std::cout << "How many questions do you want to answer? Choose a number between 5 and 30:";
	std::cin >> numQuestions;

	if (numQuestions >= 5 && numQuestions <= 30) {

		LinkedList<std::string>* questionList = new LinkedList<std::string>;

		for (int i = 0; i < numQuestions; i++) {

			ListNode<std::string>* randNode = commandList->getRandNode();  //grab a random node from our command list. Make a new node in question list with same values.
				
			questionList->insert(randNode->getCommand() , randNode->getDescription());

		}//Boom now we have a linked list of just the questions we're gonnna ask from the original list. 

		//questionList->printList();          //another test: the grabbed list is the right size!

		//Traverse list. For each node, grab 3 random nodes and throw up their descriptions alongside the current node's question. Have em guess. Update score. Bingo. 

		ListNode<std::string>* traverser = questionList->getHead();    //      ;)
		
		for (int i = 0; i < numQuestions; i++) {

			std::string command = traverser->getCommand();
			std::string description = traverser->getDescription();
			std::string description2 = commandList->getRandNode()->getDescription();
			std::string description3 = commandList->getRandNode()->getDescription();
		
			std::cout << std::endl << "Now match the command: \"" << command << "\" to the correct description:" << std::endl;

			int range = 3 - 1 + 1;                //gen 1-3 inclusive number
			int answerPos = rand() % range + 1;

			if (answerPos == 1) {
				std::cout << "1: " << description << std::endl;
				std::cout << "2: " << description2 << std::endl;
				std::cout << "3: " << description3 << std::endl;
			}
			else if (answerPos == 2) {
				std::cout << "1: " << description2 << std::endl;
				std::cout << "2: " << description << std::endl;
				std::cout << "3: " << description3 << std::endl;
			}
			else if (answerPos == 3) {
				std::cout << "1: " << description2 << std::endl;
				std::cout << "2: " << description3 << std::endl;
				std::cout << "3: " << description << std::endl;
			}
			else {
				std::cout << "ERROR: answerPos not in range";
			}

			int guessDescription = 0;
			std::cout << std::endl << "Enter your match choice:";
			std::cin >> guessDescription;

			if (guessDescription == answerPos) {

				score++;
				std::cout << std::endl << "CORRECT! Score is now: " << score;
			}
			else {
				score--;
				std::cout << std::endl << "INCORRECT! Score is now: " << score;
			}

			traverser = traverser->getNextPtr();
			if (traverser == nullptr) {
				//std::cout << "null traverse";
			}
		}
		std::cout << std::endl << "Final score: " << score << std::endl;
		//score = 0;//game is over! Back to homescreen.
	}
	else {
		std::cout << std::endl << "That wasn't an accepted number!" << std::endl;
	}

	
	//ask how many 5-30 questions to ask
	//cycle questions randomly, uniquely, with random answer lists
	//keep score

};

void Game::loadGame() {

	std::ifstream usersFile;
	usersFile.open(usersFilePath);

	std::string currentLineUserName, currentLineUserScore, usernameChoice, usersFileLineHolder;

	std::cout << "Please type your username:";
	std::cin >> usernameChoice;

	//update score based on choice
	if (usersFile.is_open()) {

		while (currentLineUserName != usernameChoice && usersFile.good()) {  //while not at end of file

			usersFile >> usersFileLineHolder;  //grab a line from the file
			currentLineUserName = usersFileLineHolder.substr(0, usersFileLineHolder.find(","));  //grab everything b4 comma (name)
			currentLineUserScore = usersFileLineHolder.substr(currentLineUserName.length()+1, currentLineUserName.npos);  //grab all after comma (score)
		}
		if (currentLineUserName == usernameChoice) {
			score = std::stoi(currentLineUserScore);
			std::cout << "Welcome " << usernameChoice << "! Your saved score is: " << score << std::endl;
		}
		else {
			std::cout << "User does not exist!" << std::endl;
		}
	}

	this->runGame();
}//;

void Game::exitAndUpdate() {

	std::ofstream writefile("profiles.csv", std::ios::app);

	if (writefile.is_open()) {

		std::cout << std::endl << "writing final score!" << std::endl;
		writefile << username << "," << score << std::endl;	
	}

	writefile.close();
}