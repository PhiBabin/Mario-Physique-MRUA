#ifndef DATAPOINT_HPP_INCLUDED
#define DATAPOINT_HPP_INCLUDED
class dataPoint: public sf::Sprite{
    dataPoint();
    dataPoint(float theTime);
    float GetTime();
    void SetTime(float theTime);
    private:
    float time;
};



#endif // DATAPOINT_HPP_INCLUDED
