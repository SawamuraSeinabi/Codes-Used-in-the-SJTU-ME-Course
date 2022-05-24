import numpy as np
import pandas as pd
import torch
import Utils
import Dataset
import os


m = Utils.mvalue()
test_dir = 'data/DATA_testing.csv'

model = torch.load('save10/net.pkl')
df = pd.read_csv(test_dir)
sr = []
df1 = df.fillna(method='ffill', limit=500)
input1 = df1[['GearboxOilTemperature', 'GeneratorWinding2Temperature', 'WindSpeed', 'RotorRPM']].values
input1 = (input1 - m[1]) / (m[0] - m[1])
length = len(input1)
for i in range(length):
    a = torch.Tensor(input1[i])
    output1 = model(a).item()
    output1 = output1 * (m[2] - m[3]) + m[3]
    sr.append(output1[0])
sr1 = pd.Series(sr)
df['ActivePower'] = sr1
df.rename(columns={'Unnamed: 0': ''}, inplace=True)
df.to_csv(test_dir, mode='w', index=False)
print('done')

file1_name = "data/DATA_testing_ID.csv"
# 查找文件中的点出现的位置
idx = file1_name.rfind(".")
# 利用切片添加副本文字
file2_name = "data/DATA_testing_ID.csv"
file1 = open("data/DATA_testing_ID.csv", "rb")
file2 = open("data/DATA_testing_ID.csv", "wb")

while True:
    # 读取1024字节如果为零说明已读完
    info = file1.read(1024)
    if len(info) == 0:
        break
    else:
        # 如果不等于零把读取到的东西写入file2
        file2.write(info)
file1.close()
file2.close()
