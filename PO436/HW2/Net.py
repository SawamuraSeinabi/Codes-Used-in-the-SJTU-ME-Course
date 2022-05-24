from torch import nn


class MLP(nn.Module):
    def __init__(self, insize=4, outsize=1):
        super(MLP, self).__init__()

        self.output = nn.Sequential(
            nn.Linear(insize, 32),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(32, outsize)
        )

    def forward(self, x):
        return self.output(x)
