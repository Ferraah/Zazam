#include "MusicTensor.hpp"


template<typename Scalar>
MusicTensor<Scalar>::MusicTensor(const std::string &path){
   load_time_signal(path);
}

template<typename Scalar>
MusicTensor<Scalar>::MusicTensor(std::vector<Scalar> &vector){
   this.get_tensor() = Vector<std::complex<Scalar>>(vector.size());
   utils::std_to_complex_eigen_vector(vector, this.get_tensor(), 0, vector.size());
}

template<typename Scalar>
void MusicTensor<Scalar>::load_time_signal(const std::string &path){

   // Load file form path
   bool loadedOK = audio_file.load(path);
   assert(loadedOK);

   // Cut to mono
   convert_to_mono();

   this.get_tensor() = Vector<std::complex<Scalar>>(audio_file.getNumSamplesPerChannel());
   // Copy samples into the tensor 
   zazam::utils::std_to_complex_eigen_vector(audio_file.samples[0], this.get_tensor(), 0, audio_file.getNumSamplesPerChannel());
}

template<typename Scalar>
void MusicTensor<Scalar>::slice_tensor(e_index &begin, e_index &dimension){
   this.get_tensor() = Vector<std::complex<Scalar>>(dimension); 
   zazam::utils::std_to_complex_eigen_vector(audio_file.samples[0], this.get_tensor(), begin, dimension);
}

template<typename Scalar>
void MusicTensor<Scalar>::convert_to_mono(){
   // Only if is stereo
   if(audio_file.getNumChannels()==2){
      for(auto &s : audio_file.samples){
         s[0] = (s[0] + s[1])/2;
      }
      audio_file.setNumChannels(1);
   }
}

template<typename Scalar>
void MusicTensor<Scalar>::normalize(){
   this.get_tensor() /= this.get_tensor().constant(this.get_tensor().size()); 
}