clc;clear;close all;


%For a linear acceleration of 2 𝑚/𝑠, produce a graph of time vs displacement for 10 seconds.

time = linspace(0,10);
displacement = time.^2; % Using SUVAT equation
plot(time,displacement);
xline(0);
yline(0);
xlabel("Time (s)");
ylabel("Displacement (m)");