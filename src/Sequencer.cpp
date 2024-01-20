
#include "Sequencer.hpp"



void Sequencer::sequence_from_path(std::string &path, Song &result, bool save_hash = true){

    SignalTensor song_tensor(path);
    Matrix_d song_matrix;

    FFTSolver<1, double> solver(std::make_unique<OmpFFT<double>>());
    int sequence_window = 1 << 11;
    
    spectrogram::SpectrogramGenerator<fftwFFT<>> spectrogram_generator;

    spectrogram_generator.load_audio(song_tensor,sequence_window, sequence_window, false);

    spectrogram_generator.compute_spectrogram();

    auto spectrograms = spectrogram_generator.get_spectrograms();
    
    song_matrix = spectrograms.at(0).get_tensor();

    unsigned int file_index = 0;
    std::string base_filename = path.substr(path.find_last_of("/\\") + 1);
    spectrograms[0].write_to_file("../dataset/txt/"+ base_filename+ ".txt");
    file_index++;

    HashGenerator hash_generator;

    std::cout << "Rows: " << song_matrix.dimension(0); 
    std::cout << "Cols: " << song_matrix.dimension(1); 
    hash_generator.generate(song_matrix, result.hash, true);

    if(save_hash)
        zazam::utils::save_real_vector(result.hash, "../dataset/hash/"+base_filename+".txt");
    assert(result.hash.size() > 0);
    result.title = path;
    
}
