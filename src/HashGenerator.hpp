#ifndef HASHGENERATOR_HPP
#define HASHGENERATOR_HPP

#include "../utils/ZazamDataTypes.hpp"

using namespace zazam; 
class HashGenerator{

    public:
        HashGenerator(){};
        void generate(Matrix& spectrogram, Vector& result) const;
    // private:
        void reduce_spectrogram(Matrix& spectrogram, Matrix& key_points_matrix);
        void reduce_vector(const Vector& input, Vector& output);
        
};

#endif