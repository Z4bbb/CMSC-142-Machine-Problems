#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

void readInclude(string); 

int main(){
  string fileName; 

  cin>>fileName; 

  readInclude(fileName);

  return 0; 
}


void readInclude(string file){
  ifstream reader(file); 
  // vector<string>includes; 

  if(reader.is_open()){
    string line, str; 
    while(getline(reader, line)){     
      stringstream ss(line); 
      ss>>str; //it will eliminate the include since it extracts the first whitespace-separated token


      if(str.compare("#include")==0){ //if a line has no "include", then it will not enter in this part of the code
        ss>>str;
        string newFile = str.substr(1, str.length()-2); 
        // cout<<"included file: "<<newFile<<endl; 
        readInclude(newFile); 
      }
      else{
         cout << line<<endl; //backtracks printing
      }
    }

  }

  reader.close();
}