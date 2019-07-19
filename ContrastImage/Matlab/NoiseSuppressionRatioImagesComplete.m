clear all
close all
tic
load lenrTlow_toss1.txt
load lenrThigh_toss1.txt
load lenrTtotal_toss1.txt
load lenrTlow_toss1_errorSTD.txt
load lenrThigh_toss1_errorSTD.txt

[ratioOriglenr_toss1, ratioNSlenr_toss1] = RatioNoiseSuppression(lenrTtotal_toss1, lenrTlow_toss1, lenrThigh_toss1);
[ratioOrigErrorlenr_toss1, ratioNSErrorlenr_toss1] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss1, lenrTlow_toss1, lenrThigh_toss1, lenrTlow_toss1_errorSTD, lenrThigh_toss1_errorSTD);
rodMeanslenrOrig_toss1 = RodMeans(ratioOriglenr_toss1)
rodMeanslenrNS_toss1 = RodMeans(ratioNSlenr_toss1)
dlmwrite('ratioOriglenr_toss1.txt', ratioOriglenr_toss1, ' ');
dlmwrite('ratioNSlenr_toss1.txt', ratioNSlenr_toss1, ' ');
dlmwrite('ratioOrigErrorlenr_toss1.txt', ratioOrigErrorlenr_toss1, ' ');
dlmwrite('ratioNSErrorlenr_toss1.txt', ratioNSErrorlenr_toss1, ' ');

load lenrTlow_toss2.txt
load lenrThigh_toss2.txt
load lenrTtotal_toss2.txt
load lenrTlow_toss2_errorSTD.txt
load lenrThigh_toss2_errorSTD.txt

[ratioOriglenr_toss2, ratioNSlenr_toss2] = RatioNoiseSuppression(lenrTtotal_toss2, lenrTlow_toss2, lenrThigh_toss2);
[ratioOrigErrorlenr_toss2, ratioNSErrorlenr_toss2] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss2, lenrTlow_toss2, lenrThigh_toss2, lenrTlow_toss2_errorSTD, lenrThigh_toss2_errorSTD);
rodMeanslenrOrig_toss2 = RodMeans(ratioOriglenr_toss2)
rodMeanslenrNS_toss2 = RodMeans(ratioNSlenr_toss2)
dlmwrite('ratioOriglenr_toss2.txt', ratioOriglenr_toss2, ' ');
dlmwrite('ratioNSlenr_toss2.txt', ratioNSlenr_toss2, ' ');
dlmwrite('ratioOrigErrorlenr_toss2.txt', ratioOrigErrorlenr_toss2, ' ');
dlmwrite('ratioNSErrorlenr_toss2.txt', ratioNSErrorlenr_toss2, ' ');

load lenrTlow_toss3.txt
load lenrThigh_toss3.txt
load lenrTtotal_toss3.txt
load lenrTlow_toss3_errorSTD.txt
load lenrThigh_toss3_errorSTD.txt

[ratioOriglenr_toss3, ratioNSlenr_toss3] = RatioNoiseSuppression(lenrTtotal_toss3, lenrTlow_toss3, lenrThigh_toss3);
[ratioOrigErrorlenr_toss3, ratioNSErrorlenr_toss3] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss3, lenrTlow_toss3, lenrThigh_toss3, lenrTlow_toss3_errorSTD, lenrThigh_toss3_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss3.txt', ratioOrigErrorlenr_toss3, ' ');
dlmwrite('ratioNSErrorlenr_toss3.txt', ratioNSErrorlenr_toss3, ' ');
rodMeanslenrOrig_toss3 = RodMeans(ratioOriglenr_toss3)
rodMeanslenrNS_toss3 = RodMeans(ratioNSlenr_toss3)
dlmwrite('ratioOriglenr_toss3.txt', ratioOriglenr_toss3, ' ');
dlmwrite('ratioNSlenr_toss3.txt', ratioNSlenr_toss3, ' ');

load lenrTlow_toss4.txt
load lenrThigh_toss4.txt
load lenrTtotal_toss4.txt
load lenrTlow_toss4_errorSTD.txt
load lenrThigh_toss4_errorSTD.txt

