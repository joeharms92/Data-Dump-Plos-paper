clear all
close all
tic
load lenrTlow_toss1.txt
load lenrThigh_toss1.txt
load lenrTtotal_toss1.txt

[ratioOriglenr_toss1, ratioNSlenr_toss1] = RatioNoiseSuppression(lenrTtotal_toss1, lenrTlow_toss1, lenrThigh_toss1);
rodMeanslenrOrig_toss1 = RodMeans(ratioOriglenr_toss1)
rodMeanslenrNS_toss1 = RodMeans(ratioNSlenr_toss1)

load lenrTlow_toss2.txt
load lenrThigh_toss2.txt
load lenrTtotal_toss2.txt

[ratioOriglenr_toss2, ratioNSlenr_toss2] = RatioNoiseSuppression(lenrTtotal_toss2, lenrTlow_toss2, lenrThigh_toss2);
rodMeanslenrOrig_toss2 = RodMeans(ratioOriglenr_toss2)
rodMeanslenrNS_toss2 = RodMeans(ratioNSlenr_toss2)

load lenrTlow_toss3.txt
load lenrThigh_toss3.txt
load lenrTtotal_toss3.txt

[ratioOriglenr_toss3, ratioNSlenr_toss3] = RatioNoiseSuppression(lenrTtotal_toss3, lenrTlow_toss3, lenrThigh_toss3);
rodMeanslenrOrig_toss3 = RodMeans(ratioOriglenr_toss3)
rodMeanslenrNS_toss3 = RodMeans(ratioNSlenr_toss3)

load lenrTlow_toss4.txt
load lenrThigh_toss4.txt
load lenrTtotal_toss4.txt

[ratioOriglenr_toss4, ratioNSlenr_toss4] = RatioNoiseSuppression(lenrTtotal_toss4, lenrTlow_toss4, lenrThigh_toss4);
rodMeanslenrOrig_toss4 = RodMeans(ratioOriglenr_toss4)
rodMeanslenrNS_toss4 = RodMeans(ratioNSlenr_toss4)

load lenrTlow_toss5.txt
load lenrThigh_toss5.txt
load lenrTtotal_toss5.txt

[ratioOriglenr_toss5, ratioNSlenr_toss5] = RatioNoiseSuppression(lenrTtotal_toss5, lenrTlow_toss5, lenrThigh_toss5);
rodMeanslenrOrig_toss5 = RodMeans(ratioOriglenr_toss5)
rodMeanslenrNS_toss5 = RodMeans(ratioNSlenr_toss5)

load lenrTlow_toss6.txt
load lenrThigh_toss6.txt
load lenrTtotal_toss6.txt

[ratioOriglenr_toss6, ratioNSlenr_toss6] = RatioNoiseSuppression(lenrTtotal_toss6, lenrTlow_toss6, lenrThigh_toss6);
rodMeanslenrOrig_toss6 = RodMeans(ratioOriglenr_toss6)
rodMeanslenrNS_toss6 = RodMeans(ratioNSlenr_toss6)

load lenrTlow_toss7.txt
load lenrThigh_toss7.txt
load lenrTtotal_toss7.txt

[ratioOriglenr_toss7, ratioNSlenr_toss7] = RatioNoiseSuppression(lenrTtotal_toss7, lenrTlow_toss7, lenrThigh_toss7);
rodMeanslenrOrig_toss7 = RodMeans(ratioOriglenr_toss7)
rodMeanslenrNS_toss7 = RodMeans(ratioNSlenr_toss7)

load lenrTlow_toss8.txt
load lenrThigh_toss8.txt
load lenrTtotal_toss8.txt

[ratioOriglenr_toss8, ratioNSlenr_toss8] = RatioNoiseSuppression(lenrTtotal_toss8, lenrTlow_toss8, lenrThigh_toss8);
rodMeanslenrOrig_toss8 = RodMeans(ratioOriglenr_toss8)
rodMeanslenrNS_toss8 = RodMeans(ratioNSlenr_toss8)

load lenrTlow_toss9.txt
load lenrThigh_toss9.txt
load lenrTtotal_toss9.txt

[ratioOriglenr_toss9, ratioNSlenr_toss9] = RatioNoiseSuppression(lenrTtotal_toss9, lenrTlow_toss9, lenrThigh_toss9);
rodMeanslenrOrig_toss9 = RodMeans(ratioOriglenr_toss9)
rodMeanslenrNS_toss9 = RodMeans(ratioNSlenr_toss9)

load lenrTlow_toss10.txt
load lenrThigh_toss10.txt
load lenrTtotal_toss10.txt

