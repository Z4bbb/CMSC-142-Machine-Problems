#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    string myText;
    string fileName; 
    cin >> fileName;

    // Use the fileName variable to open the file
    ifstream MyReadFile(fileName);

    // Check if the file is open
    if (!MyReadFile.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        cout << myText << endl;
    }

    // Close the file
    MyReadFile.close();

    return 0;
}
