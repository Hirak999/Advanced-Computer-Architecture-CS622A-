-------------------- README -----------------------



--------------  General Instructions ---------------------

Step 1: Download Pin 3.15 and set up.

Step 2: Paste the Directory named "CS622" that is being provided by us under "pin-3.15-98253-gb56e429b1-gcc-linux/source/tools/".

Step 3: Set the path of the terminal to this folder using the "cd" command. If your "pin-3.15-98253-gb56e429b1-gcc-linux" file is at the HOME directory then you can use the command--> "cd pin-3.15-98253-gb56e429b1-gcc-linux/source/tools/CS622"



--------------- Intstruction to Compile and Run Question 1 ----------------------


• Compile the program whose machine access you want to compute. The command for that is → "gcc -O3 -static -pthread filename.c -o filename"

• Then enter the command → "make obj-intel64/trace.so"

• Then finally run it using → "../../../pin -t obj-intel64/trace.so -- ./prog4 8
"

• To know the line count, we can use → "wc -l trace.out"

  Output : It outputs a file named trace.out which contains the thread id, Read or Write information and Address of Machine Accesses and 
  "wc -l trace.out" gives us the total number of machine accesses




--------------- Intstruction to Compile and Run Question 2 ----------------------


• Compile the program whose Access Distance Analysis you want to compute. The command for that is → "gcc -O3 -static -pthread filename.c -o filename"

• Then enter the command → "make obj-intel64/tracel1.so"

• Then finally run it using → "../../../pin -t obj-intel64/trace1.so – ./filename number_of_threads"

  This will generate a .out file named trace1.out, which will be input to our "cdf.cpp" file

• Compile this cpp file using → "g++ cdf.cpp"

• Run it using → "./a.out"

  Output: It outputs a file named "cdf.csv" which contains X and Y axis, where the X axis represents distance in log base 10 scale and the Y axis represents the CDF
          of the machine accesses
          
          
          

--------------- Intstruction to Compile and Run Question 3 ----------------------



• Run the python file "cache.py"  using this command → "python3 cache.py" 
  
  This will calculate the total number of hits and misses from the "trace.out" file, which we have generated in question 1. Along with this it will also produce a
  "trace_misses.out" file containing all the misses

• Then compile the "cdf3.cpp" using the command → "g++ cdf3.cpp"

• And then run it using → ./a.out

  This will generate "cdf3.csv" file which contains all the X and Y axis, where the X axis represents distance in log base 10 scale and the Y axis represents the CDF
  of the misses






--------------- Intstruction to Compile and Run Question 4 ----------------------


• Run the python file "sharing_profile.py", using this command → "python3 sharing_profile.py"

  This will calculate the total number of memory blocks, number of private memory blocks and the number of memory blocks shared by 2 to 8 threads

