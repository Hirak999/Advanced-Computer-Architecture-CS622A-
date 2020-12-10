#include <stdio.h>
#include<math.h>      
#include <stdlib.h>  
#include<cassert>
#include<list>
#include<string.h>
#include<iostream>
#include<fstream>
#include <bits/stdc++.h> 
#include <chrono>
#include <algorithm>
#include <sys/time.h>
#define ll long long int
using namespace std;
using namespace std::chrono;


//unordered map of L2 cache for keeping track of which processor is having the block in modified state
 unordered_map<long long int, int> umap;  //index is the block number and the value is the processor in which it is stored in the modified state

unordered_map<long long int, int> l2m;

//unordered maps to keep track of the state of the block in L1 cache for upgrade messages

unordered_map<long long int, char> m[8];



//for storing the L1 access
long long int qsize[8]={0};


//unordered map to track the block shared between caches
 unordered_map<long long int, int> bc;  //bc=block count
 

void miss(long long int addr, int tid, int b,char rw);

void invalid(long long int addr, int tid);

struct Queue
{ 
    int tid; 
    long long int gc; //gc means global count
    char rw;
    long long add;
   
    struct Queue* next;
};



int bankid(long long int n)
{

    int a[64];
    long long int c;
    long long int k;

 for (c = 63; c >= 0; c--)
    {
        k = n >> c;
/*
        if (k & 1)
            putc('1', stdout);
        else
            putc('0', stdout);
    
*/ 

		if (k & 1)
		    a[c]=1;
		else
		    a[c]=0;
	
    
    }

int sum=0;
int j=0;

for(int i=6;i<=8;i++)
{

 sum+= (pow(2,j))*a[i];
 j++;
}

return sum;


return 0;

}
ll flag1[8]={0}; 
ll flag2=0,flag3=0,flag4=0;

    
//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Declaring the L1 and L2 caches

/////////////////////////////////////////////////////////////////////////////////////////////////////////      
    
    
	list <long long int> l1[8][64];  //Level 1 cache for processor 1 for maintaining 64 dll, corresponding to each set of level 2
      
        
	
	
	list <long long int> l2[8][512];  //Level 2 cache banks, l21 means cache bank 1
     

        

//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Declaring the other queues for storing of messages

/////////////////////////////////////////////////////////////////////////////////////////////////////////      


list <char> l1b[8][64]; //it will store the state of the block i.e. whether anyone of MESI

     
     
     
     

//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Declaring the variables to  queues for storing of messages

/////////////////////////////////////////////////////////////////////////////////////////////////////////      
     
     
long long int g1[8]={0};  //g1 means get values for all the L1 cache
long long int gx1[8]={0}; //gx1 means getx values for all the l1 cache


long long int upg=0;         //upgrade message as recieved by L1 cache
long long int upg_ack[8]={0};  //upgrade acknowledgement message as recieved by various L1 cache


long long int g2=0;  //g2 means get values for all the L2 cache
long long int gx2=0; //gx2 means getx values for all the l2 cache



long long int put[8]={0} ;
long long int px1[8]={0};

    
long long int swb=0;  //when a block in the modified state in one of the cache is tried to be read by some other processor that is we are trying to convert 
                      //from m state to s state then the processor which has the block in the m state must update the current value to the L2 cache. Which is 
                      //known as the sharing writeback
                      

long long int wb=0; //when a processor wants to perform read on a block which is in modified state in its own cache then it is writeback
                      

long long int inv[8]={0};
long long invac[8]={0};   //invalidate acknowledgement to L2 cache    
    
    
    
    
    
    
    
    
    
//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Declaring the Hit and Miss variables

/////////////////////////////////////////////////////////////////////////////////////////////////////////    

     
    
long long int hit1[8],hit2=0;
long long int miss1[8],miss2=0; // miss1 and miss2 represents miss of L1 and L2 cache respectively


        
long long int block1,set1,block2,set2;  //block 1 and block 2 represents the block in which the Byte will be present in l1 and l2 cache respectively and 
//set 1 and set2 represents the block in which the Block will be present in l1 and l2 cache respectively
                                     

        


