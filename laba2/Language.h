#include "Rule.h"
#include <list>
#include <string>
#include <random>

class Language
{
public:
    std::list<Rule> rules;
    int MaxRepetitionsCount;

    Language(std::list<Rule>& _rules);

    void SetMaxRepetitionsCount(int count);
    int GetMaxRepetitionsCount();
    void SetRules(std::list<Rule>& _rules);
    std::list<Rule> GetRules();

    bool CheckLoop(std::string input, Rule rule);
    std::string OutputLeft();
    std::string Translate(std::string text);
    void RefreshRules();

    bool CheckLoop2(std::string input, Rule rule, bool isReverse, int count);
    std::string TranslateRight(std::string text);
    std::string TranslateRandom(std::string text);
private:

};

Language::Language(std::list<Rule>& r)
{
    int count = 10000;
    rules = r;
    MaxRepetitionsCount = count;
}

void Language::SetRules(std::list<Rule>& _rules)
{
    rules = _rules;
}

std::list<Rule> Language::GetRules()
{
    return rules;
}

void Language::SetMaxRepetitionsCount(int count)
{
    MaxRepetitionsCount = count;
}

int Language::GetMaxRepetitionsCount()
{
    return MaxRepetitionsCount;
}

bool Language::CheckLoop(std::string input, Rule rule) {
    int count = 5;
    for (int i = 0; i < count; i++) {
        std::string key = rule.Key;
        std::string value = rule.Value;

        std::size_t pos = input.find(key);

        if (pos != -1) {
            input.replace(pos, key.length(), value);
        }
        else {
            return false;
        }
    }

    return true;
}



std::string Language::OutputLeft() {
    std::string result = "S";
    int count = 0;
    while (count < MaxRepetitionsCount) {
        int pos = -1;

        // найдем крайний левый нетерминальный символ в цепочке
        for (const Rule& rule : rules) {
            std::string key = rule.Key;
            int findPos = result.find(key);
            if ((pos > findPos || pos == -1) && findPos != -1) {
                pos = findPos;
            }
        }

        // если не найдено ниодного подходящего правила - выходим
        if (pos == -1) {
            break;
        }

        // найдем все правил подходящие для крайнего левого нетерминального символа
        std::list<Rule> _rules;
        for (const Rule& rule : rules) {
            std::string key = rule.Key;
            if (pos == result.find(key)) {
                _rules.push_back(rule);
            }
        }
        // случайно выберем правило

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, _rules.size() - 1);
        //int index = random(0, _rules.size() - 1);
        int index = dis(gen);

        auto it = std::next(_rules.begin(), index);
        Rule r = *it;

        int p = result.find(r.Key);
        result.replace(p, r.Key.length(), r.Value);

        count++;
    }

    return result;
}


void Language::RefreshRules() {
    for (Rule& rule : rules) {
        rule.IsLooped = false;
    }
}


bool Language::CheckLoop2(std::string input, Rule rule, bool isReverse, int count = 5) {
    for (int i = 0; i < count; i++) {
        std::string key = rule.Key;
        std::string value = rule.Value;

        std::size_t pos;
        if (isReverse) {
            pos = input.rfind(key);
        }
        else {
            pos = input.find(key);
        }

        if (pos != std::string::npos) {
            input.erase(pos, key.length());
            input.insert(pos, value);
        }
        else {
            return false;
        }
    }

    return true;
}


std::string Language::Translate(std::string text) {
    int count = 0;
    bool isEnd = false; // true - если ни одно из правил неприменимо
    while (count < MaxRepetitionsCount) {
        if (isEnd) break;

        count++;
        isEnd = true;
        // Применяем по очереди каждое правило языка к строке
        for (Rule& rule : rules) {
            if (!rule.IsLooped) { // Если правило зацикливает
                std::string key = rule.Key;
                std::string value = rule.Value;

                size_t pos = text.find(key);

                if (pos != std::string::npos) { // Если ключ найден
                    // Если правило зацикливает перевод - запоминаем это
                    if (CheckLoop(text, rule)) {
                        rule.IsLooped = true;
                    }
                    else {
                        text.replace(pos, key.length(), value);
                        isEnd = false;

                        break;
                    }
                }
            }
            else {
                rule.IsLooped = !rule.IsLooped;
            }
        }
    }

    RefreshRules();
    return text;
}


std::string Language::TranslateRight(std::string text) {
    int count = 0;
    bool isEnd = false; // true - если ни одно из правил непреминимо
    bool isReverse = true;
    while (count < MaxRepetitionsCount) {
        if (isEnd) break;

        count++;
        isEnd = true;
        // применяем по очереди каждое правило языка к строке
        for (auto rule : rules) {
            if (!rule.IsLooped) { // если правило зацикливает
                std::string key = rule.Key;
                std::string value = rule.Value;

                std::size_t pos = text.rfind(key);

                if (pos != std::string::npos) {
                    std::cout << pos << std::endl;
                    // если ключ найден
                    // если правило зацикливает перевод - запоминаем это
                    if (CheckLoop2(text, rule, isReverse)) {
                        rule.IsLooped = true;
                    }
                    else {
                        text.erase(pos, key.length());
                        text.insert(pos, value);
                        isEnd = false;

                        break;
                    }
                }
            }
            else {
                rule.IsLooped = !rule.IsLooped;
            }
        }
    }

    RefreshRules();
    return text;
}

std::string Language::TranslateRandom(std::string text) {
    int count = 0;
    bool isEnd = false; // true - если ни одно из правил непреминимо

    while (count < MaxRepetitionsCount) {
        if (isEnd) break;

        count++;
        isEnd = true;
        // правила, которые применимы к текущему состоянию строки
        std::list<Rule> checkedRules;
        // применяем по очереди каждое правило языка к строке
        for (auto rule : rules) {
            std::string key = rule.Key;
            std::string value = rule.Value;

            std::size_t pos = text.rfind(key);

            if (pos != std::string::npos) { // если ключ найден
                checkedRules.push_back(rule);
                isEnd = false;
            }
        }

        if (!checkedRules.empty()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(0, checkedRules.size() - 1);
            int index = dist(gen);

            Rule ruleChecked = checkedRules.front();

            std::string k = ruleChecked.Key;
            std::string v = ruleChecked.Value;
            std::size_t p = text.rfind(k);
            text.erase(p, k.length());
            text.insert(p, v);
        }
    }

    RefreshRules();
    return text;
}