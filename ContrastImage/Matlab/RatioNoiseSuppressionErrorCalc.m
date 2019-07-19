function [ratioOrigErrorMap, ratioNSerrorMap] = RatioNoiseSuppressionErrorCalc(tTotal, tLow, tHigh, tLowError, tHighError)

[m n] = size(tHigh);
tLow = tLow(:);
tHigh = tHigh(:);
tLowError = tLowError(:);
tHighError = tHighError(:);

list = find(tLow>1.0);
tLow(list) = 0.9999;

list = find(tHigh>1.0);
tHigh(list) = 0.9999;

list = find(tLowError>1.0);
tLowError(list) = 0.9999;

list = find(tHighError>1.0);
tHighError(list) = 0.9999;

dummy = find(tLow>0);
minNonZerolow = min(tLow(dummy));
list = find(tLow==0);
tLow(list) = minNonZerolow;

dummy = find(tHigh>0);
minNonZeroHigh = min(tHigh(dummy));
list = find(tHigh==0);
tHigh(list) = minNonZeroHigh;

dummy = find(tLowError>0);
minNonZerolowError = min(tLowError(dummy));
list = find(tLowError==0);
tLowError(list) = minNonZerolowError;

dummy = find(tHighError>0);
minNonZeroHighError = min(tHighError(dummy));
list = find(tHighError==0);
tHighError(list) = minNonZeroHighError;

tLowLinear = -log(tLow);
dummy = find(tLowLinear<=0);
tLowLinear(dummy) = 0.0001;
tHighLinear = -log(tHigh);

tLowSq = tLow.*tLow;
tHighSq = tHigh.*tHigh;
lnTLowSq = tLowLinear.*tLowLinear;
lnTHighSq = tHighLinear.*tHighLinear;

ratioUncertaintyPt1 = tLowSq.*lnTLowSq.*tHighError.*tHighError;
ratioUncertaintyPt2 = tHighSq.*lnTHighSq.*tLowError.*tLowError;
ratioUncertaintyPt3 = tLowSq.*tHighSq.*lnTLowSq.*lnTLowSq;

ratioOrigVariance = (ratioUncertaintyPt1 + ratioUncertaintyPt2) ./ ratioUncertaintyPt3;
ratioOrigErrorMap = sqrt(ratioOrigVariance);

simMat = nonlocal_weight_fast(tTotal,0.001,20,1);
errorSqNS = simMat'*ratioOrigVariance(:);
errorSqNS = simMat'*errorSqNS;
ratioNSerrorMap = sqrt(errorSqNS);
ratioNSerrorMap = reshape(ratioNSerrorMap,m,n);
ratioOrigErrorMap = reshape(ratioOrigErrorMap,m,n);