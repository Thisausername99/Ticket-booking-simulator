https://youtu.be/57GHi8Er964
# project4
Thread and synchronization by Huy Hoang, Veronica Gusev, and Nhan Le

Important details:
  The hardest part of the implementation was making sure things were in the right critical sections and getting the semaphores to work properly. 
  We made our semaphores static global variables so that we can initialize them in main instead of in phonecall since it was causing problems. 
  The while loop we keep the calls in while they wait for an available line only prints that the lines are busy once by using a boolean print so that the console doesn't repeatedly say that the lines are busy. 
  

Grading breakdown:
  Binary semaphores used to protect critical regions of code
  Counting semaphore used to restrict the use of resources (operators)
  All semaphores initialized and destroyed
  Thread function exists (phonecall) and is implemented using the algorithm
  next_id exists and is updated in phonecall
  phonecall properly updates the number of callers connected in a critical section
  Correct caller ids printed
  Static modifier properly used for thread local variables and any globals
  Functions declared and used properly
  Data structures and data types declared and used properly
  Variable and function names are clear
  Global variables are minimized, declared, and used properly
  If statements, loops, and function calls used properly
  No unreachable code
  Algorithms are efficient
  Code is written consistently with indents, curly braces, and spacing
  Comments used to document and explain the code
  Video shows compilation from the command line, 1 phone call, 10 phone calls, and 240 phone calls
