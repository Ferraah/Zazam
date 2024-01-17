#include "HashGenerator.hpp"
#include <iostream>

void HashGenerator::generate(Matrix_d& spectrogram, Vector_ui& result) {

    Matrix_d key_points_matrix;
    int rows_number = spectrogram.dimension(0);
    int cols_number = zazam::KeyPointsNumber;
    
    // Create key points matrix
    std::cout << spectrogram<< std::endl;
    reduce_spectrogram(spectrogram, key_points_matrix);
    std::cout << key_points_matrix << std::endl;
    // Inizialize hash vector
    result = Vector_ui(rows_number);

    int hash;
    for(int i=0; i<rows_number; i++){
        hash = cols_number; // Any other number other than 0 will work
        for(int j=0; j<cols_number; j++){
            hash = 17 * hash + key_points_matrix(i, j);
        }
        result(i) = hash;
    }
        
}

/**
 * @brief For every row of the matrix, the function map the the initial spectrogram 
 * to a matrix with the max amplitude between certain ranges. ("Song Key Points")
 * 
*/

void HashGenerator::reduce_spectrogram(Matrix_d& spectrogram, Matrix_d& key_points_matrix) {
    Vector_d row;
    int rows_number = spectrogram.dimension(0);

    // Initialize new matrix
    key_points_matrix = Matrix_d(rows_number, zazam::KeyPointsNumber);

    for(int y=0; y < rows_number; y++ ){

        reduce_vector(spectrogram.chip(y,0), row);
//        std::cout << spectrogram.chip(y, 0) << std::endl;
        key_points_matrix.chip(y,0) = row;

    }

}

void HashGenerator::reduce_vector(const Vector_d& input, Vector_d& output){
    int range_dim =
        (zazam::KeyPointsRange.second - zazam::KeyPointsRange.first) / zazam::KeyPointsNumber;

    int offset = zazam::KeyPointsRange.first-1;
    Vector_d sub_vector(range_dim);

    output = Vector_d(zazam::KeyPointsNumber);
    for(int j=0; j<zazam::KeyPointsNumber; j++){
        
        // Create subvector
        for(int i=0; i<range_dim; i++){
           // std::cout << offset+i << std::endl;
            sub_vector(i) = input(offset+i);
        }

        // Finding the index of the maximum of the sub-vector
        output(j) = offset +find_max_element_index(sub_vector); 

        offset += range_dim; 
    } 
}

int HashGenerator::find_max_element_index(const Vector_d& input){
    const double *max = std::max_element(input.data(), input.data()+input.size());
    return std::distance(input.data(), max);
}
