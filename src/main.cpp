#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;

  while (true) {
	  std::cout << "$ ";
	  std::getline(std::cin, input);
	  std::string command;

	  auto space_index = input.find(" ");

	  if (space_index == std::string::npos) {
		  command = input;
	  }
	  else {
		  command = input.substr(0, space_index);
	  }

	  if (command == "exit")
		  break;
	  if (command == "echo")
	  {
		  if (space_index == std::string::npos)
			  std::cout << "\n";
		  else
			std::cout << input.substr(space_index + 1) << "\n";

		  continue;
	  }
	  else if (command == "type")
	  {
		  std::string content = input.substr(space_index + 1);
		  if (content == "echo" || content == "type" || content == "exit")
		  {
			  std::cout << content << " is a shell builtin\n";
		  }
		  else {
			  std::cout << content << ": " << "not found\n";
		  }

		  continue;
	  }

	  std::cout << command << ": " << "not found\n";
  }
}
