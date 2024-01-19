
#include "Sequencer.hpp"



void Sequencer::sequence_from_path(std::string &path, Song &result){

    SignalTensor song_tensor(path);
    Matrix_d song_matrix;
    e_index a=0, b = 44100;
    std::cout << song_tensor.get_audio_file().getNumSamplesPerChannel()/1024;
    //song_tensor.slice_tensor(a,b);

    FFTSolver<1, double> solver(std::make_unique<OmpFFT<double>>());
    int sequence_window = 1024;
    //solver.spectogram(song_matrix, song_tensor, sequence_window)
    //song_tensor.normalize();
    spectrogram::SpectrogramGenerator<fftwFFT<>> spectrogram_generator;
    spectrogram_generator.load_audio(song_tensor,sequence_window, 64, true);

    spectrogram_generator.compute_spectrogram();

    auto spectrograms = spectrogram_generator.get_spectrograms();
    
    auto tmp = spectrograms.at(0);

    unsigned int file_index = 0;
    for(auto &spectrogram : spectrograms){
        spectrogram.write_to_file("output/"+std::to_string(file_index) + ".txt");
        file_index++;
    }

    //HashGenerator hash_generator;
    //hash_generator.generate(song_matrix, result.hash);
    result.title = path;
    
}
