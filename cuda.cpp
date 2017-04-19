#include<iostream>
#include<string>
#include<fstream>
#include<thrust/device_vector.h>
using namespace std;


__global__ void brute(char *v,char *s,int *d,int *max,int *count){
    int i=threadIdx.x+blockIdx.x*blockDim.x;
    int j=0;
    while(j<*d&&i<*max&&v[i++]==s[j++])
    ;
    if(j==*d)
    count[i]=1;
    _syncthreads();
}

int main(){
    int max=50000,*d_max;
    vector<string> v(1000);
    int **d_f,f=4,i,l1,j=0;
    char *d_str,str[max];
    char *d_cmp,*cmp;
    int *d_count,*count;
    cmp=new char[]="the";
    count=new int(max);
    ifstream fil("inp.txt"); 
    string line;
    int c;
    while(getline(fil,line)&&j<max)
    {   //cout<<line;
        v.push_back(line);
        l1=line.length();
        for(i=0;i<l1&&j<max;i++)
        str[j++]=line[i];

    }
    cudaMalloc((void**)d_str,sizeof(char)*max);
    cudaMalloc((void**)d_cmp,sizeof(char)*f);
    cudaMalloc((void**)d_f,sizeof(int));
    cudaMalloc((void**)d_max,sizeof(int));
    cudaMalloc((void**)d_count,sizeof(int)*max);

    cudaMemcpy(&f,d_f,sizeof(int),cudaMemcpyDeviceToHost);  
    cudaMemcpy(&cmp,d_cmp,sizeof(char)*f,cudaMemcpyDeviceToHost);  
    cudaMemcpy(&max,d_max,sizeof(int),cudaMemcpyDeviceToHost);
    cudaMemcpy(&str,d_str,50000*sizeof(char),cudaMemcpyDeviceToHost);

    brute<<<(max/512)+1,512>>>(d_str,d_cmp,d_f,d_max,d_count);
    cudaDeviceSynchronise();
    cudaFree(d_str);
    cudaFree(d_cmp);
    cudaFree(d_max);
    cudaFree(d_f);

    cudaMemcpy(d_count,count,max*sizeof(int),cudaMemcpyHostToDevice);
    cudaFree(d_count);
    thrust::device_vector< int > iVec(count, data+max);
    int sum=thrust::reduce(iVec.begin(),iVec.end());
    cout<<sum;
    return 0;

}