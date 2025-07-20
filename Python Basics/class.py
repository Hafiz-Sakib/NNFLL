class Calculator:
    def summation(self, a, b):
        return a + b

    def multiplication(self, a, b):
        return a * b

# Create an object of the class
calc = Calculator()

# Call the methods
x = 5
y = 3

sum_result = calc.summation(x, y)
product_result = calc.multiplication(x, y)

print(f"Summation of {x} and {y} is: {sum_result}")
print(f"Multiplication of {x} and {y} is: {product_result}")
