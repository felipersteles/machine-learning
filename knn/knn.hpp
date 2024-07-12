//
//  knn.hpp
//  ml-from-scratch
//
//  Created by Felipe Teles on 11/07/24.
//

#ifndef knn_hpp
#define knn_hpp

#include <stdio.h>
#include <vector>
#include "data.hpp"

class KNN{
    int k;
    
    std::vector<Data *> *neighbors;
    std::vector<Data *> *training_data;
    std::vector<Data *> *test_data;
    std::vector<Data *> *validation_data;
    
public:
    KNN(int);
    KNN();
    ~KNN();
    
    void find_knearest(Data *query_point);
    void set_training_data(std::vector<Data *> *vect);
    void set_test_data(std::vector<Data *> *vect);
    void set_validation_data(std::vector<Data *> *vect);
    void set_k(int val);
    
    int predict();
    double calculate_distance(Data *query_point, Data *input);
    double validate_performance();
    double test_performance();
};

#endif /* knn_hpp */
