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
void getWords(const Lexicon &dictionary);
string checkWord(const Lexicon &dictionary, const string &prompt, string &word);
bool areWordsSameLength(const string &wordOne, const string &wordTwo);
bool areWordsDifferent(const string &wordOne, const string &wordTwo);
void getWordLadder(const Lexicon &dictionary, const string wordOne, const string wordTwo);
void findNeighbourWord(
        const Lexicon &dictionary
        , Set<string> &usedWords
        , Queue<Stack<string>> &queue
        , const Stack<string> &initialLadder);
int main() {
    //Initialising the dictionary as a Lexicon
    Lexicon dictionary;
    string wordOne;
    string wordTwo;

    cout << "Welcome to Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the first into "
            "the second by modifying one letter at a time" << endl;
    cout << endl;

    //Ask for the dictionary file name
    getDictionary(dictionary);

    getWords(dictionary);

    //Output word ladder "A ladder from [word 2] back to [word1]: [word ladder]
    getWordLadder(dictionary, wordOne, wordTwo);

    //Repeat the sequence

    cout << "Have a nice day." << endl;
    return 0;
}

/*
 * Function: getDictionary
 * Usage: Prompts the user to get the reference dictionary by typing the file name. Reprompts the
 * user if an invalid name is given.
 * Params: dictionary as Lexicon
 * -----------------------------------------------------------------
 * Returns: None. Void function
*/

void getDictionary(Lexicon &dictionary){
    string filename = promptUserForFile(
                "Dictionary file name: ","Unable to open that file. Try again.");
    dictionary = Lexicon(filename);
    // Comment out later
    cout << dictionary << endl;
    }

/*
 * Function: getWords
 * Usage:
 * - Ignore case
 * - Check for users inputs, including:
 * a. word 1 and 2 are valid dictionary words
 * b. they are the same length
 * c. they are not they same word
 * - If the input is invalid, print warning messages and re-prompt:
 * "The two words must be found in the dictionary"
 * "The two words must be the same length"
 * "The two words must be different"
 * Params: GBufferedImage, GWindow
 * -----------------------------------------------------------------
 * Returns: None. Void function
*/

void getWords(const Lexicon &dictionary, string &wordOne, string &wordTwo){
    while (true) {
        // Ask for word 1 and check if it is a valid dictionary word
        string wordOne = checkWord(dictionary, "Word 1 (or hit Enter to quit): ", wordOne);

        // Ask for word 2 and check if it is a valid dictionary word
        string wordTwo = checkWord(dictionary, "Word 2 (or hit Enter to quit): ", wordTwo);

        // Check words are the same length and different from each other
        if (areWordsSameLength(wordOne, wordTwo) && areWordsDifferent(wordOne, wordTwo)) {
                break;
        }
    }
}

// Improved version for enhancement
//string checkWord(const Lexicon &dictionary, const string &prompt){
//    while (true) {
//        string word = getLine(prompt);
//        // Quit the program when the user enters blank as a word
//        if (word.empty()){
//            cout << "Exiting... see you later babes!" << endl;
//            return "";
//        }
//        // Remove white spaces in word and ignore case
//        word = toLowerCase(trim(word));
//        // Check if the word is in the dictionary
//        if (dictionary.contains(word)){
//            return word;
//        }
//        // If the word is not in the dictionary ignore the messages
//        cout << "The two words must be found in the dictionary." << endl;
//    }
//}

string checkWord(const Lexicon &dictionary, const string &prompt, string &word){
    while (true) {
        string word = getLine(prompt);
        // Quit the program when the user enters blank as a word
        if (word.empty()){
            cout << "Exiting... see you later babes!" << endl;
            return "";
        }
        // Remove white spaces in word and ignore case
        word = toLowerCase(trim(word));
        // Check if the word is in the dictionary
    }
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
 * Returns: boolean true or false
*/

void getWordLadder(const Lexicon &dictionary, const string wordOne, const string wordTwo){
    // Initialise a stack storing wordOne only
    Stack<string> stack {wordOne};
    // Initialise a queue of stacks storing the initial stack
    Queue<Stack<string>> queue {stack};
    // Initialise a set of words use in any previous ladders so these can be ignored to avoid
    // reusing words
    Set<string> usedWords;
    while (queue.peek().peek() != wordTwo || !queue.isEmpty()){
        Stack<string> initialladder = queue.dequeue();
        findNeighbourWord(dictionary, usedWords, queue, initialladder);
    }
}


/*    repeat until queue is empty or w2 is found:
        dequeue a stack s.
        for each valid unused English word w
                that is a "neighbor" (differs by 1 letter)
                of the word on top of s:
            create a new stack s2 whose contents are the same as s,
                    but with w added on top,
            and add s2 to the queue.
 * { {cat} } - 1 stack with starting word
{ {cat,cot}, {cat,cad}, {cat,car} } - enqueue the neighbours
{ {cat,cad}, {cat,car}, {cat,cot,dot}, {cat,cot,cog}, {cat,cot,con} }  - enqueue the neighbours etc.
{ {cat,car}, {cat,cot,dot}, {cat,cot,cog}, {cat,cot,con}, {cat,cad,bad} }
{ {cat,cot,dot}, {cat,cot,cog}, {cat,cot,con}, {cat,cad,bad}, {cat,car,bar}, {cat,car,war} }
{ {cat,cot,cog}, {cat,cot,con}, {cat,cad,bad}, {cat,car,bar}, {cat,car,war}, {cat,cot,dot,dog} }

}

/*
 * Function: findNeighbourWord
 * Usage:
 * Find the neighbour word from a given start word, which is a word of the same length but differs
 * from the start word by exactly 1 letter e.g.date and data
 * Params: dictionary (Lexicon), usedWords (Set), startWord (string)
 * -------------------------------------------------------------------------------------------------
 * Returns: boolean true or false
*/
void findNeighbourWord(
        const Lexicon &dictionary
        , Set<string> &usedWords
        , Queue<Stack<string>> &queue
        , const Stack<string> &initialLadder) {
    // Get the start word at the top of the initial word ladder
    string startWord = initialLadder.peek();
    // The algorith uses 2 nested loops for efficiency: 1st loop for index of the start word,
    // 2nd loop to loop through a-z of the alphabet
    for (int i: startWord) {
        for ( char l = 'a'; l<='z'; ++l) {
            // Replace the letter with another letter in turn
            string neighbourWord = stringReplace(startWord, startWord[i], l, 1);
            // Check word is a valid dictionary word and it hasn't been used already
            if (dictionary.contains(neighbourWord) && !usedWords.contains(neighbourWord)) {
                // Add the neighbour word to the set of used words
                usedWords.add(neighbourWord);
                // Create a copy of the initial ladder and add the neighbour word on top
                Stack<string> newLadder = initialLadder;
                newLadder.push(neighbourWord);
                // Add the new ladder into the queue
                queue.enqueue(newLadder);
            }
        }
    }
}
