% lat1=input("lat1:");
% lon1=input("lon1:");
% lat2=input("lat2:");
% lon2=input("lon2:");
lat1=55.739399;
lon1=37.592572;
lat2=55.735632;
lon2=37.678367;
res=azimuth(lat1,lon1,lat2,lon2);
res2=deg2km(distance(lat1, lon1, lat2, lon2));
sprintf("Angle Between Co ordinates is: %f degrees",res)
sprintf("Distance Between co ordinates is: %f Km",res2)
res;
res2;

%distance
