
/**
 * DO NOT EDIT THIS FILE
 */

//
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


//
#include "MyStack.hpp"
#include "MyQueue.hpp"
#include "MyDetector.hpp"
#include "puhp-tests/PuhPTests.h"


//
using std::cout, std::cin, std::endl;
using std::string, std::to_string;
using std::vector;


//
using PuhPTests::Tests;
using PuhPTests::Test;
using PuhPTests::OutputCapture;
using PuhPTests::Timer;
using PuhPTests::Complexity;
using PuhPTests::Random;


//
using CPSC131::PalindromeDetector::MyDetector;
using CPSC131::MyStack;
using CPSC131::MyQueue;


//	PROTO
void initPalindromes();
//
void testStack(Tests& tests);
void testQueue(Tests& tests);
void testComplexities(Tests& tests);
void testDetector(Tests& tests);


//	Globals
vector<string>
	palindromes_simple,
	palindromes_case,
	palindromes_complex,
	palindromes_all
	;
std::map<string, vector<string>> palindromes;


//
int main()
{
	//
	Tests tests(50);
	
	//
	initPalindromes();
	
	//
	std::vector<std::function<void(Tests&)>> fs = {
		testStack,
		testQueue,
		testComplexities,
		testDetector
	};
	
	//
	for ( auto f : fs ) {
		f(tests);
	}
	
	//
	tests.run(true);
	
	//
	cout << "Tests complete" << endl;
	
	return 0;
}


//
void initPalindromes()
{
	//	Thank you, Grammarly: https://www.grammarly.com/blog/16-surprisingly-funny-palindromes/
	
	//
	palindromes["simple"] = std::vector<string>({
		"never odd or even",
		"a nut for a jar of tuna"
	});
	palindromes["case"] = std::vector<string>({
		"Taco Cat",
		"Oozy Rat in a Sanitary Zoo"
	});
	palindromes["complex"] = std::vector<string> ({
		"Was it a car or a cat I saw?",
		"Yo, banana boy!"
	});
}


//
void testStack(Tests& tests)
{
	//
	Test t("Stack");
	
	//
	{
		MyStack<int> stack;
		stack.push(4);
		stack.push(5);
		stack.push(7);
		t.assertEqual(stack.size(), 3ULL, 1, "Stack size after basic push");
		t.assertEqual(stack.top(), 7, 1, "Stack top() after basic push");
		t.assertFalse(stack.empty(), 1, "Stack shouldn't be empty after basic push");
		stack.pop();
		t.assertEqual(stack.size(), 2ULL, 1, "Stack size after a pop");
		t.assertEqual(stack.top(), 5, 1, "Stack top() after a pop");
		stack.pop();
		t.assertFalse(stack.empty(), 1, "Stack shouldn't be empty with elements remaining");
		stack.pop();
		t.assertTrue(stack.empty(), 1, "Stack should be empty with no elements remaining");
		
		//
		stack.push(8);
		t.assertEqual(stack.top(), 8, 0, "Checking stack top value after a push");
		stack.push(3);
		t.assertEqual(stack.top(), 3, 0, "Checking stack top value after two pushes");
		stack.push(4);
		stack.push(6);
		stack.push(8);
		t.assertEqual(stack.top(), 8, 0, "Checking stack top value after five pushes");
		stack.clear();
		t.assertTrue(stack.empty(), 1, "Stack should be empty after call to clear()");
	}
	
	{
		//	Make sure it works with another data type
		MyStack<string> s;
		s.push("One");
		s.push("Two");
		s.push("Three");
		t.assertEqual(s.top(), "Three", 0, "Checking top of stack with strings");
		s.pop();
		s.pop();
		t.assertEqual(s.top(), "One", 0, "Checking top of stack with strings");
		s.pop();
		t.assertTrue(s.empty(), 1, "Stack should be empty after clear (strings)");
	}
	
	//	Check for exceptions
	t.assertException(
		[]()
		{
			//
			MyStack<int> stack;
			stack.pop();
			
		}, 1, "Attempting to pop an empty stack should throw an exception"
	);
	t.assertException(
		[]()
		{
			//
			MyStack<int> stack;
			stack.top();
			
		}, 1, "Attempting to get the top element of an empty stack should throw an exception"
	);
	
	//
	tests << t;
}

//
void testQueue(Tests& tests)
{
	//
	Test t("Queue");
	
	//
	{
		MyQueue<int> q;
		q.enqueue(4);
		q.enqueue(5);
		q.enqueue(7);
		t.assertEqual(q.size(), 3ULL, 1, "Queue size after basic enqueue");
		t.assertEqual(q.front(), 4, 1, "Queue front() after basic enqueue");
		t.assertFalse(q.empty(), 1, "Queue shouldn't be empty after basic enqueue");
		q.dequeue();
		t.assertEqual(q.size(), 2ULL, 1, "Queue size after a dequeue");
		t.assertEqual(q.front(), 5, 1, "Queue front() after a dequeue");
		q.dequeue();
		t.assertFalse(q.empty(), 1, "Queue shouldn't be empty with elements remaining");
		q.dequeue();
		t.assertTrue(q.empty(), 1, "Queue should be empty with no elements remaining");
		
		//
		q.enqueue(8);
		t.assertEqual(q.front(), 8, 0, "Checking Queue front value after one enqueue");
		q.enqueue(3);
		t.assertEqual(q.front(), 8, 0, "Checking Queue front value after two enqueues");
		q.enqueue(4);
		q.enqueue(6);
		q.enqueue(8);
		t.assertEqual(q.front(), 8, 0, "Checking Queue front value after five enqueues");
		q.dequeue();
		t.assertEqual(q.front(), 3, 0, "Checking Queue front value after five enqueues and a dequeue");
		q.clear();
		t.assertTrue(q.empty(), 1, "Queue should be empty after call to clear()");
	}
	
	{
		//	Make sure it works with another data type
		MyQueue<string> q;
		q.enqueue("One");
		q.enqueue("Two");
		q.enqueue("Three");
		t.assertEqual(q.front(), "One", 0, "Checking top of queue with strings");
		q.dequeue();
		q.dequeue();
		t.assertEqual(q.front(), "Three", 0, "Checking top of queue with strings");
		q.dequeue();
		t.assertTrue(q.empty(), 1, "Queue should be empty after dequeuing last item (strings)");
	}
	
	//	Check for exceptions
	t.assertException(
		[]()
		{
			//
			MyQueue<int> q;
			q.dequeue();
			
		}, 1, "Attempting to dequeue an empty queue should throw an exception"
	);
	t.assertException(
		[]()
		{
			//
			MyQueue<int> q;
			q.front();
			
		}, 1, "Attempting to get the front element of an empty queue should throw an exception"
	);
	
	{
		//	Add a ton of items
		size_t count = 100000;
		MyQueue<int> q;
		for ( size_t i = 0; i < count; i++ ) {
			q.enqueue((i * 4) - 10000);
		}
		t.assertEqual(q.size(), count, 0, "Check queue size after lots of enqueuing");
	}
	
	//
	tests << t;
}


