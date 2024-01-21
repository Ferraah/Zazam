#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "../../AudioFile/AudioFile.h"
#include "utils/ZazamDataTypes.hpp"
#include "utils/MusicTensor.hpp"
#include "utils/Utils.hpp"
#include "../../FFT-Carra-Ferrario-Gentile/ffft/include/ffft.hpp"
#include "../../FFT-Carra-Ferrario-Gentile/ffft/src/spectrogram/Spectrogram.hpp"
#include "../../FFT-Carra-Ferrario-Gentile/ffft/src/spectrogram/SpectrogramDataTypes.hpp"
#include "HashGenerator.hpp"

#include <memory>
namespace zazamcore{

    /**
     * @brief Sequencer class takes care of sequencing audio data into hashes vector
     * through operations on its spectrogram.
     *
    */
    class Sequencer 
    {
        public:
            /**
             * @brief Contructor for Sequencer.
             * @param _output_path The path of the directory in which the sequenced songs 
             * hashes will be saved.
            */
            Sequencer(std::string _output_path):
                output_path(_output_path)
            {};
            /**
             * Constructor for Sequencer.
            */
            Sequencer(){};


            /**
             * @brief Sequence a song from a WAV or AIFF file.
             * @param path WAV or AIFF audio file path
             * @param result The resulting Song object
             * @param save_hash If true, save to the location specified in Sequencer.hpp
             * @returns A Song object with title and hash
            */
            void sequence_from_path(const std::string &path, Song &resukt, bool save_hash = true) const;
        private:
            /**
             * @brief Path of the directory where the sequenced songs hashes will be saved. 
            */
            std::string output_path; 
    };
}
#endif