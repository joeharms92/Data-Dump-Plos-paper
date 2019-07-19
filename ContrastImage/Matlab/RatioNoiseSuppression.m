function [ratioOrig, ratioNS] = RatioNoiseSuppression(tTotal, tLow, tHigh)

[m n] = size(tHigh);
tLow = tLow(:);
tHigh = tHigh(:);
list = find(tLow>1.0);
tLow(list) = 0.9999;

list = find(tHigh>1.0);
tHigh(list) = 0.9999;

dummy = find(tLow>0);
minNonZerolow = min(tLow(dummy));
list = find(tLow==0);
tLow(list) = minNonZerolow;

dummy = find(tHigh>0);
minNonZeroHigh = min(tHigh(dummy));
list = find(tHigh==0);
tHigh(list) = minNonZeroHigh;

tLowLinear = -log(tLow);
dummy = find(tLowLinear<=0);
tLowLinear(dummy) = 0.0001;
tHighLinear = -log(tHigh);

ratioOrig = reshape(tHighLinear./tLowLinear,m,n);

simMat = nonlocal_weight_fast(tTotal,0.001,20,1);
ratioNS = reshape(simMat'*ratioOrig(:),m,n);
