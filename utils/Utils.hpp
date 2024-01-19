#ifndef UTILS_HPP
#define UTILS_HPP

#include "ZazamDataTypes.hpp"
#include <algorithm>
#include <iostream>

namespace zazam{
    namespace utils {

        // @Todo: ADD ASSERTS
        template<typename Scalar> 
        int find_max_element_index(const Vector<Scalar> &input, Scalar &max_element){
            auto max = std::max_element(input.data(), input.data()+input.size());
            return std::distance(input.data(), max);
        }
        
        template<typename Scalar> 
        int find_max_element_index(const Vector<Scalar> &input){
            auto max = std::max_element(input.data(), input.data()+input.size());
            return std::distance(input.data(), max);
        }
        
        template<typename Scalar> 
        int find_max_element_index(const std::vector<Scalar> &input, Scalar &max_element){
            auto max = std::max_element(input.begin(), input.end()); 
            return std::distance(input.begin(), max);
        }
        
        template<typename Scalar> 
        int find_max_element_index(const std::vector<Scalar> &input){
            auto max = std::max_element(input.begin(), input.end());
            return std::distance(input.begin(), max);
        }

        template<typename T>
        void print_std_vector(const std::vector<T> &input){
            std::cout << "[";
            for(int i=0; i<input.size(); i++){
                std::cout << " " << input[i] << ",";
            }
            std::cout << "]" <<std::endl;
        }
        template<typename T>
        void std_to_eigen_vector(std::vector<T> &vector, Vector<T> &eigen_vector, size_t begin, e_index dimension){
            for(e_index i=0; i<dimension; i++){
                eigen_vector(i) = vector[begin+i];
            } 
        } 
    }
} 

#endif