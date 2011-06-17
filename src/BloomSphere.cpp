//
//  BloomSphere.cpp
//  Kepler
//
//  Created by Tom Carden on 6/12/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/CinderMath.h"
#include "cinder/Vector.h"
#include "BloomSphere.h"

using namespace ci;
using namespace std;

namespace bloom {

    void BloomSphere::setup( int segments )
    {	
        if (mInited) {
            delete[] mVerts;
        }
        
        mNumVerts		= segments * (segments/2) * 2 * 3;
        mVerts			= new VertexData[ mNumVerts ];
        
        const float TWO_PI = 2.0f * M_PI;
        
        int vert = 0;
        for( int j = 0; j < segments / 2; j++ ) {
            
            float theta1 = (float)j * TWO_PI / (float)segments - ( M_PI_2 );
            float cosTheta1 = cos( theta1 );
            float sinTheta1 = sin( theta1 );
            
            float theta2 = (float)(j + 1) * TWO_PI / (float)segments - ( M_PI_2 );
            float cosTheta2 = cos( theta2 );
            float sinTheta2 = sin( theta2 );
            
            Vec4f oldv1, oldv2, newv1, newv2;
            Vec4f oldt1, oldt2, newt1, newt2;
            
            for( int i = 0; i <= segments; i++ ) {
                oldv1			= newv1;
                oldv2			= newv2;
                
                oldt1			= newt1;
                oldt2			= newt2;
                
                float invSegs   = 1.0f / (float)segments;
                float theta3	= (float)i * TWO_PI * invSegs;
                float cosTheta3 = cos( theta3 );
                float sinTheta3 = sin( theta3 );
                
                float invI		= (float)i * invSegs;
                float u			= 0.999f - invI;
                float v1		= 0.999f - 2.0f * (float)j * invSegs;
                float v2		= 0.999f - 2.0f * (float)(j+1) * invSegs;
                
                newt1			= Vec4f( u, v1, 0, 0 );
                newt2			= Vec4f( u, v2, 0, 0 );
                
                newv1			= Vec4f( cosTheta1 * cosTheta3, sinTheta1, cosTheta1 * sinTheta3, 0 );			
                newv2			= Vec4f( cosTheta2 * cosTheta3, sinTheta2, cosTheta2 * sinTheta3, 0 );
                
                if( i > 0 ){
                    mVerts[vert].vertex = oldv1;
                    mVerts[vert].texture = oldt1;
                    vert++;

                    mVerts[vert].vertex = oldv2;
                    mVerts[vert].texture = oldt2;
                    vert++;
                    
                    mVerts[vert].vertex = newv1;
                    mVerts[vert].texture = newt1;
                    vert++;

                    mVerts[vert].vertex = oldv2;
                    mVerts[vert].texture = oldt2;
                    vert++;
                    
                    mVerts[vert].vertex = newv2;
                    mVerts[vert].texture = newt2;
                    vert++;
                    
                    mVerts[vert].vertex = newv1;
                    mVerts[vert].texture = newt1;
                    vert++;
                }
            }
        }
                
        mInited = true;
    }

    void BloomSphere::draw()
    {
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glEnableClientState( GL_NORMAL_ARRAY );
        glVertexPointer( 3, GL_FLOAT, sizeof(VertexData), &mVerts[0].vertex );
        glNormalPointer( GL_FLOAT, sizeof(VertexData), &mVerts[0].vertex );
        glTexCoordPointer( 2, GL_FLOAT, sizeof(VertexData), &mVerts[0].texture );
		glDrawArrays( GL_TRIANGLES, 0, mNumVerts );
		glDisableClientState( GL_VERTEX_ARRAY );
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_NORMAL_ARRAY );        
    }
    
}