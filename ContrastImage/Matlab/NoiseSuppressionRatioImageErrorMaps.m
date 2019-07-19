clear all
close all
tic

load lenrTlow_toss1.txt
load lenrThigh_toss1.txt
load lenrTlow_toss1_errorSTD.txt
load lenrThigh_toss1_errorSTD.txt
load lenrTtotal_toss1.txt

[ratioOrigErrorlenr_toss1, ratioNSErrorlenr_toss1] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss1, lenrTlow_toss1, lenrThigh_toss1, lenrTlow_toss1_errorSTD, lenrThigh_toss1_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss1.txt', ratioOrigErrorlenr_toss1, ' ');
dlmwrite('ratioNSErrorlenr_toss1.txt', ratioNSErrorlenr_toss1, ' ');

load lenrTlow_toss2.txt
load lenrThigh_toss2.txt
load lenrTlow_toss2_errorSTD.txt
load lenrThigh_toss2_errorSTD.txt
load lenrTtotal_toss2.txt

[ratioOrigErrorlenr_toss2, ratioNSErrorlenr_toss2] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss2, lenrTlow_toss2, lenrThigh_toss2, lenrTlow_toss2_errorSTD, lenrThigh_toss2_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss2.txt', ratioOrigErrorlenr_toss2, ' ');
dlmwrite('ratioNSErrorlenr_toss2.txt', ratioNSErrorlenr_toss2, ' ');

load lenrTlow_toss3.txt
load lenrThigh_toss3.txt
load lenrTlow_toss3_errorSTD.txt
load lenrThigh_toss3_errorSTD.txt
load lenrTtotal_toss3.txt

[ratioOrigErrorlenr_toss3, ratioNSErrorlenr_toss3] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss3, lenrTlow_toss3, lenrThigh_toss3, lenrTlow_toss3_errorSTD, lenrThigh_toss3_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss3.txt', ratioOrigErrorlenr_toss3, ' ');
dlmwrite('ratioNSErrorlenr_toss3.txt', ratioNSErrorlenr_toss3, ' ');

load lenrTlow_toss4.txt
load lenrThigh_toss4.txt
load lenrTlow_toss4_errorSTD.txt
load lenrThigh_toss4_errorSTD.txt
load lenrTtotal_toss4.txt

[ratioOrigErrorlenr_toss4, ratioNSErrorlenr_toss4] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss4, lenrTlow_toss4, lenrThigh_toss4, lenrTlow_toss4_errorSTD, lenrThigh_toss4_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss4.txt', ratioOrigErrorlenr_toss4, ' ');
dlmwrite('ratioNSErrorlenr_toss4.txt', ratioNSErrorlenr_toss4, ' ');

load lenrTlow_toss5.txt
load lenrThigh_toss5.txt
load lenrTlow_toss5_errorSTD.txt
load lenrThigh_toss5_errorSTD.txt
load lenrTtotal_toss5.txt

[ratioOrigErrorlenr_toss5, ratioNSErrorlenr_toss5] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss5, lenrTlow_toss5, lenrThigh_toss5, lenrTlow_toss5_errorSTD, lenrThigh_toss5_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss5.txt', ratioOrigErrorlenr_toss5, ' ');
dlmwrite('ratioNSErrorlenr_toss5.txt', ratioNSErrorlenr_toss5, ' ');

load lenrTlow_toss6.txt
load lenrThigh_toss6.txt
load lenrTlow_toss6_errorSTD.txt
load lenrThigh_toss6_errorSTD.txt
load lenrTtotal_toss6.txt

[ratioOrigErrorlenr_toss6, ratioNSErrorlenr_toss6] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss6, lenrTlow_toss6, lenrThigh_toss6, lenrTlow_toss6_errorSTD, lenrThigh_toss6_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss6.txt', ratioOrigErrorlenr_toss6, ' ');
dlmwrite('ratioNSErrorlenr_toss6.txt', ratioNSErrorlenr_toss6, ' ');

load lenrTlow_toss7.txt
load lenrThigh_toss7.txt
load lenrTlow_toss7_errorSTD.txt
load lenrThigh_toss7_errorSTD.txt
load lenrTtotal_toss7.txt

