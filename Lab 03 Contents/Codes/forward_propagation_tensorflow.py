import tensorflow as tf
import numpy as np

# Define weights and biases
W1 = np.array([[2, 4, 6], [3, 5, 7], [4, 6, 8]], dtype=np.float32)
b1 = np.array([[1], [1], [1]], dtype=np.float32)
W2 = np.array([[3, 5], [4, 6], [7, 8]], dtype=np.float32)
b2 = np.array([[2], [2]], dtype=np.float32)
W3 = np.array([[5, 7], [6, 8]], dtype=np.float32)
b3 = np.array([[3], [3]], dtype=np.float32)
W4 = np.array([[4], [5]], dtype=np.float32)
b4 = np.array([[1]], dtype=np.float32)

# Define input as column vector
X = np.array([[5], [3], [2]], dtype=np.float32)

# Forward propagation with transposition during calculation
Z1 = tf.matmul(tf.transpose(W1), X) + b1
A1 = tf.nn.relu(Z1)
Z2 = tf.matmul(tf.transpose(W2), A1) + b2
A2 = tf.nn.relu(Z2)
Z3 = tf.matmul(tf.transpose(W3), A2) + b3
A3 = tf.nn.sigmoid(Z3)
Z4 = tf.matmul(tf.transpose(W4), A3) + b4
output = tf.nn.sigmoid(Z4)

print("TensorFlow Output:", output.numpy())
