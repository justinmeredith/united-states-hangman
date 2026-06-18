// United States Hangman Game
// by Justin Meredith, June 9th, 2026

// A warm-up, one-day summer C++ project. 
// Play a game of hangman where the possible words are any of the 50 US states. 

#include<iostream>
#include<string>
#include<random>
#include<vector>
#include<cctype>
using namespace std;

// Data
const string usa_states[50] = {"Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida", "Georgia", "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts", "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey", "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia", "Wisconsin", "Wyoming"};

vector<string> hangman = {
    "  __\n |  |\n |\n |\n |\n_|_\n",
    "  __\n |  |\n |  O\n |\n |\n_|_\n",
    "  __\n |  |\n |  O\n |  |\n |\n_|_\n",
    "  __\n |  |\n |  O\n | /|\n |\n_|_\n",
    "  __\n |  |\n |  O\n | /|\\\n |\n_|_\n",
    "  __\n |  |\n |  O\n | /|\\\n | /\n_|_\n",
    "  __\n |  |\n |  O\n | /|\\\n | / \\\n_|_\n"
};

// Functions

// Returns a random state
string selectRandomState(const string usa_states[50]) {
    static mt19937 random_number_generator(random_device{}());
    uniform_int_distribution<int> range(0, 49);
    return usa_states[range(random_number_generator)];
};

// Returns a vector of underscores equivalent to the number of letters in the selected state
vector<char> createPuzzle(const string& selected_state) {
    vector<char> puzzle;

    for (int i = 0; i < selected_state.length(); ++i) {
        if (selected_state[i] == ' ') {
            puzzle.push_back(' ');
        } else {
            puzzle.push_back('_');
        }
    }

    return puzzle;
}

// Displays the current puzzle
void displayPuzzle(const vector<char>& puzzle) {
    for (char c : puzzle) {
        cout << c;
    }

    cout << endl;
}

// Displays the guessed letters
void displayGuessedLetters(const vector<char>& guessed_letters) {
    for (int i = 0; i < guessed_letters.size(); ++i) {
        cout << guessed_letters.at(i) << ' ';
    }
    cout << endl;
}

// Checks for duplicate guesses
bool alreadyGuessed(const char& current_guess, const vector<char>& guessed_letters) {
    for (char c : guessed_letters) {
        if (c == current_guess) {
            return true;
        }
    }
    return false;
}

// Prompts user for a guessed letter and validates the input guess
char collectUserGuessedLetter(const vector<char>& guessed_letters) {
    string current_guess;
    bool valid_guess = false;
    bool contains_a_digit = false;
    bool contains_a_space = false;

    // Validates input
    while (!valid_guess) {
        contains_a_digit = false;
        contains_a_space = false;
        cout << endl << "Please enter a single letter as your guess: ";
        cin >> current_guess;
        current_guess = (char)tolower(current_guess[0]);

        // Checks for numbers in input
        for (int i = 0; i < current_guess.length(); ++i) {
            if (isdigit(current_guess[i])) {
                contains_a_digit = true;
            } else if (current_guess[i] == ' ') {
                contains_a_space = true;
            }
        }

        if (contains_a_digit) {
            cout << "Numbers are not a valid guess." << endl;
        } else if (current_guess.length() > 1) {
            cout << "Only a single letter can be a guess." << endl;
        } else if (contains_a_space) {
            cout << "Your guess cannot contain spaces." << endl;
        } else if (alreadyGuessed(current_guess[0], guessed_letters)) {
            cout << "You've already guessed this letter - try something new!" << endl;
        } else {
            valid_guess = true;
        }
    }

    return (char)tolower(current_guess[0]);
}

// Returns the location of a guessed letter, if that letter is in the state's name
vector<int> checkGuessCorrectness(char guessed_letter, const string& current_state) {
    vector<int> correct_locations;
    for (int i = 0; i < current_state.length(); ++i) {
        if (guessed_letter == (char)tolower(current_state[i])) {
            correct_locations.push_back(i);
        }
    }
    if (correct_locations.size() > 0) {
        cout << "Good job! \'" << guessed_letter << "\' is in the state's name." << endl;
    }
    return correct_locations;
}

// Replaces unsolved letters with solved letters
vector<char> solvePuzzleSpaces(vector<char> puzzle, const string& current_state, const vector<int>& correct_locations) {
    for (int i = 0; i < correct_locations.size(); ++i) {
        puzzle.at(correct_locations[i]) = current_state.at(correct_locations[i]);
    }

    return puzzle;
}

// Checks if the puzzle has been solved
bool checkPuzzleStatus(const vector<char>& puzzle) {
    for (char c : puzzle) {
        if (c == '_') {
            return false;
        }
    }
    return true;
}

// Main Function
int main() {
    string current_state = selectRandomState(usa_states);
    vector<char> puzzle = createPuzzle(current_state);
    vector<int> correct_locations;
    vector<char> guessed_letters;
    char current_guess;
    bool solved = false;
    int mistakes = 0;
    int turns = 1;

    cout << "Turn #" << turns << endl;
    cout << hangman.at(mistakes);
    displayPuzzle(puzzle);
    cout << endl;

    while (!solved) {
        current_guess = collectUserGuessedLetter(guessed_letters);
        guessed_letters.push_back(current_guess);
        cout << endl;

        correct_locations = checkGuessCorrectness(current_guess, current_state);

        if (correct_locations.size() > 0) {
            puzzle = solvePuzzleSpaces(puzzle, current_state, correct_locations);
        } else {
            cout << "Sorry, " << current_guess << " is not in this state's name." << endl;
            ++mistakes;
            if (mistakes == hangman.size() - 1) {
                cout << hangman.at(mistakes);
                cout << "Sorry, you're out of attempts, and poor old Stickman has kicked the bucket!" << endl;
                cout << "The correct answer was " << current_state << "." << endl;
                return 0;
            }
        }

        cout << endl << " - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
        ++turns;
        cout << "Turn #" << turns << endl;
        cout << endl << "So far you've guessed ";
        displayGuessedLetters(guessed_letters);
        cout << hangman.at(mistakes) << endl;
        displayPuzzle(puzzle);
        solved = checkPuzzleStatus(puzzle);
    }

    cout << endl << "Great job! You guessed the right state!" << endl;
    return 0;
};