[ratioOriglenr_toss10, ratioNSlenr_toss10] = RatioNoiseSuppression(lenrTtotal_toss10, lenrTlow_toss10, lenrThigh_toss10);
rodMeanslenrOrig_toss10 = RodMeans(ratioOriglenr_toss10)
rodMeanslenrNS_toss10 = RodMeans(ratioNSlenr_toss10)

load bremTlow_toss1.txt
load bremThigh_toss1.txt
load bremTtotal_toss1.txt

[ratioOrigbrem_toss1, ratioNSbrem_toss1] = RatioNoiseSuppression(bremTtotal_toss1, bremTlow_toss1, bremThigh_toss1);
rodMeansbremOrig_toss1 = RodMeans(ratioOrigbrem_toss1)
rodMeansbremNS_toss1 = RodMeans(ratioNSbrem_toss1)

load bremTlow_toss2.txt
load bremThigh_toss2.txt
load bremTtotal_toss2.txt

[ratioOrigbrem_toss2, ratioNSbrem_toss2] = RatioNoiseSuppression(bremTtotal_toss2, bremTlow_toss2, bremThigh_toss2);
rodMeansbremOrig_toss2 = RodMeans(ratioOrigbrem_toss2)
rodMeansbremNS_toss2 = RodMeans(ratioNSbrem_toss2)

load bremTlow_toss3.txt
load bremThigh_toss3.txt
load bremTtotal_toss3.txt

[ratioOrigbrem_toss3, ratioNSbrem_toss3] = RatioNoiseSuppression(bremTtotal_toss3, bremTlow_toss3, bremThigh_toss3);
rodMeansbremOrig_toss3 = RodMeans(ratioOrigbrem_toss3)
rodMeansbremNS_toss3 = RodMeans(ratioNSbrem_toss3)

load bremTlow_toss4.txt
load bremThigh_toss4.txt
load bremTtotal_toss4.txt

[ratioOrigbrem_toss4, ratioNSbrem_toss4] = RatioNoiseSuppression(bremTtotal_toss4, bremTlow_toss4, bremThigh_toss4);
rodMeansbremOrig_toss4 = RodMeans(ratioOrigbrem_toss4)
rodMeansbremNS_toss4 = RodMeans(ratioNSbrem_toss4)

load bremTlow_toss5.txt
load bremThigh_toss5.txt
load bremTtotal_toss5.txt

[ratioOrigbrem_toss5, ratioNSbrem_toss5] = RatioNoiseSuppression(bremTtotal_toss5, bremTlow_toss5, bremThigh_toss5);
rodMeansbremOrig_toss5 = RodMeans(ratioOrigbrem_toss5)
rodMeansbremNS_toss5 = RodMeans(ratioNSbrem_toss5)

load bremTlow_toss6.txt
load bremThigh_toss6.txt
load bremTtotal_toss6.txt

[ratioOrigbrem_toss6, ratioNSbrem_toss6] = RatioNoiseSuppression(bremTtotal_toss6, bremTlow_toss6, bremThigh_toss6);
rodMeansbremOrig_toss6 = RodMeans(ratioOrigbrem_toss6)
rodMeansbremNS_toss6 = RodMeans(ratioNSbrem_toss6)

load bremTlow_toss7.txt
load bremThigh_toss7.txt
load bremTtotal_toss7.txt

[ratioOrigbrem_toss7, ratioNSbrem_toss7] = RatioNoiseSuppression(bremTtotal_toss7, bremTlow_toss7, bremThigh_toss7);
rodMeansbremOrig_toss7 = RodMeans(ratioOrigbrem_toss7)
rodMeansbremNS_toss7 = RodMeans(ratioNSbrem_toss7)

load bremTlow_toss8.txt
load bremThigh_toss8.txt
load bremTtotal_toss8.txt

[ratioOrigbrem_toss8, ratioNSbrem_toss8] = RatioNoiseSuppression(bremTtotal_toss8, bremTlow_toss8, bremThigh_toss8);
rodMeansbremOrig_toss8 = RodMeans(ratioOrigbrem_toss8)
rodMeansbremNS_toss8 = RodMeans(ratioNSbrem_toss8)

load bremTlow_toss9.txt
load bremThigh_toss9.txt
load bremTtotal_toss9.txt

[ratioOrigbrem_toss9, ratioNSbrem_toss9] = RatioNoiseSuppression(bremTtotal_toss9, bremTlow_toss9, bremThigh_toss9);
rodMeansbremOrig_toss9 = RodMeans(ratioOrigbrem_toss9)
rodMeansbremNS_toss9 = RodMeans(ratioNSbrem_toss9)