//
void testComplexities(Tests& tests)
{
	//
	Test t("Complexity");
	
	//
	Complexity complex;
	//complex.verbose(true);
	Timer timer1, timer2;
	size_t size1 = 1, size2 = 1000, addCount = 10000000;
	
	{
		//	Prep to measure stack complexities
		MyStack<int> stack1, stack2;
		
		//	Setup differently-sized stacks
		for ( size_t i = 0; i < size1; i++ ) {
			stack1.push((i * 4) - 10000);
		}
		for ( size_t i = 0; i < size2; i++ ) {
			stack2.push((i * 4) - 10000);
		}
		t.assertEqual(stack1.size(), size1, 0, "Check stack size after " + to_string(size1) + " pushes");
		t.assertEqual(stack2.size(), size2, 0, "Check stack size after " + to_string(size2) + " pushes");
		
		//	Measure complexity of a push
		timer1.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			stack1.push(5);
		}
		timer1.stop();
		//
		timer2.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			stack2.push(5);
		}
		timer2.stop();
		//
		t.assertTrue(complex.checkConstantTime(timer1, size1, timer2, size2), 2, "Stack push should be O(1)");
		
		//	Measure complexity of a pop
		timer1.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			stack1.pop();
		}
		timer1.stop();
		//
		timer2.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			stack2.pop();
		}
		timer2.stop();
		//
		t.assertTrue(complex.checkConstantTime(timer1, size1, timer2, size2), 2, "Stack pop should be O(1)");
	}
	
	{
		//	Prep to measure queue complexities
		MyQueue<int> q1, q2;
		
		//	Setup differently-sized queues
		for ( size_t i = 0; i < size1; i++ ) {
			q1.enqueue((i * 4) - 10000);
		}
		for ( size_t i = 0; i < size2; i++ ) {
			q2.enqueue((i * 4) - 10000);
		}
		t.assertEqual(q1.size(), size1, 0, "Check queue size after " + to_string(size1) + " enqueues");
		t.assertEqual(q2.size(), size2, 0, "Check queue size after " + to_string(size2) + " enqueues");
		
		//	Measure complexity of an enqueue
		timer1.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			q1.enqueue(5);
		}
		timer1.stop();
		//
		timer2.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			q1.enqueue(5);
		}
		timer2.stop();
		//
		t.assertTrue(complex.checkConstantTime(timer1, size1, timer2, size2), 2, "Queue enqueue should be O(1)");
		
		//	Measure complexity of dequeue
		timer1.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			q1.dequeue();
		}
		timer1.stop();
		//
		timer2.start();
		for ( size_t i = 0; i < addCount; i++ ) {
			q1.dequeue();
		}
		timer2.stop();
		//
		t.assertTrue(complex.checkConstantTime(timer1, size1, timer2, size2), 2, "Queue dequeue should be O(1)");
	}
	
	//
	tests << t;
}


//
void testDetector(Tests& tests)
{
	//
	Test t("Detector");
	
	//
	{
		//
		MyDetector d;
		Random r;
		
		//	Test each type of palindrome, one by one
		for ( auto itr = palindromes.begin(); itr != palindromes.end(); itr++ ) {
			string key = itr->first;
			for ( auto s : itr->second ) {
				string temp = s;
				temp.insert(r.get(0, temp.size() - 1), "ac");
				t.assertTrue(d.isPalindrome(s), 0, "Detect " + key + " palindrome: " + s);
				t.assertFalse(d.isPalindrome(temp), 0, "Detect " + key + " non-palindrome: " + temp + " (ruined)");
			}
		}
		t.assertTrue(true, 5, "Successfully detected preset palindromes");
		
		//	Generate nonsense palindromes
		for ( size_t i = 0; i < 100; i++ ) {
			
			//
			string s1, s2;
			int len = r.get(5, 25);
			for ( int j = 0; j < len; j++ ) {
				s1 += r.getChar(true);
			}
			
			string mirror = s1;
			std::reverse(mirror.begin(), mirror.end());
			
			s2 = s1 + "vd" + mirror;
			s1 = s1 + mirror;
			
			t.assertTrue(d.isPalindrome(s1), 0, "Detect random palindrome: " + s1);
			t.assertFalse(d.isPalindrome(s2), 0, "Detect random non-palindrome: " + s2);
		}
		t.assertTrue(true, 5, "Detect random palindromes");
	}
	
	//
	tests << t;
}





















