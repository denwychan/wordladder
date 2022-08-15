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
using namespace std;

// Function prototypes
void getDictionary(Lexicon &dictionary);
void getWords(const Lexicon &dictionary);
string checkWord(const Lexicon &dictionary, const string &prompt);
void getWordLadder(const Lexicon &dictionary);


int main() {
    //Initialising the dictionary as a Lexicon
    Lexicon dictionary;

    cout << "Welcome to Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the first into "
            "the second by modifying one letter at a time" << endl;
    cout << endl;

    //Ask for the dictionary file name
    getDictionary(dictionary);

    getWords(dictionary);

    //Output word ladder "A ladder from [word 2] back to [word1]: [word ladder]
    getWordLadder(dictionary);

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

void getWords(const Lexicon &dictionary){
    // Ask for word 1
    string wordOne = checkWord(dictionary, "Word 1 (or hit Enter to quit): ");

    // Ask for word 2
    string wordTwo = checkWord(dictionary, "Word 2 (or hit Enter to quit): ");

    // Check words are valid
}

string checkWord(const Lexicon &dictionary, const string &prompt){
    while (true){
        string word = getLine(prompt);
        // Quit the program when the user enters blank as a word
        if (word.empty()){
            cout << "Exiting... see you later babes!" << endl;
            return "";
        }
        // Remove white spaces in word and ignore case
        word = toLowerCase(trim(word));
        // Check if the word is in the dictionary
        if (dictionary.contains(word)){
            return word;
        }
        // If the word is not in the dictionary ignore the messages
        cout << "The two words must be found in the dictionary." << endl;
    }
}

void getWordLadder(const Lexicon &dictionary){
/* Word ladder pseudo code
 * how to find a word ladder from word w1 to w2:
    create a queue of stacks, initially containing only a single stack storing {w1}.
    repeat until queue is empty or w2 is found:
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
* Do not reuse words in previous shorter ladder so do not enqueue longer ladder in algo
* To do this keep track of the set of words used in any ladder and ignore these
*/
}

void findNeigbourWords(const Lexicon &dictionary){
/*
 * Finding neighbor words
 * A neighbor of a given word w is a word of the same length as w that differs by exactly 1 letter from w
 * e.g. date and data
 * Use 2 nested loops for efficiency: 1st loop for index of the word, 2nd loop that loops through a-z to
 * replace the letter with another letter in turn
 * Check against dictionary this is a valid word
 * * Do not reuse words in previous shorter ladder so do not enqueue longer ladder in algo
* To do this keep track of the set of words used in any ladder and ignore these
*/
}
