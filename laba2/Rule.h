#pragma once
#include <iostream>
#include <string>
#include<list>

class Rule
{
public:
	std::string Key;
	std::string Value;
	bool IsLooped;

	Rule(std::string k, std::string v);
	Rule();

	void SetKey(std::string _key);
	std::string GetKey();
	void SetValue(std::string _key);
	std::string GetValue();
	void SetIsLooped(bool _IsLooped);
	bool GetIsLooped();


};

Rule::Rule(std::string k, std::string v) {
	bool l = false;
	Key = k;
	Value = v;
	IsLooped = l;
}

Rule::Rule() {};

void Rule::SetKey(std::string _key) {
	Key = _key;
}


std::string Rule::GetKey() {
	return Key;
};

void Rule::SetValue(std::string _value) {
	Value = _value;
}


std::string Rule::GetValue() {
	return Value;
};

void Rule::SetIsLooped(bool _IsLooped) {
	IsLooped = _IsLooped;
}


bool Rule::GetIsLooped() {
	return IsLooped;
};

void PrintRules(const std::list<Rule>& R) {
	std::cout << "Правила для языка" << std::endl;
	for (const auto& rule : R) {
		std::cout << "   \u2022" << rule.Key << "-->" << rule.Value << std::endl;
	}
}