load bremTlow_toss10.txt
load bremThigh_toss10.txt
load bremTtotal_toss10.txt

[ratioOrigbrem_toss10, ratioNSbrem_toss10] = RatioNoiseSuppression(bremTtotal_toss10, bremTlow_toss10, bremThigh_toss10);
rodMeansbremOrig_toss10 = RodMeans(ratioOrigbrem_toss10)
rodMeansbremNS_toss10 = RodMeans(ratioNSbrem_toss10)

toc

save RatioRodsWorkspace

dlmwrite('ratioOrigbrem_toss1.txt', ratioOrigbrem_toss1, ' ');
dlmwrite('ratioNSbrem_toss1.txt', ratioNSbrem_toss1, ' ');
dlmwrite('ratioOrigbrem_toss2.txt', ratioOrigbrem_toss2, ' ');
dlmwrite('ratioNSbrem_toss2.txt', ratioNSbrem_toss2, ' ');
dlmwrite('ratioOrigbrem_toss3.txt', ratioOrigbrem_toss3, ' ');
dlmwrite('ratioNSbrem_toss3.txt', ratioNSbrem_toss3, ' ');
dlmwrite('ratioOrigbrem_toss4.txt', ratioOrigbrem_toss4, ' ');
dlmwrite('ratioNSbrem_toss4.txt', ratioNSbrem_toss4, ' ');
dlmwrite('ratioOrigbrem_toss5.txt', ratioOrigbrem_toss5, ' ');
dlmwrite('ratioNSbrem_toss5.txt', ratioNSbrem_toss5, ' ');
dlmwrite('ratioOrigbrem_toss6.txt', ratioOrigbrem_toss6, ' ');
dlmwrite('ratioNSbrem_toss6.txt', ratioNSbrem_toss6, ' ');
dlmwrite('ratioOrigbrem_toss7.txt', ratioOrigbrem_toss7, ' ');
dlmwrite('ratioNSbrem_toss7.txt', ratioNSbrem_toss7, ' ');
dlmwrite('ratioOrigbrem_toss8.txt', ratioOrigbrem_toss8, ' ');
dlmwrite('ratioNSbrem_toss8.txt', ratioNSbrem_toss8, ' ');
dlmwrite('ratioOrigbrem_toss9.txt', ratioOrigbrem_toss9, ' ');
dlmwrite('ratioNSbrem_toss9.txt', ratioNSbrem_toss9, ' ');
dlmwrite('ratioOrigbrem_toss10.txt', ratioOrigbrem_toss10, ' ');
dlmwrite('ratioNSbrem_toss10.txt', ratioNSbrem_toss10, ' ');

dlmwrite('ratioOriglenr_toss1.txt', ratioOriglenr_toss1, ' ');
dlmwrite('ratioNSlenr_toss1.txt', ratioNSlenr_toss1, ' ');
dlmwrite('ratioOriglenr_toss2.txt', ratioOriglenr_toss2, ' ');
dlmwrite('ratioNSlenr_toss2.txt', ratioNSlenr_toss2, ' ');
dlmwrite('ratioOriglenr_toss3.txt', ratioOriglenr_toss3, ' ');
dlmwrite('ratioNSlenr_toss3.txt', ratioNSlenr_toss3, ' ');
dlmwrite('ratioOriglenr_toss4.txt', ratioOriglenr_toss4, ' ');
dlmwrite('ratioNSlenr_toss4.txt', ratioNSlenr_toss4, ' ');
dlmwrite('ratioOriglenr_toss5.txt', ratioOriglenr_toss5, ' ');
dlmwrite('ratioNSlenr_toss5.txt', ratioNSlenr_toss5, ' ');
dlmwrite('ratioOriglenr_toss6.txt', ratioOriglenr_toss6, ' ');
dlmwrite('ratioNSlenr_toss6.txt', ratioNSlenr_toss6, ' ');
dlmwrite('ratioOriglenr_toss7.txt', ratioOriglenr_toss7, ' ');
dlmwrite('ratioNSlenr_toss7.txt', ratioNSlenr_toss7, ' ');
dlmwrite('ratioOriglenr_toss8.txt', ratioOriglenr_toss8, ' ');
dlmwrite('ratioNSlenr_toss8.txt', ratioNSlenr_toss8, ' ');
dlmwrite('ratioOriglenr_toss9.txt', ratioOriglenr_toss9, ' ');
dlmwrite('ratioNSlenr_toss9.txt', ratioNSlenr_toss9, ' ');
dlmwrite('ratioOriglenr_toss10.txt', ratioOriglenr_toss10, ' ');
dlmwrite('ratioNSlenr_toss10.txt', ratioNSlenr_toss10, ' ');