[ratioOriglenr_toss4, ratioNSlenr_toss4] = RatioNoiseSuppression(lenrTtotal_toss4, lenrTlow_toss4, lenrThigh_toss4);
[ratioOrigErrorlenr_toss4, ratioNSErrorlenr_toss4] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss4, lenrTlow_toss4, lenrThigh_toss4, lenrTlow_toss4_errorSTD, lenrThigh_toss4_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss4.txt', ratioOrigErrorlenr_toss4, ' ');
dlmwrite('ratioNSErrorlenr_toss4.txt', ratioNSErrorlenr_toss4, ' ');
rodMeanslenrOrig_toss4 = RodMeans(ratioOriglenr_toss4)
rodMeanslenrNS_toss4 = RodMeans(ratioNSlenr_toss4)
dlmwrite('ratioOriglenr_toss4.txt', ratioOriglenr_toss4, ' ');
dlmwrite('ratioNSlenr_toss4.txt', ratioNSlenr_toss4, ' ');

load lenrTlow_toss5.txt
load lenrThigh_toss5.txt
load lenrTtotal_toss5.txt
load lenrTlow_toss5_errorSTD.txt
load lenrThigh_toss5_errorSTD.txt

[ratioOriglenr_toss5, ratioNSlenr_toss5] = RatioNoiseSuppression(lenrTtotal_toss5, lenrTlow_toss5, lenrThigh_toss5);
[ratioOrigErrorlenr_toss5, ratioNSErrorlenr_toss5] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss5, lenrTlow_toss5, lenrThigh_toss5, lenrTlow_toss5_errorSTD, lenrThigh_toss5_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss5.txt', ratioOrigErrorlenr_toss5, ' ');
dlmwrite('ratioNSErrorlenr_toss5.txt', ratioNSErrorlenr_toss5, ' ');
rodMeanslenrOrig_toss5 = RodMeans(ratioOriglenr_toss5)
rodMeanslenrNS_toss5 = RodMeans(ratioNSlenr_toss5)
dlmwrite('ratioOriglenr_toss5.txt', ratioOriglenr_toss5, ' ');
dlmwrite('ratioNSlenr_toss5.txt', ratioNSlenr_toss5, ' ');

load lenrTlow_toss6.txt
load lenrThigh_toss6.txt
load lenrTtotal_toss6.txt
load lenrTlow_toss6_errorSTD.txt
load lenrThigh_toss6_errorSTD.txt

[ratioOriglenr_toss6, ratioNSlenr_toss6] = RatioNoiseSuppression(lenrTtotal_toss6, lenrTlow_toss6, lenrThigh_toss6);
[ratioOrigErrorlenr_toss6, ratioNSErrorlenr_toss6] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss6, lenrTlow_toss6, lenrThigh_toss6, lenrTlow_toss6_errorSTD, lenrThigh_toss6_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss6.txt', ratioOrigErrorlenr_toss6, ' ');
dlmwrite('ratioNSErrorlenr_toss6.txt', ratioNSErrorlenr_toss6, ' ');
rodMeanslenrOrig_toss6 = RodMeans(ratioOriglenr_toss6)
rodMeanslenrNS_toss6 = RodMeans(ratioNSlenr_toss6)
dlmwrite('ratioOriglenr_toss6.txt', ratioOriglenr_toss6, ' ');
dlmwrite('ratioNSlenr_toss6.txt', ratioNSlenr_toss6, ' ');

load lenrTlow_toss7.txt
load lenrThigh_toss7.txt
load lenrTtotal_toss7.txt
load lenrTlow_toss7_errorSTD.txt
load lenrThigh_toss7_errorSTD.txt

