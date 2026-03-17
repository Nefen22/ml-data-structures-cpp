/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   ReLU.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:44 PM
 */

#include "layer/ReLU.h"
#include "sformat/fmt_lib.h"
#include "ann/functions.h"

ReLU::ReLU(string name) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::ReLU(const ReLU& orig) {
    m_sName = "ReLU_" + to_string(++m_unLayer_idx);
}

ReLU::~ReLU() {
}

xt::xarray<double> ReLU::forward(xt::xarray<double> X) {
    // Lưu mask để backward
    if (this->m_trainable) {
        this->m_aMask = xt::cast<double>(X > 0);
    }

    // Tính tỷ lệ neuron chết (dead neurons)
    double total_elements = static_cast<double>(X.size());
    double positive_count = xt::sum(this->m_aMask)();
    double live_ratio = positive_count / total_elements;
    double dead_ratio = 1.0 - live_ratio;

    return xt::where(X > 0, X, 0.0);
}
xt::xarray<double> ReLU::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE
    return this->m_aMask * DY;
}

string ReLU::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}:",
                    "ReLU", this->getname());
    return desc;
}