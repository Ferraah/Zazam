#ifndef MUSICTENSOR_HPP
#define MUSICTENSOR_HPP

#include "../FFT-Carra-Ferrario-Gentile/ffft/src/fftcore/Tensor/TensorFFTBase.hpp"
#include "Utils.hpp"
#include "ZazamDataTypes.hpp"
#include "../AudioFile/AudioFile.h"
#include <string>
#include <complex>

using namespace zazam;
/**
 * @brief An implementation of the FFFT Tensor wrapper which takes care of the 
 * tensor loading from different sources.
*/
template<typename Scalar>
class MusicTensor: public fftcore::TensorFFTBase<std::complex<Scalar>, 1>{
    public:

        /**
         * @brief Constructor for MusicTensor.
         * @param path Path of the WAV or AIFF file 
        */
        MusicTensor(const std::string &path);

        /**
         * @brief Constructor for MusicTensor
         * @param vector Input vector to load 
        */
        MusicTensor(std::vector<Scalar> &vector);

        void load_time_signal(const std::string &path);

        void slice_tensor(e_index &, e_index &);        

        AudioFile<Scalar> get_audio_file(){
            return audio_file;
        };

        void normalize();

    private:
        AudioFile<Scalar> audio_file; 
        void convert_to_mono();
}; 

#endif