import soundfile as sf
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np

input_signal,fs = sf.read('filter_codes_Sound_Noise.wav')
sample_freq = fs
order = 4
cutoff_freq = 4000.0
Wn = 2*cutoff_freq/sample_freq
b,a = signal.butter(order,Wn, 'low')
output_signal = signal.filtfilt(b,a,input_signal)
sf.write('Sound with Reduced Noise.wav',output_signal,fs)

N = len(input_signal)
w = np.linspace(0,2*np.pi,N)

num = np.polyval(b,np.exp(1j*w))
den = np.polyval(a,np.exp(1j*w))
Hz = num/den

X = np.fft.fft(input_signal)
Y = np.multiply(Hz,X)
y = np.fft.ifft(Y).real

sf.write('7.1_Sound_With_ReducedNoise.wav',y,fs)
####plotting

t = np.linspace(0,len(output_signal)-1,len(output_signal))

plt.figure(1)
plt.subplot(2,1,1)
plt.plot(t,output_signal)
plt.xlabel('time')
plt.ylabel('built-in function')

plt.subplot(2,1,2)
plt.plot(t,y,color='orange')
plt.xlabel('time')
plt.ylabel('our function')

plt.figure(2)
freq = np.arange(-np.pi,np.pi,2*np.pi/len(input_signal))
Y1 = np.abs((np.fft.fftshift(np.fft.fft(y))))
O1 = np.abs(np.fft.fftshift(np.fft.fft(output_signal)))

plt.subplot(2,1,1)
plt.plot(freq,O1)
plt.xlabel('frequency')
plt.ylabel('built-in function')

plt.subplot(2,1,2)
plt.plot(freq,Y1,color='orange')
plt.xlabel('frequency')
plt.ylabel('our function')

plt.show()
