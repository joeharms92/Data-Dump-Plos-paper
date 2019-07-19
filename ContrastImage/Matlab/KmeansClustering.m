clear all
close all
load lenrTlow_toss1.txt
load lenrThigh_toss1.txt

[m n] = size(lenrThigh_toss1);
lenrTlow_toss1 = lenrTlow_toss1(:);
lenrThigh_toss1 = lenrThigh_toss1(:);

list = find(lenrTlow_toss1>1);
lenrTlow_toss1(list) = 1;

list = find(lenrThigh_toss1>1);
lenrThigh_toss1(list) = 1;

dummy = find(lenrTlow_toss1>0);
minNonZerolow = min(lenrTlow_toss1(dummy));
list = find(lenrTlow_toss1==0);
lenrTlow_toss1(list) = minNonZerolow;

dummy = find(lenrThigh_toss1>0);
minNonZeroHigh = min(lenrThigh_toss1(dummy));
list = find(lenrThigh_toss1==0);
lenrThigh_toss1(list) = minNonZeroHigh;

lenrLinearLow = -log(lenrTlow_toss1);
lenrLinearHigh = -log(lenrThigh_toss1);

k = 14;
nReps = 10;
meansLow = zeros(k,1);
meansHigh = zeros(k,1);
ratioImage = zeros(size(lenrTlow_toss1));
tic
[idx, C] = kmedoids([lenrTlow_toss1 lenrThigh_toss1],k,'Replicates',nReps);
CM = jet(k);
figure;
hold on
for idxIter = 1:k
	scatter(lenrTlow_toss1(idx==idxIter),lenrThigh_toss1(idx==idxIter),'markerfacecolor',CM(idxIter,:),'marker','.')
	meansLow(idx==idxIter) = mean(lenrTlow_toss1(idx==idxIter));
	meansHigh(idx==idxIter) = mean(lenrThigh_toss1(idx==idxIter));
	ratioImage(idx==idxIter) = log(meansHigh(idx==idxIter))./log(meansLow(idx==idxIter));
	end
hold off
toc
ratioImage = reshape(ratioImage,m,n);
figure,imshow(ratioImage,[0.4 1.4])
RodMeans(ratioImage)