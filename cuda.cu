#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<chrono>
#include<thrust/device_vector.h>
using namespace std;


__global__ void brute(const char *v,const char *s,int *d,int *max,int *count){
    int i=threadIdx.x+blockIdx.x*blockDim.x;
    count[blockIdx.x]=0;
    __shared__ int  countl[1024]; 
    int j=0;
    while((j<(*d))&&(i<(*max))&&(v[i]==s[j]))
    {
    i++;    
   j++;
    }
    
    if(j==(*d))
    countl[threadIdx.x]=1;
    else
    countl[threadIdx.x]=0;
    __syncthreads();    
    for(i=0;i<blockDim.x;i++)
    count[blockIdx.x]=count[blockIdx.x]+countl[i];


}


int main(int argc,char **argv){
    int max,*d_max;    
    max=5000000;
    vector<string> v(1000);
    int *d_f,i,l1,j=0,num_blocks=max/1024+1,tot=0;
    char *d_str,*str;
    str=new char[max];
    char *d_cmp;
    int *d_count,*count;
    count=new int[num_blocks];
    for(i=0;i<num_blocks;i++)
    count[i]=0;
    char cmp[]="the";
    int f=sizeof(cmp)/sizeof(cmp[0])-1;
    ifstream fil("inp.txt"); 
    string line;
    while(getline(fil,line)&&j<max)
    {   //cout<<line;
        v.push_back(line);
        l1=line.length();
        for(i=0;i<l1&&j<max;i++)
        str[j++]=line[i];

    }
  //  cout<<"herre";
 //   cout<<f;
  //  for(i=0;i<max;i++)
   // cout<<str[i];
  // brute(str);
    cudaMalloc((void**)&d_str,sizeof(char)*max);
    cudaMalloc((void**)&d_cmp,sizeof(char)*f);
    cudaMalloc((void**)&d_f,sizeof(int));
    cudaMalloc((void**)&d_max,sizeof(int));
    cudaMalloc((void**)&d_count,sizeof(int)*num_blocks);

    cudaMemcpy(d_count,count,sizeof(int)*num_blocks,cudaMemcpyHostToDevice);  
    cudaMemcpy(d_f,&f,sizeof(int),cudaMemcpyHostToDevice);  
    cudaMemcpy(d_cmp,&cmp,sizeof(char)*f,cudaMemcpyHostToDevice);  
    cudaMemcpy(d_max,&max,sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(d_str,str,max*sizeof(char),cudaMemcpyHostToDevice);
 // auto start_time = std::chrono::high_resolution_clock::now();

    brute<<<num_blocks,1024>>>(d_str,d_cmp,d_f,d_max,d_count);
    
    cudaThreadSynchronize();
    cudaFree(d_str);
    cudaFree(d_cmp);
    cudaFree(d_max);
    cudaMemcpy(count,d_count,sizeof(int)*num_blocks,cudaMemcpyDeviceToHost);
        for(i=0;i<num_blocks;i++){
        tot+=count[i];
        }

    cudaFree(d_count);
    cout<<tot<<endl;
    delete[] count;
    delete[] str;
 // auto end_time = std::chrono::high_resolution_clock::now();
   // auto time = end_time - start_time;

  // cout<<std::chrono::duration_cast<std::chrono::milliseconds>(time).count()<<" to run.\n";

    return 0;

}