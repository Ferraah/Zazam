#ifndef MUSICTENSOR_HPP
#define MUSICTENSOR_HPP

#include "../FFT-Carra-Ferrario-Gentile/ffft/src/fftcore/Tensor/TensorFFTBase.hpp"
#include "Utils.hpp"
#include "ZazamDataTypes.hpp"
#include "../AudioFile/AudioFile.h"
#include <string>

using namespace zazam;

class SignalTensor: public fftcore::TensorFFTBase<double, 1>{
    public:
        SignalTensor(std::string &);

        SignalTensor(std::vector<double> &);

        void load_time_signal(std::string &path);
        void slice_tensor(e_index &, e_index &);        
        AudioFile<double> get_audio_file(){
            return audio_file;
        };
    private:
        AudioFile<double> audio_file; 
        void convert_to_mono();
}; 

#endif