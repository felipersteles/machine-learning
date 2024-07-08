//
//  data.cpp
//  cnn-from-scratch
//
//  Created by Felipe Teles on 08/07/24.
//

#include <stdio.h>
#include "data.hpp"

Data::Data(){
    feature_vector = new std::vector<uint8_t>;
}

Data::~Data(){}

void Data::set_feature_vector(std::vector<uint8_t>* vect){
    feature_vector = vect;
}

void Data::append_to_feature_vector(uint8_t value){
    feature_vector->push_back(value);
}

void Data::set_label(uint8_t value){
    label = value;
}

void Data::set_enumerated_label(int value){
    enum_label = value;
}

int Data::get_feture_vector_size(){
    return (int) feature_vector->size();
}

uint8_t Data::get_label(){
    return label;
}

uint8_t Data::get_enumerated_label(){
    return enum_label;
}

std::vector<uint8_t>* Data::get_feature_vector(){
    return feature_vector;
}
