// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

////A word ladder is a connection from one word to another formed by changing one
/// letter at a time with the constraint that at each step the sequence of letters
/// still forms a valid word.
///code → cade → cate → date → data
///

/*
 *rogram that repeatedly prompts the user for two words and finds a minimum-length
 *ladder between the words. You must use the Stanford Stack and Queue collections
 *from Chapter 5, along with following a particular provided algorithm to find the
 *shortest word ladder. If there are multiple short word ladder, the program only
 *needs to generate 1
 *
 *Requirements
 *- Ignore case
 *- Check for users inputs, including: word 1 and 2 are valid dictionary words,they
 *are the same length and they are not they same word. If the input is invalid,
 *print warning messages and re-prompt
 *"The two words must be the same length"
 *"The two words must be found in the dictionary"
 *"The two words must be different"
 *- Keep a dictionary of all English words (Lexicon)
 *- Use breadth-first-search (BFS)
 * - Check word 1 change, then 2, 3, 4, changes away from the original word
 * - Use a Queue to store partial ladders to explore
 * - A partial ladder is a Stack
 * - Overall collection is  a Queue of Stacks
 * Use small dictionary to test first
 * As much as possible pass collections by reference
*/

#include <iostream>
#include "console.h"
#include "lexicon.h"
using namespace std;

int main() {
    //Initialising the dictionary as a Lexicon
    Lexicon dictionary;

    cout << "Welcome to Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the first into"
            "the second by modifying one letter at a time" << endl;

    //Ask for the dictionary file name
    getDictionary(dictionary);

    getWords(dictionary);

    //Output word ladder "A ladder from [word 2] back to [word1]: [word ladder]
    getWordLadder(dictionary);

    //Repeat the sequence

    cout << "Have a nice day." << endl;
    return 0;
}

void getDictionary(Lexicon &dictionary){
    //TO DO
    //"Dictionary file name please: " reprompt if file name doesn't exist
}

void getWords(const Lexicon &dictionary){
    //TO DO
    //Ask for word 1 "Word 1 (or hit Enter to quit): "
    //Ask for word 2 "Word 2 (or hit Enter to quit): "
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
