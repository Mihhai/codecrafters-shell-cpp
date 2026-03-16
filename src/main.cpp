#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string command;
  while (true) {
	  std::cout << "$ ";
	  std::getline(std::cin, command);
	  auto first_word_end_index = command.find(" ");

	  auto first_word = command.substr(0, first_word_end_index);
	  if (first_word == "echo")
	  {
		  std::cout << command.substr(first_word_end_index + 1 , command.size()) << "\n";
		  continue;
	  }

	  if (command == "exit")
		  break;

	  std::cout << command << ": " << "not found\n";
  }
}
