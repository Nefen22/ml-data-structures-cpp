/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CrossEntropy.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction): ILossLayer(reduction){
    
}

CrossEntropy::CrossEntropy(const CrossEntropy& orig):
ILossLayer(orig){
}

CrossEntropy::~CrossEntropy() {
}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t) {
    const double EPS = 1e-7;

    // cache for backward
    m_aCached_Ypred = X;
    m_aYtarget = t;

    int N = X.shape()[0];

    xt::xarray<double> logY = xt::log(X + EPS);
    double loss = -xt::sum(t * logY)() / N;

    return loss;
}
xt::xarray<double> CrossEntropy::backward() {
    const double EPS = 1e-7;

    int N = m_aCached_Ypred.shape()[0];

    xt::xarray<double> DY =
        -(m_aYtarget / (m_aCached_Ypred + EPS)) / N;

    return DY;
}