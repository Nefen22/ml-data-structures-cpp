#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#include <filesystem> //require C++17
namespace fs = std::filesystem;

//#include "list/listheader.h"
#include "list/XArrayListDemo.h"
#include "list/DLinkedListDemo.h"
#include "loader/DataLoaderDemo.h"
//#include "sformat/fmt_lib.h"
//#include "tensor/xtensor_lib.h"
//#include "ann/annheader.h"
//#include "loader/dataset.h"
//#include "loader/dataloader.h"
//#include "config/Config.h"
//#include "dataset/DSFactory.h"
//#include "optim/Adagrad.h"
//#include "optim/Adam.h"
//#include "modelzoo/twoclasses.h"
//#include "modelzoo/threeclasses.h"


int main(int argc, char** argv) {
    //dataloader:
    //case_data_wo_label_1();
    //case_data_wi_label_1();
    //case_batch_larger_nsamples();
    
    //Classification:
    //twoclasses_classification();
    //threeclasses_classification();
    xlistDemo1();
    xlistDemo2();
    xlistDemo3();
    xlistDemo4();

    dlistDemo1();
    dlistDemo3();
    dlistDemo4();
    dlistDemo5();
    dlistDemo6();
    case_data_wo_label_1();
    case_data_wi_label_1();
    case_batch_larger_nsamples();
 
    return 0;
}
