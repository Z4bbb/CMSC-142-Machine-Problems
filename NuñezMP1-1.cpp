#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <regex>
using namespace std; 

void tokenize(const string); 

string removeSpace(string str){
    regex leading_whitespace("^\\s+");
    string spaceStr = regex_replace(str, leading_whitespace, "");
    
    return spaceStr;
}

void ifDisplay(string temp){
    vector<string>ifTokens;
    cout<<"if:"<<endl; 
    regex rgx("[^();]+"); 

    auto begin = sregex_iterator(temp.begin(), temp.end(), rgx);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        ifTokens.push_back(match.str());
    }    
    cout<<"condition: "<<ifTokens[1]<<endl; 
    cout<<"if statements:"<<endl; 
    for(int j = 2; j < ifTokens.size(); j++){
        string temp = ifTokens[j]; 
        cout<<removeSpace(temp)<<endl;; 
    }
}

void forDisplay(vector<string>tokens){  
    cout<<"for:"<<endl; 
    vector<string>forTokens;
    string forString = ""; 
    
    string tempStr = tokens[0];
    for(int i = 1; i < tokens.size(); i++){
        forString += tokens[i];
    }
     
    regex rgx("[^()]+"); 
    auto begin = sregex_iterator(tempStr.begin(), tempStr.end(), rgx);
    auto end = sregex_iterator();
     
    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        
        string tempFor = match.str(); 
        string strFor = removeSpace(tempFor); 
        forTokens.push_back(strFor);

    } 
    string tempFor = forTokens[1]; 
    regex component_pattern("[^;]+");
    auto components_begin = sregex_iterator(tempFor.begin(), tempFor.end(), component_pattern);
    auto components_end = sregex_iterator();
    
    int ctr = 0; 
    for (sregex_iterator i = components_begin; i != components_end; ++i) {
        smatch match = *i;
        string initStr = match.str(); 
        if(ctr == 0){
            cout<<"initializer: "<<removeSpace(initStr)<< endl;      
        }
        else if(ctr == 1){
            cout<<"condition: "<<removeSpace(initStr)<< endl;       
        }
        else if(ctr == 2){
            cout<<"update: "<<removeSpace(initStr)<< endl;          
        }
        ctr++; 
    }
    cout<<"for statements:"<<endl; 

    vector<string>sepStr; 
    regex rgxColon("[^}]+");
    auto for_begin = sregex_iterator(forString.begin(), forString.end(), rgxColon);
    auto for_end = sregex_iterator();
    for (sregex_iterator i = for_begin; i != for_end; ++i) {
        smatch match = *i;
        sepStr.push_back(removeSpace(match.str()));
    } 
    
    bool flag = false; 
    bool statementFlag = false; 
    for(int j = 0; j < sepStr.size(); j++){
        if(sepStr[j].find("if") != string::npos){
            string temp = sepStr[j]; 
            vector<string>ifTokens;
            cout<<"if:"<<endl; 
            regex rgx("[^();]+"); 

            auto begin = sregex_iterator(temp.begin(), temp.end(), rgx);
            auto end = sregex_iterator();
            
            for (sregex_iterator i = begin; i != end; ++i) {
                smatch match = *i;
                ifTokens.push_back(match.str());
            }    
            cout<<"condition: "<<ifTokens[1]<<endl; 
            cout<<"if statements:"<<endl; 
            for(int j = 2; j < ifTokens.size(); j++){
                string temp = ifTokens[j]; 
                cout<<removeSpace(temp);
                if(j != ifTokens.size()-1)
                    cout<<endl; 
            }
            flag = true; 
        }
        else if(sepStr[j].find("else") != string::npos){
            string temp = sepStr[j]; 
            vector<string>elseStr; 
            cout<<"else statements:"<<endl; 
            regex rgx("[^{]+");
            
            auto begin = sregex_iterator(temp.begin(), temp.end(), rgx);
            auto end = sregex_iterator();
        
            for (sregex_iterator i = begin; i != end; ++i) {
                smatch match = *i;
                elseStr.push_back(match.str()); 
            }  
            for(int i = 1; i < elseStr.size(); i++){
                cout<<removeSpace(elseStr[i])<<endl; 
            }
            flag = true; 
        }
        else if(statementFlag==false){
            if(flag)
                cout<<"for statements continued:"<<endl; 
                
            string tempStr = sepStr[j]; 
            vector<string>statementStr; 
            regex rgx("[^;]+");
            auto stateBegin = sregex_iterator(tempStr.begin(), tempStr.end(), rgx);
            auto stateEnd = sregex_iterator();

            for (sregex_iterator i = stateBegin; i != stateEnd; ++i) {
            smatch match = *i;
                cout<<removeSpace(match.str())<<endl; 
            }
            statementFlag = true; 
        }
        else if(statementFlag){
            cout<<"statements:"<<endl; 
            string tempStr = sepStr[j]; 
            vector<string>statementStr; 
            regex rgx("[^;]+");
            auto stateBegin = sregex_iterator(tempStr.begin(), tempStr.end(), rgx);
            auto stateEnd = sregex_iterator();

            for (sregex_iterator i = stateBegin; i != stateEnd; ++i) {
            smatch match = *i;
                cout<<removeSpace(match.str())<<endl; 
            }
        }
    }
}

