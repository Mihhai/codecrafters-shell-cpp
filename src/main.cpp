#include <iostream>
#include <string>
#include <vector>
#include "tokenizer.cpp"

// directions to improve
//1. build input tokenizer to separate the command from parameters
//2. improve command management, migrate from if/else stuff

const std::vector<std::string> commands{ "exit", "type", "echo" };

int main() 
{
	//flush after every std::cout / std:cerr
	std::cout << std::unitbuf;
	std::cerr << std::unitbuf;

	std::string input;
	while (true) {
		std::cout << "$ ";
		std::getline(std::cin, input);
		std::string command;
		auto tokens = CommandLineTokenizer::tokenize_with_states(input);
		command = tokens[0];

		if (command == "exit")
			break;
		if (command == "echo")
		{
			std::cout << tokens[1];
			continue;
		}
		else if (command == "type")
		{
			if (tokens[1] == "echo" || tokens[1] == "type" || tokens[1] == "exit")
			{
				std::cout << tokens[1] << " is a shell builtin\n";
			}
			else {
				std::cout << tokens[1] << ": " << "not found\n";
			}

			continue;
		}

		std::cout << command << ": " << "not found\n";
	}
}
