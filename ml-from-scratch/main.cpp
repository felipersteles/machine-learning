//
//  main.cpp
//  cnn-from-scratch
//
//  Created by Felipe Teles on 08/07/24.
//

#include <iostream>

#include "data.hpp"
#include "data_handler.hpp"

int main(int argc, const char * argv[]) {
    // Setup Dataset
    DataHandler *data_handler = new DataHandler();
    data_handler->read_feature_vector("/Users/felipeteles/Development/ufma/cnn-from-scratch/mnist/train-images-idx3-ubyte");
    data_handler->read_feature_labels("/Users/felipeteles/Development/ufma/cnn-from-scratch/mnist/train-labels-idx1-ubyte");
    
    data_handler->split_data();
    data_handler->count_classes();
    
    return 0;
}
