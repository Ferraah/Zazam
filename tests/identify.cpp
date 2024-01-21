#include "../src/HashGenerator.hpp"
#include "../src/Identificator.hpp"
#include "../src/Sequencer.hpp"
#include "../utils/MusicTensor.hpp"

#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

int main(){
    Identificator identificator("../dataset/hashes");
    Sequencer sequencer;
    Song sample,result;
    std::string sample_path = "../dataset/samples/21 Savage - redrum_5s.wav";


    sequencer.sequence_from_path(sample_path, sample, false);

    identificator.identify(sample.hash, result);

    std::cout << "============================================================" << std::endl;
    std:cout << "Result: " << result.title << std::endl;
    std::cout << "============================================================" << std::endl;
}