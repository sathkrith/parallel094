#include<iostream>
#include<string>
#include<fstream>
#include<thrust/host_vector>
#include<thrust/device>
using namespace std;


__global__ void brute(vector<string> v*,int *count,vect){
    int i=ThreadIdx.x;
    string str="the";
    int l=v.size(),l2=str.length(),l1;
    for(i=0;i<l;i++){
        l1=v[i].length();
        for(j=0;j<l1;j++){
            while(j<l1&&k<l2&&v[i][j++]==str[k++])
            ;
            if(k==l2)
            c++;
            k=0;
            }
        }
    cout<<c;
}

int main(){
    thrust::host_vector<string> v(1000);
    thrust::device_vector<string> v(1000);

    int d_c,s,l=0,i,l1,j=0;
    char *d_str,str[50000];
    

    ifstream fil("inp.txt"); 
    string line;
    int c;
    while(getline(fil,line)&&j<50000)
    {   //cout<<line;
        v.push_back(line);
        l1=line.length();
        for(i=0;i<l1&&j<50000;i++)
        str[j++]=line[i];

    }
    for()
    cudaMalloc(d_str,sizeof(char)*50000);
    cudaMalloc(c,sizeof(int));
    cudaMemcpy(&str,d_str,50000*sizeof(char));
    brute<<<1,1>>>(d_str,c);
    cudaDeviceSynchronise();
    return 0;

}