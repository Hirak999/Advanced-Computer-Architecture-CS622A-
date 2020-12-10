-------------------- README -----------------------



--------------  General Instructions ---------------------

Step 1: Download Pin 3.15 and set up.

Step 2: Paste the Directory named "CS622" that is being provided by us under "pin-3.15-98253-gb56e429b1-gcc-linux/source/tools/".

Step 3: Set the path of the terminal to this folder using the "cd" command. If your "pin-3.15-98253-gb56e429b1-gcc-linux" file is at the HOME directory then you can use the command--> "cd pin-3.15-98253-gb56e429b1-gcc-linux/source/tools/CS622"



--------------- Intstruction to Compile and Run the Program to Calculate Trace (trace.cpp) ----------------------

• A file named "trace.cpp" is provided inside the directory named "CS622" to record the total number of machine accesses along with its 
  nature whether read/write as well as the thread number.

• Compile the program whose machine access you want to compute. The command for that is → "gcc -O3 -static -pthread filename.c -o filename"

• Then enter the command → "make obj-intel64/trace.so"

• Then finally run it using → "../../../pin -t obj-intel64/trace.so -- ./filename 8
"

• To know the line count, we can use → "wc -l trace.out"

  Output : It outputs a file named trace.out which contains the thread id, Read or Write information and Address of Machine Accesses and 
  "wc -l trace.out" gives us the total number of machine accesses




--------------- Intstruction to Compile and Run the Simulator (simulator.cpp) ----------------------


• Compile the code using the command ---> " g++ simulator.cpp "


• Run the code using the command --->  " ./a.out "


  Output : It outputs total number of machine cycles, total L1 access, total number of machine accesses, total miss in L1 and L2 cache, total invalidation requests 	   and acknowledgement received by the L1 cache, total GET, GETX, PUT, PUTX messages received by the L1 caches, total GET and GETX message,Upgrade request, 	   Upgrade Acknowledgement,Writeback messages, Sharing writeback messages  received by the L2 caches

