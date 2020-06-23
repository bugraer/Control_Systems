
clc
den = [1 12 20];
num = [200 0];
G = tf(num, den)
bode(G),grid