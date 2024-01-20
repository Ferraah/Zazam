
#include "Sequencer.hpp"

/**
 * Sequence a song from a WAV or AIFF file.
 * @param path WAV or AIFF audio file
 * @param save_hash if true, save to the location specified in Sequencer.hpp
 * @returns A Song object with title and hash
*/
void Sequencer::sequence_from_path(std::string &path, Song &result, bool save_hash = true) const{

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
        zazam::utils::save_real_vector(result.hash, "../dataset/hash/"+base_filename+".txt");

    // Write spectrogram matrix to file
    /*
    unsigned int file_index = 0;
    spectrograms[0].write_to_file("../dataset/txt/"+ base_filename+ ".txt");
    file_index++;
    */

    result.title = path;
}
