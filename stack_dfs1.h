/*"stack_dfs1.h" file*/


//struct Stack
struct Stack1{
	unsigned char top;
	unsigned char capacity;
	unsigned char* turn_dfs1;
};

// Stack is full when top is equal to the last index
unsigned char isFull_1(struct Stack1* stack_dfs1);

// Stack is empty when top is equal to
unsigned char isEmpty_1(struct Stack1* stack_dfs1);

// Function to add an item to stack. It increases top by 1
void push_1(struct Stack1* stack_dfs1, unsigned char turn_dfs1);

// Function to remove an item from stack. It decreases top by 1
unsigned char pop_1(struct Stack1* stack_dfs1);

////**************************************************************
