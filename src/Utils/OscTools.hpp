#ifndef OSCTOOLS_HPP_INCLUDED
#define OSCTOOLS_HPP_INCLUDED

#include "ofxOsc.h"

class OscOptionalUnpacker
{
    ofxOscMessage & msg;
    int n;
    public:
    OscOptionalUnpacker(ofxOscMessage & m):msg(m),n(0){}
    OscOptionalUnpacker & operator >> (int & i) {
        if(n < msg.getNumArgs()) {
            switch(msg.getArgType(n)) {
            case OFXOSC_TYPE_INT32:
                i = msg.getArgAsInt32( n++ );
                break;
            case OFXOSC_TYPE_INT64:
                i = static_cast<int>(msg.getArgAsInt64( n++ ));
                break;
            case OFXOSC_TYPE_FLOAT:
                i = static_cast<int>(msg.getArgAsFloat( n++ ));
                break;
            default:
                i = msg.getArgAsInt32(n++);
                break;
            }
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (long & i) {
        if(n < msg.getNumArgs()) {
            switch(msg.getArgType(n)) {
            case OFXOSC_TYPE_INT32:
                i = msg.getArgAsInt32( n++ );
                break;
            case OFXOSC_TYPE_INT64:
                i = msg.getArgAsInt64( n++ );
                break;
            case OFXOSC_TYPE_FLOAT:
                i = static_cast<long>(msg.getArgAsFloat( n++ ));
                break;
            default:
                i = msg.getArgAsInt64(n++);
                break;
            }
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (float & i) {
        if(n < msg.getNumArgs()) {
            switch(msg.getArgType(n)) {
            case OFXOSC_TYPE_INT32:
                i = static_cast<float>(msg.getArgAsInt32( n++ ));
                break;
            case OFXOSC_TYPE_INT64:
                i = static_cast<float>(msg.getArgAsInt64( n++ ));
                break;
            case OFXOSC_TYPE_FLOAT:
                i = msg.getArgAsFloat( n++ );
                break;
            default:
                i = msg.getArgAsFloat(n++);
                break;
            }
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (double & i) {
        if(n < msg.getNumArgs()) {
            switch(msg.getArgType(n)) {
            case OFXOSC_TYPE_INT32:
                i = static_cast<double>(msg.getArgAsInt32( n++ ));
                break;
            case OFXOSC_TYPE_INT64:
                i = static_cast<double>(msg.getArgAsInt64( n++ ));
                break;
            case OFXOSC_TYPE_FLOAT:
                i = msg.getArgAsFloat( n++ );
                break;
            default:
                i = msg.getArgAsFloat(n++);
                break;
            }
        }
        return *this;
    }
    OscOptionalUnpacker & operator >> (std::string & i) {
        if(n < msg.getNumArgs()) {
            i = msg.getArgAsString( n++ );
        }
        return *this;
    }
    bool Eos() {
        return n >= msg.getNumArgs();
    }
};

class OscPacker
{
    ofxOscMessage & msg;
    public:
    OscPacker(ofxOscMessage & m):msg(m){}
    OscPacker & operator << (int i) {
        msg.addIntArg(i);
        return *this;
    }
    OscPacker & operator << (unsigned int i) {
        msg.addIntArg(i);
        return *this;
    }
    OscPacker & operator << (float i) {
        msg.addFloatArg(i);
        return *this;
    }
    OscPacker & operator << (const std::string & i) {
        msg.addStringArg(i);
        return *this;
    }
};

#endif // OSCTOOLS_HPP_INCLUDED
