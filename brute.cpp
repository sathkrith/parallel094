#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
//#include<chrono>

using namespace std;

vector<string> v(1000);

void brute(char *str,int max,char pat[],int len){
    int i,j=0,c=0;
  //  cout<<l2;
    for(i=0;i<max;i++){
        for(j=0;j<len;j++){
            if(str[i+j]!=pat[j]){
                c=c-1;
                break;
            }
            }
        c=c+1;
        }
    cout<<c<<endl;
}

int main(int argc,char **argv){
    int max,i=0,j=0,k=0,len;
    max=5000000;
    //cout<<max;
    ifstream fil("inp.txt"); 
    char *str;
    char pat[]="the";
    len=sizeof(pat)/sizeof(pat[0])-1;
    str=new char[max];
    string line;
    if(!fil)
    cout<<"err";
    while(getline(fil,line))
    {   //cout<<line;
        j=line.length();
        while(k<j&&i<max)
        str[i++]=line[k++];
        k=0;
    }
  //auto start_time = std::chrono::high_resolution_clock::now();

    brute(str,max,pat,len);
    
    delete[] str;
 // auto end_time = std::chrono::high_resolution_clock::now();
  ////  auto time = end_time - start_time;

   //cout<<std::chrono::duration_cast<std::chrono::microseconds>(time).count()<<" to run.\n";
    return 0;

}