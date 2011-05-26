//
//  ScrollingLabel.h
//  Kepler
//
//  Created by Tom Carden on 5/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <string>
#include "cinder/Font.h"
#include "cinder/Color.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Rect.h"

using namespace std;
using namespace ci;

class ScrollingLabel {

public:

    ScrollingLabel() {}
    ~ScrollingLabel() {}
    
    void setup(Rectf rect, Font font, Color color) {
        mRect = rect;
        mFont = font;
        mColor = color;
    }
    
    void update() {}
    void draw();

    void setText(string text);

    void setRect(Rectf rect) { mRect = rect; }
    Rectf getRect() { return mRect; }

private:
    
    void updateTexture();
    
    Rectf mRect;
    Font mFont;
    Color mColor;
    string mText;
    
    gl::Texture mTexture;
    
};