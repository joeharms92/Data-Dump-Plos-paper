function [means] = RodMeans(img)

	[m n] = size(img);
	centers(1,:) = [83 49];
	centers(2,:) = [124 49];
	centers(3,:) = [145 70];
	centers(4,:) = [124 92];
	centers(5,:) = [83 92];
	centers(6,:) = [62 70];

	minorRad = 3.5;
	majorRad = 6.5;
	rSqEllipse = minorRad*minorRad*majorRad*majorRad;
	means = zeros(6,1);
	counter = 0;
	for nRods = 1:6
		lowerX = centers(nRods,1)-7;
		lowerY = centers(nRods,2)-4;
		upperX = centers(nRods,1)+7;
		upperY = centers(nRods,2)+4;
		for ii = lowerX:upperX
			for jj = lowerY:upperY
				ellipVal = ((ii-centers(nRods,1))*(ii-centers(nRods,1)))*minorRad*minorRad + ((jj-centers(nRods,2))*(jj-centers(nRods,2)))*majorRad*majorRad;
				if (ellipVal < rSqEllipse)
					counter = counter+1;
					means(nRods) = means(nRods) + img(jj,ii);
				end
			end
		end
		means(nRods) = means(nRods)/counter;
		counter = 0;
	end