[ratioOriglenr_toss7, ratioNSlenr_toss7] = RatioNoiseSuppression(lenrTtotal_toss7, lenrTlow_toss7, lenrThigh_toss7);
[ratioOrigErrorlenr_toss7, ratioNSErrorlenr_toss7] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss7, lenrTlow_toss7, lenrThigh_toss7, lenrTlow_toss7_errorSTD, lenrThigh_toss7_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss7.txt', ratioOrigErrorlenr_toss7, ' ');
dlmwrite('ratioNSErrorlenr_toss7.txt', ratioNSErrorlenr_toss7, ' ');
rodMeanslenrOrig_toss7 = RodMeans(ratioOriglenr_toss7)
rodMeanslenrNS_toss7 = RodMeans(ratioNSlenr_toss7)
dlmwrite('ratioOriglenr_toss7.txt', ratioOriglenr_toss7, ' ');
dlmwrite('ratioNSlenr_toss7.txt', ratioNSlenr_toss7, ' ');

load lenrTlow_toss8.txt
load lenrThigh_toss8.txt
load lenrTtotal_toss8.txt
load lenrTlow_toss8_errorSTD.txt
load lenrThigh_toss8_errorSTD.txt

[ratioOriglenr_toss8, ratioNSlenr_toss8] = RatioNoiseSuppression(lenrTtotal_toss8, lenrTlow_toss8, lenrThigh_toss8);
[ratioOrigErrorlenr_toss8, ratioNSErrorlenr_toss8] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss8, lenrTlow_toss8, lenrThigh_toss8, lenrTlow_toss8_errorSTD, lenrThigh_toss8_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss8.txt', ratioOrigErrorlenr_toss8, ' ');
dlmwrite('ratioNSErrorlenr_toss8.txt', ratioNSErrorlenr_toss8, ' ');
rodMeanslenrOrig_toss8 = RodMeans(ratioOriglenr_toss8)
rodMeanslenrNS_toss8 = RodMeans(ratioNSlenr_toss8)

dlmwrite('ratioOriglenr_toss8.txt', ratioOriglenr_toss8, ' ');
dlmwrite('ratioNSlenr_toss8.txt', ratioNSlenr_toss8, ' ');

load lenrTlow_toss9.txt
load lenrThigh_toss9.txt
load lenrTtotal_toss9.txt
load lenrTlow_toss9_errorSTD.txt
load lenrThigh_toss9_errorSTD.txt

[ratioOriglenr_toss9, ratioNSlenr_toss9] = RatioNoiseSuppression(lenrTtotal_toss9, lenrTlow_toss9, lenrThigh_toss9);
[ratioOrigErrorlenr_toss9, ratioNSErrorlenr_toss9] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss9, lenrTlow_toss9, lenrThigh_toss9, lenrTlow_toss9_errorSTD, lenrThigh_toss9_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss9.txt', ratioOrigErrorlenr_toss9, ' ');
dlmwrite('ratioNSErrorlenr_toss9.txt', ratioNSErrorlenr_toss9, ' ');
rodMeanslenrOrig_toss9 = RodMeans(ratioOriglenr_toss9)
rodMeanslenrNS_toss9 = RodMeans(ratioNSlenr_toss9)
dlmwrite('ratioOriglenr_toss9.txt', ratioOriglenr_toss9, ' ');
dlmwrite('ratioNSlenr_toss9.txt', ratioNSlenr_toss9, ' ');

load lenrTlow_toss10.txt
load lenrThigh_toss10.txt
load lenrTtotal_toss10.txt
load lenrTlow_toss10_errorSTD.txt
load lenrThigh_toss10_errorSTD.txt

[ratioOriglenr_toss10, ratioNSlenr_toss10] = RatioNoiseSuppression(lenrTtotal_toss10, lenrTlow_toss10, lenrThigh_toss10);
[ratioOrigErrorlenr_toss10, ratioNSErrorlenr_toss10] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss10, lenrTlow_toss10, lenrThigh_toss10, lenrTlow_toss10_errorSTD, lenrThigh_toss10_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss10.txt', ratioOrigErrorlenr_toss10, ' ');
dlmwrite('ratioNSErrorlenr_toss10.txt', ratioNSErrorlenr_toss10, ' ');
rodMeanslenrOrig_toss10 = RodMeans(ratioOriglenr_toss10)
rodMeanslenrNS_toss10 = RodMeans(ratioNSlenr_toss10)
dlmwrite('ratioOriglenr_toss10.txt', ratioOriglenr_toss10, ' ');
dlmwrite('ratioNSlenr_toss10.txt', ratioNSlenr_toss10, ' ');

