#ifndef _CUSTOM_STACK_H_
#define _CUSTOM_STACK_H_

#pragma once

#include <cstdint>                //standard integer types, mainly int32_t
#include <iostream>
#include <vector>



#ifndef MAX_STACK_LENGTH 
#define	MAX_STACK_LENGTH 0x32
#endif

namespace Postfix
{

	template<typename T>
	class CustomStack
	{
	private:

		//--------------------------------------------------
		//Variable declarations
		//--------------------------------------------------

		std::vector<T> stack;                                //instantiate an array on the heap... be sure to delete this pointer on destructor 
		int top;                                 //check this and make sure if -1, it is empty, otherwise buffer underflow!! or overflow!!

	protected:

	public:


		CustomStack(void) : top(-1) { }

		//delete dynamically allocated array in memory pool
		~CustomStack(void) { stack.~vector(); }

		//Do not allow outside access to change what is already in the stack
		void push(const T& item);

		//send out copy of what was on top of the stack.
		T pop(void);

		//check what is on top of the stack, make sure to disallow any tampering with...
		const T& peek(void);

		//get how many items are in the stack
		int size(void);

		//check is the stack is empty 
		bool isEmpty(void) { return top == -1; }

		//return a string representation of the stack
		void toString(void);
	};    /* CustomStack */

	//---------------------------------------------------------
	// Template source definitions for CustomStack.h 
	//---------------------------------------------------------
	template<typename T>
	void CustomStack<T>::push(const T& item)
	{

		//preincrement then assign item to top of stack
		stack.push_back(item);
		top++;
	}

	template<typename T>
	T CustomStack<T>::pop(void)
	{
		//check if stack is empty before proceeding
		if (isEmpty())
		{
			return NULL;
		}

		//copy the item onto a buffer data variable
		T buffer = stack.back();

		//remove the item from the stack, set to null
		top--;
		stack.pop_back();

		return buffer;
	}

	//check the top of the stack...
	template<typename T>
	const T& CustomStack<T>::peek(void)
	{
		return stack.at(top);
	}

	//get the current size of the stack, how many items currently in structure
	template<typename T>
	int CustomStack<T>::size(void)
	{
		return top + 1;
	}

	/*
	Sends the string representation of the stack.
	*/
	template<typename T>
	void CustomStack<T>::toString(void)
	{
		std::cout << "BOTTEM [ ";
		for (int i = 0; i < (top + 1); i++)
		{
			std::cout << i + 1 << ": ";
			std::cout << stack.at(i) << " ";
		}

		std::cout << "] TOP" << std::endl;
	}
	//-------------------------------------------------------------------

}
#endif /* _CUSTOM_STACK_H_ */