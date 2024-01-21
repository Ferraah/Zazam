#include "../src/core/HashGenerator.hpp"
#include "../src/core/Identificator.hpp"
#include "../src/core/Sequencer.hpp"

#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;
using namespace zazamcore;

int main(){
    Identificator identificator("../local_dataset/hashes");
    Sequencer sequencer;
    Song sample,result;
    std::string sample_path = "../local_dataset/samples/Burn_5s_noise.wav";


    sequencer.sequence_from_path(sample_path, sample, false);

    identificator.identify(sample.hash, result);

    std::cout << "============================================================" << std::endl;
    std:cout << "Result: " << result.title << std::endl;
    std::cout << "============================================================" << std::endl;
}