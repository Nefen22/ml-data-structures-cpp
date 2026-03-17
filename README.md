# ml-data-structures-cpp

A C++ implementation of core data structures and their application to a neural network pipeline, built as part of the **Data Structures & Algorithms** course at HCMUT (2024).

Implemented a Multi-Layer Perceptron (MLP) training pipeline from scratch in C++, including custom data structures, forward/backward propagation, and dataset handling.

---

## What I Implemented

### Data Structures
- **XArrayList** — generic dynamic array with x2 amortized resize strategy
- **DLinkedList** — generic doubly linked list; used for bidirectional layer traversal in the neural network
- **Stack, Queue** — built on top of the list structures
- **BST, AVL Tree** — binary search tree with AVL balancing
- **Graph** (directed/undirected) — with Topological Sort
- **Heap** — priority queue implementation
- **Hash Map (xMap)** — hash table with chaining
- **Sorting algorithms** — Bubble, Quick, Heap, Shell, Insertion, Selection

### Neural Network Pipeline
- **TensorDataset** — wraps data and label tensors with shape metadata
- **DataLoader** — batched data iteration with configurable shuffle and train/val split
- **FCLayer** — fully connected layer with forward and backward pass
- **ReLU, Sigmoid, Tanh, Softmax** — activation layers with forward and backward pass
- **CrossEntropy** — loss function
- **MLPClassifier** — full model using DLinkedList to chain layers; supports forward, backward, training, evaluation, save/load

---

## What Was Provided
- All header interfaces (`IList`, `ILayer`, `IModel`, `IOptimizer`, etc.)
- Optimizer implementations (SGD, Adam, Adagrad)
- Tensor library (xtensor)
- Formatting library (fmtlib)

---

## Key Design Decisions

**DLinkedList for neural network layers**
Each layer is stored as a node in a doubly linked list. This allows natural forward pass (head → tail) and backward pass (tail → head) traversal without reversing the structure.

**XArrayList with x2 resize**
When capacity is exceeded, the internal array doubles in size. This gives amortized O(1) append performance — inserting N elements total costs O(N) rather than O(N²).

**Generic templates**
Both list structures use C++ templates, allowing reuse across different data types: `XArrayList<double>` for tensor data, `DLinkedList<ILayer*>` for model layers, `Dataset<DType, LType>` for typed data/label pairs.

---

## Build & Run

```bash
# Requires g++, C++17
chmod +x compilation-command.sh
./compilation-command.sh

# Run
./program
```

Or using Makefile:

```bash
make
./program
```

---

## Results

Trained and evaluated on 2-class and 3-class classification tasks. Model checkpoints saved under `models/`.

| Task | Layers | Optimizer |
|---|---|---|
| 2-class classification | FC → ReLU → FC → ReLU → FC → Softmax | SGD / Adam |
| 3-class classification | FC → ReLU → FC → ReLU → FC → Softmax | SGD / Adam |

---

## Project Structure

```
.
├── include/
│   ├── list/          # XArrayList, DLinkedList interfaces
│   ├── ann/           # Neural network layer, model, optimizer headers
│   ├── loader/        # Dataset, DataLoader
│   ├── tensor/        # xtensor library
│   └── ...
├── src/
│   ├── ann/           # Layer, model, optimizer implementations
│   └── program.cpp    # Entry point
├── models/            # Saved model checkpoints
├── Makefile
└── compilation-command.sh
```

## 📊 Dataset

The project includes synthetic datasets for classification tasks.

You can generate new datasets using:

```bash
python gendata.py
```

This will create datasets under:

```
datasets/
├── 2c-classification/
│   ├── 2c_train.npy
│   ├── 2c_valid.npy
│   └── 2c_test.npy
├── 3c-classification/
│   ├── 3c_train.npy
│   ├── 3c_valid.npy
│   └── 3c_test.npy
```

Each sample consists of:

* 2 input features `(x, y)`
* 1 label (class index)

---

## ▶️ Entry Point

The main entry point is:

```
src/program.cpp
```

This file:

* Loads datasets via `DSFactory`
* Builds the MLP model
* Trains the model
* Evaluates performance on validation/test sets
* Saves trained models to `models/`

---

## ⚡ Build Optimization

The project supports parallel compilation using `make`.

```bash
make -j$(nproc)
```

This enables multi-core compilation and significantly reduces build time for large projects.

---

## 📈 Example Training Output

```
Start the training ...
Epoch 10: loss ~0.8 | acc ~0.88
Epoch 30: loss ~0.3 | acc ~0.95
Epoch 40+: acc ~0.96

Evaluation result:
{ accuracy ~0.96 }
```

---

## 🧪 Key Learning Outcomes

* Implemented neural network training **from scratch in C++**
* Understood backpropagation at a low level (tensor operations, gradients)
* Applied classical data structures in a real ML pipeline
* Built a modular system with reusable components (datasets, layers, optimizers)

---

## 🚀 Possible Extensions

* LeakyReLU / ELU to mitigate dead neuron problem
* CNN layers for computer vision tasks
* GPU acceleration (CUDA / OpenCL)
* Visualization tools (loss curves, decision boundaries)
* Serialization improvements (portable model format)

---

## ⭐ Highlights

* End-to-end ML pipeline without frameworks (no PyTorch / TensorFlow)
* Combines **Data Structures + Machine Learning**
* Emphasis on **low-level implementation and performance awareness**
* Clean modular design using interfaces and templates

---

