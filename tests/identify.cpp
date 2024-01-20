#include "../src/HashGenerator.hpp"
#include "../src/Identificator.hpp"
#include "../src/Sequencer.hpp"
#include "../utils/MusicTensor.hpp"

#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

int main(){
    Identificator identificator;
    Sequencer sequencer;
    Song sample,result;
    std::string sample_path = "../dataset/samples/Burn_5s_noise.wav";

    sequencer.sequence_from_path(sample_path, sample, false);

    identificator.identify(sample.hash, result);
    std:cout << "Result: " << result.title << std::endl;
}