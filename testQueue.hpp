//This is where the declarations of all the test files go.
#include "queue.hpp"

/*
you will need 1 test case for each of the following functions :
queue::size()                                                                <---Done! Blocked! Debugged!
queue::isEmpty()                                                             <---Done! Blocked! Debugged!
queue::isFull(),                                                             <---Done! Blocked! Debugged!

you will need 2 test cases for the following :
queue::dequeue()
    queue empty                                                              <---Done! Blocked! Debugged!
    queue not empty                                                          <---Done! Blocked! Debugged!
queue::enqueue()
    queue full                                                               <---Done! Blocked! Debugged!
    queue not full                                                           <---Done! Blocked! Debugged!
queue::peek()
    queue not empty                                                          <---Done! Blocked! Debugged!
    queue empty                                                              <---Done! Blocked! Debugged!
*/

/* Test ID: Empty queue check - EQC              EXAMPLE TEST CASE
    Unit: queue::isEmpty ()
    Description: test to determine if queue::isEmpty () returns 1 if a
    queue object is empty
    Test steps:
    1. Construct an empty queue object
    2. Invoke queue::isEmpty ()
    3. Conditionally evaluate the valued returned by
    queue::isEmpty ()
    Test data: size = 0
    Precondition: queue object is empty
    Postcondition: queue object is still empty
    Expected result: queue is empty; 1 is returned
    Actual result: queue is empty; 1 is returned
    Status: passed

*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/* Test ID: Queue Size Check - QSC
    Unit: queue::size()
    Description: test if size correctly returns size 1 for single item queue.
    Test steps:
    1. Construct an empty queue object
    2. Invoke queue::enqueue ()
    3. Conditionally evaluate the valued returned by queue::size()
    Test data: size = 1
    Precondition: queue object has 1 item in it
    Postcondition: queue object in same state
    Expected result: queue has 1 item; 1 is returned

    Actual result: 1
    Status: PASSED!!!
*/
void testQueueSize(void);

/* Test ID: Queue Empty Check - QEC
    Unit: queue::isEmpty()
    Description: test if empty queue correctly returns that it is empty.
    Test steps:
    1. Construct an empty queue object
    2. Conditionally evaluate the valued returned by queue::isEmpty()
    Test data: none
    Precondition: queue object empty
    Postcondition: queue object in same state
    Expected result: isEmpty() returns True or 1

    Actual result: 1
    Status: PASSED!!!!!!!!!
*/
void testQueueEmpty(void);

/* Test ID: Queue Full Check - QFC
    Unit: queue::isFull()
    Description: test if empty queue correctly returns that it is full.
    Test steps:
    1. Construct an empty queue object
    2. Fill to 10 items
    2. Conditionally evaluate the valued returned by queue::isFull()
    Test data: queue size = 10
    Precondition: queue object has 10 items
    Postcondition: queue object in same state
    Expected result: isFull() returns True or 1

    Actual result: 1
    Status: PASSED!!!!!!!!!
*/
void testQueueFull(void);

/* Test ID: Dequeue Empty - DE0
    Unit: queue::dequeue()
    Description: test if empty queue correctly refuses to underflow
    Test steps:
    1. Construct an empty queue object
    2. Conditionally evaluate if dequeue() refueses to underflow when called on empty queue
    Test data: none
    Precondition: queue object has 0 items
    Postcondition: queue object in same state
    Expected result: "UnderFlow\nProgram Terminated\n" will print

    Actual result: "UnderFlow\nProgram Terminated\n" 
    Status: PASSED!!!!!!!!!
*/
void testDequeueEmpty(void);

/* Test ID: Dequeue Not Empty - DNE
    Unit: queue::dequeue()
    Description: test if  queue correctly deques correctly when not empty
    Test steps:
    1. Construct an empty queue object
    2. enqueue a number
    3. dequeue a number
    4. Conditionally evaluate if queue size matches what it should be
    Test data: queue size 0
    Precondition: queue object has 0 items
    Postcondition: queue object in same state
    Expected result: queue size will be 0

    Actual result: 0
    Status: PASSED!!!!!!!!!
*/
void testDequeueNotEmpty(void);

/* Test ID: Enqueue When Full - EWF
    Unit: queue::enqueue()
    Description: test if  queue correctly refuses to overflow
    Test steps:
    1. Construct an empty queue object
    2. enqueue 11 numbers
    3. Eval if the queue refused to enqeue the 11'th number. 
    Test data: queue size 10 when the pivotal moment happens
    Precondition: queue object has 10 items
    Postcondition: queue object in same state
    Expected result: queue size will be 10 and "OverFlow\nProgram Terminated\" will print

    Actual result: As expected
    Status: PASSED!!!!!!!!!
*/
void testEnqueueFull(void);

/* Test ID: Enqueue Not Full - ENF
    Unit: queue::enqueue()
    Description: test if  queue correctly enques when not full
    Test steps:
    1. Construct an empty queue object
    2. enqueue 1 number
    3. Eval if the queue size is now 1
    Test data: queue size 1
    Precondition: queue object has 1
    Postcondition: queue object in same state
    Expected result: queue size will be 1

    Actual result: 1
    Status: PASSED!!!!!!!!!
*/
void testEnqueueNotFull(void);

/* Test ID: Peek Not Empty - PNE
    Unit: queue::peek()
    Description: test if  queue correctly peeks when not empty
    Test steps:
    1. Construct an empty queue object
    2. enqueue 1 number
    3. Eval if peek() returns that number
    Test data: queue size 1
    Precondition: queue object has 1
    Postcondition: queue object in same state
    Expected result: queue returns first item in it

    Actual result: 69
    Status: PASSED!!!!!!!!!
*/
void testPeekNotEmpty(void);

/* Test ID: Peek When Empty - PWE
    Unit: queue::peek()
    Description: test if  queue correctly detects underflow when peek() is called on empty queue
    Test steps:
    1. Construct an empty queue object
    2. Eval if peek() refuses to underflow
    Test data: queue size 0
    Precondition: queue object has 0
    Postcondition: queue object in same state
    Expected result: queue returns "UnderFlow\nProgram Terminated\n"

    Actual result: "UnderFlow\nProgram Terminated\n"s
    Status: PASSED!!!!!!!!!
*/
void testPeekEmpty(void);