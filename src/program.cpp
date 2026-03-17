#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#include <filesystem> //require C++17
namespace fs = std::filesystem;

//#include "list/listheader.h"
//#include "list/XArrayListDemo.h"
//#include "list/DLinkedListDemo.h"
//#include "loader/DataLoaderDemo.h"
//#include "hash/xMapDemo.h"

#include "sformat/fmt_lib.h"
#include "tensor/xtensor_lib.h"
#include "ann/annheader.h"
#include "loader/dataset.h"
#include "loader/dataloader.h"
#include "config/Config.h"
#include "dataset/DSFactory.h"
#include "optim/Adagrad.h"
#include "optim/Adam.h"
#include "modelzoo/twoclasses.h"
#include "modelzoo/threeclasses.h"

/* ******* BEGIN MLP ******* */
void mlpDemo1() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    cout << "Train dataset: " << train_ds->len() << endl;
    cout << "Valid dataset: " << valid_ds->len() << endl;
    cout << "Test dataset: " << test_ds->len() << endl;

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new ReLU(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers) / sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}

void mlpDemo2() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new Sigmoid(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers) / sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}
void mlpDemo3() {
    xt::random::seed(42);
    DSFactory factory("./config.txt");
    xmap<string, TensorDataset<double, double>*>* pMap = factory.get_datasets_2cc();
    TensorDataset<double, double>* train_ds = pMap->get("train_ds");
    TensorDataset<double, double>* valid_ds = pMap->get("valid_ds");
    TensorDataset<double, double>* test_ds = pMap->get("test_ds");
    DataLoader<double, double> train_loader(train_ds, 50, true, false);
    DataLoader<double, double> valid_loader(valid_ds, 50, false, false);
    DataLoader<double, double> test_loader(test_ds, 50, false, false);

    int nClasses = 2;
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new Tanh(),
        new FCLayer(50, nClasses, true),
        new Softmax()
    };

    MLPClassifier model("./config.txt", "2c-classification", layers, sizeof(layers) / sizeof(ILayer*));

    SGD optim(2e-3);
    CrossEntropy loss;
    ClassMetrics metrics(nClasses);

    model.compile(&optim, &loss, &metrics);
    model.fit(&train_loader, &valid_loader, 10);
    string base_path = "./models";
    // model.save(base_path + "/" + "2c-classification-1");
    double_tensor eval_rs = model.evaluate(&test_loader);
    cout << "Evaluation result on the testing dataset: " << endl;
    cout << eval_rs << endl;
}
/* ******* END MLP ******* */

void (*func_ptr[])() = {
    // Hash
    /*hashDemo1,
    hashDemo2,
    hashDemo3,
    hashDemo4,
    hashDemo5,
    hashDemo6,*/
    // MLP
    mlpDemo1,
    mlpDemo2,
    mlpDemo3,
};

void run(int func_idx) {
    func_ptr[func_idx]();
}
#include <filesystem>
xt::xarray<double> b1 = { 1.0, -1.0 };
xt::xarray<double> W1 = {
    {1.0, 0.0},
    {0.0, 1.0}
};
xt::xarray<double> X = {
    {1.0, 2.0},
    {3.0, 4.0}
};


xt::xarray<double> forward(xt::xarray<double> X) {
    xt::xarray<double> sub = b1;
    return xt::linalg::dot(X, xt::transpose(W1)) + sub;
}


int main(int argc, char** argv) {
    cout << std::filesystem::current_path() << endl;

    //dataloader:
    //case_data_wo_label_1();
    //case_data_wi_label_1();
    //case_batch_larger_nsamples();
    
    //Classification:
    twoclasses_classification();
    //threeclasses_classification();
    /*hashDemo1();
    hashDemo2();
    hashDemo3();
    hashDemo4();
    hashDemo5();
    hashDemo6();*/
    // MLP
    //mlpDemo1();
    //mlpDemo2();
    //mlpDemo3();
    //xlistDemo1();
    //xlistDemo2();
    //xlistDemo3();
    //xlistDemo4();

    /*dlistDemo1();
    dlistDemo3();
    dlistDemo4();
    dlistDemo5();*/
    //dlistDemo6();
    //case_data_wo_label_1();
    //case_data_wi_label_1();
    //case_batch_larger_nsamples();
    //hashDemo1();
    //hashDemo2();
    //hashDemo3();
    //hashDemo4();
    //hashDemo5();
    //hashDemo6();
    //hashDemo7();
    //countryDemo();


    return 0;
}
