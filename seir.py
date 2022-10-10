
import scipy.integrate as spi
import numpy as np
import pylab as pl
alpha=1.4247
beta=0.14286
TS=1.0 #观察间隔
ND=70.0 #观察结束日期
S0=1-1e-6 #初始易感人数
I0=1e-6 #初始感染人数
INPUT = (S0, I0, 0.0)
def diff_eqs(INP,t):
    '''The main set of equations'''
    Y=np.zeros((3))
    V = INP
    Y[0] = - alpha * V[0] * V[1]
    Y[1] = alpha * V[0] * V[1] - beta * V[1]
    Y[2] = beta * V[1]
    return Y
t_start = 0.0
t_end = ND
t_inc = TS
t_range = np.arange(t_start, t_end+t_inc, t_inc) #生成日期范围
RES = spi.odeint(diff_eqs,INPUT,t_range)

pl.subplot(111)
pl.plot(RES[:,0], '-g', label='Susceptible')
pl.plot(RES[:,1], '-r', label='Infective')
pl.plot(RES[:,2], '-k', label='Removal')
pl.legend(loc=0)
pl.title('SIR_Model')
pl.xlabel('Time')
pl.ylabel('Numbers')
pl.xlabel('Time')
pl.show()
