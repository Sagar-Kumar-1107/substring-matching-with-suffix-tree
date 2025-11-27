#include <bits/stdc++.h>

using namespace std;

int main(){
    srand(time(0));
    ofstream fout("input.txt");

    int n = 10000;
    
    char bases[] = {'A', 'G', 'C', 'T'};
    string dna_string;

    for(int i = 0; i < n; i++) {
        dna_string += bases[rand() % 4];
    }

    int r = 10;

    fout << dna_string << endl;
    fout << r << endl;
    //string pattern[r];

    for(int i = 0; i < r; i++){ 
        
        string pat = "";
        
        
        int pat_len = 5 + (rand() %8 ); 

        
        for(int j = 0; j < pat_len; j++){
            pat += bases[rand() % 4];
        }

        fout << pat << endl; 
    }

    fout.close();



    return 0;
}