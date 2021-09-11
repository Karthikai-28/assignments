clear all;
close all;
clc;

L=3;
H=3;

% Number of nodes
nx=9;
ny=9;
x=linspace(0,L,nx);
y=linspace(0,H,ny);

%Temperature Initialization
T=zeros(nx,ny);

%Boundary Conditions
T(:,1)=25;
T(1,:)=20;
T(:,end)=20;
T(end,:)=30;
T_old=T;


err = 27.5;
tol = 1e-6

A = [4 -1 -1 0; -1 4 0 -1; -1 0 4 -1; 0 -1 -1 4]

X=unique(x1x2x3x4(:,1));
b=[45 40 55 50]
b_new=[35 20 35 30]

A_inv=[7/24 1/12 1/12 1/24; 1/12 7/24 1/24 1/12; 1/12 1/24 7/24 1/12; 1/24 1/12 1/12 7/24]
while err>tol
    for i=4:nx-1
        for j=4:ny-1
            X=inv(A)*b
            %x1=(20+25+x2+x3)/4
            %x2=(20+20+x1+x4)/4
            %x3=(25+30+x1+x4)/4
            %x4=(20+30+x2+x3)/4
        end
    end
    err = abs(max(max(T-T_old)))
    T_old=T
end
contourf(x,y,T)
