#include "../src/HashGenerator.hpp"
#include "../src/Identificator.hpp"
#include "../src/Sequencer.hpp"
#include "../utils/MusicTensor.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main(){
    /*
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
    Song result;
    Identificator identificator;

    identificator.identify(fake_hash, result);
    
    */  
    Sequencer sequencer;
    Song song;
    string path = "../AudioFile/examples/song.wav";
    //SignalTensor signal(path);
    sequencer.sequence_from_path(path ,song);
    
}