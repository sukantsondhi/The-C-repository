A program that simulates the organization of the virtual memory in a
running process. The virtual address space will be represented by a dynamic doubly linked list. The list will
store integers in two stacks, which will grow and shrink during the program execution. In particular,
• the first stack, which starts at the head of the list and grow towards the tail, will contain odd digits,
i.e. 1, 3, 5, 7, or 9,
• the second stack, which starts at the tail of the list and grows towards the head, will contain even
digits, e.g. 0, 2, 4, 6, or 8,
• between the two stacks, the program will maintain a free space, i.e. a set of free nodes, simulating the
free memory between the heap and the stack in a process virtual address space.
Here is an illustrative diagram of the list that your program is supposed to build:

head odd integers → free space ← even integers tail

The list will grow or shrink by adding or removing fixed-size blocks of free nodes. The number of free
nodes added to or removed from the list will be fixed by a macro, BLOCKSIZE, defined at the beginning of the
program. Newly allocated free nodes will temporarily store a fixed negative value, e.g. −1. When some free
space is available, the program will be able to push digits to the list. The program will also include a pull
function, to free one node from a selected stack. The user will control the pushing and pulling operations by
writing two strings in the terminal. The number of digits accepted from the input will be capped at a fixed
value to avoid overflow. The program will keep track of all dynamic memory allocations through leak-aware
allocation and deallocation functions, which update a counter defined in main.