///////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    //MAIN FUNCTION 
    
///////////////////////////////////////////////////////////////////////////////////////////////////////
    

int main()
{
    FILE *fp = fopen("trace.out", "r");                //change the file name from here
    int tid;
    long long int gc; //gc means global count
    char rw;
    long long add;
    
    
	for(int i=0;i<8;i++)
	{
	    miss1[i]=0;
	    hit1[i]=0;
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////    
    
    //Declare the linked list queues for this problem 
    
///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
     Queue* q0 = new Queue;
     Queue* q1 = new Queue;
     Queue* q2 = new Queue;
     Queue* q3 = new Queue;
     Queue* q4 = new Queue;
     Queue* q5 = new Queue;
     Queue* q6 = new Queue;
     Queue* q7 = new Queue;
     
     
     
//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Initializing previous and start for all queues

/////////////////////////////////////////////////////////////////////////////////////////////////////////     
    
    Queue* previous0 = NULL;
    Queue* start0 = NULL;
     
    Queue* previous1 = NULL;
    Queue* start1 = NULL;
    
    Queue* previous2 = NULL;
    Queue* start2 = NULL;
    
    Queue* previous3 = NULL;
    Queue* start3 = NULL;
    
    Queue* previous4 = NULL;
    Queue* start4 = NULL;
    
    Queue* previous5 = NULL;
    Queue* start5 = NULL;
    
    Queue* previous6 = NULL;
    Queue* start6 = NULL;
    
    Queue* previous7 = NULL;
    Queue* start7 = NULL;
    

//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Writing the main logic to store in different queues

/////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
    
    
while (fscanf(fp, "%d %lld %c %ld", &tid, &gc, &rw, &add) != EOF)
{
        
	if(tid==0)      
	{        
	       //number of L1 access for processor 0
	       qsize[0]++;
	
	        q0 = new Queue;
	       
		if(previous0!= NULL)
		{
			previous0->next=q0;
		}
		
		q0->next = NULL;

		if (start0 == NULL)
		    start0 = q0;

		q0->gc=gc;
		q0->rw=rw;
		q0->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous0 = q0;
		
	}
	
	
	
	if(tid==1)      
	{        
	
		//number of L1 access for processor 1
	       qsize[1]++;
	
		 q1 = new Queue;
	
		if(previous1!= NULL)
		{
			previous1->next=q1;
		}
		
		q1->next = NULL;

		if (start1 == NULL)
		    start1 = q1;

		q1->gc=gc;
		q1->rw=rw;
		q1->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous1 = q1;
		
	}
	
	
	
	if(tid==2)      
	{        
	
		//number of L1 access for processor 2
	       qsize[2]++;
		
		 q2 = new Queue;
	
		if(previous2!= NULL)
		{
			previous2->next=q2;
		}
		
		q2->next = NULL;

		if (start2 == NULL)
		    start2 = q2;

		q2->gc=gc;
		q2->rw=rw;
		q2->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous2 = q2;
		
	}
    
        
        
	if(tid==3)      
	{        
	
	        //number of L1 access for processor 3
	       qsize[3]++;
	      
		 q3 = new Queue;
	
		if(previous3!= NULL)
		{
			previous3->next=q3;
		}
		
		q3->next = NULL;

		if (start3 == NULL)
		    start3 = q3;

		q3->gc=gc;
		q3->rw=rw;
		q3->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous3 = q3;
		
	}
	
	
	if(tid==4)      
	{        
	
		//number of L1 access for processor 4
	       qsize[4]++;
	
		 q4 = new Queue;
	
		if(previous4!= NULL)
		{
			previous4->next=q4;
		}
		
		q4->next = NULL;

		if (start4 == NULL)
		    start4 = q4;

		q4->gc=gc;
		q4->rw=rw;
		q4->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous4 = q4;
		
	}
	
	
	if(tid==5)      
	{        
	
		//number of L1 access for processor 5
	       qsize[5]++;
	
		 q5 = new Queue;
	
		if(previous5!= NULL)
		{
			previous5->next=q5;
		}
		
		q5->next = NULL;

		if (start5 == NULL)
		    start5 = q5;

		q5->gc=gc;
		q5->rw=rw;
		q5->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous5 = q5;
		
	}
	
	
	if(tid==6)      
	{        
	
		//number of L1 access for processor 6
	       qsize[6]++;
	
	 	 q6 = new Queue;
	
		if(previous6!= NULL)
		{
			previous6->next=q6;
		}
		
		q6->next = NULL;

		if (start6 == NULL)
		    start6 = q6;

		q6->gc=gc;
		q6->rw=rw;
		q6->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous6 = q6;
		
	}
    
        
        
	if(tid==7)      
	{        
		
		//number of L1 access for processor 7
	       qsize[7]++;
	         
		 q7 = new Queue;
	
		if(previous7!= NULL)
		{
			previous7->next=q7;
		}
		
		q7->next = NULL;

		if (start7 == NULL)
		    start7 = q7;

		q7->gc=gc;
		q7->rw=rw;
		q7->add=add;

	      //setting the previous pointer to the present node, so that in the next iteration we can do previous->next=present to maintain the linked list
	      previous7 = q7;
		
	}
    
      
    
    
}
  
  
    


//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// To count the number of cycles

/////////////////////////////////////////////////////////////////////////////////////////////////////////       
  

   
  long long int count =0;  
  long long int cycles=0;


  
Queue* p0 = start0;
Queue* p1 = start1;
Queue* p2 = start2;
Queue* p3 = start3;
Queue* p4 = start4;
Queue* p5 = start5;
Queue* p6 = start6;
Queue* p7 = start7;    





                                     

    
//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Counting the number of cycles

/////////////////////////////////////////////////////////////////////////////////////////////////////////      
                                      


while(p0!=NULL || p1!=NULL || p2!=NULL || p3!=NULL || p4!=NULL || p5!=NULL || p6!=NULL || p7!=NULL)
    {
    int occ0=0,occ1=0,occ2=0,occ3=0,occ4=0,occ5=0,occ6=0,occ7=0;
                
    	for(int i=0;i<8;i++)
    	{	
    		if(p0!=NULL && p0->gc==count && occ0==0)
    		{
    		  
    		  //bankid() function is called which will give us the bankid of the L2 cache
    		  int b=bankid(p0->add);
    		  
    		
    		  
    		  // miss() is called to count the hit and the miss
    		  miss(p0->add,0,b,p0->rw);
    		 
    		
    		        
    		 
    		  if(p0->rw=='W')
    		  {
    		  invalid(p0->add, 0);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }
    		 
    		 
    		 
    		  
    		  //Now we will increment the head to the next location
    		  p0=p0->next;
    		  count++; 
    		  occ0=1; 
    		  
    		  
    		  
                }
                
                if(p1!=NULL && p1->gc==count && occ1==0)
    		{
    		
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p1->add);
    		
    		 
    		  
    		  // miss() is called to count the hit and the miss
		     miss(p1->add,1,b,p1->rw);
    		
    		
    		 
    		  if(p1->rw=='W')
    		  {
    		  invalid(p1->add, 1);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		
    		
    		  //Now we will increment the head to the next location
    		  p1=p1->next;
    		  count++;
    		  occ1=1;   
                }
                
                if(p2!=NULL && p2->gc==count && occ2==0)
    		{
    		  
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p2->add);
    		  
    		    
    		  
    		  // miss() is called to count the hit and the miss

    		  miss(p2->add,2,b,p2->rw);
    		 
    		 
    		  if(p2->rw=='W')
    		  {
    		  invalid(p2->add, 2);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }     
    		
    		 
    		  
    		  //Now we will increment the head to the next location
    		  p2=p2->next;
    		  count++;
    		  occ2=1;   
                }
                
                if(p3!=NULL && p3->gc==count && occ3==0)
    		{
    		  
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p3->add);
    		  
    		  // miss() is called to count the hit and the miss

    		  miss(p3->add,3,b,p3->rw);
    		  
    		  
    		  if(p3->rw=='W')
    		  {
    		  invalid(p3->add, 3);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		  
    		  
    		  
    		  //Now we will increment the head to the next location
    		  
    		  p3=p3->next;
    		  count++;
    		  occ3=1;   
                }
                
                if(p4!=NULL && p4->gc==count && occ4==0)
    		{
    		
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p4->add);
    		  
    		
    		 
    		  // miss() is called to count the hit and the miss

    		  miss(p4->add,4,b,p4->rw);
    		 
    		
    		
    		  if(p4->rw=='W')
    		  {
    		  invalid(p4->add, 4);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		  
    		 
    		  
    		  //Now we will increment the head to the next location
    		  p4=p4->next;
    		  count++;
    		  occ4=1;   
                }
                
                if(p5!=NULL && p5->gc==count && occ5==0)
    		{
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p5->add);
    		 
    		
    		  // miss() is called to count the hit and the miss

    		  miss(p5->add,5,b,p5->rw);
    		
    		
    		 
    		   if(p5->rw=='W')
    		  {
    		  invalid(p5->add, 5);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		
    		  
    		  //Now we will increment the head to the next location
    		  p5=p5->next;
    		  count++;
    		  occ5=1;   
                }
                
                if(p6!=NULL && p6->gc==count && occ6==0)
    		{
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p6->add);
    		 
    		  
    		  // miss() is called to count the hit and the miss

    		  miss(p6->add,6,b,p6->rw);
    		 
    		 
    		   if(p6->rw=='W')
    		  {
    		  invalid(p6->add, 6);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		 
    		 
    		  
    		  //Now we will increment the head to the next location
    		  p6=p6->next;
    		  count++;
    		  occ6=1;   
                }
                
                if(p7!=NULL && p7->gc==count && occ7==0)
    		{
    		  //Now we will process the address at the head and calculate hit miss in the L1 and the L2 cache
    		  int b=bankid(p7->add);

    		  
    		  // miss() is called to count the hit and the miss

    		  miss(p7->add,7,b,p7->rw);
    		 
    		   
    		   if(p7->rw=='W')
    		  {
    		  invalid(p7->add, 7);      // we are calling invalid() to invalidate/delete the same block that are present in the other cache
    		  }       
    		 
    		 
    		 
    		  
    		  //Now we will increment the head to the next location
    		  p7=p7->next;
    		  count++;
    		  occ7=1;   
                }
                
            }//for loop ending bracket    
                
                
                cycles++;
    
    } //while loop ending bracket
    
  
  long long int L2_access=0;
  
  cout<<"Total Number Of machine cycles: " <<cycles<<endl;
  
  
  
  cout<<"Total L1 Access: ";
  
  long long int mt=0;  //mt=machine traces
  
  for(int i=0;i<8;i++)
  {
  	cout<<qsize[i]<<" ";
  	mt=mt+qsize[i];
  	
  }
  
  cout<<endl;
  cout<<"the number of machine accesses is: "<<mt;
 
  cout<<endl;
  
  cout<<"Total Miss in L1 caches: ";
  
  for(int i=0;i<8;i++)
  {
  	cout<<miss1[i]<<" ";
  	L2_access=L2_access+miss1[i];
  	
  }
 
  cout<<endl;
 
  cout<<"Total Miss in L2 caches: " <<miss2/*(L2_access-hit2)*/<<endl;
 
 
  
  //printing total invalidation in L1
  
  cout<<"Total Invalidate requests for L1: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<inv[i]<<" ";
  }
  

   cout<<endl<<"Total Invalidate acknowledgement for L1: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<invac[i]<<" ";
  }
  
  cout<<endl;
  
  
  cout<<"The total number of GET messages for L2 cache = "<<g2<<endl;
  
  cout<<"The total number of GETX messages for L2 cache = "<<gx2<<endl;
  
  
  
  cout<<endl<<"Total PUT message in L1 cache: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<put[i]<<" ";
  }
  
  
  
   cout<<endl<<"Total PUTX message in L1 caches: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<px1[i]<<" ";
  }
 
  
  
  cout<<endl;
  
  cout<<"Total number of Sharing writeback is: "<<swb;
  
    
  cout<<endl<<"Total GET Message of L1 caches: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<g1[i]<<" ";
  }
  
  
  cout<<endl<<"Total GETX Message of L1 caches: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<gx1[i]<<" ";
  }
 
 
 cout<<endl<<"Total Upgrade request is: "<<upg;
 
 cout<<endl<<"Total Upgrade Acknowledgement is: ";
  
  
  for(int i=0;i<8;i++)
  {
  	cout<<upg_ack[i]<<" ";
  }
 
 cout<<endl;
 
 cout<<"The number of writeback messages is: "<<wb;
 
 cout<<endl;
  
 
  /*for (auto x : bc) 
      cout << x.first << " " << x.second << endl; 
  */
  
   fclose(fp);
   return 0; 
    
  
     
    
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Function to Invalidate the same blocks from the L1 cache

