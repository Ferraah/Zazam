#include "../src/HashGenerator.hpp"
#include <iostream>

using namespace std;

int main(){
    HashGenerator hash_generator;

    // N rows, M columns
    int n = 3 , m = 20; 
    Matrix_d input(n,m);
    Vector_ui hash;
    for(int y=0; y<n; y++){
        for(int x=0; x<m; x++){
            input(y,x) = x;
        }
    }
    hash_generator.generate(input, hash);
    cout << hash;

    
}