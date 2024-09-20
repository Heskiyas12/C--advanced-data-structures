#include "testQueue.hpp"

int main(void) {

	testQueueSize();
	testQueueEmpty();
	testQueueFull();
	testDequeueEmpty();
	testDequeueNotEmpty();
	testEnqueueFull();
	testEnqueueNotFull();
	testPeekNotEmpty();
	testPeekEmpty();

	return 0;
}


