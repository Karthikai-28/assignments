def load_titanic_train_data():
    
    import numpy as np
    
    """Load data and convert it to the list of columns"""
    path_dataset = 'titanic_train.csv'
    
    data = np.genfromtxt(path_dataset, delimiter=",", skip_header=1, usecols=[0,2,3,4,5,6], dtype = None, converters = {5: lambda x: 0 if x == b'male' else 1}, names = ('Age','Fare','Parch','Pclass','Sex','SibSp'))
        
    survival = 2*np.genfromtxt(path_dataset, delimiter=",", skip_header=1, usecols=[7], dtype = int)-1
    
    embarkation_port = np.genfromtxt(path_dataset, delimiter=",", usecols=[1], dtype = str, skip_header = 1)
    
    embarkation_port_S = np.where(embarkation_port == 'S',1,0)
    embarkation_port_Q = np.where(embarkation_port == 'Q',1,0)
    embarkation_port_C = np.where(embarkation_port == 'C',1,0)
    
    data = np.c_[data['Age'], data['Fare'], data['Parch'], data['Pclass'], data['Sex'], data['SibSp'], embarkation_port_S, embarkation_port_Q, embarkation_port_C]
    
    return data, survival

def load_glass_data():
    import numpy as np
    
    """Load data"""
    path_dataset = 'glass.data'
    data = np.genfromtxt(
        path_dataset, delimiter=",", usecols=[1,2,3,4,5,6,7,8,9])
    labels = np.genfromtxt(
        path_dataset, delimiter=",", usecols=[10], dtype = int)
    return data, labels

def load_fashion_mnist(path, kind = 'train'):
    
    import os
    import gzip
    import numpy as np

    """Load MNIST data from `path`"""
    labels_path = os.path.join(path,
                               '%s-labels-idx1-ubyte.gz'
                               % kind)
    images_path = os.path.join(path,
                               '%s-images-idx3-ubyte.gz'
                               % kind)

    with gzip.open(labels_path, 'rb') as lbpath:
        labels = np.frombuffer(lbpath.read(), dtype=np.uint8,
                               offset=8)

    with gzip.open(images_path, 'rb') as imgpath:
        images = np.frombuffer(imgpath.read(), dtype=np.uint8,
                               offset=16).reshape(len(labels), 784)

    return images, labels