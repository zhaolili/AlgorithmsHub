/*
greedy algorithm.
"Greedy algorithms are simple and straightforward. They are shortsighted in their approach in the sense that they take decisions on the basisi of information at hand without worrying about the effect these decisions may have in the future. They are easy to invent, easy to implement and most of the time quite efficient. Many problems cannot be solved correctly by greedy approach."
"Unlike DP, which solves the subproblems bottom-up, a greedy strategy usually progresses in a top-down fashion, maiking one greedy choice after another, reducing each problem to a smaller one."
"
Structure Greedy Alogrithm
Initially the set of chosen items is empty i.e., solution set.
At each step
	item will be added in asolution set by uisng selection function.
	If the set would no longer feasible
		reject items under consideration
	ELse IF set is still feasible THEN
		add the current item
"
--from http://www.personal.kent.edu/~rmuhamma/Algorithms/algorithm.html
*/

#include "..\header\common_def.h"