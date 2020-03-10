#define ROGUEVALUE ' '
struct Stack {
	Node * top;
};

Stack * initStack ();
bool isEmptyStack (Stack * s);
void push (Stack * s, char data);
char pop (Stack * s);
char peekStack(Stack* s);
