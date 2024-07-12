//
//  knn.cpp
//  ml-from-scratch
//
//  Created by Felipe Teles on 11/07/24.
//

#include <cmath>
#include <cstdint>
#include <limits>
#include <map>

#include "data_handler.hpp"
#include "knn.hpp"

KNN::KNN(int val){
    k  = val;
}
KNN::KNN(){
    
}
KNN::~KNN(){
    
}

void KNN::find_knearest(Data *query_point){
    neighbors = new std::vector<Data *>;
    double min = std::numeric_limits<double>::max();
    double previous_min = min;
    int index = 0;
    
    for(int i = 0; i < k; i++){
        if(i == 0){
            for(int j = 0; j < training_data->size(); j++){
                double distance = calculate_distance(query_point, training_data->at(j));
                training_data->at(j)->set_distance(distance);
                
                if(distance < min){
                    min = distance;
                    index = j;
                }
            }
            
            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }else{
            for (int j = 0; j < training_data->size(); j++) {
                double distance = training_data->at(j)->get_distance();
                if(distance > previous_min && distance < min){
                    min = distance;
                    index = j;
                }
            }
            
            neighbors->push_back(training_data->at(index));
            previous_min = min;
            min = std::numeric_limits<double>::max();
        }
    }
}
void KNN::set_training_data(std::vector<Data *> *vect){
    training_data = vect;
}
void KNN::set_test_data(std::vector<Data *> *vect){
    test_data = vect;
}
void KNN::set_validation_data(std::vector<Data *> *vect){
    validation_data = vect;
}
void KNN::set_k(int val){
    k = val;
}

int KNN::predict(){
    std::map<uint8_t, int> class_freq;
    for (int i = 0; i < neighbors->size(); i++) {
        if(class_freq.find(neighbors->at(i)->get_label()) == class_freq.end()){
            class_freq[neighbors->at(i)->get_label()] = 1;
        }else{
            class_freq[neighbors->at(i)->get_label()]++;
            
        }
    }
    
    int best = 0;
    int max = 0;
    for (auto kv: class_freq) {
        if (kv.second > max) {
            max = kv.second;
            best = kv.first;
        }
    }
    
    neighbors->clear();
    return best;
}

double KNN::calculate_distance(Data *query_point, Data *input){
    double distance = 0.0;
    if(query_point->get_feture_vector_size() != input->get_feture_vector_size()){
        printf("[Error]: Vector Size Mistmatch.\n");
        exit(1);
    }
    
//#ifdef EUCLID
    for (unsigned i = 0; i < query_point->get_feture_vector_size(); i++) {
        distance += pow(query_point->get_feature_vector()->at(i) - input->get_feature_vector()->at(i), 2);
        
    }
    distance = sqrt(distance);
//    printf("distance %f\n", distance);
    
    return distance;
//#elif defined MANHATTAN
//    // MANHATTAN DISTANCE
//#endif
}

double KNN::validate_performance(){
    double current_perfomance = 0;
    int count = 0;
    int data_index = 0;
    
    
    printf("--------------------------------------\n");
    for (Data* query_point: *validation_data) {
        find_knearest(query_point);
        
        int pred = predict();
        printf("[Debug]: Valitation missing %d\n", (int) validation_data->size() - data_index);
        printf("[Debug]: Pred: %d -> Query: %d\n", pred, query_point->get_label());
        if (pred == query_point->get_label()) {
            count++;
        }
        data_index++;
        printf("[Debug]: Current Performance = %.3f %%\n", ((double)count*100.0)/((double)data_index));
        printf("--------------------------------------\n");
    }
    printf("--------------------------------------\n");
    
    current_perfomance = ((double)count*100.0)/((double)validation_data->size());
    printf("[Info]: Validation Performance = %.3f %%\n", current_perfomance);
    
    return current_perfomance;
}
double KNN::test_performance(){
    double current_perfomance = 0;
    int count = 0;
    
    for (Data* query_point: *validation_data) {
        find_knearest(query_point);
        
        int pred = predict();
        if (pred == query_point->get_label()) {
            count++;
        }
    }
    
    current_perfomance = ((double)count*100.0)/((double)test_data->size());
    printf("[Info]: Tested Performance = %.3f %%\n", current_perfomance);
    
    return current_perfomance;
}
