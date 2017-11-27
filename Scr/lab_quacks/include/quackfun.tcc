/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */
#include <stack>
#include <queue>
#include <cstddef>

namespace quackfun
{

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the standard library stack in this problem. Its pop
 * function works a bit differently from the stack we built. Try searching
 * for "stl stack" to learn how to use it.
 *
 * @hint Think recursively!
 */
template <typename T>
T sum(std::stack<T>& s)
{
   // Your code here
   T t = s.top();
   s.pop();
   if (s.size() == 0)
   {
       s.push(t);
       return t;
   }
   T sum_store = t + sum(s);
   s.push(t);
   return sum_store;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the standard library queue in this problem. Its pop
 * function works a bit differently from the stack we built. Try searching
 * for "stl stack" to learn how to use it.
 *
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(std::queue<T>& q)
{
    std::stack<T> s{};
    std::queue<T> q_cont{};
    // optional: std::queue<T> q2;
    // Your code here

    size_t block_size = 0;
    size_t q_size = q.size();
    for (size_t i = 0; i < q_size + block_size; i += block_size)
    {
        ++block_size;
        for (size_t j = 0; j < block_size; ++j)
        {
            if (q.size() == 0)
                break; // must be in the last block and block_size > num of remaining elements
            if (block_size % 2 == 0) // even blocks need special attention
            {
                s.push(q.front());
                q.pop();
            }
            else // odd blocks
            {
                q_cont.push(q.front());
                q.pop();
            }
        }

        if (block_size % 2 == 0) // even blocks need special attention
        {
            while (s.size() != 0)
            {
                q_cont.push(s.top());
                s.pop();
            }
        }
    }
    q = q_cont;
}
/**
 * @return true if the parameter stack and queue contain only elements of
 * exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to
 *   use in your return statement, and you may only declare TWO local
 *   variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verify_same, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verify_same(std::stack<T>& s, std::queue<T>& q)
{
    bool retval = true; // 
    //T temp1; // rename me
    //T temp2; // rename :)
    
    if(!s.empty()) // pop the stack until it is empty so that we can compare the bottom of the stack with the front of the queue.
    {
    	T s_t = s.top(); // local variable to store the popped element on each recursion call.
    	s.pop();
	retval = verify_same(s, q); // recursion call start from here and returns here. After all recursion levels return, the stack is empty and we need to start popping the queue.
	T q_f = q.front(); // local variable for elements of the queue
	q.pop();
	q.push(q_f); // queue is FIFO, so this push the front element to the end, when verify_same ends, the queue is restored.
	s.push(s_t); // restoring the stack

	if (s_t != q_f) // comparing elements at corresponding position in the two container adaptors.
	    return false; // elements at this position not same: retval = false.

	return retval; // elements at this position same: retval keeps its default value
    } else {
	return true; // both are empty, which case is considered as "same"
    }
}

}
