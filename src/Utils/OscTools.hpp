#ifndef OSCTOOLS_HPP_INCLUDED
#define OSCTOOLS_HPP_INCLUDED

class OscOptionalUnpacker
{
    ofxOscMessage & msg;
    int n;
    public:
    OscOptionalUnpacker(ofxOscMessage & m):msg(m),n(0){}
    OscOptionalUnpacker & operator >> (int & i)
    {
        if(n < msg.getNumArgs())
        {
            i = msg.getArgAsInt32( n++ );
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (float & i)
    {
        if(n < msg.getNumArgs())
        {
            i = msg.getArgAsFloat( n++ );
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (double & i)
    {
        if(n < msg.getNumArgs())
        {
            i = msg.getArgAsFloat( n++ );
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (std::string & i)
    {
        if(n < msg.getNumArgs())
        {
            i = msg.getArgAsString( n++ );
        }
        return *this;
    }
    bool Eos()
    {
        return n >= msg.getNumArgs();
    }
};

class OscPacker
{
    ofxOscMessage & msg;
    public:
    OscPacker(ofxOscMessage & m):msg(m){}
    OscPacker & operator << (int i)
    {
        msg.addIntArg(i);
        return *this;
    }
    OscPacker & operator << (unsigned int i)
    {
        msg.addIntArg(i);
        return *this;
    }
    OscPacker & operator << (float i)
    {
        msg.addFloatArg(i);
        return *this;
    }
    OscPacker & operator << (const std::string & i)
    {
        msg.addStringArg(i);
        return *this;
    }
};

#endif // OSCTOOLS_HPP_INCLUDED
