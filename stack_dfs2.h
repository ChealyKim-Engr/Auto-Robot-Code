/*"stack_dfs1.h" file*/


//struct Stack
struct Stack2{
	unsigned char top;
	unsigned char capacity;
	unsigned char* turn_dfs2;
};

// Stack is full when top is equal to the last index
unsigned char isFull_2(struct Stack2* stack_dfs2);

// Stack is empty when top is equal to
unsigned char isEmpty_2(struct Stack2* stack_dfs2);

// Function to add an item to stack. It increases top by 1
void push_2(struct Stack2* stack_dfs2, unsigned char turn_dfs2);

// Function to remove an item from stack. It decreases top by 1
unsigned char pop_2(struct Stack2* stack_dfs2);

////**************************************************************
