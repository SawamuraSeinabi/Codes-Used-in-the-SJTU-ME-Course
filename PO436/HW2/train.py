import torch
from torch.utils.data import Dataset, DataLoader, Sampler
import pandas as pd
import numpy as np
from torch import nn
from torch import optim
from Net import MLP
import Dataset
from sklearn.metrics import r2_score
from tensorboardX import SummaryWriter
import Utils
from sklearn.impute import SimpleImputer
Imputer = SimpleImputer(missing_values=np.nan, strategy='mean')

save_dir = 'save10'


class Mynet(nn.Module):
    def __init__(self):
        super(Mynet, self).__init__()
        self.mylayer1 = MLP(4, 1)


net = MLP()

M = Utils.mvalue()

Loss_func = nn.MSELoss()

Opt = optim.Adam(net.parameters(), lr=0.0001)

print(net.parameters())
Norm_trans = True
train_csv = 'Data/DATA_tr.csv'
test_csv = 'Data/DATA_ts.csv'

'''定义数据集'''

print('==>processing data')
train_set = Dataset.Dataset_myself(train_csv, trans=Norm_trans)
train_loader = DataLoader(train_set, batch_size=256, shuffle=True, drop_last=False)
test_set = Dataset.Dataset_myself(test_csv, trans=Norm_trans)
test_loader = DataLoader(test_set, batch_size=256, shuffle=False)

print(len(train_set))
print(len(test_set))

'''保存目录'''

writer_tr = SummaryWriter(save_dir + '/train')
writer_ts = SummaryWriter(save_dir + '/test')

test_r2 = []
train_r2 = []
test_mse = []
train_mse = []

for i in range(500):

    '''training'''
    net.train()
    train_loss = 0
    r2_tr = 0
    ii = 0
    for input, target in train_loader:
        out = net(input)
        loss = Loss_func(out, target)
        Opt.zero_grad()
        loss.backward()
        Opt.step()
        train_loss += loss.item()
        r2 = r2_score(out.detach().numpy(), target.detach().numpy())

        r2_tr += r2
        ii += 1
    r2_tr = r2_tr/ii
    MSE = train_loss/ii
    writer_tr.add_scalar('r2', r2_tr, i)
    writer_tr.add_scalar('MSE', MSE, i)
    print(i, 'train_mse %.7g' % MSE, 'r_score %.3g' % r2_tr)
    train_r2.append(MSE)
    train_r2.append(MSE)
    train_r2.append(r2_tr)

    '''测试'''
    net.eval()
    test_loss = 0
    r2_0 = 0
    with torch.no_grad():
        iii = 0
        for input0, target0 in test_loader:
            out0 = net(input0)
            loss0 = Loss_func(out0, target0)
            test_loss += loss0.item()
            r2 = r2_score(out0.numpy(), target0.numpy())
            r2_0 += r2
            iii += 1
    r2_0 = r2_0/iii
    MSE_0 = test_loss/iii
    writer_ts.add_scalar('r2', r2_0, i)
    writer_ts.add_scalar('MSE', MSE_0, i)
    print(i, 'test_mse %.7g' % MSE_0, 'r_score%.3g' % r2_0)
    test_mse.append(MSE_0)
    test_r2.append(r2_0)

np.save(save_dir + '/test_r2', test_r2)
np.save(save_dir + '/train_r2', train_r2)
np.save(save_dir + '/test_mse', test_mse)
np.save(save_dir + '/train_mse', train_mse)
torch.save(net, save_dir + '/net.pkl')
writer_ts.close()
writer_tr.close()

print()
