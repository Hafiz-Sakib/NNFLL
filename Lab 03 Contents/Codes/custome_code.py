import numpy as np

class NeuralNetwork:
    def __init__(self):
        # Layer 1 weights and biases (input: 3 → hidden1: 3)
        self.W1 = np.array([[2, 4, 6],
                            [3, 5, 7],
                            [4, 6, 8]], dtype=np.float32)
        self.b1 = np.array([[1], [1], [1]], dtype=np.float32)

        # Layer 2 weights and biases (hidden1: 3 → hidden2: 2)
        self.W2 = np.array([[3, 5],
                            [4, 6],
                            [7, 8]], dtype=np.float32)
        self.b2 = np.array([[2], [2]], dtype=np.float32)

        # Layer 3 weights and biases (hidden2: 2 → hidden3: 2)
        self.W3 = np.array([[5, 7],
                            [6, 8]], dtype=np.float32)
        self.b3 = np.array([[3], [3]], dtype=np.float32)

        # Output layer weights and biases (hidden3: 2 → output: 1)
        self.W4 = np.array([[4],
                            [5]], dtype=np.float32)
        self.b4 = np.array([[1]], dtype=np.float32)

    def relu(self, x):
        return np.maximum(0, x)

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def forward(self, x):
        x = x.reshape(-1, 1)  # Ensure column vector

        # Layer 1
        z1 = np.dot(self.W1.T, x) + self.b1
        a1 = self.relu(z1)

        # Layer 2
        z2 = np.dot(self.W2.T, a1) + self.b2
        a2 = self.relu(z2)

        # Layer 3
        z3 = np.dot(self.W3.T, a2) + self.b3
        a3 = self.sigmoid(z3)

        # Output Layer
        z4 = np.dot(self.W4.T, a3) + self.b4
        output = self.sigmoid(z4)

        return output

# Instantiate model
model = NeuralNetwork()

# Input vector
x = np.array([5, 3, 2], dtype=np.float32)

# Forward pass
output = model.forward(x)

print("Python Output:", output[0][0])
