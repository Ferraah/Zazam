#include "../src/HashGenerator.hpp"
#include <iostream>

using namespace std;

int main(){
    HashGenerator generator;

    // N rows, M columns
    int n = 3 , m = 20; 
    Matrix input(n,m), output;
    for(int y=0; y<n; y++){
        for(int x=0; x<m; x++){
            input(y,x) = x;
        }
    }

    generator.reduce_spectrogram(input, output);
    cout << output;

    
}