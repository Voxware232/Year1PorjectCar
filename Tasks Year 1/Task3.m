clc;clear;close all;

% For a linear acceleration of 2 𝑚/𝑠, produce a graph of time vs displacement which stops after 5m has been travelled.

time = linspace(0,sqrt(5));
displacement = time.^2; % Using SUVAT equation
plot(time,displacement);
xline(0);
yline(0);
xlabel("Time (s)");
ylabel("Displacement (m)");