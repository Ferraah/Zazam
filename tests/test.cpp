#include "../src/HashGenerator.hpp"
#include "../src/Identificator.hpp"

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
            input(y,x) = x*y;
        }
    }
    hash_generator.generate(input, hash);
    cout << hash << endl;


    // Fake Hash
    Vector_ui fake_hash(16);
    fake_hash.setConstant(0);
    fake_hash[0] = 4000;
    fake_hash[4] = 5000;
    fake_hash[8] = 6000;
    fake_hash[9] = 6000;
    fake_hash[11] = 5000;
    fake_hash[14] = 6000;
    Song result;
    Identificator identificator;

    identificator.identify(fake_hash, result);
    
}