#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>
#include <unordered_set>
#include <cmath>

using namespace std;

unordered_set<string> dictionary;

bool loadDictionary(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "[ERROR] Could not open dictionary file.\n";
        return false;
    }

    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        dictionary.insert(word); 
    }

    file.close();

    if (dictionary.size() < 100) {
        cout << "[Error] Dictionary contains less than 100 words.\n"; //atleast 100 word in dictionary
        exit(1);
    } else {
        cout << "[INFO] Dictionary loaded successfully. Total words: " << dictionary.size() << "\n";
    }

    return true;
}

int levenshteinDistance(const string& a, const string& b) {
    // Create a 2D matrix (table) to store distances between substrings
    vector<vector<int>> dp(a.length() + 1, vector<int>(b.length() + 1));
    for (size_t i = 0; i <= a.length(); ++i) dp[i][0] = i;
    for (size_t j = 0; j <= b.length(); ++j) dp[0][j] = j;

    for (size_t i = 1; i <= a.length(); ++i) {
        for (size_t j = 1; j <= b.length(); ++j) {
            int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost}); // deletion, insertion and substitution
        }
    }
    return dp[a.length()][b.length()];
}

bool isWordCorrect(const string& word) {
    return dictionary.count(word) > 0;
}

void suggestSimilarWords(const string& word) {
    cout << "[SUGGESTION] Did you mean for the word '" << word << "':\n";
    bool suggestionFound = false;

    for (const string& dictWord : dictionary) {
        if (levenshteinDistance(word, dictWord) <= 2) {
            cout << "  - " << dictWord << endl;
            suggestionFound = true;
        }
    }

    if (!suggestionFound) {
        cout << "  No similar words found in the dictionary.\n";
    }
}

void addToDictionary(const string& word, const char* filename) {
    dictionary.insert(word);
    ofstream file(filename, ios::app);
    if (file) {
        file << word << endl;
        cout << "[INFO] Added " << word << " to the dictionary.\n";
    } else {
        cerr << "[ERROR] Could not update dictionary file.\n";
    }
}

int main() {
    const char* filename = "C:\\Users\\amanh\\.vscode\\.vscode\\dictionary.txt";
    if (!loadDictionary(filename)) {
        return 1;
    }

    cout << "[OK] Dictionary loaded. Total words: " << dictionary.size() << endl;

    string input;
    cout << "Enter text to check spelling (or type 'quit' or 'exit' to stop):\n";

    while (true) {
        getline(cin, input);

        if (input == "quit") {
            cout << "[INFO] Exiting the spell checker.\n";
            break;
        }
        if (input == "exit") {
            cout << "[INFO] Exiting the spell checker.\n";
            break;
        }

        transform(input.begin(), input.end(), input.begin(), ::tolower);

        regex wordRegex(R"(\b[a-zA-Z]+(?:[-'][a-zA-Z]+)*\b)");
        sregex_iterator words_begin(input.begin(), input.end(), wordRegex);
        sregex_iterator words_end;

        int totalWords = 0, incorrectWords = 0;
        unordered_set<string> seenWords;

        vector<string> correctWords;
        vector<string> incorrectWordsList;

        cout << "\n[RESULT] Spell Check Result:\n";
        
        for (auto it = words_begin; it != words_end; ++it) {
            string word = it->str();
            totalWords++;

            if (seenWords.count(word)) {
                cout << "[REPEAT] Repeated word: " << word << endl;
            } else {
                seenWords.insert(word);
            }

            if (isWordCorrect(word)) {
                correctWords.push_back(word);
            } else {
                incorrectWordsList.push_back(word);
                incorrectWords++;
            }
        }

        if (!correctWords.empty()) {
            cout << "[CORRECT] Correct words:\n";
            for (const string& word : correctWords) {
                cout << "  - " << word << endl;
            }
        } else {
            cout << "[INFO] No correct words found in the entered sentence.\n";
        }

        if (!incorrectWordsList.empty()) {
            cout << "[WRONG] Incorrect words:\n";
            for (const string& word : incorrectWordsList) {
                cout << "  - " << word << endl;

                suggestSimilarWords(word);

                char choice;
                cout << "Do you want to add this word to the dictionary? (y/n): ";
                cin >> choice;
                cin.ignore();
                if (choice == 'y' || choice == 'Y') {
                    addToDictionary(word, filename);
                }
            }
        }

        cout << "\n[INFO] Total words: " << totalWords << ", Incorrect words: " << incorrectWords << ", Correct words: " << totalWords - incorrectWords << endl;
        if (incorrectWords == 0) {
            cout << "[OK] All words are spelled correctly!" << endl;
        }

        cout << "\nEnter text to spelling check (or type 'quit' or 'exit' to stop):\n";
    }

    return 0;
}
