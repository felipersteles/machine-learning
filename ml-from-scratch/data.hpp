//
//  data.hpp
//  cnn-from-scratch
//
//  Created by Felipe Teles on 08/07/24.
//

#ifndef data_hpp
#define data_hpp

#include <stdio.h>
#include <vector>
#include <cstdint>

class Data{
    std::vector<uint8_t>* feature_vector; // No classes
    uint8_t label;
    int enum_label; // A -> 1, B -> 2
    
public:
    Data();
    ~Data();
    
    void set_feature_vector(std::vector<uint8_t>*);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t);
    void set_enumerated_label(int);
    
    int get_feture_vector_size();
    uint8_t get_label();
    uint8_t get_enumerated_label();
    
    std::vector<uint8_t>* get_feature_vector();
};

#endif /* data_hpp */
