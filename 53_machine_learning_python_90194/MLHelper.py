def load_housing_data():
    
    import numpy as np
    
    """Load house prices data and split it into input and output"""
    path_dataset = "house_prices.csv"
    data = np.genfromtxt(
        path_dataset, delimiter=",", skip_header=1, usecols=[0, 1, 2, 3, 4, 5, 6, 7])
    input_data = data[:, 0:7]
    output_data = data[:, 7]
    return input_data, output_data

def load_measurements_data():
    
    import numpy as np
    
    """Load data and convert it to the metric system."""
    path_dataset = "height_weight_genders.csv"
    data = np.genfromtxt(
        path_dataset, delimiter=",", skip_header=1, usecols=[1, 2])
    height = data[:, 0]
    weight = data[:, 1]
    gender = np.genfromtxt(
        path_dataset, delimiter=",", skip_header=1, usecols=[0],
        converters={0: lambda x: 0 if b"Male" in x else 1})
    # Convert to metric system
    height *= 0.025
    weight *= 0.454
    return height, weight, gender
def polynomial_basis(inputs, degree):  
    
    import numpy as np
    
    basis_matrix = np.ones((len(inputs), 1))
    for counter in range(1, degree + 1):
        basis_matrix = np.c_[basis_matrix, np.power(inputs, counter)]
    return basis_matrix

def ridge_regression(data_matrix, data_samples, alpha):
    
    import numpy as np
    
    gram_matrix = data_matrix.T @ data_matrix+alpha*np.identity(data_matrix.shape[1])
    right_hand_side = data_matrix.T @ data_samples
    return np.linalg.solve(gram_matrix, right_hand_side)