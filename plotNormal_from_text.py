### Extract Zip file for 14 materials in does_dep_14 folder
### Install python3
### place this file at same location as does_dep_14 folder
### Run this file from vscode code runner or use this command from tearminal:
## ## /usr/bin/python3 /home/aanamika/..location of does_dep_14 folder.../plotNormal_from_text.py

import matplotlib.pyplot as plt
import numpy as np
from numpy.core.fromnumeric import size
import pandas as pd
from sklearn import preprocessing
import os

Path = "dose_dep_14/Dose&Edep_14materials_N5000/Dosefiles_N_5000"
fileList = os.listdir(Path)

colnames = ['# iX', 'iY', 'iZ', 'total(value) [Gy]', 'total(val^2)', 'entry']

ax = plt.gca()
bx = plt.gca()

number = 20
cmap = plt.get_cmap('gnuplot')
colors = [cmap(i) for i in np.linspace(0, 1, number)]

Count = 0
for file in fileList:
    df = pd.read_csv(Path+'/'+file ,skiprows=3,header=None,names=colnames,sep=',')
    
    px = df.values #returns a numpy array
    min_max_scaler = preprocessing.MinMaxScaler()
    standard_scaler = preprocessing.StandardScaler()
    
    x_scaled = min_max_scaler.fit_transform(px)
    df = pd.DataFrame(x_scaled, columns=df.columns)

    df['MeanData'] = df['total(value) [Gy]'].rolling(window=50, min_periods=1).mean()

    MaxVal = df['MeanData'].max()
    MaxVal_37 = MaxVal*0.37

    Dataframe_37 = df.loc[(df['MeanData']>=(MaxVal_37-.05)) & (df['MeanData']<=(MaxVal_37+.05))]
    print(Dataframe_37)
    print("===============================================")
    print("Max value %d and 37\% is %d", MaxVal, MaxVal_37)

    #MaxVal_y_index =  df.index[df['MeanData'] >= MaxVal_37 and df['MeanData'] < MaxVal_37 + 1 ].tolist()
    #MaxVal_x_index = df.iloc[MaxVal_y_index]
    #print("37x %d and 37y %d ", MaxVal_x_index, MaxVal_y_index)

    df.plot(kind='line',x='iZ', y='MeanData', label=file, color=colors[Count], ax=ax)
    Dataframe_37.plot(kind='scatter',x='iZ', y='MeanData', label=file, color=colors[Count], ax=bx)

    # point = pd.DataFrame({'x':})
    # ax = point.plot(x='x', y='y', ax=ax, style='bx', label='point')

    Count+=1

plt.legend()
plt.show()