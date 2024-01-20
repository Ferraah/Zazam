#include "Identificator.hpp"
#include <iostream>
#include <filesystem>

using namespace std;
void Identificator::identify(Vector_ui &sample_hash, Song &result){

   std::vector<Vector_ui> music_hashes;
   std::vector<std::string> file_names;

   int count =0;
   Vector_ui tmp;
   for (const auto & entry : std::filesystem::directory_iterator(hash_dataset_path)){
      // Debugging limit
      if(count < 100) {
         // Load hash from file
         fftcore::utils::load_tensor_mtx(tmp, entry.path().string());
         music_hashes.push_back(tmp);
         // Load also the name of the file 
         file_names.push_back(entry.path().filename());
      }
      count++;
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
      all_ratios.push_back(ratio);
   }


   for(int i=0; i<all_ratios.size(); i++){
      std::cout << "i: " << i<< ":" <<all_ratios[i] << std::endl;
   }


   int res_i = utils::find_max_element_index(all_ratios);
   std::cout << "ID: " << res_i << std::endl; 
   result.hash = music_hashes[res_i];   
   result.title = file_names[res_i];
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