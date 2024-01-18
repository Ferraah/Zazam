#ifndef ZAZAM_DATATYPES_HPP
#define ZAZAM_DATATYPES_HPP

#include <unsupported/Eigen/CXX11/Tensor>
#include <utility>

namespace zazam{

    template<typename ScalarType>    
    using Vector = Eigen::Tensor<ScalarType, 1>;
    template<typename ScalarType>    
    using Matrix = Eigen::Tensor<ScalarType, 2>;

    using Matrix_d = Matrix<double>;
    using Vector_d = Vector<double>;

    using Vector_ui = Vector<unsigned int>;


    struct Song{
        std::string title;
        Vector_ui hash;
    };

    // The range of frequencies to subdivide 
    static const std::pair<int, int> KeyPointsRange = {2,18};

    // The number of key points to use
    static const int KeyPointsNumber = 4;
}

#endif