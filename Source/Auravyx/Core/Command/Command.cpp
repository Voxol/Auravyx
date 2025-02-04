#include "Auravyx/Core/Command/Command.h"
#include "Auravyx/Core/Chat.h"
#include <algorithm>
#include <iostream>

const std::string Command::argumentTypeStrings[] = { "literal", "string", "integer", "float", "double", "option" };

Command::Command()
{
}

Command& Command::condition(Command condition)
{
	subCommands.emplace_back(condition);
	return *this;
}

Command& Command::otherwise(std::function<int(std::map<std::string, std::vector<std::string>>&)> function)
{
	this->otherwiseFunction = function;
	return *this;
}
Command Command::literal(std::string s)
{
	Command cmd;
	cmd.argumentType = Argument::LITERAL;
	cmd.argumentValue = s;
	return cmd;
}
Command Command::string()
{
	Command cmd;
	cmd.argumentType = Argument::STRING;
	//cmd.argumentValue = s;
	return cmd;
}
Command Command::selectedString()
{
	Command cmd;
	cmd.argumentType = Argument::STRING_OPTION;
	//cmd.argumentValue = s;
	return cmd;
}
Command Command::integer()
{
	Command cmd;
	cmd.argumentType = Argument::INTEGER;
	return cmd;
}

Command Command::argument(std::string argName, Command subCmd)
{
	subCmd.argumentValue = argName;
	return subCmd;
}
Command& Command::limits(std::shared_ptr<std::vector<std::string>>  suggestions)
{
	this->suggestions = suggestions;
	this->limitToSuggestions = true;
	return *this;
}
Command& Command::suggests(std::shared_ptr<std::vector<std::string>>  suggestions)
{
	this->suggestions = suggestions;
	return *this;
}

Command Command::doubleArgument()
{
	Command cmd;
	cmd.argumentType = Argument::DOUBLE;
	return cmd;
}

double Command::getDouble(std::string argName, std::map<std::string, std::vector<std::string>>& args)
{
	char* end;
	double result = strtod(args.at(argName).at(0).c_str(), &end);
	if (end == args.at(argName).at(0).c_str() || *end != '\0')
	{
		return 0;
	}
	return result;
}

void Command::load()
{
}


int Command::getInteger(std::string argName, std::map<std::string, std::vector<std::string>>& args)
{
	return std::stoi(args.at(argName).at(0));
}

Command& Command::set(std::string commandName)
{
	argumentType = Argument::LITERAL;
	argumentValue = commandName;
	return *this;
}

bool Command::validArgument(std::string s, int arg)
{
	if (arg == Argument::INTEGER)
	{
		return (!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit));
	}
	else if (arg == Argument::DOUBLE)
	{
		char* end;
		double result = strtod(s.c_str(), &end);
		if (end == s.c_str() || *end != '\0')
		{
			return false;
		}
		return true;
	}
	return false;
}
bool Command::validArgument(std::string s)
{
	if (argumentType == Argument::LITERAL)
	{
		if (argumentValue == s)
		{
			return true;
		}
		return false;
	}
	else if (argumentType == Argument::INTEGER)
	{
		return (!s.empty() && std::all_of(s.begin(), s.end(), ::isdigit));
	}
	else if (argumentType == Argument::STRING)
	{
		if (limitToSuggestions)
		{
			for (int i = 0; i < suggestions->size(); i++)
			{
				if (suggestions->at(i).rfind(s, 0) == 0)
				{
					return true;
				}
			}
			return false;
		}
		return true;
	}
	else if (argumentType == Argument::DOUBLE)
	{
		char* end;
		double result = strtod(s.c_str(), &end);
		if (end == s.c_str() || *end != '\0')
		{
			return false;
		}
		return true;
	}
	else if (argumentType == Argument::STRING_OPTION)
	{
		return false;
	}
	return false;
}

bool Command::run(std::vector<std::string> arguments, std::map<std::string, std::vector<std::string>>& argumentMap, int i)
{
	if (i >= arguments.size())
	{
		return false;
	}
	bool valid = validArgument(arguments.at(i));
	if (valid)
	{
		if (subCommands.size() > 0)
		{
			for (auto& sc : subCommands)
			{
				if (argumentType != Argument::LITERAL)
				{
					std::vector<std::string> vec;
					vec.emplace_back(arguments.at(i));
					argumentMap.emplace(argumentValue, vec);
				}
				if (sc.run(arguments, argumentMap, i + 1))
				{
					return true;
				}
			}
			if (otherwiseFunction != nullptr)
			{
				if (i != 0)
				{
					std::vector<std::string> vec;
					vec.emplace_back(arguments.at(i));
					argumentMap.emplace(argumentValue, vec);
				}
				if (arguments.size() > 1)
				{
					for (int j = 1; j < arguments.size(); j++)
					{
						std::vector<std::string> vec;
						vec.emplace_back(arguments.at(j));
						argumentMap.emplace(argumentValue, vec);
					}
				}
				otherwiseFunction(argumentMap);
				return true;
			}
			else
			{
				if (arguments.size() - i - 1 >= 0)
				{
					Chat::message("Error: Expected more arguments");
					return false;
				}
			}
			return false;
		}
		else
		{
			if (otherwiseFunction != nullptr && arguments.size() - i - 1 == 0)
			{
				if (argumentType != Argument::LITERAL)
				{
					std::vector<std::string> vec;
					vec.emplace_back(arguments.at(i));
					argumentMap.emplace(argumentValue, vec);
				}
				otherwiseFunction(argumentMap);
				return true;
			}
			Chat::message("Error: Unexpected argument '" + arguments.at(i + 1) + "'");
			return true;
		}
	}
	else
	{
		//otherwiseFunction("uh oh!!");
	}
	return false;
}
