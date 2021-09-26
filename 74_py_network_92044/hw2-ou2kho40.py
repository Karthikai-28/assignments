import re
import sys
import numpy as np

import nltk
import numpy
from sklearn.linear_model import LogisticRegression


negation_words = set(['not', 'no', 'never', 'nor', 'cannot'])
negation_enders = set(['but', 'however', 'nevertheless', 'nonetheless'])
sentence_enders = set(['.', '?', '!', ';'])


# Loads a training or test corpus
# corpus_path is a string
# Returns a list of (string, int) tuples
def load_corpus(corpus_path):
    file = open(corpus_path)
    text = file.read()
    paragraph = text.split("\n")
    result = []
    for para in paragraph:
        if len(para) != 0:
            temp = para.split("\t")
            snippet = temp[0].split(" ")
            label = int(temp[1])
            sentiment = (snippet,label)
            result.append(sentiment)
    return result


# Checks whether or not a word is a negation word
# word is a string
# Returns a boolean
def is_negation(word):
    if word in negation_words:
        return True
    if word.endswith("n't"):
        return True
    return False


# Modifies a snippet to add negation tagging
# snippet is a list of strings
# Returns a list of strings
def tag_negation(snippet):
    TaggedWords = nltk.pos_tag(snippet)
    result = []
    negation_meta_tag = "NOT_"
    negationFlag = 0
    for i, words in enumerate(TaggedWords):
        if words[0] in negation_enders or words[0] in sentence_enders or words[1] == "JJR" or words[1] == "RBR":
            negationFlag = 0
        if negationFlag == 0:
            result.append(words[0])
        else:
            result.append(negation_meta_tag+words[0])
        if is_negation(words[0]):
            if words[0] == "not" and i+1 <= len(TaggedWords)-1 and TaggedWords[i+1][0] == "only":
                pass
            else:
                negationFlag = 1

    return result


# Assigns to each unigram an index in the feature vector
# corpus is a list of tuples (snippet, label)
# Returns a dictionary {word: index}
def get_feature_dictionary(corpus):
    result = dict()
    counter = 0
    for i,ele in enumerate(corpus):
        for word in ele[0]:
            if word not in result.keys():
                result[word] = counter
                counter += 1
            
    return result
    

# Converts a snippet into a feature vector
# snippet is a list of strings
# feature_dict is a dictionary {word: index}
# Returns a Numpy array
def vectorize_snippet(snippet, feature_dict):
    vector = np.zeros(len(feature_dict))
    for words in snippet:
        if words in feature_dict.keys():
            index = feature_dict[words]
            vector[index] += 1
    return vector

# Trains a classification model (in-place)
# corpus is a list of tuples (snippet, label)
# feature_dict is a dictionary {word: label}
# Returns a tuple (X, Y) where X and Y are Numpy arrays
def vectorize_corpus(corpus, feature_dict):
    d = len(feature_dict.keys())
    n = len(corpus)
    X = np.zeros(shape=(n, d))
    y = np.zeros(n)
    for i, elements in enumerate(corpus):
        snippets = elements[0]
        label = elements[1]
        X[i] = vectorize_snippet(snippets, feature_dict)
        y[i] = label
    return (X, y)


# Performs min-max normalization (in-place)
# X is a Numpy array
# No return value
def normalize(X):
    newX = np.zeros(shape=(len(X), len(X[0])))
    for i, features in enumerate(X):
        maximum = np.amax(features)
        minimum = np.amin(features)
        #print("Maximum:{}".format(maximum))
        #print("Minimum:{}".format(minimum))
        if maximum == minimum:
            continue
        else:
            for j, ele in enumerate(features):
                newX[i][j] = abs((X[i][j] - minimum))/abs((maximum-minimum))
                #print(newX[i][j])
                #print(X[i][j])
    return newX


# Trains a model on a training corpus
# corpus_path is a string
# Returns a LogisticRegression
def train(corpus_path):
    corpus = load_corpus(corpus_path)
    negCorpus = []
    for value in corpus:
        snippet = value[0]
        label = value[1]
        negationSnippet = tag_negation(snippet)
        negCorpus.append((negationSnippet,label))
    feature_dictionary = get_feature_dictionary(negCorpus)
    feature_vector = vectorize_corpus(negCorpus,feature_dictionary)
    normaliseFeature = normalize(feature_vector[0])
    normalize_featureVector = (normaliseFeature,feature_vector[1])
    model = LogisticRegression()
    model.fit(normalize_featureVector[0],normalize_featureVector[1])
    return (model,feature_dictionary)


# Calculate precision, recall, and F-measure
# Y_pred is a Numpy array
# Y_test is a Numpy array
# Returns a tuple of floats
def evaluate_predictions(Y_pred, Y_test):
    tp = 0
    fp = 0
    fn = 0
    for i in range(len(Y_test)):
        if Y_pred[i] == 1 and Y_test[i] == 1:
            tp += 1
        elif Y_test[i] == 0 and Y_pred[i] == 1:
            fp += 1
        elif Y_test[i] == 1 and Y_pred[i] == 0:
            fn += 1
        else:
            pass
    precision = tp/(tp+fp)
    recall = tp/(tp+fn)
    fmeasure = 2 * ((precision*recall)/(precision+recall))
    return (precision, recall, fmeasure)


# Evaluates a model on a test corpus and prints the results
# model is a LogisticRegression
# corpus_path is a string
# Returns a tuple of floats
def test(model, feature_dict, corpus_path):
    corpus = load_corpus(corpus_path)
    negation_tagged_corpus = []
    for ele in corpus:
        negation_snippet = tag_negation(ele[0])
        temp = (negation_snippet,ele[1])
        negation_tagged_corpus.append(temp)
    vectorized_corpus = vectorize_corpus(negation_tagged_corpus,feature_dict)
    X = normalize(vectorized_corpus[0])
    Y_test = vectorized_corpus[1]
    Y_pred = model.predict(X)
    result = evaluate_predictions(Y_pred, Y_test)
    return result


# Selects the top k highest-weight features of a logistic regression model
# logreg_model is a trained LogisticRegression
# feature_dict is a dictionary {word: index}
# k is an int
def get_top_features(logreg_model, feature_dict, k=1):
    pass


def main(args):
    model, feature_dict = train('train.txt')

    print(test(model, feature_dict, 'test.txt'))

    weights = get_top_features(model, feature_dict)
    for weight in weights:
        print(weight)
    
if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
