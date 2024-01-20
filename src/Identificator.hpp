#ifndef IDENTIFICATOR_HPP
#define IDENTIFICATOR_HPP

#include "../utils/ZazamDataTypes.hpp"
#include "../FFT-Carra-Ferrario-Gentile/ffft/src/fftcore/utils/MtxFilesIO.hpp"
#include "../utils/Utils.hpp"
#include <vector>

using namespace zazam;
class Identificator{

    public:
        Identificator(){};
        void identify(Vector_ui &, Song&) const;
    private:
        void normalize_and_round(Vector_ui &) const;
        void fill_matches_vector(const Vector_ui &, const Vector_ui &, std::vector<int> &) const;
        void mode_of_vector(const std::vector<int> &, int &, int &) const;
        std::string hash_dataset_path = "../dataset/hash";
};

#endif