#ifndef HASHGENERATOR_HPP
#define HASHGENERATOR_HPP

#include "../utils/ZazamDataTypes.hpp"
#include "../utils/Utils.hpp"

using namespace zazam; 
class HashGenerator{

    public:
        HashGenerator(){};
        void generate(Matrix_d& , Vector_ui& , bool) ;
    private:
        void reduce_spectrogram(Matrix_d& , Matrix_d&,bool);
        void reduce_vector(const Vector_d& , Vector_d& );
};

#endif