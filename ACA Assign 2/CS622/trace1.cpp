/*BEGIN_LEGAL 
Intel Open Source License 

Copyright (c) 2002-2018 Intel Corporation. All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.  Redistributions
in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.  Neither the name of
the Intel Corporation nor the names of its contributors may be used to
endorse or promote products derived from this software without
specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE INTEL OR
ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
END_LEGAL */
#include <stdio.h>
#include "pin.H"

FILE * trace;
PIN_LOCK pinLock;

// This function is called before every instruction is executed
// and prints the IP
/*VOID printip(void *ip, THREADID tid)
{ 
   long int x=*((long int *) &ip);
   PIN_GetLock(&pinLock, tid+1);
   fprintf(trace, "%d %ld\n", tid, x);
   fflush(trace);
   PIN_ReleaseLock(&pinLock);
}*/


VOID RecordMemRead(VOID * ip, VOID * addr , THREADID tid, UINT32 s )
{

    PIN_GetLock(&pinLock, tid+1);
    
    unsigned long long int x=*((unsigned long long int *) &addr);
    
    //s= amount of byte accessed = add
    //starting address= x =st
    
    unsigned long long int st=x;
    int add= s; //number of byte accessed
    
    
    long int rem=0;

if(st%64!=0)
rem=((st/64)+1)*64 -st;

int add1=add-rem;



if(rem<=add)
{

	while(8<=rem)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	rem=rem-8;
	}
	while(4<=rem)
	{
		fprintf(trace,"%llu \n",st);
		fflush(trace);
		st=st+(4); 
	  	rem=rem-4;

	}

	while(2<=rem)
	{
	  fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  rem=rem-2;
	}

	while(1<=rem)
	{

		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(1); 
	  	rem=rem-1;

	}
	
	
	//checking for remaining after remainder
	
	while(8<=add1)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	add1=add1-8;
	}
	while(4<=add1)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
		st=st+(4); 
	  	add1=add1-4;

	}

	while(2<=add1)
	{
	  fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  add1=add1-2;
	}

	while(1<=add1)
	{

		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(1); 
	  	add1=add1-1;

	}
	


}

else
{

	while(8<=add)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	add=add-8;
	}
	while(4<=add)
	{
		fprintf(trace,"%llu \n",st);
		fflush(trace);
		st=st+(4); 
	  	add=add-4;

	}

	while(2<=add)
	{
	  fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  add=add-2;
	}

	while(1<=add)
	{

		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(1); 
	  	add=add-1;

	}

}

	    
	     PIN_ReleaseLock(&pinLock);
}

// Print a memory write record
VOID RecordMemWrite(VOID * ip, VOID * addr , THREADID tid, UINT32 s )
{
    PIN_GetLock(&pinLock, tid+1);
    
    unsigned long long int x=*((unsigned long long int *) &addr);
    
    //s= amount of byte accessed = add
    //starting address= x =st
    
    unsigned long long int st=x;
    int add= s; //number of byte accessed
    
    
    long int rem=0;

if(st%64!=0)
rem=((st/64)+1)*64 -st; 

int add1=add-rem;



if(rem<=add)
{

	while(8<=rem)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	rem=rem-8;
	}
	while(4<=rem)
	{
		fprintf(trace,"%llu \n",st);
		fflush(trace);
		st=st+(4); 
	  	rem=rem-4;

	}

	while(2<=rem)
	{
	  fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  rem=rem-2;
	}

	while(1<=rem)
	{

		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(1); 
	  	rem=rem-1;

	}
	
	
	//checking for remaining after remainder
	
	while(8<=add1)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	add1=add1-8;
	}
	while(4<=add1)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
		st=st+(4); 
	  	add1=add1-4;

	}

	while(2<=add1)
	{
	 fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  add1=add1-2;
	}

	while(1<=add1)
	{

		fprintf(trace,"%llu \n",st);
		fflush(trace);
	  	st=st+(1); 
	  	add1=add1-1;

	}
	


}

else
{

	while(8<=add)
	{
		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(8); 
	  	add=add-8;
	}
	while(4<=add)
	{
		fprintf(trace,"%llu \n",st);
		fflush(trace);
		st=st+(4); 
	  	add=add-4;

	}

	while(2<=add)
	{
	 fprintf(trace,"%llu \n",st);
	  fflush(trace);
	  st=st+(2); 
	  add=add-2;
	}

	while(1<=add)
	{

		fprintf(trace,"%llu \n",st);
	  	fflush(trace);
	  	st=st+(1); 
	  	add=add-1;

	}

}

    
     PIN_ReleaseLock(&pinLock);
}



// This routine is executed every time a thread is created.
VOID ThreadStart(THREADID tid, CONTEXT *ctxt, INT32 flags, VOID *v)
{
    PIN_GetLock(&pinLock, tid+1);
    fprintf(stdout, "thread begin %d\n",tid);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

// This routine is executed every time a thread is destroyed.
VOID ThreadFini(THREADID tid, const CONTEXT *ctxt, INT32 code, VOID *v)
{
    PIN_GetLock(&pinLock, tid+1);
    fprintf(stdout, "thread end %d code %d\n",tid, code);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

// Pin calls this function every time a new instruction is encountered
/*VOID Instruction(INS ins, VOID *v)
{
    // Insert a call to printip before every instruction, and pass it the IP
    INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)printip, IARG_INST_PTR, IARG_THREAD_ID, IARG_END);
}*/



VOID Instruction(INS ins, VOID *v)
{
    // Instruments memory accesses using a predicated call, i.e.
    // the instrumentation is called iff the instruction will actually be executed.
    //
    // On the IA-32 and Intel(R) 64 architectures conditional moves and REP 
    // prefixed instructions appear as predicated instructions in Pin.
    UINT32 memOperands = INS_MemoryOperandCount(ins);

    // Iterate over each memory operand of the instruction.
    for (UINT32 memOp = 0; memOp < memOperands; memOp++)
    {
        if (INS_MemoryOperandIsRead(ins, memOp))
        {
        
           UINT32 s = INS_MemoryOperandSize(ins,memOp);		

            
            INS_InsertPredicatedCall(
                ins, IPOINT_BEFORE, (AFUNPTR)RecordMemRead,
                IARG_INST_PTR,
                IARG_MEMORYOP_EA, memOp,IARG_THREAD_ID, IARG_UINT32, s,
                IARG_END);
        }
        // Note that in some architectures a single memory operand can be 
        // both read and written (for instance incl (%eax) on IA-32)
        // In that case we instrument it once for read and once for write.
        if (INS_MemoryOperandIsWritten(ins, memOp))
        {
        
             UINT32 s = INS_MemoryOperandSize(ins,memOp);	
        
            INS_InsertPredicatedCall(
                ins, IPOINT_BEFORE, (AFUNPTR)RecordMemWrite,
                IARG_INST_PTR,
                IARG_MEMORYOP_EA, memOp, IARG_THREAD_ID, IARG_UINT32, s,
                IARG_END);
        }
    }
}




// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
 
    fclose(trace);
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    PIN_ERROR("This Pintool prints the IPs of every instruction executed\n" 
              + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    trace = fopen("trace1.out", "w");
    
    PIN_InitLock(&pinLock);

    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddThreadStartFunction(ThreadStart, 0);
    PIN_AddThreadFiniFunction(ThreadFini, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
