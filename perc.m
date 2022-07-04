clear; clc; clf;
a=load("dataIav1000.txt");
b=load("dataIavtonos1000.txt");
c=load("datapmax1000.txt");

%% PLOTS
figure(1)
plot(a(:,1),a(:,2),'*-')
title('Mέσο μέγεθος σμηνών συναρτήσει πιθανότητας - I_{av}(p)')
xlabel('p')
ylabel('I_{av}')
figure(2)
plot(b(:,1),b(:,2))
title("Mέσο μέγεθος σμηνών, χωρίς το μεγαλύτερο cluster, συναρτήσει πιθανότητας - I'_{av}(p)")
xlabel('p')
ylabel("I'_{av}")
figure(3)
plot(c(:,1),c(:,2))
title('Αναλογία του μεγαλύτερου σμήνους ως προς τα υπόλοιπα συναρτήσει πιθανότητας - P_{pax}(p)')
xlabel('p')
ylabel('P_{max}')

%% Briskw thn pc
temp=0.0;
for i=1:length(b)
       if temp<b(i,2)
           temp=b(i,2);
           imax=i;
           pc=b(i,1);
       end
end
disp(pc)

%% Statheres
xI=abs(a(imax-5:imax-1,1)-pc);
yI=a(imax-5:imax-1,2);
figure(4)
plot(log10(xI),log10(yI),'*')
hold on
pI=polyfit(log10(xI),log10(yI),1);
yfitI=polyval(pI,log10(xI));
plot(log10(xI),yfitI)
title('Διάγραμμα I_{av}(p) για πιθανότητες p<p_c')
xlabel('log_{10}(p-p_c)')
ylabel('log_{10}(I_{av})')
legend({' ',['y=',num2str(pI(1)),'*x + ','(',num2str(pI(2)),')']},'location','west');
text(-1.8,1.7,['γ=',num2str(abs(pI(1)))],'color',[0.2 0.3 1],'FontSize',13);

xIt=abs(b(imax+1:imax+8,1)-pc);
yIt=b(imax+1:imax+8,2);
figure(5)
plot(log10(xIt),log10(yIt),'*')
hold on
pIt=polyfit(log10(xIt),log10(yIt),1);
yfitIt=polyval(pIt,log10(xIt));
plot(log10(xIt),yfitIt)
title("Διάγραμμα I'_{av}(p) για πιθανότητες p>p_c")
xlabel('log_{10}(p-p_c)')
ylabel("log_{10}(I'_{av})")
legend({' ',['y=',num2str(pIt(1)),'*x + ','(',num2str(pIt(2)),')']},'location','west');
text(-1.9,-0.2,['γ^.=',num2str(abs(pIt(1)))],'color',[0.2 0.3 1],'FontSize',13);

xIp=abs(c(imax-3:imax-1,1)-pc);
yIp=c(imax-3:imax-1,2);
figure(6)
plot(log10(xIp),log10(yIp),'*')
hold on
pp=polyfit(log10(xIp),log10(yIp),1);
yfitIp=polyval(pp,log10(xIp));
plot(log10(xIp),yfitIp)
title("Διάγραμμα P'_{max}(p) για πιθανότητες p<p_c")
xlabel('log_{10}(p-p_c)')
ylabel("log_{10}(P'_{max})")
legend({['y=',num2str(pp(1)),'*x + ','(',num2str(pp(2)),')']},'location','west');
text(-1.96,-1.75,['β=',num2str(abs(pp(1)))],'color',[0.2 0.3 1],'FontSize',13);