load bremTlow_toss1.txt
load bremThigh_toss1.txt
load bremTtotal_toss1.txt
load bremTlow_toss1_errorSTD.txt
load bremThigh_toss1_errorSTD.txt

[ratioOrigbrem_toss1, ratioNSbrem_toss1] = RatioNoiseSuppression(bremTtotal_toss1, bremTlow_toss1, bremThigh_toss1);
[ratioOrigErrorbrem_toss1, ratioNSErrorbrem_toss1] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss1, bremTlow_toss1, bremThigh_toss1, bremTlow_toss1_errorSTD, bremThigh_toss1_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss1.txt', ratioOrigErrorbrem_toss1, ' ');
dlmwrite('ratioNSErrorbrem_toss1.txt', ratioNSErrorbrem_toss1, ' ');
rodMeansbremOrig_toss1 = RodMeans(ratioOrigbrem_toss1)
rodMeansbremNS_toss1 = RodMeans(ratioNSbrem_toss1)
dlmwrite('ratioOrigbrem_toss1.txt', ratioOrigbrem_toss1, ' ');
dlmwrite('ratioNSbrem_toss1.txt', ratioNSbrem_toss1, ' ');

load bremTlow_toss2.txt
load bremThigh_toss2.txt
load bremTtotal_toss2.txt
load bremTlow_toss2_errorSTD.txt
load bremThigh_toss2_errorSTD.txt

[ratioOrigbrem_toss2, ratioNSbrem_toss2] = RatioNoiseSuppression(bremTtotal_toss2, bremTlow_toss2, bremThigh_toss2);
[ratioOrigErrorbrem_toss2, ratioNSErrorbrem_toss2] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss2, bremTlow_toss2, bremThigh_toss2, bremTlow_toss2_errorSTD, bremThigh_toss2_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss2.txt', ratioOrigErrorbrem_toss2, ' ');
dlmwrite('ratioNSErrorbrem_toss2.txt', ratioNSErrorbrem_toss2, ' ');
rodMeansbremOrig_toss2 = RodMeans(ratioOrigbrem_toss2)
rodMeansbremNS_toss2 = RodMeans(ratioNSbrem_toss2)
dlmwrite('ratioOrigbrem_toss2.txt', ratioOrigbrem_toss2, ' ');
dlmwrite('ratioNSbrem_toss2.txt', ratioNSbrem_toss2, ' ');

load bremTlow_toss3.txt
load bremThigh_toss3.txt
load bremTtotal_toss3.txt
load bremTlow_toss3_errorSTD.txt
load bremThigh_toss3_errorSTD.txt

[ratioOrigbrem_toss3, ratioNSbrem_toss3] = RatioNoiseSuppression(bremTtotal_toss3, bremTlow_toss3, bremThigh_toss3);
[ratioOrigErrorbrem_toss3, ratioNSErrorbrem_toss3] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss3, bremTlow_toss3, bremThigh_toss3, bremTlow_toss3_errorSTD, bremThigh_toss3_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss3.txt', ratioOrigErrorbrem_toss3, ' ');
dlmwrite('ratioNSErrorbrem_toss3.txt', ratioNSErrorbrem_toss3, ' ');
rodMeansbremOrig_toss3 = RodMeans(ratioOrigbrem_toss3)
rodMeansbremNS_toss3 = RodMeans(ratioNSbrem_toss3)
dlmwrite('ratioOrigbrem_toss3.txt', ratioOrigbrem_toss3, ' ');
dlmwrite('ratioNSbrem_toss3.txt', ratioNSbrem_toss3, ' ');

load bremTlow_toss4.txt
load bremThigh_toss4.txt
load bremTtotal_toss4.txt
load bremTlow_toss4_errorSTD.txt
load bremThigh_toss4_errorSTD.txt

