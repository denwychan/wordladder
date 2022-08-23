////
/// This is an implementation of a word ladder. A word ladder is a connection from one word to
/// another formed by changing one letter at a time with the constraint that at each step the
/// sequence of letters still forms a valid word. For example,
/// code → cade → cate → date → data
///

/*
 * Instructions
 * Prompt the user for two words and finds a minimum-length ladder between the words
 * Use the Stanford Stack and Queue collections from Chapter 5
 * Use the provided algorithm to find the shortest word ladder
 * If there are multiple short word ladder, the program only needs to generate 1
 *
 * Requirements
 * - Ignore case
 * - Check for users inputs, including:
 * a. word 1 and 2 are valid dictionary words
 * b. they are the same length
 * c. they are not they same word
 * - If the input is invalid, print warning messages and re-prompt:
 * "The two words must be found in the dictionary"
 * "The two words must be the same length"
 * "The two words must be different"
 * - Keep a dictionary of all English words (Lexicon)
 * - Use small dictionary to test first
 * - Where possible, pass collections by reference
 * - Use breadth-first-search (BFS)
 * a. Check word 1 change, then 2, 3, 4, changes away from the original word
 * b. Use a Queue to store partial ladders to explore
 * c. A partial ladder is a Stack
 * d. Overall collection is  a Queue of Stacks
*/

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "filelib.h"
#include "simpio.h"
#include "queue.h"
#include "stack.h"
#include "set.h"
using namespace std;

// Function prototypes
void getDictionary(Lexicon &dictionary);
void getAndValidateWords(const Lexicon &dictionary, string &wordOne, string &wordTwo);
void getWord(const string &prompt, string &word);
bool wordsInDictionary(const Lexicon &dictionary, const string &wordOne, const string &wordTwo);
bool areWordsSameLength(const string &wordOne, const string &wordTwo);
bool areWordsDifferent(const string &wordOne, const string &wordTwo);
void getWordLadder(const Lexicon &dictionary, const string wordOne, const string wordTwo);
void findNeighbourWords(
        const Lexicon &dictionary
        , Set<string> &usedWords
        , Queue<Stack<string>> &queue
        , const Stack<string> &initialLadder);
