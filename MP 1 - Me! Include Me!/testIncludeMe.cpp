#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std; 

void readInclude(string); 
bool compareInclude(string); 



int main(){
  string fileName; 
 

  cin>>fileName; 

  readInclude(fileName);

  return 0; 
}


bool compareInclude(string newFile) {
    static vector<string> header;  // Static vector retains its value between calls

    if (header.empty()) {
        header.push_back(newFile);
        return true;
    } else {
        for (int i = 0; i < header.size(); i++) {
            // cout << "header: " << header[i] << endl;

            if (header[i] == newFile) {
                // cout << "error: " << newFile << endl;
                return false;
            }
        }

        // cout << "test1" << endl;
        header.push_back(newFile);
        
        // for (int i = 0; i < header.size(); i++) {
        //     cout << "header2: " << header[i] << endl;
        // }

        return true;
    }
}



void readInclude(string file){
  ifstream reader(file); 
 

  if(reader.is_open()){
    string line, str; 
    bool flag = false;
    while(getline(reader, line)){     
      stringstream ss(line); 
      ss>>str; //it will eliminate the include since it extracts the first whitespace-separated token


      if(str.compare("#include")==0){ //if a line has no "include", then it will not enter in this part of the code
        ss>>str;
        string newFile = str.substr(1, str.length()-2); 
        // cout<<"included file: "<<newFile<<endl;

        if(compareInclude(newFile) == true)
           readInclude(newFile);  
       
      }
      else{
        cout << line<<endl; //backtracks printing
      }
    }

  }

  reader.close();
}