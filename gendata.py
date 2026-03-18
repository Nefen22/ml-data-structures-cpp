import numpy as np
import os

# =========================
# Utils
# =========================
def save_dataset(path, data):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    np.save(path, data)
    print(f"Saved: {path} | shape = {data.shape}")


# =========================
# 2-CLASS DATASET
# =========================
def gen_2c(N):
    # class 0
    X0 = np.random.randn(N//2, 2) + np.array([-2, 0])
    y0 = np.zeros((N//2, 1))

    # class 1
    X1 = np.random.randn(N//2, 2) + np.array([2, 0])
    y1 = np.ones((N//2, 1))

    X = np.vstack([X0, X1])
    y = np.vstack([y0, y1])

    data = np.concatenate([X, y], axis=1)
    np.random.shuffle(data)
    return data


# =========================
# 3-CLASS DATASET
# =========================
def gen_3c(N):
    N_each = N // 3

    # class 0
    X0 = np.random.randn(N_each, 2) + np.array([-3, 0])
    y0 = np.zeros((N_each, 1))

    # class 1
    X1 = np.random.randn(N_each, 2) + np.array([3, 0])
    y1 = np.ones((N_each, 1))

    # class 2
    X2 = np.random.randn(N_each, 2) + np.array([0, 3])
    y2 = np.full((N_each, 1), 2)

    X = np.vstack([X0, X1, X2])
    y = np.vstack([y0, y1, y2])

    data = np.concatenate([X, y], axis=1)
    np.random.shuffle(data)
    return data


# =========================
# GENERATE ALL FILES
# =========================
def generate_all():
    # 2-class
    save_dataset("datasets/2c-classification/2c_train.npy", gen_2c(800))
    save_dataset("datasets/2c-classification/2c_valid.npy", gen_2c(300))
    save_dataset("datasets/2c-classification/2c_test.npy",  gen_2c(300))

    # 3-class
    save_dataset("datasets/3c-classification/3c_train.npy", gen_3c(800))
    save_dataset("datasets/3c-classification/3c_valid.npy", gen_3c(300))
    save_dataset("datasets/3c-classification/3c_test.npy",  gen_3c(300))


if __name__ == "__main__":
    generate_all()