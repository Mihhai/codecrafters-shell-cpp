#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>


#ifdef _WIN32
    constexpr char path_delimiter = ';';
#else
    constexpr char path_delimiter = ':';
#endif

class CommandLineTokenizer {
private:
	enum class TokenizerState {
		OutsideToken,
		InsideSpaceSep,
		InsideQuotesSep,
	};
public:
	static std::vector<std::string> tokenize_with_states(std::string_view input)
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
				else if (input[i] == '\"')
					currentState = TokenizerState::InsideQuotesSep;
				else
				{
					token += input[i];
					currentState = TokenizerState::InsideSpaceSep;
				}
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

		if (!token.empty())
		{
			result.emplace_back(token);
			//temporary, in case quotes are not closed at eoi it still extracts the token
		}

		return result;
	}

	static void parse_command(
		const std::string& input,
		std::string& command,
		std::string& args)
	{
		command = "";
		args = "";

		std::stringstream input_stream(input);

		if (input_stream >> command)
		{
			std::getline(input_stream >> std::ws, args);
			return;
		}

		std::cout << "Could not read command from input\n";
	}

	static std::vector<std::filesystem::path> extract_paths_from_env(const char* env_paths)
	{
		std::vector<std::filesystem::path> paths;
		std::stringstream env_paths_stream(env_paths);

		for(std::string path; std::getline(env_paths_stream >> std::ws, path , path_delimiter); )
		{
			paths.push_back(std::filesystem::path(path));
		}

		return paths;
	}
};