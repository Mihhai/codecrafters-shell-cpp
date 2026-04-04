#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "tokenizer.cpp"

// directions to improve
//1. build input tokenizer to separate the command from parameters
//2. improve command management, migrate from if/else stuff

const std::vector<std::string> commands{ "exit", "type", "echo" };

int main() 
{
	//flush after every std::cout / std:cerr

	const char* path_env = std::getenv("PATH");
	

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
			if(path_env == nullptr)
			{
				std::cout << "Could not read path from env variable";
				continue;
			}

			std::vector<std::filesystem::path> path_list = CommandLineTokenizer::extract_paths_from_env(path_env);
			bool command_found = false;

			for(const auto& path: path_list)
			{
				if(!std::filesystem::exists(path))
				{
					std::cout << "Path " << path << " does not exist, skipping\n";
					break;
				}
				
				std::filesystem::path command_file = path / args;
				std::cout << "Checking for command in " << command_file << "\n";

				if(std::filesystem::exists(command_file) && std::filesystem::is_regular_file(command_file))
				{
					std::cout << "args is " << command_file.string() << "\n";
					command_found = true;
					break; 
				}
			}
			
				if(command_found == false)
					std::cout << args << ": not found" << "\n";

		}
		else
			std::cout << command << ": " << "not found\n";
	}
}
