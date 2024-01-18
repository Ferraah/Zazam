#ifndef HASHGENERATOR_HPP
#define HASHGENERATOR_HPP

#include "../utils/ZazamDataTypes.hpp"
#include "../utils/Utils.hpp"

using namespace zazam; 
class HashGenerator{

    public:
        HashGenerator(){};
        void generate(Matrix_d& spectrogram, Vector_ui& result) ;
    private:
        void reduce_spectrogram(Matrix_d& spectrogram, Matrix_d& key_points_matrix);
        void reduce_vector(const Vector_d& input, Vector_d& output);
};

#endif