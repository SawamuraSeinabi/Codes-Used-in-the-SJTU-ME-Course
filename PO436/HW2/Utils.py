import pandas as pd
from sklearn.utils import shuffle
import numpy as np


def cat(dir1='data/DATA_training.csv', dir2='data/DATA_validating.csv'):
    df1 = pd.read_csv(dir1, low_memory=False)
    df2 = pd.read_csv(dir2, low_memory=False)

    df = pd.concat((df1, df2), axis=0)
    df.dropna(how='any', inplace=True)
    df = shuffle(df)
    length = len(df)
    size_tr = int(0.8 * length)
    size_ts = int(0.2 * length)
    df_tr = df[:size_tr]
    df_ts = df[-size_ts:]
    df.to_csv('data/DATA.csv')
    df_tr.to_csv('data/DATA_tr.csv')
    df_ts.to_csv('data/DATA_ts.csv')

    return df


def mvalue():
    df = pd.read_csv('data/DATA.csv')
    input = df[['GearboxOilTemperature',
                'GeneratorWinding2Temperature',
                'WindSpeed',
                'RotorRPM']].values
    max1 = input.max(axis=0)
    min1 = input.min(axis=0)
    target = df[['ActivePower']].values
    max2 = target.max(axis=0)
    min2 = target.min(axis=0)
    return max1, min1, max2, min2


if __name__ == '__main__':
    df = cat()
    df.dropna(how='any', inplace=True)
    input = df[['GearboxOilTemperature',
                'GeneratorWinding2Temperature',
                'WindSpeed',
                'RotorRPM']].values
    max1 = input.max(axis=0)
    min1 = input.min(axis=0)
    target = df[['ActivePower']].values
    max2 = target.max(axis=0)
    min2 = target.min(axis=0)
