clear all
close all

load lenrTlow_toss5.txt
load lenrThigh_toss5.txt

[m n] = size(lenrThigh_toss5);
lenrTlow_toss5 = lenrTlow_toss5(:);
lenrThigh_toss5 = lenrThigh_toss5(:);
list = find(lenrTlow_toss5>1);
lenrTlow_toss5(list) = 1;

list = find(lenrThigh_toss5>1);
lenrThigh_toss5(list) = 1;

dummy = find(lenrTlow_toss5>0);
minNonZerolow = min(lenrTlow_toss5(dummy));
list = find(lenrTlow_toss5==0);
lenrTlow_toss5(list) = minNonZerolow;

dummy = find(lenrThigh_toss5>0);
minNonZeroHigh = min(lenrThigh_toss5(dummy));
list = find(lenrThigh_toss5==0);
lenrThigh_toss5(list) = minNonZeroHigh;

lenrLinearLow = -log(lenrTlow_toss5);
lenrLinearHigh = -log(lenrThigh_toss5);
lenrRatioImage5 = lenrLinearHigh./lenrLinearLow;
figure,imshow(reshape(lenrRatioImage5,m,n),[0 1.4])

load bremTlow_toss1.txt
load bremThigh_toss1.txt

list = find(bremTlow_toss1>1);
bremTlow_toss1(list) = 1;

list = find(bremThigh_toss1>1);
bremThigh_toss1(list) = 1;

dummy = find(bremTlow_toss1>0);
minNonZerolow = min(bremTlow_toss1(dummy));
list = find(bremTlow_toss1==0);
bremTlow_toss1(list) = minNonZerolow;

dummy = find(bremThigh_toss1>0);
minNonZeroHigh = min(bremThigh_toss1(dummy));
list = find(bremThigh_toss1==0);
bremThigh_toss1(list) = minNonZeroHigh;

bremLinearLow = -log(bremTlow_toss1);
bremLinearHigh = -log(bremThigh_toss1);
bremRatioImage = bremLinearHigh./bremLinearLow;
figure,imshow(bremRatioImage,[0 1.4])
