clear 
A=csvread('out.csv',2,0);
t1=111;
t=A(t1:end,1);
x1=A(t1:end,3);
x1_med=0.020294;
x1=x1-x1_med;
x2=A(t1:end,2);
x2=lowpass(x2,0.00005);
x2_med=0.068824;
x2=x2-x2_med;
figure(1)
grid on

clf
plot(t,x1,'r')
hold on
plot(t,x2,'k')

a=0;
for j=1:length(x2)-1
    ac=(t(j+1)-t(j))*x2(j);
    at=(t(j+1)-t(j))*(x2(j+1)-x2(j))/2;
    a(j+1)=ac+at+a(j);
end
    

% plot(t,2*10000*a,'b')
%plot(t,2*a-0.12,'b')

%%

plot(t,-1*a*780+0.89,'b')
legend('pinza','rogowski', 'rogintegrada')

% desfasado 0.101-0.09924 = 0.0018
% ciclo 0.1192-0.09926 = 0.0199
% 0.0199 360
% 0.0018 32.5628
