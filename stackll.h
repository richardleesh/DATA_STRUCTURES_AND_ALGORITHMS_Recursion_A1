#include "a1.h"

template <typename T>
class Stack{
	DList<T> theStack_;
public:
	Stack(){		
	}
	void push (const T& data){
		theStack_.push_front(data);
	}
	void pop(){
		theStack_.pop_front();
	}
	T top()const {
		return *(theStack_.begin());
	}
	bool isEmpty(){
		return theStack_.empty();
	}
        
        int getSize(){
            return theStack_.size();
        }
        
};