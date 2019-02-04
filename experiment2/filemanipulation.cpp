#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ifstream in;
    in.open("helloworld.txt");
    if(in == NULL){
        cout<<"Error opening file";
        return 1;
    }
    ofstream out;
    out.open("byeworld.txt");
    string line;
    if(out == NULL){
        cout<<"Error opening file ";
        return 1;
    }
    while(in){
        cout<<"Writing to byeworld.txt ... \n";
        getline(in,line);
        out<<line;
    }
    cout<<"Writing finished...\n";
    out.close();
    in.close();
    return 0;
}