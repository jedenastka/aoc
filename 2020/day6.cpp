#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef std::map<char, int> Answers;

int main() {
    //std::vector<Answers> groupAnswers;
    Answers answers;
    int answerCount = 0;
    int groupMembers = 0;
    int answerCount2 = 0;

    while (true) {
        std::string line;
        getline(std::cin, line);
        
        if (line.empty() || std::cin.eof()) {
            //groupAnswers.push_back(answers);
            answerCount += answers.size();
            for (auto answer: answers) {
                if (answer.second == groupMembers) {
                    ++answerCount2;
                }
            }
            answers.clear();
            groupMembers = 0;
        } else {
            ++groupMembers;
            for (char ch: line) {
                if (answers.find(ch) == answers.end()) {
                    answers[ch] = 1;
                } else {
                    ++answers[ch];
                }
            }
        }

        if (std::cin.eof()) {
            break;
        }
    }

    /*for (auto i: groupAnswers) {
        std::cout << "\nNEXT\n";
        for (auto j: i) {
            std::cout << j.first << ' ' << j.second << '\n';
        }
    }*/

    std::cout << answerCount << '\n' << answerCount2 << '\n';
}
