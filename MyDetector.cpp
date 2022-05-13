

/**
 * TODO: Complete these class definitions
 */

/// Starter includes
#include "MyDetector.hpp"
#include "MyStack.hpp"
#include "MyQueue.hpp"
//
#include <iostream>
#include <string>


//
namespace CPSC131::PalindromeDetector
{
	/// Your welcome
	MyDetector::MyDetector() {}
	
	//
	bool MyDetector::isPalindrome(std::string s)
	{
		/* Should using stack and queue !!
 		bool check; 
		// First character in palindrome 
		int first_char = 0;
		// Last character in palindrome
		int last_char = s.length()-1;
		// While loop to check for the character
		while (first_char < last_char) {
			// t he string at first char and last char equal
			if (s[first_char]) == s[last_char])) {
				check = true; // is palindrome
			} else {
				check = false;
			}
			first_char ++;
			last_char --;
		}
		return check; // not palindrome
		*/
		
		/* Notes obtain from professor
		1. Loop through every character
		2. Check for base range 
		2. Add character to queue and stack 
		3. Ignore cases and symbols
		4. For loop of stack and queue and pull them out (pop,dequeu)
		*/
		
		// Initialize stack and queue to put the string in 
		CPSC131::MyStack<char> stack;
		CPSC131::MyQueue<char> queue;
		// Loop through every character
 		for (char character : s) {
 			// Push the character by uppercase 
 			character = std::toupper(character);
 			// Check if the character is in range from A to Z
 			if ((character >= 65) && (character <= 90)) {
 				// Add character to queue and stack 
 				stack.push(character);
 				queue.enqueue(character);
 			}	
 		}
 		// Loop through the stack and queue
 		for (unsigned int i = 0; i < s.length(); i++) {
 			while (!queue.empty() && !stack.empty()) {
 				// If stack and queue are not the same then it is not palindrome
 				if (stack.top() != queue.front()) {
 					return false; // not palindrome
 				} 
 				// if they are the same then remove for next character
 				else {
 					stack.pop();
 					queue.dequeue();
 				}
 			}
 		}
 		return true; // palindrome
	}
}












