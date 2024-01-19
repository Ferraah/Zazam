#include "MusicTensor.hpp"


SignalTensor::SignalTensor(std::string &path){
   load_time_signal(path);
}

SignalTensor::SignalTensor(std::vector<double> &vector){
   get_tensor() = Vector<std::complex<double>>(vector.size());
   utils::std_to_complex_eigen_vector(vector, get_tensor(), 0, vector.size());
}

void SignalTensor::load_time_signal(std::string &path){

   // Load file form path
   bool loadedOK = audio_file.load(path);
   assert(loadedOK);

   // Cut to mono
   convert_to_mono();

   get_tensor() = Vector<std::complex<double>>(audio_file.getNumSamplesPerChannel());
   // Copy samples into the tensor 
   zazam::utils::std_to_complex_eigen_vector(audio_file.samples[0], get_tensor(), 0, audio_file.getNumSamplesPerChannel());
}

void SignalTensor::slice_tensor(e_index &begin, e_index &dimension){
   get_tensor() = Vector<std::complex<double>>(dimension); 
   zazam::utils::std_to_complex_eigen_vector(audio_file.samples[0], get_tensor(), begin, dimension);
}

void SignalTensor::convert_to_mono(){
   // Only if is stereo
   if(audio_file.getNumChannels()==2){
      for(auto &s : audio_file.samples){
         s[0] = (s[0] + s[1])/2;
      }
      audio_file.setNumChannels(1);
   }
}

void SignalTensor::normalize(){
   get_tensor() /= get_tensor().constant(get_tensor().size()); 
}