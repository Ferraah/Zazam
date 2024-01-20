#include "Identificator.hpp"
#include <iostream>
#include <filesystem>

/**
 * Identify a sample from a dataset of songs hases
 * @param sample_hash The hash of the sample
 * @return The Song object that has been identified by the algorithm.
 * 
*/
void Identificator::identify(Vector_ui &sample_hash, Song &result) const{


   // Dataset hashes and titles
   std::vector<Vector_ui> music_hashes;
   std::vector<std::string> file_names;

   // --- Load dataset --- 
   Vector_ui tmp;
   for (const auto & entry : std::filesystem::directory_iterator(hash_dataset_path)){
      // Load hash from file
      fftcore::utils::load_tensor_mtx(tmp, entry.path().string());
      music_hashes.push_back(tmp);
      // Load also the name of the file 
      file_names.push_back(entry.path().filename());
   }

   // --- Identification algorithm ---
   std::vector<double> all_ratios; 
   std::vector<int> matches; 
   int mode, n_occurrences;
   double ratio;

   // "Normalize" the sample hash 
   normalize_and_round(sample_hash);
   // For each sampled song in the dataset
   for(auto &music_hash: music_hashes){
      matches.clear();

      // "Normalize" the current song hash 
      normalize_and_round(music_hash); 
      // Fill the matches vector according to the algorithm specifications 
      fill_matches_vector(music_hash, sample_hash, matches);

      if(matches.size() == 0){
         ratio = 0; 
      }else{
         // If there is at least one match, calculate the ratio between matches
         // and total tries 

         // Find the element which appear the most in the matches vector
         mode_of_vector(matches, mode, n_occurrences);
         ratio = n_occurrences/(double)sample_hash.size();
      }
      
      // Save the song matching ratio
      all_ratios.push_back(ratio);
   }


   std::cout << "============================================================";
   for(int i=0; i<all_ratios.size(); i++){
      std::cout << "i: " << i << " | ratio: " << all_ratios[i] << std::endl;
   }

   int res_i = utils::find_max_element_index(all_ratios);
   std::cout << "ID: " << res_i << std::endl; 


   result.hash = music_hashes[res_i];   
   result.title = file_names[res_i];
}


void Identificator::normalize_and_round(Vector_ui &hash) const{

   double normalized_value;
   for(int i=0; i<hash.size(); i++){
      normalized_value = hash(i) / 1000;
      hash(i) = std::round(normalized_value);
   }
}

void Identificator::fill_matches_vector(const Vector_ui &music, const Vector_ui &sample, std::vector<int> &matches_vector) const{

   for(int i=0; i<sample.size(); i++){
      for(int j=0; j<music.size(); j++){
         if(music(j) == sample(i)){
            matches_vector.push_back( j - i );
         }
      }
   }

}

void Identificator::mode_of_vector(const std::vector<int> &matches_vector, int &mode, int &max_occurrences) const{
   
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