int main() {
    // Initialising the dictionary as a Lexicon
    Lexicon dictionary;
    // Initialising word 1 and word 2 as strings
    string wordOne;
    string wordTwo;

    cout << "Welcome to Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the first into "
            "the second by modifying one letter at a time" << endl;
    cout << endl;

    //Ask for the dictionary file name
    getDictionary(dictionary);

    //Repeat the following sequence
    while (true) {
        // Get word 1 and word 2 from users and perform validations on them
        getAndValidateWords(dictionary, wordOne, wordTwo);

        //Output shortest word ladder from word 1 to word 2
        getWordLadder(dictionary, wordOne, wordTwo);
    }
    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Function: getDictionary
 * Usage: Prompts the user to get the reference dictionary by typing the file name. Reprompts the
 * user if an invalid name is given.
 * Params: dictionary (Lexicon)
 * -----------------------------------------------------------------
 * Returns: None. Void function
*/

void getDictionary(Lexicon &dictionary){
    string filename = promptUserForFile(
                "Dictionary file name: ","Unable to open that file. Try again.");
    dictionary = Lexicon(filename);
    }

/*
 * Function: getWords
 * Usage:
 * Prompts user to input word 1 and word 2 to calculate word ladder, and performs the following
 * validation checks:
 * a. word 1 and 2 are valid dictionary words
 * b. they are the same length
 * c. they are not they same word
 * Warning messages will be displayed to the user if any of the checks fail
 * Params: dictonary (Lexicon), wordOne (string), wordTwo (string)
 * -----------------------------------------------------------------
 * Returns: None. Void function
*/

void getAndValidateWords(const Lexicon &dictionary, string &wordOne, string &wordTwo){
    while (true) {
        // Ask for word 1 and check if it is a valid dictionary word
        getWord("Word 1 (or hit Enter to quit): ", wordOne);

        // Ask for word 2 and check if it is a valid dictionary word
        getWord("Word 2 (or hit Enter to quit): ", wordTwo);

        // Check words are the same length and different from each other
        if (wordsInDictionary(dictionary, wordOne, wordTwo)
                && areWordsSameLength(wordOne, wordTwo)
                && areWordsDifferent(wordOne, wordTwo)) {
                break;
        }
    }
}

/*
 * Function: getWord
 * Usage:
 * Prompts user to input a word and strips the case and white spaces. Exits the program if the user
 * enters blank
 * Params: prompt (string), word (string)
 * -----------------------------------------------------------------
 * Returns: None. Void function
 * NOTE for enhancement: this function would check whether the word is a valid dictionary word here
 * instead and repromt the user to re-enter the word prior to checking other validations
*/

void getWord(const string &prompt, string &word){
    word = getLine(prompt);
    // Quit the program when the user enters blank as a word
    if (word.empty()){
        cout << "Exiting... see you later babes!" << endl;
    } else {
        // Remove white spaces in word and ignore case
        word = toLowerCase(trim(word));
    }
}


/*
 * Function: isWordInDictionary
 * Usage:
 * Check if a word is in dictionary, and if not display a warning to the user
 * Params: string, string
 * -------------------------------------------------------------------------------------------------
 * Returns: boolean true or false
*/

bool wordsInDictionary(const Lexicon &dictionary, const string &wordOne, const string &wordTwo){
    if (!dictionary.contains(wordOne) || !dictionary.contains(wordTwo)){
        cout << "The two words must be found in the dictionary." << endl;
        return false;
    }
    return true;
}


/*
 * Function: areWordsSameLength
 * Usage:
 * Check if two words have the same length, and if not display a warning to the user
 * Params: string, string
 * -------------------------------------------------------------------------------------------------
 * Returns: boolean true or false
*/

bool areWordsSameLength(const string &wordOne, const string &wordTwo){
    if (wordOne.length() != wordTwo.length()) {
        cout << "The two words must be the same length" << endl;
        return false;
    }
    return true;
}

/*
 * Function: areWordsDifferent
 * Usage:
 * Check if two words are different, and if not display a warning to the user
 * Params: string, string
 * -------------------------------------------------------------------------------------------------
 * Returns: boolean true or false
*/

bool areWordsDifferent(const string &wordOne, const string &wordTwo){
    if (wordOne == wordTwo) {
        cout << "The two words must be different" << endl;
        return false;
    }
    return true;
}

/*
 * Function: getWordLadder
 * Usage:
 * Find the shortest word ladder from wordOne to wordTwo
 * Params: string, string
 * -------------------------------------------------------------------------------------------------
 * Returns: None. Void function
*/

void getWordLadder(const Lexicon &dictionary, const string wordOne, const string wordTwo){
    // Initialise a stack storing word 1 only
    Stack<string> stack {wordOne};
    // Initialise a queue of stacks storing the initial stack
    Queue<Stack<string>> queue {stack};
    // Initialise a set of words use in any previous ladders so these can be ignored to avoid
    // reusing words
    Set<string> usedWords;

    // Repeat the following until the queue is empty
    while (!queue.isEmpty()){
        // Stop if word 2 is found
        if (queue.peek().peek() == wordTwo) {
            break;
        }
        // Get the stack containing the first ladder at the front of the queue
        Stack<string> firstLadder = queue.dequeue();
        // Find the neighbouring words for the last word on the first Ladder
        findNeighbourWords(dictionary, usedWords, queue, firstLadder);
    }
    // Get the shortest word ladder at the front of the queue
    Stack<string> wordLadderStack = queue.dequeue();
    // Display the word ladder from word 1 to word 2
    string wordLadder;
    for (string word: wordLadderStack){
        wordLadder.append(wordLadderStack.pop() + " ");
    }
    cout << "A ladder from " << wordOne << " back to " << wordTwo << ":" << endl;
    cout <<  wordLadder << endl;
}

/*
 * Function: findNeighbourWords
 * Usage:
 * Find all the neighbour words from a given start word, which is a word of the same length but
 * differs from the start word by exactly 1 letter e.g. date and data
 * Params: dictionary (Lexicon), usedWords (Set), queue (Queue of Stacks of strings),
 * firstLadder (Stack of strings)
 * -------------------------------------------------------------------------------------------------
 * Returns: None. Void function
*/
void findNeighbourWords(
        const Lexicon &dictionary
        , Set<string> &usedWords
        , Queue<Stack<string>> &queue
        , const Stack<string> &firstLadder) {
    // Get the start word at the top of the initial word ladder
    string startWord = firstLadder.peek();
    // The algorith uses 2 nested loops for efficiency: 1st loop for index of the start word,
    // 2nd loop to loop through a-z of the alphabet
    for (int i = 0; i < startWord.length(); i++) {
        for (char l = 'a'; l<='z'; ++l) {
            // Replace the letter in the start word with another letter from a to z in turn to find
            // all valid word combinations
            string neighbourWord = stringReplace(startWord, startWord[i], l, 1);
            // Check word combination is a valid dictionary word and it hasn't been used already
            if (dictionary.contains(neighbourWord) && !usedWords.contains(neighbourWord)) {
                // Add the neighbour word to the set of used words
                usedWords.add(neighbourWord);
                // Create a copy of the initial ladder and add the neighbour word on top
                Stack<string> newLadder = firstLadder;
                newLadder.push(neighbourWord);
                // Add the new ladder into the queue
                queue.enqueue(newLadder);
            }
        }
    }
}
