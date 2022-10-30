#include "Language.h"

// Default constructor
Language::Language()
{
}

// Destructor
Language::~Language()
{
}

/// <summary>
/// Reads xml file and convert to a Language data object
/// </summary>
/// <param name="selectedLanguage">The language type. Default is `en`</param>
/// <returns></returns>
LanguageData Language::Read(std::string selectedLanguage)
{
	LanguageData data;
	pugi::xml_document language;
	pugi::xml_parse_result result = language.load_file("language.xml");
	if (!result) {
		return LanguageData();
	}

	pugi::xml_object_range<pugi::xml_node_iterator> states = language.child("language").children();
	if (!result) {
		return LanguageData();
	}

	pugi::xml_node_iterator languageIt;
	for (languageIt = states.begin(); languageIt != states.end(); languageIt++) {
		pugi::xml_node languageNode = *languageIt;

		pugi::xml_attribute category = languageNode.attribute("lang");
		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "welcome")
			data.welcome = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "newGame")
			data.newGame = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "savedGame")
			data.savedGame = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "hello")
			data.hello = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "hi")
			data.hi = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "if")
			data.if_ = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "you")
			data.you = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "there")
			data.there = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "thinking")
			data.thinking = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "okay")
			data.okay = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "canYou")
			data.canYou = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "hi2")
			data.hi2 = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "enterA")
			data.enterA = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "theNumber")
			data.theNumber = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "right")
			data.right = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "wrong")
			data.wrong = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "scores")
			data.scores = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "loading")
			data.loading = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "previous")
			data.previous = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "saving")
			data.saving = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "goodbye")
			data.goodbye = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "theWinner")
			data.theWinner = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "withAScore")
			data.withAScore = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "scored")
			data.scored = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "noWinner")
			data.noWinner = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "and2")
			data.and2 = languageNode.child_value();

		if (std::string(selectedLanguage.c_str()) == std::string(category.value()) && std::string(languageNode.name()) == "scoredTheSame")
			data.scoredTheSame = languageNode.child_value();

	}

	return data;
}

