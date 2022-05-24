# -*- coding = utf-8 -*-
# @Time :2020/12/13 18:07
# @Author : 陈辰
# @Studentnumber：518021911159
# @File : test.py
# @Software : PyCharm

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torch.utils.data
from tensorboardX import SummaryWriter
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import r2_score

# torch.manual_seed(2)
# np.random.seed(2)
save_dir = 'result'
df = pd.read_csv('archive/pmsm_temperature_data.csv')
writer_tr = SummaryWriter(save_dir + '/train')
writer_ts = SummaryWriter(save_dir + '/test')

col_list = df.columns.tolist()
profile_id = ['profile_id']
target_list = ['pm', 'torque', 'stator_yoke', 'stator_tooth', 'stator_winding']
feature_list = ['ambient', 'coolant', 'motor_speed', 'u_d', 'u_q', 'i_d', 'i_q']

'''检索profile_id'''
df['profile_id'] = df.profile_id.astype('category', inplace=True)
df.profile_id.unique()

df_dict = {}
for id_ in df.profile_id.unique():
    df_dict[id_] = df[df['profile_id'] == id_].reset_index(drop=True)

prof_ids = list(df_dict.keys())
df_dict.keys()

'''选择prof_id'''
prof_id = 4

curr_df = df_dict[prof_id]

curr_df = curr_df.drop('profile_id', axis=1)
columns = curr_df.columns.tolist()

'''由时间序列设置data和target'''


def build_sequences(features_df, target_df, sequence_length=10):
    data_ = []
    target_ = []

    for i in range(int(features_df.shape[0] / sequence_length)):
        data = torch.from_numpy(features_df.iloc[i:i + sequence_length].values)
        target = torch.from_numpy(target_df.iloc[i + sequence_length + 1].values)

        data_.append(data)
        target_.append(target)

    data = torch.stack(data_)
    target = torch.stack(target_)

    return data, target


'''归一化数据'''
scaler = MinMaxScaler()

curr_df = pd.DataFrame(scaler.fit_transform(curr_df), columns=columns)
curr_df.head()

sequence_length = 3

features = curr_df[feature_list]
'''选择target'''
target = curr_df[target_list][['pm']]

data, target = build_sequences(features, target, sequence_length=sequence_length)

'''分割训练集测试集'''
test_size = 0.2

indices = torch.randperm(data.shape[0])

train_indices = indices[:int(indices.shape[0] * (1 - test_size))]
test_indices = indices[int(indices.shape[0] * (1 - test_size)):]

X_train, y_train = data[train_indices], target[train_indices]
# print(X_train)
X_test, y_test = data[test_indices], target[test_indices]

'''dataset'''


class PMSMDataset(torch.utils.data.dataset.Dataset):

    def __init__(self, data, target):
        self.data = data
        self.target = target

    def __len__(self):
        return self.data.shape[0]

    def __getitem__(self, idx):
        return self.data[idx].unsqueeze(0), self.target[idx]


batch_size = 32

pm_train_dataset = PMSMDataset(X_train, y_train)
pm_train_loader = torch.utils.data.dataloader.DataLoader(pm_train_dataset, batch_size=batch_size, shuffle=True,
                                                         drop_last=False)

pm_test_dataset = PMSMDataset(X_test, y_test)
pm_test_loader = torch.utils.data.dataloader.DataLoader(pm_test_dataset, batch_size=batch_size, shuffle=True)

'''net'''


class Network(nn.Module):
    def __init__(self, sequence_length, n_features):
        super(Network, self).__init__()

        self.conv1 = nn.Conv1d(1, 3, kernel_size=(sequence_length, n_features))

        self.lin_in_size = self.conv1.out_channels * int(
            ((sequence_length - (self.conv1.kernel_size[0] - 1) - 1) / self.conv1.stride[0] + 1))

        #         print(self.lin_in_size)

        self.fc1 = nn.Linear(self.lin_in_size, 30)
        self.fc2 = nn.Linear(30, 1)

    def forward(self, x):
        x = F.relu(self.conv1(x))
        x = x.view(-1, self.lin_in_size)

        x = F.relu(self.fc1(x))
        x = self.fc2(x)

        return x


n_features = X_train.shape[-1]

net = Network(sequence_length, n_features).double()

lr = 0.001

criterion = nn.MSELoss()
optimizer = optim.Adam(net.parameters(), lr=lr)

test_r2 = []
train_r2 = []
test_mse = []
train_mse = []

'''train'''
training_losses = []
for epoch in range(250):
    running_loss = 0.0
    batch_losses = []
    train_loss = 0
    ii = 0
    r2_tr = 0
    for i, (data, target) in enumerate(pm_train_loader):
        optimizer.zero_grad()

        out = net(data)

        loss = criterion(out, target)
        # batch_losses.append(loss.item())

        loss.backward()
        optimizer.step()
        train_loss += loss.item()
        r2 = r2_score(out.detach().numpy(), target.detach().numpy())
        r2_tr += r2
        ii += 1
    MSE = train_loss / ii
    r2_tr = r2_tr / ii
    writer_tr.add_scalar('MSE', MSE, epoch)
    writer_tr.add_scalar('r2', r2_tr, epoch)
    print(epoch, 'train_mse %.7g' % MSE, 'r_score %.3g' % r2_tr)
    train_mse.append(MSE)
    train_r2.append(r2_tr)
    # training_losses.append(np.mean(batch_losses))
    # print("Epoch {}, loss {:.6f}".format(epoch+1, training_losses[-1]))

    losses = []
    batch_losses = []
    targets = []
    outputs = []
    test_loss = 0
    r2_0 = 0
    with torch.no_grad():
        iii = 0
        for i, (data, target) in enumerate(pm_test_loader):
            out = net(data)
            loss = criterion(out, target)
            test_loss += loss.item()
            r2 = r2_score(out.numpy(), target.numpy())
            r2_0 += r2
            iii += 1
        #         print('Target : {:.4f}, Predicted Output : {:.4f}'.format(target.item(), out.item()))
        # targets.append(target.item())
        # outputs.append(out.item())
        MSE_0 = test_loss / iii
        r2_0 = r2_0 / iii
        print(epoch, 'test_mse %.7g' % MSE_0, 'r_score %.3g' % r2_0)
        writer_ts.add_scalar('MSE', MSE_0, epoch)
        writer_ts.add_scalar('r2', r2_0, epoch)
        test_mse.append(MSE_0)
        test_r2.append(r2_0)

        #     batch_losses.append(loss.item())
        # losses.append(np.mean(batch_losses))

np.save(save_dir + '/test_mse', test_mse)
np.save(save_dir + '/train_mse', train_mse)
np.save(save_dir + '/train_r2', train_r2)
np.save(save_dir + '/test_r2', test_r2)
torch.save(net, save_dir + '/net.pkl')
writer_ts.close()
writer_tr.close()
