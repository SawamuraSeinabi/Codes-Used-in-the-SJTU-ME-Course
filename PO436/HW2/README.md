# 风力发电功率预测-项目报告

***

## 数据处理过程

一开始是假设参数全相关，如下：

```python
 cols = ['Ambient Temperature', 'BearingShaftTemperature', 'Blade1PitchAngle',
        'Blade2PitchAngle', 'Blade3PitchAngle', 'ControlBoxTemperature',
        'GearboxBearingTemperature', 'GearboxOilTemperature', 'GeneratorRPM',
        'GeneratorWinding1Temperature', 'GeneratorWinding2Temperature', 'HubTemperature',
        'MainBoxTemperature', 'NacellePosition', 'RotorRPM', 'WindDirection', 'WindSpeed']
```
然而随后经过相关性分析，进行PCA验证，发现只有四个参数与其强相关，分别是`'GearboxOilTemperature', 'GeneratorWinding2Temperature', 'WindSpeed', 'RotorRPM'`这四个参数。与作业中要求***通过风力发电的叶片动作参数、零部件温度参数、风力和风向预测当前的发电功率***也是相符的。因此最后训练进网络的为这四个特征参数。

> PCA(Principal Component Analysis)，即主成分分析方法，是一种使用最广泛的数据降维算法。PCA的主要思想是将n维特征映射到k维上，这k维是全新的正交特征也被称为主成分，是在原有n维特征的基础上重新构造出来的k维特征。PCA的工作就是从原始的空间中顺序地找一组相互正交的坐标轴，新的坐标轴的选择与数据本身是密切相关的。其中，第一个新坐标轴选择是原始数据中方差最大的方向，第二个新坐标轴选取是与第一个坐标轴正交的平面中使得方差最大的，第三个轴是与第1,2个轴正交的平面中方差最大的。依次类推，可以得到n个这样的坐标轴。通过这种方式获得的新的坐标轴，我们发现，大部分方差都包含在前面k个坐标轴中，后面的坐标轴所含的方差几乎为0。于是，我们可以忽略余下的坐标轴，只保留前面k个含有绝大部分方差的坐标轴。事实上，这相当于只保留包含绝大部分方差的维度特征，而忽略包含方差几乎为0的特征维度，实现对数据特征的降维处理。
>
> - 来自[主成分分析（PCA）原理详解](https://blog.csdn.net/program_developer/article/details/80632779)

## 模型设计思路

综合考虑输入特征的维度，输出维度及问题本身的隐态空间大小，我们选用了多层感知机模型，层数为2，每层神经元个数为32个：

```python
class MLP(nn.Module):
    def __init__(self, insize=4, outsize=1):
        super(MLP, self).__init__()

        self.output = nn.Sequential(
            nn.Linear(insize, 32),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(32, outsize)
        )
```

神经网络训练中，我是将`ReLU()`函数和`tan-sigmoid()`函数进行了对比训练，最终发现`ReLU()`函数的效果较好，同时也防止了使用MSE损失函数的时候，梯度传播出现传播量较小，达不到训练效果的现象。也是因为使用了`ReLU()`函数，最终才能将强相关参数缩减到四个。

同时，为了防止过拟合，我加入了`Dropout()`函数。

- 调参过程

通过多次模拟测定，发现0.2在验证集上效果比较好，同时收敛比较快，就选择了0.2作为dropout rate。

## 模型预测结果

![image-20201126001303788](C:\Users\chenchen\AppData\Roaming\Typora\typora-user-images\image-20201126001303788.png)

![image-20201126001240096](C:\Users\chenchen\AppData\Roaming\Typora\typora-user-images\image-20201126001240096.png)

但是毕竟是通过数据分析得到的结果，与实际风力发电的功率数值是否吻合，相差大不大还不得而知。