clear;clc;close all;

% For a linear acceleration of 2 𝑚/𝑠, produce a graph of time vs speed for 10 seconds.

time = linspace(0,10);
speed = 2*time;
plot(time,speed);
xline(0);
yline(0);
xlabel("Time (s)");
ylabel("Speed (m/s)");