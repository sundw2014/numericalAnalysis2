m=1:10;
plot(3.^m./((10^-20).^(1./(2*m+2))),'o');
xlabel('加速次数m')
ylabel('计算项数N')