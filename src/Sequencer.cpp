
#include "Sequencer.hpp"

void Sequencer::sequence_from_path(const std::string &path, Song &result, bool save_hash) const{

    if(save_hash){
        assert(!output_path.empty() && "The hashes saving directory has not been declared.");
    }

    // Initialize the tensor wrapper which will load the file
    SignalTensor song_tensor(path);
    // This matrix will contain the spectrogram
    Matrix_d song_matrix;

    // Initialize the FFFT solver
    FFTSolver<1, double> solver(std::make_unique<OmpFFT<double>>());
    int sequence_window = 1 << 11;
    
    // Calculate spectogram
    spectrogram::SpectrogramGenerator<fftwFFT<>> spectrogram_generator;
    spectrogram_generator.load_audio(song_tensor, sequence_window, sequence_window);
    spectrogram_generator.compute_spectrogram();
    auto spectrograms = spectrogram_generator.get_spectrograms(); 
    song_matrix = spectrograms.at(0).get_tensor(); // We calculate only one spectrogram

    // Create hash from spectrogram
    HashGenerator hash_generator;
    hash_generator.generate(song_matrix, result.hash, true);

    // --- Output saving ---

    std::string base_filename = path.substr(path.find_last_of("/\\") + 1);

    if(save_hash)
        zazam::utils::save_real_vector(result.hash, output_path+"/"+base_filename+".txt");

    // Write spectrogram matrix to file
    /*
    unsigned int file_index = 0;
    spectrograms[0].write_to_file("../dataset/txt/"+ base_filename+ ".txt");
    file_index++;
    */

    result.title = path;
}
