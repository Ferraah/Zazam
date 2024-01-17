#ifndef ZAZAM_DATATYPES_HPP
#define ZAZAM_DATATYPES_HPP

#include <unsupported/Eigen/CXX11/Tensor>
#include <utility>

namespace zazam{
    
    using Vector = Eigen::Tensor<double, 1>;
    using Matrix = Eigen::Tensor<double, 2>;

    struct SongHash{
        std::string title;
        Vector hash;
    };

    // The range of frequencies to subdivide 
    std::pair<int, int> KeyPointsRange = {2, 18};

    // The number of key points to use
    int KeyPointsNumber = 4;
}

#endif