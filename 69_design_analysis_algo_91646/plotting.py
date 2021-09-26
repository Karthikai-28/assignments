import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import logging

class Plotter:
    def plot_hist(self, df:pd.DataFrame, column:str, color:str)->None:
        plt.figure(figsize=(12, 7))
        sns.displot(data=df, x=column, color=color, bins = 50, kde=True, height=7, aspect=2)
        plt.title(f'Distribution of {column}', size=20, fontweight='bold')
        plt.show()
        logging.info(f"plotted histogram for column {column}")

    def plot_count(self, df:pd.DataFrame, column:str) -> None:
        plt.figure(figsize=(12, 7))
        sns.countplot(data=df, x=column)
        plt.title(f'Distribution of {column}', size=20, fontweight='bold')
        plt.show()
        logging.info(f"plotted count plot for column {column}")
    
    def plot_correlation(self, df:pd.DataFrame, title:str) -> None:
        f = plt.figure(figsize=(19, 15))
        plt.matshow(df.corr(), fignum=f.number)
        plt.xticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14, rotation=45)
        plt.yticks(range(df.select_dtypes(['number']).shape[1]), df.select_dtypes(['number']).columns, fontsize=14)
        cb = plt.colorbar()
        cb.ax.tick_params(labelsize=14)
        plt.title('Correlation Matrix', fontsize=16)
        logging.info(f"plotted correlation matrix")