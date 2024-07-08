//
//  data_handler.cpp
//  machine learning from scratch
//
//  Created by Felipe Teles on 08/07/24.
//

#include <stdio.h>
#include "data_handler.hpp"

DataHandler::DataHandler(){
    data_array = new std::vector<Data *>;
    test_data = new std::vector<Data *>;
    training_data = new std::vector<Data *>;
    validation_data = new std::vector<Data *>;
}

DataHandler::~DataHandler(){
    // FREE Dynamically Allocated
}

void DataHandler::read_feature_vector(std::string path){
    uint32_t header[4]; // magic - num images - rowsize - colsize
    unsigned char bytes[4];
    
    FILE* file= fopen(path.c_str(), "r");
    if(file){
        for(int i = 0 ; i < 4;i++){
            if(fread(bytes, sizeof(bytes), 1, file)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
        
        printf("[INFO]: Done getting Input File header.\n");
        int image_size = header[2]*header[3];
        
        for (int i = 0; i < header[1]; i++) {
            Data* data = new Data();
            uint8_t element[1];
            for(int j = 0; j < image_size; j++){
                if(fread(element, sizeof(element), 1, file)){
                    data->append_to_feature_vector(element[0]);
                }else{
                    printf("[Error]: Reading from File.\n");
                    exit(0);
                }
            }
            data_array->push_back(data);
        }
        printf("[INFO]: Successfully read and store %lu feature vectors.\n", data_array->size());
    }else{
        printf("[ERROR]: Could not find file.\n");
        exit(1);
    }
}

void DataHandler::read_feature_labels(std::string path){
    uint32_t header[2]; // magic - num images - rowsize - colsize
    unsigned char bytes[4];
    
    FILE* file= fopen(path.c_str(), "r");
    if(file){
        for(int i = 0 ; i < 2; i++){
            if(fread(bytes, sizeof(bytes), 1, file)){
                header[i] = convert_to_little_endian(bytes);
            }
        }
        
        printf("[INFO]: Done getting Label File header.\n");
        for (int i = 0; i < header[1]; i++) {
            uint8_t element[1];
            if(fread(element, sizeof(element), 1, file)){
                data_array->at(i)->set_label(element[0]);
            }else{
                printf("[Error]: Reading from File.\n");
                exit(1);
            }
        }
        printf("[INFO]: Successfully read and stored %lu label.\n", data_array->size());
    }else{
        printf("[ERROR]: Could not find file.\n");
        exit(1);
    }
}

void DataHandler::split_data(){
    std::unordered_set<int> used_indexes;
    int train_size = data_array->size() * TRAIN_SET_PERCENT;
    int test_size = data_array->size() * TEST_SET_PERCENT;
    int valid_size = data_array->size() * VALIDATION_PERCENT;
    
    // Training Data
    int count = 0;
    while (count < train_size) {
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            training_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }
    
    // test data
    count = 0;
    while (count < test_size) {
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            test_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }
    
    // valid data
    count = 0;
    while (count < valid_size) {
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end()){
            validation_data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
            count++;
        }
    }
    
    printf("Training Data Size: %lu.\n", training_data->size());
    printf("Test Data Size: %lu.\n", test_data->size());
    printf("Valid Data Size: %lu.\n", validation_data->size());
}

void DataHandler::count_classes(){
    int count = 0;
    for (unsigned i = 0; i < data_array->size(); i++) {
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end()) {
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }
    num_classes = count;
    printf("Successfully Extracted %d Unique Classes.\n", num_classes);
}

uint32_t DataHandler::convert_to_little_endian(const unsigned char *bytes){
    return (uint32_t) ((bytes[0] << 24) |
                       (bytes[1] << 16) |
                       (bytes[2] << 8)  |
                       (bytes[3])
                       );
}

std::vector<Data *> *DataHandler::get_training_data(){
    return training_data;
}

std::vector<Data *> *DataHandler::get_test_data(){
    return test_data;
}

std::vector<Data *> *DataHandler::get_validation_data(){
    return validation_data;
}

