/*
* This is an implementation of a word ladder. A word ladder is a connection from one word to
* another formed by changing one letter at a time with the constraint that at each step the
* sequence of letters still forms a valid word. For example,
* code → cade → cate → date → data
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
string getWord(const string &prompt);
bool emptyWord(string word);
bool areWordsValid(const Lexicon &dictionary, string wordOne, string wordTwo);
bool areWordsInDictionary(const Lexicon &dictionary, string wordOne, string wordTwo);
bool areWordsSameLength(string wordOne, string wordTwo);
bool areWordsDifferent(string wordOne, string wordTwo);
void getWordLadder(const Lexicon &dictionary, string wordOne, string wordTwo);
void findPartialWordLadders(
        const Lexicon &dictionary,
        Set<string> &usedWords,
        Queue<Stack<string>> &queue,
        const Stack<string> &initialLadder);


int main() {
    // Initialising the dictionary as a Lexicon
    Lexicon dictionary;

    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time" << endl;
    cout << endl;

    // Ask for the dictionary file name

    getDictionary(dictionary);
    cout << endl;

    // Repeat the following sequence

    while (true) {
        // Ask for word 1 and quit the program if it is blank
        string wordOne = getWord("Word 1 (or Enter to quit): ");
        if (wordOne == "") {
            break;
        }
        // Ask for word 2 and quit the program if it is blank
        string wordTwo = getWord("Word 2 (or Enter to quit): ");
        if (wordTwo == "") {
            break;
        }

        // Perform validation checks on word 1 and word 2 before proceeeding to word ladder stage
        if (areWordsValid(dictionary, wordOne, wordTwo)) {
            //Output shortest word ladder from word 1 to word 2
            getWordLadder(dictionary, wordOne, wordTwo);
            cout << endl;
        }
    }
    cout << "Exiting... see you later babes!" << endl;
    pause(1000);
    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Function: getDictionary
 * Usage: Prompts the user to get the reference dictionary by typing the file name. Reprompts the
 * user if an invalid name is given.
 * Params: dictionary (Lexicon)
 * -------------------------------------------------------------------------------------------------
 * Returns: None. Void function
*/

void getDictionary(Lexicon &dictionary) {
    string filename = promptUserForFile(
                "Dictionary file name: ", "Unable to open that file. Try again.");

    dictionary = Lexicon(filename);
}


/*
 * Function: getWord
 * Usage:
 * Prompts user to input a word and strips the case and white spaces
 * Params: prompt (string)
 * -------------------------------------------------------------------------------------------------
 * Returns: word (string)
 * NOTE for enhancement: this function would check whether the word is a valid dictionary word here
 * instead and repromt the user to re-enter the word prior to checking other validations
*/

string getWord(const string &prompt) {
    string word = getLine(prompt);
    return toLowerCase(trim(word));

}

/*
 * Function: areWordsValid
 * Usage:
 * Returns true if the words pass the following validation checks:
 * a. They are valid words in the dictionary
 * b. The words have the same length
 * c. The words are not the same word
 * Params: dictionary (Lexicon), wordOne (string), wordTwo (string)
 * -----------------------------------------------------------------
 * Returns: true or false
 * NOTE for enhancement: this function would check whether the word is a valid dictionary word here
 * instead and repromt the user to re-enter the word prior to checking other validations
*/
bool areWordsValid(const Lexicon &dictionary, string wordOne, string wordTwo) {
    // Check words are valid dictionary words, the same length and different from each other
    return areWordsInDictionary(dictionary, wordOne, wordTwo)
            && areWordsSameLength(wordOne, wordTwo)
            && areWordsDifferent(wordOne, wordTwo);
}

/*
 * Function: areWordsInDictionary
 * Usage:
 * Check if a word is in dictionary, and if not display a warning to the user
 * Params: string, string
 * -------------------------------------------------------------------------------------------------
 * Returns: boolean true or false
*/

bool areWordsInDictionary(const Lexicon &dictionary, string wordOne, string wordTwo) {
    if (!dictionary.contains(wordOne) || !dictionary.contains(wordTwo)) {
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

bool areWordsSameLength(string wordOne, string wordTwo) {
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

bool areWordsDifferent(string wordOne, string wordTwo) {
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
 * Params: dictionary (Lexicon), wordOne (string), wordTwo (string)
 * -------------------------------------------------------------------------------------------------
 * Returns: None. Void function
*/

void getWordLadder(const Lexicon &dictionary, string wordOne, string wordTwo) {
    // Initialise a stack storing word 1 only
    Stack<string> stack {wordOne};
    // Initialise a queue of stacks storing the initial stack
    Queue<Stack<string>> queue {stack};
    // Initialise a set of words use in any previous ladders so these can be ignored to avoid
    // reusing words
    Set<string> usedWords {wordOne};

    // Repeat the following until the queue is empty
    while (!queue.isEmpty()) {
        // Stop if word 2 is found
        if (queue.peek().peek() == wordTwo) {
            break;
        }
        // Get the stack containing the first ladder at the front of the queue
        Stack<string> firstLadder = queue.dequeue();
        // Find the neighbouring words for the last word on the first Ladder
        findPartialWordLadders(dictionary, usedWords, queue, firstLadder);
    }
    // Get the shortest word ladder at the front of the queue
    if (!queue.isEmpty()) {
        Stack<string> wordLadderStack = queue.dequeue();
        // Display the word ladder from word 1 to word 2
        string wordLadder;
        for (string word: wordLadderStack) {
            wordLadder.append(wordLadderStack.pop() + " ");
        }
        cout << "A ladder from " << wordTwo << " back to " << wordOne << ":" << endl;
        cout <<  wordLadder << endl;
    } else {
        // If no ladder is found, notify the user
        cout << "No word ladder found from " << wordTwo << " back to " << wordOne << endl;
    }
}

/*
 * Function: findPartialWordLadders
 * Usage:
 * Find all the neighbour words from a given start word, which is a word of the same length but
 * differs from the start word by exactly 1 letter e.g. date and data, and create partial word
 * ladders using this information in order to find final word ladder
 * Params: dictionary (Lexicon), usedWords (Set), queue (Queue of Stacks of strings),
 * firstLadder (Stack of strings)
 * -------------------------------------------------------------------------------------------------
 * Returns: None. Void function
*/
void findPartialWordLadders(
        const Lexicon &dictionary,
        Set<string> &usedWords,
        Queue<Stack<string>> &queue,
        const Stack<string> &firstLadder) {

    // Get the start word at the top of the initial word ladder
    string startWord = firstLadder.peek();
    // The algorith uses 2 nested loops for efficiency: 1st loop for index of the start word,
    // 2nd loop to loop through a-z of the alphabet
    for (int i = 0; i < startWord.length(); i++) {
        for (char letter = 'a'; letter <='z'; letter++) {
            // Copy the start word to create the neighbour word
            string neighbourWord = startWord;
            // Replace each letter in the neighbour word with another letter from a to z in turn to
            // find all valid word combinations
            neighbourWord[i] = letter;
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
