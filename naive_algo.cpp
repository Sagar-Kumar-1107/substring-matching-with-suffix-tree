#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;


void naive_search(string text, string pattern, int pattern_id) {
    int n = text.length();
    int m = pattern.length();
    vector<int> indices;

    int occurrences = 0;
    long long comparisons = 0;

    cout << "\nChecking Pattern P" << pattern_id << ": " << pattern << endl;
    cout << "Positions found: ";

    for (int i = 0; i <= n - m; i++) {
        
        int j;
        for (j = 0; j < m; j++) {
            comparisons++; 
            
            if (text[i + j] != pattern[j]) {
                break; 
            }
        }

        
        if (j == m) {
            indices.push_back(i); // Save the index
        }
    }

    if (indices.empty()) {
        cout << "   -> Not found in text." << endl;
    } 
    else {
        cout << "   -> Found at indices: ";
        for (int index : indices) {
            cout << index << " ";
        }
        cout << endl;
    }

    cout<<endl;
    
}

int main() {

    //auto start = high_resolution_clock::now();

    ifstream fin("input.txt");

    if (!fin.is_open()) {
        cout << "Error input.txt not found" << endl;
        return 1;
    }

    string dna_string;
    int r; 

    
    fin >> dna_string;

    
    if (!(fin >> r)) {
        cout << "Error reading number of patterns." << endl;
        return 0;
    }

    cout << "Length of Text T: " << dna_string.length() << endl;
    cout << "Number of Patterns: " << r << endl;

    
    for (int i = 0; i < r; i++) {
        string pat;
        fin >> pat;
        naive_search(dna_string, pat, i + 1);
    }

    fin.close();

    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds>(stop - start);
    //cout << "Time taken by naive algo: " << duration.count() << " microseconds" << endl;

    return 0;
}