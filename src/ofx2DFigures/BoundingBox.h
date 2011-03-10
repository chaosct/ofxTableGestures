#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


class BoundingBox
{
    public:
        BoundingBox();
        void Reset();
        void AddPoint(float x, float y);
        bool Collide(float x, float y);
        void Draw();
    private:
        float xmin,xmax,ymin,ymax;
        bool setedup;
};

#endif // BOUNDINGBOX_H
