#include "HashGenerator.hpp"
#include <iostream>

void HashGenerator::generate(Matrix_d& spectrogram, Vector_ui& result) {

    Matrix_d key_points_matrix;
    e_index rows_number = spectrogram.dimension(0);
    e_index cols_number = zazam::KeyPointsNumber;
    
    // Create key points matrix
    std::cout << spectrogram<< std::endl;
    reduce_spectrogram(spectrogram, key_points_matrix);
    std::cout << key_points_matrix << std::endl;
    // Inizialize hash vector
    result = Vector_ui(rows_number);

    int hash;
    for(e_index i = 0; i<rows_number; i++){
        hash = cols_number; // Any other number other than 0 will work
        for(e_index j=1; j<cols_number; j++){
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
    e_index rows_number = spectrogram.dimension(0);

    // Initialize new matrix
    key_points_matrix = Matrix_d(rows_number, zazam::KeyPointsNumber);

    for(e_index y=0; y < rows_number; y++ ){

        reduce_vector(spectrogram.chip(y,0), row);
//        std::cout << spectrogram.chip(y, 0) << std::endl;
        key_points_matrix.chip(y,0) = row;

    }

}

void HashGenerator::reduce_vector(const Vector_d& input, Vector_d& output){
    e_index range_dim =
        (zazam::KeyPointsRange.second - zazam::KeyPointsRange.first) / zazam::KeyPointsNumber;

    e_index offset = zazam::KeyPointsRange.first-1;
    Vector_d sub_vector(range_dim);

    output = Vector_d(zazam::KeyPointsNumber);
    for(e_index j=0; j<zazam::KeyPointsNumber; j++){
        
        // Create subvector
        for(e_index i=0; i<range_dim; i++){
           // std::cout << offset+i << std::endl;
            sub_vector(i) = input(offset+i);
        }

        // Finding the index of the maximum of the sub-vector
        output(j) = offset + utils::find_max_element_index(sub_vector); 

        offset += range_dim; 
    } 
}

