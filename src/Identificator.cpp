#include "Identificator.hpp"
#include <iostream>


std::vector<Vector_ui> music_hashes;

void Identificator::identify(Vector_ui &sample_hash, Song &result){

   // From database

   Vector_ui fake_hash(8);
   // Add fake song hashes
   for(int i=0; i<8; i++){
      music_hashes.push_back(fake_hash.setConstant(i*1000));
   }



   std::vector<double> all_ratios; 
   std::vector<int> matches; 
   int mode, n_occurrences;
   double ratio;
   
   normalize_and_round(sample_hash);
   for(auto &music_hash: music_hashes){
      matches.clear();
      normalize_and_round(music_hash); 
      fill_matches_vector(music_hash, sample_hash, matches);
      
      if(matches.size() == 0){
         std::cout << "No match" << std::endl;
         ratio = 0; 
      }else{
         mode_of_vector(matches, mode, n_occurrences);
         ratio = n_occurrences/(double)sample_hash.size();
         std::cout << "mode: " << mode << ", no: " << n_occurrences << std::endl;
      }
      //utils::print_std_vector(matches);
      all_ratios.push_back(ratio);
   }

   result.title = "test result";
   //result.hash = music_hashes[find_max_element_index(all_ratios)];   
}


void Identificator::normalize_and_round(Vector_ui &hash){

   double normalized_value;
   for(int i=0; i<hash.size(); i++){
      normalized_value = hash(i) / 1000;
      hash(i) = std::round(normalized_value);
   }
}

void Identificator::fill_matches_vector(Vector_ui &music, Vector_ui &sample, std::vector<int> &matches_vector){

   for(int i=0; i<sample.size(); i++){
      for(int j=0; j<music.size(); j++){
         if(music(j) == sample(i)){
            matches_vector.push_back( j - i );
         }
      }
   }

}

void Identificator::mode_of_vector(const std::vector<int> &matches_vector, int &mode, int &max_occurrences){
   
   assert(matches_vector.size() > 0);

   std::unordered_map<int, int> frequencyMap;

   // Count the frequency of each number in the vector
   for (int num : matches_vector) {
      frequencyMap[num]++;
   }

   // Find the mode (number with the highest frequency)
   mode = matches_vector[0]; // Initialize mode with the first element
   max_occurrences = frequencyMap[mode];

   for (const auto& entry : frequencyMap) {
      if (entry.second > max_occurrences) {
         mode = entry.first;
         max_occurrences = entry.second;
      }
   }
   
}