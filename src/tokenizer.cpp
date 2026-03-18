#include <vector>
#include <string>

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
		}

		return result;
	}
};