# United States Hangman

A command-line Hangman game where players guess the name of a U.S. state before running out of attempts. Built as a portfolio project to practice core C++ concepts and program structure.

## Features

- Randomly selected U.S. states each game
- Input validation for player guesses
- Case-insensitive letter handling
- Clean CLI display of game state
- Menu interface with input validation

## How To Run

To compile, run the following code in the same directory as the `united_states_hangman.cpp` file:

`g++ united_states_hangman.cpp -o hangman`

After compiling, run the program with:

`./hangman`

## Technologies Used

* C++
* Standard Library components:
  - Random number generation (`<random>`)
  - Dynamic arrays (`<vector>`)
  - String manipulation (`<string>`)
  - Input/output (`<iostream>`)

## What I Learned

* How to properly use C++’s `<random>` library to generate non-repetitive sequences by seeding a random engine
* The difference between passing variables by value vs. by reference, and how to use `const` references to improve performance and safety
* Structuring a small program to keep logic modular and readable

## Future Improvements

* Implement difficulty settings (word pool size + allowed mistakes)
* Add persistent player statistics (wins, losses, total guesses)
* (Optional) Allow users to create and store a custom word bank