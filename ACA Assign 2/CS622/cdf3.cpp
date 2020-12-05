#include<bits/stdc++.h>
using namespace std;
#include<fstream>

FILE * trace;

int main()
{
ifstream file("trace_misses.out");

 unordered_map<long long int, long long int> access;
 unordered_map<long long int, long long int> dist;
 
 long long int count=0;
 
 long long int inp;
 
 int b=64; //b= block size

while(file>>inp)
{
     
 
  count++;
  
  if(access[inp/b]==0)
  {
      access[inp/b]=count;
  }
  else
  {
      dist[inp]=count-access[inp/b];
      access[inp/b]=count;
  }
 
}
 
 /*
     // Traversing an unordered map 
    for (auto x : access) 
    cout << x.first << " " << x.second<<endl; 
    cout<<endl<<endl<<endl;
    
    for (auto x : dist) 
    cout << x.first << " " << x.second << endl; 
    */
    
    //calculating the value of N
     int N = dist.size();
     
    /* cout<<"N = "<<N<<endl<<endl; */ 
    
    // Now we will define the ordered map which will contain the distances as index and number of times those distance is obtained as values
    
      map<int, int> dc; //dc=distance count map
      
      for (auto x : dist) 
      dc[x.second]++; 
    
     /* for (auto x : dc) 
      cout << x.first << " " << x.second << endl<<endl;    */
      
      
      // Now calculating cdf
      
         map<long long int, float> cdf;
         
         float sum=0;
         
         for (auto x : dc)
         {
            sum=sum+x.second;
           
            cdf[x.first]= (float)sum/(float)N;
         } 
         
         
      //creating a file for dumping values   
      
      trace = fopen("cdf3.csv", "w");
      
      
      //adding 0,0 so that the graph starts from here
      fprintf(trace,"0 0 \n");
      fflush(trace);
       
      
      for (auto x : cdf)
      { 
      // printf("%d %f",x.first,x.second);
      
      fprintf(trace,"%f %f \n",log10(x.first),x.second);
      fflush(trace);
       
      cout<<endl;
      }
      
      fclose(trace);
             
}

