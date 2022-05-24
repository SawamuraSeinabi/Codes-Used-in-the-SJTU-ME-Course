import torch
import numpy as np
from torch.utils.data import Dataset, DataLoader
import pandas as pd


class Dataset_myself(Dataset):
    def __init__(self, csv_dir='Data\DATA_training.csv', trans=False):
        data = pd.read_csv(csv_dir, low_memory=False)
        data.dropna(how='any', inplace=True)
        data.drop_duplicates(inplace=True)
        # cols = ['Ambient Temperature', 'BearingShaftTemperature', 'Blade1PitchAngle',
        #        'Blade2PitchAngle', 'Blade3PitchAngle', 'ControlBoxTemperature',
        #        'GearboxBearingTemperature', 'GearboxOilTemperature', 'GeneratorRPM',
        #        'GeneratorWinding1Temperature', 'GeneratorWinding2Temperature', 'HubTemperature',
        #        'MainBoxTemperature', 'NacellePosition', 'RotorRPM', 'WindDirection', 'WindSpeed']
        cols = ['GearboxOilTemperature', 'GeneratorWinding2Temperature', 'WindSpeed', 'RotorRPM']
        '''归一化'''
        data_in = data[cols]
        self.len = int(len(data))
        data_in = (data_in - data_in.min()) / (data_in.max() - data_in.min())
        input = data_in.values

        target_in = data['ActivePower']
        target_in = (target_in - target_in.min()) / (target_in.max() - target_in.min())
        target0 = target_in.values
        target = np.array(target0).reshape(len(target0), 1)

        input = input.astype(np.float32)
        target = target.astype(np.float32)
        self.input = torch.from_numpy(input)
        self.target = torch.from_numpy(target)

    def __getitem__(self, index):
        return self.input[index].float(), self.target[index].float()

    def __len__(self):
        return self.len


if __name__ == '__main__':
    file_csv = 'Data/DATA_training.csv'
    dataset_example = Dataset_myself(file_csv)
    '''loader'''
    my_loader = DataLoader(dataset_example, batch_size=30, shuffle=True, drop_last=False)
