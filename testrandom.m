r1 = rand(100,1);
r1=r1/1000;
lat=12.973701;
r1=r1+lat;
format long
r1;
csvwrite('first1.txt',r1);