[ratioOrigbrem_toss4, ratioNSbrem_toss4] = RatioNoiseSuppression(bremTtotal_toss4, bremTlow_toss4, bremThigh_toss4);
[ratioOrigErrorbrem_toss4, ratioNSErrorbrem_toss4] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss4, bremTlow_toss4, bremThigh_toss4, bremTlow_toss4_errorSTD, bremThigh_toss4_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss4.txt', ratioOrigErrorbrem_toss4, ' ');
dlmwrite('ratioNSErrorbrem_toss4.txt', ratioNSErrorbrem_toss4, ' ');
rodMeansbremOrig_toss4 = RodMeans(ratioOrigbrem_toss4)
rodMeansbremNS_toss4 = RodMeans(ratioNSbrem_toss4)
dlmwrite('ratioOrigbrem_toss4.txt', ratioOrigbrem_toss4, ' ');
dlmwrite('ratioNSbrem_toss4.txt', ratioNSbrem_toss4, ' ');

load bremTlow_toss5.txt
load bremThigh_toss5.txt
load bremTtotal_toss5.txt
load bremTlow_toss5_errorSTD.txt
load bremThigh_toss5_errorSTD.txt

[ratioOrigbrem_toss5, ratioNSbrem_toss5] = RatioNoiseSuppression(bremTtotal_toss5, bremTlow_toss5, bremThigh_toss5);
[ratioOrigErrorbrem_toss5, ratioNSErrorbrem_toss5] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss5, bremTlow_toss5, bremThigh_toss5, bremTlow_toss5_errorSTD, bremThigh_toss5_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss5.txt', ratioOrigErrorbrem_toss5, ' ');
dlmwrite('ratioNSErrorbrem_toss5.txt', ratioNSErrorbrem_toss5, ' ');
rodMeansbremOrig_toss5 = RodMeans(ratioOrigbrem_toss5)
rodMeansbremNS_toss5 = RodMeans(ratioNSbrem_toss5)
dlmwrite('ratioOrigbrem_toss5.txt', ratioOrigbrem_toss5, ' ');
dlmwrite('ratioNSbrem_toss5.txt', ratioNSbrem_toss5, ' ');

load bremTlow_toss6.txt
load bremThigh_toss6.txt
load bremTtotal_toss6.txt
load bremTlow_toss6_errorSTD.txt
load bremThigh_toss6_errorSTD.txt

[ratioOrigbrem_toss6, ratioNSbrem_toss6] = RatioNoiseSuppression(bremTtotal_toss6, bremTlow_toss6, bremThigh_toss6);
[ratioOrigErrorbrem_toss6, ratioNSErrorbrem_toss6] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss6, bremTlow_toss6, bremThigh_toss6, bremTlow_toss6_errorSTD, bremThigh_toss6_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss6.txt', ratioOrigErrorbrem_toss6, ' ');
dlmwrite('ratioNSErrorbrem_toss6.txt', ratioNSErrorbrem_toss6, ' ');
rodMeansbremOrig_toss6 = RodMeans(ratioOrigbrem_toss6)
rodMeansbremNS_toss6 = RodMeans(ratioNSbrem_toss6)
dlmwrite('ratioOrigbrem_toss6.txt', ratioOrigbrem_toss6, ' ');
dlmwrite('ratioNSbrem_toss6.txt', ratioNSbrem_toss6, ' ');

load bremTlow_toss7.txt
load bremThigh_toss7.txt
load bremTtotal_toss7.txt
load bremTlow_toss7_errorSTD.txt
load bremThigh_toss7_errorSTD.txt

[ratioOrigbrem_toss7, ratioNSbrem_toss7] = RatioNoiseSuppression(bremTtotal_toss7, bremTlow_toss7, bremThigh_toss7);
[ratioOrigErrorbrem_toss7, ratioNSErrorbrem_toss7] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss7, bremTlow_toss7, bremThigh_toss7, bremTlow_toss7_errorSTD, bremThigh_toss7_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss7.txt', ratioOrigErrorbrem_toss7, ' ');
dlmwrite('ratioNSErrorbrem_toss7.txt', ratioNSErrorbrem_toss7, ' ');
rodMeansbremOrig_toss7 = RodMeans(ratioOrigbrem_toss7)
rodMeansbremNS_toss7 = RodMeans(ratioNSbrem_toss7)
dlmwrite('ratioOrigbrem_toss7.txt', ratioOrigbrem_toss7, ' ');
dlmwrite('ratioNSbrem_toss7.txt', ratioNSbrem_toss7, ' ');

