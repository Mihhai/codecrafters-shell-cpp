#include <iostream>
#include <string>
#include <vector>

// directions to improve
//1. build input tokenizer to separate the command from parameters
//2. improve command management, migrate from if/else stuff
enum class TokenizerState {
	OutsideToken,
	InsideSpaceSep,
	InsideQuotesSep,
};

const std::vector<std::string> commands{ "exit", "type", "echo" };


std::vector<std::string> tokenize(std::string_view input)
{
	TokenizerState currentState = TokenizerState::OutsideToken;
	std::vector<std::string> result;
	std::string token;
	auto length = input.size();

	for (int i = 0; i < length; ++i)
	{
		switch (currentState)
		{
			case TokenizerState::OutsideToken:

				if (input[i] == ' ')
					continue;
				else if(input[i] == '\"')
					currentState = TokenizerState::InsideQuotesSep;
				else
					currentState = TokenizerState::InsideSpaceSep;
				break;

			case TokenizerState::InsideQuotesSep:

				if (input[i] == '\"')
				{
					result.emplace_back(token);
					token = "";
					currentState = TokenizerState::OutsideToken;
				}
				else
					token += input[i];
				break;

			case TokenizerState::InsideSpaceSep:

				if (input[i] == ' ')
				{
					result.emplace_back(token);
					token = "";
					currentState = TokenizerState::OutsideToken;
				}
				else {
					token += input[i];
				}
			}
	}

	return result;
}

int main() {

	//some tests

	std::string input;
	while (true)
	{
		std::cout << "\n";
		std::getline(std::cin, input);
		auto tokens = tokenize(input);
		std::cout << "\n";
		std::cout << "TOKENS: ";
		for (auto token : tokens)
		{
			std::cout << token << " ";
		}
	}

  // Flush after every std::cout / std:cerr
  //std::cout << std::unitbuf;
  //std::cerr << std::unitbuf;

  //std::string input;
  //while (true) {
	 // std::cout << "$ ";
	 // std::getline(std::cin, input);
	 // std::string command;

	 // auto space_index = input.find(" ");

	 // if (space_index == std::string::npos) {
		//  command = input;
	 // }
	 // else {
		//  command = input.substr(0, space_index);
	 // }

	 // if (command == "exit")
		//  break;
	 // if (command == "echo")
	 // {
		//  if (space_index == std::string::npos)
		//	  std::cout << "\n";
		//  else
		//	std::cout << input.substr(space_index + 1) << "\n";

		//  continue;
	 // }
	 // else if (command == "type")
	 // {
		//  std::string content = input.substr(space_index + 1);
		//  if (content == "echo" || content == "type" || content == "exit")
		//  {
		//	  std::cout << content << " is a shell builtin\n";
		//  }
		//  else {
		//	  std::cout << content << ": " << "not found\n";
		//  }

		//  continue;
	 // }

	 // std::cout << command << ": " << "not found\n";
  //}
}