[ratioOrigErrorlenr_toss7, ratioNSErrorlenr_toss7] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss7, lenrTlow_toss7, lenrThigh_toss7, lenrTlow_toss7_errorSTD, lenrThigh_toss7_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss7.txt', ratioOrigErrorlenr_toss7, ' ');
dlmwrite('ratioNSErrorlenr_toss7.txt', ratioNSErrorlenr_toss7, ' ');

load lenrTlow_toss8.txt
load lenrThigh_toss8.txt
load lenrTlow_toss8_errorSTD.txt
load lenrThigh_toss8_errorSTD.txt
load lenrTtotal_toss8.txt

[ratioOrigErrorlenr_toss8, ratioNSErrorlenr_toss8] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss8, lenrTlow_toss8, lenrThigh_toss8, lenrTlow_toss8_errorSTD, lenrThigh_toss8_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss8.txt', ratioOrigErrorlenr_toss8, ' ');
dlmwrite('ratioNSErrorlenr_toss8.txt', ratioNSErrorlenr_toss8, ' ');

load lenrTlow_toss9.txt
load lenrThigh_toss9.txt
load lenrTlow_toss9_errorSTD.txt
load lenrThigh_toss9_errorSTD.txt
load lenrTtotal_toss9.txt

[ratioOrigErrorlenr_toss9, ratioNSErrorlenr_toss9] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss9, lenrTlow_toss9, lenrThigh_toss9, lenrTlow_toss9_errorSTD, lenrThigh_toss9_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss9.txt', ratioOrigErrorlenr_toss9, ' ');
dlmwrite('ratioNSErrorlenr_toss9.txt', ratioNSErrorlenr_toss9, ' ');

load lenrTlow_toss10.txt
load lenrThigh_toss10.txt
load lenrTlow_toss10_errorSTD.txt
load lenrThigh_toss10_errorSTD.txt
load lenrTtotal_toss10.txt

[ratioOrigErrorlenr_toss10, ratioNSErrorlenr_toss10] = RatioNoiseSuppressionErrorCalc(lenrTtotal_toss10, lenrTlow_toss10, lenrThigh_toss10, lenrTlow_toss10_errorSTD, lenrThigh_toss10_errorSTD);
dlmwrite('ratioOrigErrorlenr_toss10.txt', ratioOrigErrorlenr_toss10, ' ');
dlmwrite('ratioNSErrorlenr_toss10.txt', ratioNSErrorlenr_toss10, ' ');

load bremTlow_toss1.txt
load bremThigh_toss1.txt
load bremTlow_toss1_errorSTD.txt
load bremThigh_toss1_errorSTD.txt
load bremTtotal_toss1.txt

[ratioOrigErrorbrem_toss1, ratioNSErrorbrem_toss1] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss1, bremTlow_toss1, bremThigh_toss1, bremTlow_toss1_errorSTD, bremThigh_toss1_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss1.txt', ratioOrigErrorbrem_toss1, ' ');
dlmwrite('ratioNSErrorbrem_toss1.txt', ratioNSErrorbrem_toss1, ' ');

load bremTlow_toss2.txt
load bremThigh_toss2.txt
load bremTlow_toss2_errorSTD.txt
load bremThigh_toss2_errorSTD.txt
load bremTtotal_toss2.txt

[ratioOrigErrorbrem_toss2, ratioNSErrorbrem_toss2] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss2, bremTlow_toss2, bremThigh_toss2, bremTlow_toss2_errorSTD, bremThigh_toss2_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss2.txt', ratioOrigErrorbrem_toss2, ' ');
dlmwrite('ratioNSErrorbrem_toss2.txt', ratioNSErrorbrem_toss2, ' ');

load bremTlow_toss3.txt
load bremThigh_toss3.txt
load bremTlow_toss3_errorSTD.txt
load bremThigh_toss3_errorSTD.txt
load bremTtotal_toss3.txt

[ratioOrigErrorbrem_toss3, ratioNSErrorbrem_toss3] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss3, bremTlow_toss3, bremThigh_toss3, bremTlow_toss3_errorSTD, bremThigh_toss3_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss3.txt', ratioOrigErrorbrem_toss3, ' ');
dlmwrite('ratioNSErrorbrem_toss3.txt', ratioNSErrorbrem_toss3, ' ');

load bremTlow_toss4.txt
load bremThigh_toss4.txt
load bremTlow_toss4_errorSTD.txt
load bremThigh_toss4_errorSTD.txt
load bremTtotal_toss4.txt