load bremTlow_toss8.txt
load bremThigh_toss8.txt
load bremTtotal_toss8.txt
load bremTlow_toss8_errorSTD.txt
load bremThigh_toss8_errorSTD.txt

[ratioOrigbrem_toss8, ratioNSbrem_toss8] = RatioNoiseSuppression(bremTtotal_toss8, bremTlow_toss8, bremThigh_toss8);
[ratioOrigErrorbrem_toss8, ratioNSErrorbrem_toss8] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss8, bremTlow_toss8, bremThigh_toss8, bremTlow_toss8_errorSTD, bremThigh_toss8_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss8.txt', ratioOrigErrorbrem_toss8, ' ');
dlmwrite('ratioNSErrorbrem_toss8.txt', ratioNSErrorbrem_toss8, ' ');
rodMeansbremOrig_toss8 = RodMeans(ratioOrigbrem_toss8)
rodMeansbremNS_toss8 = RodMeans(ratioNSbrem_toss8)
dlmwrite('ratioOrigbrem_toss8.txt', ratioOrigbrem_toss8, ' ');
dlmwrite('ratioNSbrem_toss8.txt', ratioNSbrem_toss8, ' ');

load bremTlow_toss9.txt
load bremThigh_toss9.txt
load bremTtotal_toss9.txt
load bremTlow_toss9_errorSTD.txt
load bremThigh_toss9_errorSTD.txt

[ratioOrigbrem_toss9, ratioNSbrem_toss9] = RatioNoiseSuppression(bremTtotal_toss9, bremTlow_toss9, bremThigh_toss9);
[ratioOrigErrorbrem_toss9, ratioNSErrorbrem_toss9] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss9, bremTlow_toss9, bremThigh_toss9, bremTlow_toss9_errorSTD, bremThigh_toss9_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss9.txt', ratioOrigErrorbrem_toss9, ' ');
dlmwrite('ratioNSErrorbrem_toss9.txt', ratioNSErrorbrem_toss9, ' ');
rodMeansbremOrig_toss9 = RodMeans(ratioOrigbrem_toss9)
rodMeansbremNS_toss9 = RodMeans(ratioNSbrem_toss9)
dlmwrite('ratioOrigbrem_toss9.txt', ratioOrigbrem_toss9, ' ');
dlmwrite('ratioNSbrem_toss9.txt', ratioNSbrem_toss9, ' ');

load bremTlow_toss10.txt
load bremThigh_toss10.txt
load bremTtotal_toss10.txt
load bremTlow_toss10_errorSTD.txt
load bremThigh_toss10_errorSTD.txt

[ratioOrigbrem_toss10, ratioNSbrem_toss10] = RatioNoiseSuppression(bremTtotal_toss10, bremTlow_toss10, bremThigh_toss10);
[ratioOrigErrorbrem_toss10, ratioNSErrorbrem_toss10] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss10, bremTlow_toss10, bremThigh_toss10, bremTlow_toss10_errorSTD, bremThigh_toss10_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss10.txt', ratioOrigErrorbrem_toss10, ' ');
dlmwrite('ratioNSErrorbrem_toss10.txt', ratioNSErrorbrem_toss10, ' ');
rodMeansbremOrig_toss10 = RodMeans(ratioOrigbrem_toss10)
rodMeansbremNS_toss10 = RodMeans(ratioNSbrem_toss10)
dlmwrite('ratioOrigbrem_toss10.txt', ratioOrigbrem_toss10, ' ');
dlmwrite('ratioNSbrem_toss10.txt', ratioNSbrem_toss10, ' ');

toc

save RatioRodsWorkspaceWhole

