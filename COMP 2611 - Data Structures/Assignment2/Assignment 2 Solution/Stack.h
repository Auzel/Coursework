struct Stack {
	Node * top;
};

Stack * initStack ();
bool isEmptyStack (Stack * s);
void push (Stack * s, BTNode * data);
BTNode * pop (Stack * s);
