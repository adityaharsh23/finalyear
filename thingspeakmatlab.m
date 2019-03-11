

* {margin: 0; padding: 0;}
body {text-align: start; line-height: normal; min-height: 0px; white-space: normal; color: rgb(0, 0, 0); font-family: Menlo, Monaco, Consolas, "Courier New", monospace; font-style: normal; font-size: 14px; font-weight: 400; text-decoration: none solid rgb(0, 0, 0); white-space: normal; }
h1, h2 {font-weight: normal;}
.S0 { min-height: 18px; white-space: pre; white-space: pre; margin-left: 1em;  }
.S1 { min-height: 0px; margin-right: 45px;  }
.S2 { color: rgb(34, 139, 34); text-decoration: none;  }
.S3 {  }
.S4 { color: rgb(160, 32, 240); text-decoration: none;  }

.CodeBlock {margin: 10px 0 10px 0; background-color: #F7F7F7;}
.CodeBlock+.paragraphNode {margin-top: 10px;}
.lineNode {padding-left: 10px; border-left: 1px solid #E9E9E9; border-right: 1px solid #E9E9E9;}
.inlineWrapper:first-child .lineNode,.inlineWrapper.outputs+.inlineWrapper .lineNode {padding-top: 5px; border-top: 1px solid #E9E9E9;}
.inlineWrapper:last-child .lineNode,.inlineWrapper.outputs .lineNode {padding-bottom: 5px; border-bottom: 1px solid #E9E9E9;}
.lineNode .textBox {white-space: pre;}


% Template MATLAB code for reading data from a private channel, analyzing
% the data and storing the analyzed data in another channel.
% Prior to running this MATLAB code template, assign the channel ID to read
% data from to the 'readChannelID' variable. Since this is a private
% channel, also assign the read API Key to the 'readAPIKey' variable. You
% can find the read API Key in the right side pane of this page.
% To store the analyzed data, you will need to write it to a channel other
% than the one you are reading data from. Assign this channel ID to the
% 'writeChannelID' variable. Also assign the write API Key to the
% 'writeAPIKey' variable below. You can find the write API Key in the right
% side pane of this page.
% TODO - Replace the [] with channel ID to read data from:
readChannelID =716675;
readChannelID1 =716686;
readChannelID2 =717502;
readChannelID3 =717515;
% TODO - Enter the Read API Key between the '' below:
readAPIKey = 'VV3H191M46MA1SZX';
readAPIKey1 = 'FANXU4N7I8EFJJJD';
readAPIKey2 = 'SQOXJ38Y2LXHQTDE';
readAPIKey3 ='68YXJQ5UEJAG6AR2';
% TODO - Replace the [] with channel ID to write data to:
writeChannelID =716643;
% TODO - Enter the Write API Key between the '' below:
writeAPIKey = 'BDWILOQ33C4WH2KJ';
%% Read Data %%
data = thingSpeakRead(readChannelID, 'ReadKey', readAPIKey);
data1= thingSpeakRead(readChannelID1, 'ReadKey', readAPIKey1);
lat1= thingSpeakRead(readChannelID2, 'ReadKey', readAPIKey2);
lon1= thingSpeakRead(readChannelID3, 'ReadKey', readAPIKey3);
%lat1=55.739399;
%lon1=37.592572;
%data=12.34;
%data1=34.234;
%lat2=55.735632;
%lon2=37.678367;
res=azimuth(lat1,lon1,data,data1);
%res2=deg2km(distance(lat1, lon1, lat2, lon2));
sprintf("Angle Between Co ordinates is: %f degrees",res)
%sprintf("Distance Between co ordinates is: %f Km",res2)
res;
%% Analyze Data %%
% Add code in this section to analyze data and store the result in the
% analyzedData variable.
analyzedData = res;
%% Write Data %%
thingSpeakWrite(writeChannelID, analyzedData, 'WriteKey', writeAPIKey);
