// Author: Pathik Sangani
// Date: 10-18-2024
// Description : Program "Countdown Letter" is a 2 - player game where each round generates 
// random letters, with 3 to 5 of them being vowels.

#include <iostream>
#include <fstream>
#include <vector>  
#include <string>  
#include <algorithm>  
#include <cctype>
#include "mersenne-twister.h"  

using namespace std;

// functions declaration
int chooseRandomNumber(int min, int max);
string fullSetOfVowels();
string fullSetOfConsonants();
bool isWordValid(const string& word, string letters);
bool isWordInDictionary(const string& word, const vector<string>& dictionary); 
string findLongestWord(const vector<string>& dictionary, const string& letters);

// main function
int main() 
{
	// read words from file "words.txt" and store it in string "word"
	vector<string> dictionary;
	ifstream fileIn("words.txt");
	string word;
	while (fileIn >> word) {
		dictionary.push_back(word);
	}
	fileIn.close();

	// asking for a seed to generate random number accordingly. 
	int randSeed = 0;
	cout << "Enter random seed: ";
	cin >> randSeed;
	seed(randSeed); 
	cout << endl;

    cout << "Let's play Countdown!" << endl;

	// a loop to play again if user input y.
    char playAgain;
    do{
        // asks for number of vowels
        int numOfVowels;
        cout << "How many vowels would you like (3-5)? " << endl;
        cin >> numOfVowels;

        // loop to ask the user number of vowels if the user input invalid number.
        do {
            // invalid expression if number of vowels input is out of range.
            if (numOfVowels < 3 || numOfVowels > 5) {
                cout << "Invalid number of vowels." << endl;
                cout << "How many vowels would you like (3-5)?";
                cin >> numOfVowels; 
                '\n';
            }
        } while ((numOfVowels < 3) || (numOfVowels > 5));

        // varaibles to generate random letters and functions call
        string vowel = fullSetOfVowels(); 
        string consonant = fullSetOfConsonants();
        string letters = "";

        // generating vowels
        for (int i = 0; i < numOfVowels; i++) {
            int index = chooseRandomNumber(0, vowel.length() - 1);
            letters = letters + vowel[index];
            vowel.erase(index, 1);
        }

        // generating consonants
        for (int i = 0; i < 9 - numOfVowels; i++) {
            int index = chooseRandomNumber(0, consonant.length() - 1);
            letters = letters + consonant[index];
            consonant.erase(index, 1);
        }

        cout << "The letters are: " << letters << endl;

        // ask each player to enter their word
        string player1, player2;
        cout << "Player 1, enter your word: ";
        cin >> player1;

        // loop to convert player's input to uppercase letters.
        for (int i = 0; i < player1.length(); i++) {
            player1.at(i) = toupper(player1.at(i)); 
        }

        cout << "Player 2, enter your word: ";
        cin >> player2;

        // loop to convert player's input to uppercase letters.
        for (int i = 0; i < player2.length(); i++) {
            player2.at(i) = toupper(player2.at(i)); 
        }

        // calling the isWordValid and isWordDictionary function.
        bool player1Valid, player2Valid;
        player1Valid = isWordValid (player1, letters) && isWordInDictionary(player1, dictionary);
        player2Valid = isWordValid (player2, letters) && isWordInDictionary(player2, dictionary);

        // conditions on who won the game or game tie. 
        if (!player1Valid){
            cout << "Player 1's word is not valid." << endl;
        }
        if (!player2Valid){
            cout << "Player 2's word is not valid." << endl;
        }

        // condition if both player's word are valid who will win or the game is tie. 
        if (player1Valid && player2Valid) {
            if (player1.length() > player2.length()) {
                cout << "Player 1 wins!" << endl;
            }else if (player2.length() > player1.length()) {
               cout << "Player 2 wins!" << endl;
            }else{
               cout << "Tie game." << endl;
            }
        }else if (player1Valid) {
            cout << "Player 1 wins!" << endl;
        }else if (player2Valid) {
            cout << "Player 2 wins!" << endl;
        }else{
            cout << "Tie game." << endl;
        }
    
        //function call of "findLongestWord"
        string longestWord;
        longestWord = findLongestWord(dictionary, letters);
        cout << "The longest possible word is: " << longestWord << endl;

        // ask if want to play again.
        cout << "Do you want to play again (y/n)? " << endl;
        cin >> playAgain;

    } while (tolower(playAgain) == 'y');
    
    return 0;
}


// function to generate random number according to the seed. 
int chooseRandomNumber(int min, int max) {
	return rand_u32() % (max + 1 - min) + min;
}

// function to generate vowels
string fullSetOfVowels() {
	return 
		string(15, 'A') + 
		string(21, 'E') + 
		string(13, 'I') + 
		string(13, 'O') + 
		string(5, 'U');
}

// function to generate consonants
string fullSetOfConsonants() {
	return
		string(2, 'B') +
		string(3, 'C') +
		string(6, 'D') +
		string(2, 'F') +
		string(3, 'G') +
		string(2, 'H') +
		string(1, 'J') +
		string(1, 'K') +
		string(5, 'L') +
		string(4, 'M') +
		string(8, 'N') +
		string(4, 'P') +
		string(1, 'Q') +
		string(9, 'R') +
		string(9, 'S') +
		string(9, 'T') +
		string(1, 'V') +
		string(1, 'W') +
		string(1, 'X') +
		string(1, 'Y') +
		string(1, 'Z');
}


// function to check if the word is from the given letters.
bool isWordValid(const string& word, string letters) {
    for (int i = 0; i < word.size(); i++){
        int found = -1;
        for (int j = 0; j < letters.length(); j++) {
            if (letters[j] == word[i]){
                found = j;
                break;
            }
        }
        if (found == -1) return false;   
        letters[found] = ' '; 
    }
    return true;
}

// function to check if the word is in the dictionary.
bool isWordInDictionary(const string& word, const vector<string>& dictionary){
    return find(dictionary.begin(), dictionary.end(), word) != dictionary.end();
}

// find the longest word from the dictionary
string findLongestWord(const vector<string>& dictionary, const string& letters){
    string longestWord;
    for (const string& word : dictionary){
        if(isWordValid(word, letters) && word.length() > longestWord.length()){
            longestWord = word;
        }
    }
    return longestWord;
}