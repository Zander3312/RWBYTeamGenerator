#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

string generateBase(vector<char>& firstLetters, vector<char>& lastLetters, int count);
void permute(string& currentTitle, int l, int r, vector<string>& titleList);

int main()
{
    int numPeople{0};
    string currentName = "";
    vector<char> firstLetters;
    vector<char> lastLetters;

    cout << "How many people? ";
    cin >> numPeople;

    if (numPeople < 1) {
        cerr << "Error: Number of people must be a positive integer.\nPress enter to continue...";
        cin.get();
        cin.get();
        return 0;
    }

    for (int i = 0; i < numPeople; i++) {
        cout << "Enter person " << i + 1 << "'s first name (first initial also works):";
        cin >> currentName;
        firstLetters.push_back(currentName[0]);
    }

    for (int i = 0; i < numPeople; i++) {
        cout << "Enter person " << i + 1 << "'s last name (last initial also works):";
        cin >> currentName;
        lastLetters.push_back(currentName[0]);
    }

    //Logic for writing combinations to output file goes here
    ofstream outFile; //Begin handling output file
    outFile.open("RWBYoutput.txt");
    if (!outFile) //Checks if given output file exists
    {
        cerr << "Error creating output file.\nPress enter to continue...";
        cin.get();
        cin.get();
        return 0;
    }

    string currentTitle = "";
    vector<string> titleList;
    
    for (int i = 0; i < pow(2,numPeople); i++) {
        currentTitle = generateBase(firstLetters, lastLetters, i);
        
        permute(currentTitle, 0, numPeople - 1, titleList);
    }

    int numTitles{0};
    for (int i = 0; i < titleList.size(); i++) {
        outFile << titleList[i] << endl;
        numTitles++;
    }

    cout << numTitles << " different combinations of names written to output.txt.\nPress enter to exit program.";
    cin.get();
    cin.get();
}

void permute(string& currentTitle, int l, int r, vector<string>& titleList) {
    if (l == r) {
        titleList.push_back(currentTitle);
    } else {
        for (int i = l; i <= r; i++) {
            swap(currentTitle[l], currentTitle[i]);
            permute(currentTitle, l + 1, r, titleList);
            swap(currentTitle[l], currentTitle[i]);
        }
    }
}

string generateBase(vector<char>& firstLetters, vector<char>& lastLetters, int count) {
    string base = "";
    string binaryCount = "";
    int binDigit = 2;

    while (count > 0) {
        binDigit = count % 2;
        if (binDigit == 1) {
            binaryCount.insert(0, "1");
        } else {
            binaryCount.insert(0, "0");
        }
        
        count = count / 2;
    }

    while (binaryCount.size() != firstLetters.size()) {
        binaryCount.insert(0, "0");
    }

    for (int i = 0; i < firstLetters.size(); i++) {
        if (binaryCount.at(i) == '0') {
            base.push_back(firstLetters[i]);
        }
        else {
            base.push_back(lastLetters[i]);
        }
    }

    return base;
}