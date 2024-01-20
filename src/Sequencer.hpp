#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "../AudioFile/AudioFile.h"
#include "../utils/ZazamDataTypes.hpp"
#include "../utils/MusicTensor.hpp"
#include "../utils/Utils.hpp"
#include "../FFT-Carra-Ferrario-Gentile/ffft/include/ffft.hpp"
#include "../FFT-Carra-Ferrario-Gentile/ffft/src/spectrogram/Spectrogram.hpp"
#include "../FFT-Carra-Ferrario-Gentile/ffft/src/spectrogram/SpectrogramDataTypes.hpp"
#include "HashGenerator.hpp"

#include <memory>

using namespace zazam;
using namespace fftcore;

class Sequencer 
{
    public:
        Sequencer(){};
        void sequence_from_path(std::string &, Song &, bool) const;
    private:
        std::string output_path = "../dataset/hash";
};
#endif