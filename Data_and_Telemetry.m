clc
clear
%Mass (prototype + pilot)
m = 65;%(kg)
%Gravity
g = 9.81;%(m/s�)
%Weight (prototype + pilot)
G = m*g;%(N)
%Axle distance
l = 1.274;%(m)
%GC position
x = 0.24;
%GC height
h = 0.262;%(m)
%Rolling coefficient
f = 0.011;
%Tire-lane friction coefficient
u = 0.8;
%Front tire diameter
Dd = 0.3556;%(m)
%Front tire static radius
red = 0.47*Dd;%(m)
%Front tire dynamic radius
rdd = 1.02*red;%(m)
%Rear tire diameter
Dt = 0.4064;%(m)
%Rear tire static radius
ret = 0.47*Dt;%(m)
%Rear tire dynamic radius
rdt = 1.02*ret;%(m)
%Front wheel moment of inertia
Jrd = 8431.56*10^-6;%(kg.mm�)
%Rear wheel moment of inertia
Jrt = 19912.38*10^-6;%(kg.mm�)
%Motor moment of inertia
Jm = 2067.07*10^-6;%(kg.mm�)
%Front area
A = 0.26;%(m�)
%Drag coefficient
Cx = 0.1;
%Slip
e = 0.01;
%RPM data
rpm = [25.2,38.9,53.9,67.5,82.5,95.5,111.9,124.1,139.2,152.8,167.1,180.5,194.4,208,223.1,236,248.3,261.9,273.5,288.5,298.8,313.8,326.1,330.1,341.1,354,357.4];
%Track distance
dt = 10805;

%Case 1:
printf("\nCase 1:\n")

%Throttle data
Th = [10,14,18,22,26,30,34,38,42,46,50,54,58,62,66,70,74,78,82,86,90,94,98,100,100,100,100];

%Power data
Pci = [5,12,18,28,36,50,54,73,82,96,108,123,138,153,161,180,201,216,241,247,279,284,301,325,265,191,171];

%Consumption data
Ci = [5.6,6.9,6.9,8.1,8.1,9.7,8.7,10.4,10.2,10.9,11.1,11.6,12.0,12.3,12.0,12.6,13.4,13.5,14.4,14.0,15.2,14.7,15.1,15.9,12.6,9.0,8.1];

for i = 1:27
  %Tangential velocity
  vt(i) = rpm(i)*2*pi*rdt/60;
  %Vehicle velocity
  v(i) = vt(i)*(1 - e);
  %Air drag
  Qa(i) = 1.22*v(i)^2*Cx*A;
  %Rolling resistance
  Qr = f*G;
  %Liquid power
  Pi(i) = Pci(i) - Qa(i)*vt(i) - Qr*vt(i);
end
for i = 2:27
  ai(i-1) = Pi(i-1)/(m*vt(i-1)*(1 + ((2*Jrd/(rdd^2)) + (Jrt + Jm)/(rdt^2))/m));
  ti(i) = (v(i) - v(i-1))/ai(i-1);
  di(i) = (v(i)^2 - v(i-1)^2)/2*ai(i-1);
  
  tit(1) = 0;
  Cit(1) = 0;
  
  tit(i) = tit(i-1) + ti(i);
  Cit(i) = Cit(i-1) + Ci(i-1)*di(i)/1000;
end
ai(27) = Pi(27)/(m*vt(27)*(1 + ((2*Jrd/(rdd^2)) + (Jrt + Jm)/(rdt^2))/m));
dip(1) = 0;
for i = 2:27
  ais(1) = ai(1);
  ais(i) = ais(i-1) + ai(i);
  dip(i) = dip(i-1) + di(i);
end
printf("\nAverage acceleration:\n")
aim = ais(27)/27
printf("\nTime to reach 26 km/h:\n")
tit = tit(27)
printf("\nDistance traveled until reaching 26 km/h:\n")
dip = dip(27)
printf("\nAverage speed to reach 26 km/h:\n")
vim = dip*3.6/tit
printf("\nRemaining distance:\n")
dir = dt - dip
printf("\nTime keeping constant speed:\n")
tivc = dir/v(27)
printf("\nTotal race time:\n")
tirace = tivc + tit
printf("\nAverage race speed:\n")
vimrace = dt*3.6/tirace
printf("\nConsumption to reach 26 km/h:\n")
Cit = Cit(27)
printf("\nConsumption during constant speed:\n")
Cic = 3.4*v(27)*tivc/3600
printf("\nTotal consumption of the race:\n")
Cirace = Cit + Cic
printf("\nVehicle autonomy:\n")
Ai = dt/Cirace

%Case 2:
printf("\nCase 2:\n")

%Power data
Pc100 = [166,244,321,383,445,493,546,582,622,654,685,711,734,755,736,705,671,627,585,524,479,408,346,325,265,191,171];

%Consumption data
C = [585.6,380.3,274.4,218.9,179.1,154.8,132.1,119.1,106.2,96.7,88.4,81.8,76,71,62.2,54.6,48.1,41.5,36.3,30.2,26.4,21.1,17.2,15.9,12.6,9.0,8.1];


for i = 1:27
  %Tangential velocity
  vt100(i) = rpm(i)*2*pi*rdt/60;
  %Vehicle velocity
  v100(i) = vt100(i)*(1 - e);
  %Air drag
  Qa100(i) = 1.22*v100(i)^2*Cx*A;
  %Rolling resistance
  Qr = f*G;
  %Liquid power
  P100(i) = Pc100(i) - Qa100(i)*vt100(i) - Qr*vt100(i);
end

for i = 2:27
  a(i-1) = P100(i-1)/(m*vt100(i-1)*(1 + ((2*Jrd/(rdd^2)) + (Jrt + Jm)/(rdt^2))/m));
  t(i) = (v100(i) - v100(i-1))/a(i-1);
  d(i) = (v100(i)^2 - v100(i-1)^2)/2*a(i-1);
  
  tt(1) = 0;
  Ct(1) = 0;
  
  tt(i) = tt(i-1) + t(i);
  Ct(i) = Ct(i-1) + C(i-1)*d(i)/1000;
end
a(27) = P100(27)/(m*vt100(27)*(1 + ((2*Jrd/(rdd^2)) + (Jrt + Jm)/(rdt^2))/m));
dp(1) = 0;
for i = 2:27
  as(1) = a(1);
  as(i) = as(i-1) + a(i);
  dp(i) = dp(i-1) + d(i);
end
printf("\nAverage acceleration:\n")
am = as(27)/27
printf("\nTime to reach 26 km/h:\n")
tt = tt(27)
printf("\nDistance traveled until reaching 26 km/h:\n")
dp = dp(27)
printf("\nAverage speed to reach 26 km/h:\n")
vm = dp*3.6/tt
printf("\nRemaining distance:\n")
dr = dt - dp
printf("\nTime keeping constant speed:\n")
tvc = dr/v(27)
printf("\nTotal race time:\n")
trace = tvc + tt
printf("\nAverage race speed:\n")
vmrace = dt*3.6/trace
printf("\nConsumption to reach 26 km/h:\n")
Ct = Ct(27)
printf("\nConsumption during constant speed:\n")
Cc = 3.4*v(27)*tvc/3600
printf("\nTotal consumption of the race:\n")
Crace = Ct + Cc
printf("\nVehicle autonomy:\n")
A100 = dt/Crace

printf("\nFinal results:\n")

printf("\nEnergy saved percentage:\n")
Ep = (1 - (Cirace/Crace))*100
printf("\nEnergy saved:\n")
Eq = Crace - Cirace
printf("\nAutonomy difference:\n")
Ad = Ai - A100