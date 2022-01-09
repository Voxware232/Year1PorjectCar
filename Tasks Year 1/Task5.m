clc;clear;close all;

%For an angular acceleration of 0.5 𝑟𝑎𝑑/𝑠
%, produce a graph of time vs angular displacement
% which stops after 90 degrees.

% Angular suvats can be used, similar to task 4

a = 0.5*57.29; % Conversion to degrees per second
s = 90;
t = sqrt((2*s)/a); % Total time

time = linspace(0,t);
% Using suvat s = ut + 1/2 a t^2 and u = 0
displacement = 0.5*a*time.^2;
    
plot(time,displacement);

hold on;

xline(0);
yline(0);
xlabel("Time (s)");
ylabel("Displacement (degrees)");