# 🚀 ml-data-structures-cpp

> A from-scratch implementation of a mini machine learning framework in **modern C++**, combining custom data structures with a full neural network training pipeline.

Built as part of the **Data Structures & Algorithms course at HCMUT (2024)**, this project focuses on **system design, memory efficiency, and low-level ML implementation** without relying on high-level frameworks like PyTorch or TensorFlow.

---

## 🎯 Overview

This project reconstructs a complete ML pipeline in C++, including:

- Custom data structures (lists, trees, hash maps, graphs)
- A mini neural network framework (MLP)
- Data loading system with batching and shuffling
- Forward & backward propagation (backpropagation)
- Model training, evaluation, and persistence

👉 The goal is to bridge **Data Structures ↔ Machine Learning Systems** in a practical implementation.

---

## ⚡ Core Features

### 🧠 Neural Network Pipeline (Main Focus)

- **MLPClassifier** — fully connected neural network
- **Forward & Backward propagation** implemented from scratch
- **Activation layers**: ReLU, Sigmoid, Tanh, Softmax
- **Loss function**: CrossEntropy
- **Training loop** with evaluation support
- **Model save/load** for reproducibility

---

### ⚡ DataLoader (Key Highlight)

A custom implementation inspired by PyTorch:

- Iterator-based design (`for (auto batch : loader)`)
- Mini-batch loading
- Shuffle with reproducible seed
- Lazy shape initialization (reduces unnecessary dataset access)
- `drop_last` support for consistent batch sizes

👉 Demonstrates understanding of **data pipeline design in ML systems**

---

### 🔢 Tensor Computation

- Built on top of **xtensor** (NumPy-like library for C++)
- Supports multi-dimensional arrays and vectorized operations
- Enables efficient numerical computation

---

### 🧩 Supporting Data Structures (Built from Scratch)

- **XArrayList** — dynamic array with amortized O(1) append
- **DLinkedList** — used to store and traverse NN layers
- **Stack / Queue**
- **BST / AVL Tree**
- **Graph** (with Topological Sort)
- **Heap (Priority Queue)**
- **Hash Map (xMap)**
- **Sorting algorithms** — Quick, Heap, Shell, etc.

👉 These structures are integrated into the ML pipeline, not just standalone implementations.

---

## 🏗️ System Architecture


Dataset

↓

DataLoader (batching, shuffle)

↓

Model (MLP)

↓

Loss (CrossEntropy)

↓

Backward Pass

↓

Optimizer

↓

Evaluation / Save Model


---

## 🧠 Key Design Decisions

### DLinkedList for Neural Network Layers
Each layer is stored as a node in a doubly linked list:
- Forward pass: head → tail
- Backward pass: tail → head

→ Simplifies traversal without reversing structures.

---

### Lazy Initialization in DataLoader
Shape information is initialized only when needed:
- Avoids unnecessary dataset access
- Reduces overhead in large datasets

---

### Template-based Generic Design
- `Dataset<DType, LType>`
- `XArrayList<T>`
- `DLinkedList<ILayer*>`

→ Ensures flexibility and reusability.

---

## ▶️ Build & Run

```bash
make -j$(nproc)
./program
📊 Dataset

Generate synthetic datasets:

python gendata.py

Structure:

datasets/
├── 2c-classification/
├── 3c-classification/

Each sample:

2 input features (x, y)

1 label

📈 Example Output
Start the training ...
Epoch 10: loss ~0.8 | acc ~0.88
Epoch 30: loss ~0.3 | acc ~0.95
Epoch 40+: acc ~0.96

Evaluation result:
{ accuracy ~0.96 }
📂 Project Structure
.
├── include/
│   ├── list/
│   ├── ann/
│   ├── loader/
│   ├── tensor/
├── src/
│   ├── ann/
│   └── program.cpp
├── models/
├── datasets/
├── Makefile
🧪 Learning Outcomes

Implemented a neural network from scratch in C++

Understood backpropagation at a low level (gradients, tensor ops)

Designed a modular ML system with reusable components

Applied classical data structures in a real-world pipeline

Practiced memory-safe programming (validated with Valgrind)

🚀 Future Improvements

Multi-threaded DataLoader (prefetching)

Custom samplers (random, weighted)

CNN / advanced architectures

GPU acceleration (CUDA / OpenCL)

Visualization tools (training curves, decision boundaries)

⭐ Highlights

End-to-end ML pipeline without high-level frameworks

Strong combination of Data Structures + Machine Learning

Emphasis on system design & low-level implementation

Clean architecture using templates and interfaces
