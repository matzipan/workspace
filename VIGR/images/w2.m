function [ val ] = w( i )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if(i <127.5)
    val = i;
else
    val = 255 -i;

end

