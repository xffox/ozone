#ifndef GEOM_ANGLE_H
#define GEOM_ANGLE_H

namespace geom
{
    class Angle
    {
    public:
        Angle()
            :radian(.0)
        {
        }

        Angle(double radian)
            :radian(radian)
        {
        }

        double getRadian() const
        {
            return radian;
        }

        double getDegrees() const;

        void setRadian(double radian)
        {
            this->radian = radian;
        }

        void setDegrees(double degrees);

    private:
        double radian;
    };

    bool operator==(const Angle &left, const Angle &right);
    bool operator!=(const Angle &left, const Angle &right);
}

#endif
