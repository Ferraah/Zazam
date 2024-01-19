
#include "Sequencer.hpp"



void Sequencer::sequence_from_path(std::string &path, Song &result){

    SignalTensor song_tensor(path);
    Matrix_d song_matrix;

    FFTSolver<1, double> solver(std::make_unique<OmpFFT<double>>());
    int sequence_window = 2048;
    //solver.spectogram(song_matrix, song_tensor, sequence_window)

    
    HashGenerator hash_generator;
    hash_generator.generate(song_matrix, result.hash);
    result.title = path;
}
