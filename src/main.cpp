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
		std::string args;
		CommandLineTokenizer::parse_command(input, command, args);


		if (command == "exit")
			break;
		if (command == "echo")
		{
			std::cout << args << "\n";
		}
		else if (command == "type")
		{
			if (args == "echo" || args == "type" || args == "exit")
			{
				std::cout << args << " is a shell builtin\n";
			}
			else {
				std::cout << args << ": " << "not found\n";
			}

			continue;
		}
		else
			std::cout << command << ": " << "not found\n";
	}
}
