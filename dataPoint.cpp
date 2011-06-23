#include "dataPoint.hpp"
    dataPoint::dataPoint():time(0){
    }
    dataPoint::dataPoint(float theTime):time(theTime){
    }
    float dataPoint::GetTime(){
        return time;
    }
    void dataPoint::SetTime(float theTime){
        time=theTime;
    }