/////////////////////////////////////////////////////////////////////////////////////////////////////////      

void invalid(long long int addr, int tid)
{

  //for l1 cache
         
 	block1=floor(addr/64);      //the block in which the address will be mapped in L1 cache 
 	
     	set1= floor(block1 % 64);   //the set in which the address will be mapped in L1 cache



         for(int i=0;i<8;i++)
         {
                 if(i!=tid)  // we are removing the same block from other private caches
                 {
			 list<long long int>::iterator f= find(l1[i][set1].begin(), l1[i][set1].end(), block1);
			  
			    if(f != l1[i][set1].end()) //i.e. the block is found inside the set i.e. l2 hit
			 	{ 
			 	        
					l1[i][set1].erase(f);
					inv[i]++;                 //increasing the number of invalid message recieved by that processor
					invac[tid]++;                 //increasing the number of invalid acknowledgement recieved by that processor
				}
		
		//invalidating them also from the map which are storing read / write
		
		m[i][block1]='I'; //making it invalid with I
				
		}	 
		
		
		
		
	 }						

}



    
//////////////////////////////////////////////////////////////////////////////////////////////////////////     
     
// Function to calculate the Misses in L1 and L2 cache

/////////////////////////////////////////////////////////////////////////////////////////////////////////      


void miss(long long int addr, int tid, int b, char rw)  //b=bank of level 2 cache
 {
         //for l1 cache
         
 	block1=floor(addr/64);      //the block in which the address will be mapeped in L1 cache 
 	
     	set1= floor(block1 % 64);   //the set in which the address will be mapped in L1 cache
						
	
	//for level 2 cache
	
	block2=floor(addr/64);     //the block in which the address will be mapeped in L2 cache 
     	set2= floor(block2 % 512); //the set in which the address will be mapped in L2 cache 
	
	
	// Now we will check if the block is present in the set1 of the L1 cache or not
	
	  list<long long int>::iterator f= find(l1[tid][set1].begin(), l1[tid][set1].end(), block1);
	  
	    if(f != l1[tid][set1].end()) //i.e. the block is found inside the set i.e. l1 hit
	 	{ 
	 	        hit1[tid]++;
	 	   
	 	   
	 	        //Now we are writing the upgrade condition for L2 cache
	 	        
	 	        if(m[tid][block1]=='S' && rw=='W')
	 	        {
	 	        upg++;
	 	        upg_ack[tid]++;
	 	        m[tid][block1]='M';
	 	        }
	 	        
	 	        
	 	      
	 	        if(rw=='W')
	    		{
	    		m[tid][block1]='M';
	    		bc[block1]=1;           //invalidating other blocks
	    		}
	    		
	 	      
	 	        
			l1[tid][set1].erase(f);
			l1[tid][set1].push_back(block1);
			
			
			

		} 
	    else //i.e. the block is not found inside the set i.e. L1 miss
	    {
	    
	    		if(bc[block1]==0 && rw=='R')
	    		{
	    		m[tid][block1]='E';
	    		}

			if(bc[block1]>0 && rw=='R')
	    		{
	    		m[tid][block1]='S';
	    		
	    		// Now since one of the new access is reading we will change the state of all the blocks to shared
	    		
		    		for(int tid1=0;tid1<8;tid1++)   
		    		{
		    			if(m[tid1][block1]=='E')
		    			{
		    				m[tid1][block1]='S';
		    			}
		    		
				}
	    		
	    		}
	    		
	    		bc[block1]++;
	    		
	    		if(rw=='W')
	    		{
	    		m[tid][block1]='M';
	    		bc[block1]=1;           //invalidating other blocks
	    		}
	    		
	    		
	    		
	    		
	                if(rw=='R')
	                {
	                
	                if(flag3%2==0)
	                {
	                g2++;
	                put[tid]++;
	                }
	                flag3++;
	                
	                }
	                
	                
	                
	                if(rw=='W')
	                {
	                if(flag4%2==0)
	                {
	                gx2++;
	                px1[tid]++;
	                }
	                flag4++;
	                
	                }
	                
	                
	    		if(flag1[tid]%2==0)
	    		{
	    		miss1[tid]++;
	    		}
	    		flag1[tid]++;
	    		
	    		
	    		
	    		
	    		//this is for checking the get,getx and swb messages
	    	    
	                  if(umap[block1]!= 0) //this means that a block has this block in the modified state (if the block is not evicted)
	                  {
	                  	//Now we need to check if the block is still there in the cache of is evicted
	                  	list<long long int>::iterator f3= find(l1[ umap[block1]-1 ][set1].begin(), l1[ umap[block1]-1 ][set1].end(), block1); // we are 					doing -1 because we have stored the thread id as +1
	                  	
	                  	 if(f3 != l1[umap[block1]-1 ][set1].end()) //i.e. the block is found inside the set i.e. l1 hit
	 			 {
	 			 	swb++;
	 			 	
	 			 	if(rw=='R')
	 			 	{
	 			 	g1[umap[block1]-1]++;
	 			 	umap[block1]=0;
	 			 	}
	 			 	
	 			 	if(rw=='W')
	 			 	gx1[umap[block1]-1]++;
	 			  
	 	    		 }
                          }
	                
	                
	    		
	    		
	    		
	    		//Now we will like to store the processers which has the block in the modified state
	    		
	    		if(rw=='W')
	                {
	                  umap[block1]=tid+1; //we are storing the processor number as 1 to 8 here or else during the checking time it will create problem for us
	                }                     //since umap assigns by default value of 0 to locations 
	    		
	    		  
	      	
			 //we need to see in the L2 cache now.
			 
			 list<long long int>::iterator f2= find(l2[b][set2].begin(), l2[b][set2].end(), block2);
		          
		          if (f2 != l2[b][set2].end()) //i.e. the block is found inside L2 cache
	 		  { 
	 		        
	 		      /* if(flag2%2==1)
	 		       {
	 		        hit2++;
	 		        }
	 		        flag2++;
				*/
	 		        
				l2[b][set2].erase(f2);
				l2[b][set2].push_back(block2);
				
				
				//inserting in L1 now
				
				if(l1[tid][set1].size() < 8) //which means that the set is NOT full
	      			{
	         		//then add the block at the last
	         		l1[tid][set1].push_back(block1);
	      			}

	      			if(l1[tid][set1].size() == 8) //which means that the set is full
	      			{
	      			
	      			//getting the value of the first block present in the list
	      			
	      			long long int x=l1[tid][set1].front();
	      			
	      			//Now checking the writeback condition
		      			
		      			if(m[tid][x]=='M')
		      			{
		      				wb++;
					}
	      			
	      			//now invalidating it from the map, where read/write state of that is stored
	      			m[tid][x]='I';
	      			
	      			//if(bc[x]>0)
	      			bc[x]--;
	      			
	         		//delete the first element, which is the LRU
	           		l1[tid][set1].pop_front();
	           
	          		//Then add the block at the last
	            		l1[tid][set1].push_back(block1);
	      			}
			
				
			  }  	
			  else  //i.e. L2 miss
			  {
			     	if(flag2 %2==1)
	    			{
	    			miss2++;
	    			}
	    			flag2++;
			    
			     
			     	if(l2[b][set2].size() < 16)
			     	{
			     		
			     		
			     		l2[b][set2].push_back(block2);
			     		
			     		
			     		//inserting in l1 now
			     		
			     		if(l1[tid][set1].size() < 8) //which means that the set is NOT full
	      				{
	         				//then add the block at the last
	         				l1[tid][set1].push_back(block1);
	      				}

	      				if(l1[tid][set1].size() == 8) //which means that the set is full
	      				{
	      				                 
		      			//getting the value of the first block present in the list
		      			
		      			long long int x=l1[tid][set1].front();
		      			
		      			//Now checking the writeback condition
		      			
		      			if(m[tid][x]=='M')
		      			{
		      				wb++;
					}
		      			
		      			
		      			//now invalidating it from the map, where read/write state of that is stored
		      			m[tid][x]='I';
 		      			
 		      			//if(bc[x]>0)
		      			bc[x]--;

		     		
		     		
	         			//delete the first element, which is the LRU
	           			l1[tid][set1].pop_front();
	           
	          			//Then add the block at the last
	            			l1[tid][set1].push_back(block1);
	      				}
			
			   
			     	}
			    	else  //if that set of l2 is full
			     	{
			     		
			     		        // we need to pop the first lru block, and also delete it from l1 as well
			     		        ll front_element=l2[b][set2].front();
			     		        ll set=floor(front_element%64);
			                        
			                         
			                        
			                             		        
			     		        for(int tid1=0;tid<8;tid++)
			     		        {
				     		        list<long long int>::iterator f4= find(l2[tid1][set].begin(), l2[tid1][set].end(), front_element);
				     		         
				     		        if (f4 != l2[tid1][set].end()) //i.e. the block is found inside the set
		 					{ 
								l2[tid1][set].erase(f4);
								
							} 
							
							//Now checking the writeback condition
		      			
				      			if(m[tid][front_element]=='M')
				      			{
				      				wb++;
							}
												      			
				      			//now invalidating it from the map, where read/write state of that is stored
				      			m[tid1][front_element]='I';
				      			
				     		        //if(bc[front_element]>0)
	      						bc[front_element]--;

				     		         
			     		         }
			     		         
			     		         
			     		        //popping the first lru block from l2 cache 
			     		 	l2[b][set2].pop_front();
	            				l2[b][set2].push_back(block2);
	            				
	            				// now inserting in l1
	            				
	            				if(l1[tid][set1].size() < 8) //which means that the set is NOT full
	      					{
	         				//then add the block at the last
	         				l1[tid][set1].push_back(block1);
	      					}

	      					if(l1[tid][set1].size() == 8) //which means that the set is full
	      					{
	         				//delete the first element, which is the LRU
	           				l1[tid][set1].pop_front();
	           
	          				//Then add the block at the last
	            				l1[tid][set1].push_back(block1);
	      					}
			
			     		 
			     		
			     }
			     
			     
			  }
			   
			 
	    }
 	
 }    
 

      	