[ratioOrigErrorbrem_toss4, ratioNSErrorbrem_toss4] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss4, bremTlow_toss4, bremThigh_toss4, bremTlow_toss4_errorSTD, bremThigh_toss4_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss4.txt', ratioOrigErrorbrem_toss4, ' ');
dlmwrite('ratioNSErrorbrem_toss4.txt', ratioNSErrorbrem_toss4, ' ');

load bremTlow_toss5.txt
load bremThigh_toss5.txt
load bremTlow_toss5_errorSTD.txt
load bremThigh_toss5_errorSTD.txt
load bremTtotal_toss5.txt

[ratioOrigErrorbrem_toss5, ratioNSErrorbrem_toss5] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss5, bremTlow_toss5, bremThigh_toss5, bremTlow_toss5_errorSTD, bremThigh_toss5_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss5.txt', ratioOrigErrorbrem_toss5, ' ');
dlmwrite('ratioNSErrorbrem_toss5.txt', ratioNSErrorbrem_toss5, ' ');

load bremTlow_toss6.txt
load bremThigh_toss6.txt
load bremTlow_toss6_errorSTD.txt
load bremThigh_toss6_errorSTD.txt
load bremTtotal_toss6.txt

[ratioOrigErrorbrem_toss6, ratioNSErrorbrem_toss6] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss6, bremTlow_toss6, bremThigh_toss6, bremTlow_toss6_errorSTD, bremThigh_toss6_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss6.txt', ratioOrigErrorbrem_toss6, ' ');
dlmwrite('ratioNSErrorbrem_toss6.txt', ratioNSErrorbrem_toss6, ' ');

load bremTlow_toss7.txt
load bremThigh_toss7.txt
load bremTlow_toss7_errorSTD.txt
load bremThigh_toss7_errorSTD.txt
load bremTtotal_toss7.txt

[ratioOrigErrorbrem_toss7, ratioNSErrorbrem_toss7] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss7, bremTlow_toss7, bremThigh_toss7, bremTlow_toss7_errorSTD, bremThigh_toss7_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss7.txt', ratioOrigErrorbrem_toss7, ' ');
dlmwrite('ratioNSErrorbrem_toss7.txt', ratioNSErrorbrem_toss7, ' ');

load bremTlow_toss8.txt
load bremThigh_toss8.txt
load bremTlow_toss8_errorSTD.txt
load bremThigh_toss8_errorSTD.txt
load bremTtotal_toss8.txt

[ratioOrigErrorbrem_toss8, ratioNSErrorbrem_toss8] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss8, bremTlow_toss8, bremThigh_toss8, bremTlow_toss8_errorSTD, bremThigh_toss8_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss8.txt', ratioOrigErrorbrem_toss8, ' ');
dlmwrite('ratioNSErrorbrem_toss8.txt', ratioNSErrorbrem_toss8, ' ');

load bremTlow_toss9.txt
load bremThigh_toss9.txt
load bremTlow_toss9_errorSTD.txt
load bremThigh_toss9_errorSTD.txt
load bremTtotal_toss9.txt

[ratioOrigErrorbrem_toss9, ratioNSErrorbrem_toss9] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss9, bremTlow_toss9, bremThigh_toss9, bremTlow_toss9_errorSTD, bremThigh_toss9_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss9.txt', ratioOrigErrorbrem_toss9, ' ');
dlmwrite('ratioNSErrorbrem_toss9.txt', ratioNSErrorbrem_toss9, ' ');

load bremTlow_toss10.txt
load bremThigh_toss10.txt
load bremTlow_toss10_errorSTD.txt
load bremThigh_toss10_errorSTD.txt
load bremTtotal_toss10.txt

[ratioOrigErrorbrem_toss10, ratioNSErrorbrem_toss10] = RatioNoiseSuppressionErrorCalc(bremTtotal_toss10, bremTlow_toss10, bremThigh_toss10, bremTlow_toss10_errorSTD, bremThigh_toss10_errorSTD);
dlmwrite('ratioOrigErrorbrem_toss10.txt', ratioOrigErrorbrem_toss10, ' ');
dlmwrite('ratioNSErrorbrem_toss10.txt', ratioNSErrorbrem_toss10, ' ');


toc

save RatioRodsErrorsWorkspace
