
#include<iostream>
#include<omp.h>
double total_time_serial,total_time_parallel;
using namespace std;
int main()  
{
    int n = 10000000;
    int * vec1 = new int[n];
    int * vec2 = new int[n];
    int * sum_serial = new int[n];
    int * sum_parallel = new int[n];
    double start, end;
    int num_thread;

    
        for(int i=0;i<n;i++)
        {
            vec1[i] = rand();
            vec2[i] = rand();
        }
        
    start = omp_get_wtime(); 
    
    for(int i=0;i<n;i++)
    {
        sum_serial[i] = vec1[i] + vec2[i];
    }

     end = omp_get_wtime();

     //total_time_serial = ((double) (end - start));
     total_time_serial = end-start;

    cout<<"total_time_serial- "<<total_time_serial<<endl;

    for(int k=1;k<=4;k++)
    {
            omp_set_num_threads(k);

            start = omp_get_wtime();
            #pragma omp parallel 
            {
                #pragma omp single
                {
                    num_thread = omp_get_num_threads();
                }
                
                #pragma omp for
                for(int i=0;i<n;i++)
                {
                    sum_parallel[i] = vec1[i] + vec2[i];
                }
            }

            end = omp_get_wtime();
            total_time_parallel = end-start;
            cout<<"total_time_parallel with threads("<<num_thread<<")- "<<total_time_parallel<<endl;
    }
    // for(int i=0;i<n;i++)
    // {
    //     cout<<vec1[i]<<" "<<vec2[i]<<" "<<sum_serial[i]<<" "<<sum_parallel[i]<<endl;
    // }
     return 0;

}