#pragma once

#include <string>
#include <pugixml.hpp>

// The struct for parsing xml
struct LanguageData {
	std::string welcome = "";
	std::string newGame = "";
	std::string savedGame = "";
	std::string hello = "";
	std::string hi = "";
	std::string if_ = "";
	std::string you = "";
	std::string there = "";
	std::string thinking = "";
	std::string okay = "";
	std::string canYou = "";
	std::string hi2 = "";
	std::string enterA = "";
	std::string theNumber = "";
	std::string right = "";
	std::string wrong = "";
	std::string scores = "";
	std::string loading = "";
	std::string previous = "";
	std::string saving = "";
	std::string goodbye = "";
	std::string theWinner = "";
	std::string withAScore = "";
	std::string scored = "";
	std::string noWinner = "";
	std::string and2 = "";
	std::string scoredTheSame = "";
};

class Language
{
public:
	Language();
	~Language();
	LanguageData Read(std::string selectedLanguage);

private:
	LanguageData mData;
};
