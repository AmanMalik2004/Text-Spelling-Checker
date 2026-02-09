# C++ Text and Spell Checker

## Description
This is a **C++ console-based text and spell checker**. The program reads user input, checks each word against a dictionary, identifies repeated or incorrect words, suggests similar words for misspellings using **Levenshtein distance**, and allows users to add new words to the dictionary interactively.  

It provides a simple yet effective way to check spelling for English text and maintain a growing dictionary.

---

## Features
- Checks spelling of input text against a dictionary (minimum 100 words required).  
- Detects and reports repeated words.  
- Suggests similar words for incorrect entries (words with Levenshtein distance ≤ 2).  
- Allows adding new words to the dictionary dynamically.  
- Displays summary of total words, correct words, and incorrect words.  
- Interactive command-line interface with easy prompts.

---

## How It Works
1. **Dictionary Loading**:  
   - Loads a dictionary file containing one word per line.  
   - Converts all words to lowercase for consistency.  

2. **Spell Checking**:  
   - Accepts user input line by line.  
   - Uses regex to extract words.  
   - Checks each word against the dictionary and tracks repetitions.  

3. **Suggestions and Updates**:  
   - For incorrect words, suggests similar words from the dictionary.  
   - Prompts the user to optionally add the new word to the dictionary.  

4. **Results Summary**:  
   - Displays lists of correct and incorrect words.  
   - Shows repeated words in the input.  
   - Continues until the user types `quit` or `exit`.

---

## Requirements
- C++ compiler supporting **C++11 or higher**.  
- Standard C++ libraries: `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<regex>`, `<unordered_set>`, `<algorithm>`, `<cmath>`.  

---

## Usage
1. Place your dictionary file and update the `filename` path in the code:
   ```cpp
   const char* filename = "C:\\path\\to\\dictionary.txt";
2. Compile the program:
    g++ spell_checker.cpp -o spell_checker
3. Run the program:
    ./spell_checker
4. Enter the text to check spelling.
5. For each incorrect word, view suggestions and optionally add it to the dictionary.
6. Type quit or exit to stop the program.
