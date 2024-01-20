#include "../src/HashGenerator.hpp"
#include "../src/Identificator.hpp"
#include "../src/Sequencer.hpp"
#include "../utils/MusicTensor.hpp"

#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

int main(){

    Sequencer sequencer;
    Song song ;

    std::string wav_path = "../dataset/wav";
    for (const auto & entry : std::filesystem::directory_iterator(wav_path)){
        std::cout << entry.path() << std::endl;
        std::string path = entry.path().string();
        sequencer.sequence_from_path(path, song, true);
    }
}