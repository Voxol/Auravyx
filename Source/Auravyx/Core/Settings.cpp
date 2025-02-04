#pragma once
#include "Auravyx/Core/Settings.h"
#include <iostream>
#include <Logger/Log.h>
Settings::Settings()
{
}


Settings::~Settings()
{
}
std::string Settings::getSetting(const std::string& setting)
{
	try
	{
		return settings.at(setting);
	}
	catch (std::out_of_range e)
	{
		Log::out("Setting not found");
	}
	return std::string("Error : Setting not found");
}
bool Settings::getBool(const std::string& setting)
{
	std::string b = getSetting(setting);
	std::string bc;
	for (int i = 0; i < b.size(); i++)
	{
		bc += toupper(b.at(i));
	}
	if (bc.compare("TRUE") == 0)
	{
		return true;
	}
	else if (bc.compare("FALSE") == 0)
	{
		return false;
	}
	Log::out("Get Bool setting error!");
	return false;
}
std::map<std::string, std::string> Settings::settings;