void display(vector<string>tokens){
    int size = tokens.size(); 
    bool flag = false; 
    
    for(int i = 0; i < size; i++){
        string str = tokens[i];
        regex leading_whitespace("^\\s+");
        string temp = regex_replace(str, leading_whitespace, "");
        
        regex rgx("[^=>><<]+"); 
        if(regex_match(temp, rgx)) //for regular statements 
            continue;
        else if(temp.find("for") != string::npos){
            forDisplay(tokens); 
            break;
        }    
        else if(temp.find("if") != string::npos){ //for if
            ifDisplay(temp); 
            flag = false; 
        }
        else if(temp.find("else") != string::npos){
            vector<string>elseStr; //for if
            cout<<"else statements:"<<endl; 
            regex rgx("[^{]+");
            
            auto begin = sregex_iterator(temp.begin(), temp.end(), rgx);
            auto end = sregex_iterator();
        
            for (sregex_iterator i = begin; i != end; ++i) {
                smatch match = *i;
                elseStr.push_back(match.str()); 
            }  
            for(int i = 1; i < elseStr.size(); i++){
                    cout<<removeSpace(elseStr[i])<<endl; 
            }
            flag = true; 
        }
        else{
            if(!flag){
                cout<<"statements:"<<endl; 
                flag = true; 
            }
            cout<<temp<<endl; 
        }
    }
}

void tokenize(const string snippet) {
    vector<string> tokens;

    // Regex pattern to remove certain keywords (int, char)
    regex remove_pattern("\\b(?:int|char)\\b");

    // Remove matches by replacing them with an empty string
    string result = regex_replace(snippet, remove_pattern, "");

    // Clean up extra spaces 
    regex space_pattern("\\s+");
    result = regex_replace(result, space_pattern, " ");

    // Trim leading and trailing spaces 
    regex trim_pattern("^\\s+|\\s+$");
    result = regex_replace(result, trim_pattern, "");

    if (snippet.find("for") != string::npos) {
        regex rgx("[^{]+"); 
        auto begin = sregex_iterator(result.begin(), result.end(), rgx);
        auto end = sregex_iterator();

        for (sregex_iterator i = begin; i != end; ++i) {
            smatch match = *i;
            tokens.push_back(match.str());
        }
    } else {
        // Regex to split by commas and semicolons
        regex rgx("[^,;]+"); 
        auto begin = sregex_iterator(result.begin(), result.end(), rgx);
        auto end = sregex_iterator();

        for (sregex_iterator i = begin; i != end; ++i) {
            smatch match = *i;
            tokens.push_back(match.str());
        }
    }
    display(tokens);
}

int main() {
    int line;
    cin >> line;
    cin.ignore(); 
    string input;
    string snippet = "";
    int ctr = 0;

    while (ctr < line) {
        getline(cin, input);
        snippet += input;
        ctr++;
    }

    tokenize(snippet);
    return 0;
}
