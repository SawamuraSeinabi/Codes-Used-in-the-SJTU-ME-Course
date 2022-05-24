import pandas as pd

df = pd.read_excel('data/data.xlsx')
df2 = pd.read_excel('data/data2.xlsx')
df_new = pd.concat((df[['T','P','Q']],df2[['T','P','Q']]),axis = 0)

'''
归一化
(x-xmin)/(xmax-xmin)
'''
cloms=['T','Q']
df_new1 = pd.DataFrame(columns = ['T','Q'])
for col in cloms:
    max_val = df_new[col].max(axis = 0)
    min_val = df_new[col].min(axis = 0)
    length = max_val - min_val
    a = df_new[col].values

    array = (df_new[col].values - min_val) / length
    df_new1[col] = array

print()