//This file holds the test function definitions

#include "testQueue.hpp"

void testQueueSize(void) {

	cout << "testQueueSize test begin:" << endl;
	queue a;
	a.enqueue(69);
	cout << "Size should be 1 and it is: " << a.size() << endl;
	cout << "testQueueSize test end:" << endl;
}

void testQueueEmpty(void) {

	cout << "testQueueEmpty begin:" << endl;
	queue a;
	cout << "should return 1. Actual return value: " << a.isEmpty() << endl;
	cout << "testQueueEmpty end: " << endl;
}

void testQueueFull(void) {

	cout << "testQueueFull begin:" << endl;
	queue a;
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	cout << "queue size is now " << a.size() << endl;
	cout << "should return 1. Actual return value: " << a.isFull() << endl;
	cout << "testQueueFill end: " << endl;
}

void testDequeueEmpty(void) {

	cout << "testDequeueEmpty begin:" << endl;
	queue a;
	a.dequeue();
	cout << "Should have refuesed to underflow! testDequeueEmpty over:" << endl;
}

void testDequeueNotEmpty(void){

	cout << "testDequeueNotEmpty start:" << endl;
	queue a;
	a.enqueue(69);
	a.dequeue();
	cout << "size should be 0. Actual size: " << a.size() << " testDequeueNotEmpty over:" << endl;
}

void testEnqueueFull(void) {
	
	cout << "testEnqueueFull begin:" << endl;
	queue a;
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	a.enqueue(0);
	cout << "should return refuse to overflow!" << endl;
	cout << "testQueueFull end: " << endl;

}

void testEnqueueNotFull(void) {

	cout << "testEnqueueNotFull start:" << endl;
	queue a;
	a.enqueue(69);
	cout << "size should be 1. Actual size: " << a.size() << " testEnqueueNotFull over:" << endl;
}

void testPeekNotEmpty(void) {

	cout << "testPeekNotEmpty start:" << endl;
	queue a;
	a.enqueue(69);
	cout << "peek() should return 69. Actual return value: " << a.peek() << " testPeekNotEmpty over:" << endl;
}

void testPeekEmpty(void) {
	
	cout << "testPeekNotEmpty start:" << endl;
	queue a;
	a.peek();
	cout << "peek() should return refuse to underflow! testPeekNotEmpty over:" << endl;

}