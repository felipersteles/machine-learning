//
//  main.cpp
//  machine learning from scratch
//
//  Created by Felipe Teles on 08/07/24.
//

#include <iostream>

#include "data.hpp"
#include "data_handler.hpp"
#include "knn.hpp"

int main(int argc, const char * argv[]) {
    // Setup Dataset
    DataHandler *data_handler = new DataHandler();
    data_handler->read_feature_vector("/Users/felipeteles/Development/ufma/cnn-from-scratch/mnist/train-images-idx3-ubyte");
    data_handler->read_feature_labels("/Users/felipeteles/Development/ufma/cnn-from-scratch/mnist/train-labels-idx1-ubyte");
    
    data_handler->split_data();
    data_handler->count_classes();
    
    KNN* knn = new KNN();
    knn->set_training_data(data_handler->get_training_data());
    knn->set_test_data(data_handler->get_test_data());
    knn->set_validation_data(data_handler->get_validation_data());
    
    double performance = 0;
    double best_perfomance = 0;
    int best_k;
    
    for(int i = 1; i <= 4; i++){
        if (i == 1) {
            knn->set_k(i);
            performance = knn->validate_performance();
            best_perfomance = performance;
        }else{
            knn->set_k(i);
            performance = knn->validate_performance();
            best_perfomance = performance;
            
            if(performance > best_perfomance){
                best_perfomance = performance;
                best_k = i;
            }
        }
    }
    
    knn->set_k(best_k);
    knn->test_performance();
    
    return 0;
}
