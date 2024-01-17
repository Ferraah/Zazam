#include "HashGenerator.hpp"
#include <iostream>
void HashGenerator::generate(Matrix& spectrogram, Vector& result) const{

}

/**
 * @brief For every row of the matrix, the function map the the initial spectrogram 
 * to a matrix with the max amplitude between certain ranges. ("Song Key Points")
 * 
*/

void HashGenerator::reduce_spectrogram(Matrix& spectrogram, Matrix& key_points_matrix) {
    Vector row;


    // Initialize new matrix
    key_points_matrix = Matrix(zazam::KeyPointsNumber, spectrogram.dimension(1));

    for(int y=0; y < spectrogram.dimension(1); y++ ){
        reduce_vector(spectrogram.chip(y,1), row);
        key_points_matrix.chip(y,1) = row;
    }
}

void HashGenerator::reduce_vector(const Vector& input, Vector& output){
    int range_dim =
        (zazam::KeyPointsRange.second - zazam::KeyPointsRange.first) / zazam::KeyPointsNumber;

    int offset = zazam::KeyPointsRange.first-1;
    Vector sub_vector(range_dim);

    output = Vector(zazam::KeyPointsNumber);
    for(int j=0; j<zazam::KeyPointsNumber; j++){
        
        // Create subvector
        for(int i=0; i<range_dim; i++){
           // std::cout << offset+i << std::endl;
            sub_vector(i) = input(offset+i);
        }

        // Finding the maximum of the sub-vector
        Eigen::Tensor<double, 0> MaxAsTensor = sub_vector.maximum();
        output(j) =  MaxAsTensor(0); 

        offset += range_dim; 
    } 
}