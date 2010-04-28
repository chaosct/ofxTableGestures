#ifndef SIMPLEOBJECTCONTROLLER_HPP_INCLUDED
#define SIMPLEOBJECTCONTROLLER_HPP_INCLUDED

template<typename T>
class SimpleObjectController: public tuio::CanDirectObjects <Graphic>
{

    T Min, Max;
    std::string Addr;
    unsigned int f_id;
    tuio::DirectObject * dobj;
    T & value;
    float angle;
    bool todelete;
    bool present;
    float & fontResolution;
    static ofTrueTypeFont & getFont()
    {
        static bool loaded = false;
        static ofTrueTypeFont font;
        if(!loaded)
        {
            std::string fontF = GlobalConfig::getRef<std::string>("SIMPLEOBJECTCONTROLLER:FONT:FILE","arial.ttf");
            int & size = GlobalConfig::getRef("SIMPLEOBJECTCONTROLLER:FONT:RESOLUTION",20);
            font.loadFont(fontF,size);
            loaded = true;
        }
        return font;
    }

    void Create(tuio::DirectObject * d)
    {
        SimpleObjectController * i = new SimpleObjectController(value,f_id,Min,Max,d);
        i->angle = d->angle;
    }

    public:
    SimpleObjectController(T & v,unsigned int F_id,T min,T max,tuio::DirectObject * d=NULL):
        Min(min),
        Max(max),
        f_id(F_id),
        dobj(d),
        todelete(false),
        angle(0),
        value(v),
        present(true),
        fontResolution(GlobalConfig::getRef("SIMPLEOBJECTCONTROLLER:FONT:SIZE",0.001f))
        {
            this->Register(NULL);
        }
    void update()
    {
        if(todelete)
            delete this;
    }
    void draw()
    {
        if(dobj && present)
        {
            float x = dobj->getX();
            float y = dobj->getY();
            float mangle = dobj->getAngle(DirectPoint(0.5,0.5)) + HALF_PI;
            ofSetColor(255,255,255);
            ofPushMatrix();
            ofTranslate(x,y,0);
            ofRotateZ(mangle*180.0f/M_PI);
            ofScale(fontResolution,fontResolution,1);
            getFont().drawString(ofToString(value),-60,-80);
            ofPopMatrix();
        }
    }
    void newObject(tuio::DirectObject * object)
    {
        if((!dobj) && object->f_id == f_id)
        {
            Create(object);
        }
    }
    void removeObject(tuio::DirectObject * object)
    {
        if(object == dobj)
        {
            present = false;
            todelete = true;
        }
    }
    void updateObject(tuio::DirectObject * object)
    {
        if(object == dobj)
        {
            float diff = dobj->angle - angle;
            while (diff > HALF_PI) diff -= M_PI;
            while (diff < -HALF_PI) diff += M_PI;
            angle = dobj->angle;
            float ang = float(value-Min) / float(Max-Min) * TWO_PI;
            ang += diff;
            T nvalue = (ang / TWO_PI * (Max-Min)) + Min;
            value = min(max(nvalue,Min),Max);
        }
    }
};


template<>
void SimpleObjectController<int>::updateObject(tuio::DirectObject * object)
{
    static float accumulated_diff = 0.0f;
    static float step = fabs(TWO_PI / (Max-Min));
    if(object == dobj)
    {
        float diff = dobj->angle - angle;
        while (diff > HALF_PI) diff -= M_PI;
        while (diff < -HALF_PI) diff += M_PI;
        accumulated_diff += diff;
        int steps = accumulated_diff/ step;

        angle = dobj->angle;
        float ang = float(value-Min) / float(Max-Min) * TWO_PI;
        int nvalue = ((ang / TWO_PI) * (Max-Min)) + Min;
        ang += diff;
        if(value==nvalue)
        {
            accumulated_diff = diff;
        }
        else
        {
            accumulated_diff = 0;
        }
        value = min(max(nvalue,Min),Max);
    }
}
#endif // SIMPLEOBJECTCONTROLLER_HPP_INCLUDED
