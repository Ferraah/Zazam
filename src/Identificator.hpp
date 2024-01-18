#ifndef IDENTIFICATOR_HPP
#define IDENTIFICATOR_HPP

#include "../utils/ZazamDataTypes.hpp"
#include "../utils/Utils.hpp"
#include <vector>

using namespace zazam;
class Identificator{

    public:
        Identificator(){};
        void identify(Vector_ui &, Song &);
    private:
        void normalize_and_round(Vector_ui &);
        void fill_matches_vector(Vector_ui &, Vector_ui &, std::vector<int> &);
        void mode_of_vector(const std::vector<int> &, int &, int &);
};

#endif