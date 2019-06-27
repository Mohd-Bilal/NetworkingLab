#include<iostream>
#include<fstream>
using namespace std;

int main(){
    ifstream inp;
    inp.open("helloword.txt");
    if(inp == NULL){
        cout<<"Error opening file !";
        return 1;
    }
    ofstream outputfile;
    outputfile.open("byeworld.txt");
    if(outputfile == NULL){
        cout<<"Error opening file !";
        return 1;
    }
    string line;
    while(inp){
        cout<<"Writing to byeworld.txt....";
        getline(inp,line);
        outputfile<<line;
    }
    cout<<"Writing finished !";
    inp.close();
    outputfile.close();



    return 0;
}