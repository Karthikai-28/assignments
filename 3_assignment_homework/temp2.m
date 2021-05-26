L=3;
H=3;

% Number of nodes
nx=9;
ny=9;
x=linspace(0,L,nx);
y=linspace(0,H,ny);

T=ones(9,5)*5;
T(:,1)=0;T(:,5)=0;
T(1,:)=0;T(9,:)=100;
for j=1:5
    jb=6-j;
    fprintf('%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f\n',T(:,jb))
end    
omega=1.3;
for n=1:100
for i=2:8
    for j=2:4
        e(i,j) = 0.25*(T(i,j-1) + T(i,j+1) + T(i-1,j) + T(i+1,j)) - T(i,j);
        T(i,j)=T(i,j)+omega*e(i,j);
    end
end
if max(abs(e))<.01, break, end
end
fprintf('Number of iteration = %g\n',n)
for j=1:5
    jb=6-j;
    fprintf('%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f%8.2f\n',T(:,jb))
end
contourf(x,y,T)