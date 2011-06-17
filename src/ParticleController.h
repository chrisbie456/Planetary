#pragma once
#include "Particle.h"
#include "Dust.h"
#include "Node.h"
#include <list>

class ParticleController {
 public:
	ParticleController();
	void update( const ci::Vec3f &camEye, float radius, const ci::Vec3f &bbRight, const ci::Vec3f &bbUp );
	void buildParticleVertexArray( float scaleOffset, ci::Color c, float eclipseStrength );
	void buildDustVertexArray( float scaleOffset, Node *node, float pinchAlphaOffset, float dustAlpha );
	void drawParticleVertexArray( Node *node );
	void drawDustVertexArray( Node *node );
	void addParticles( int amt );
	void removeParticles( int amt );
	void addDusts( int amt );
	
	std::list<Particle>	mParticles;
	int mNumParticles;
	int mTotalParticleVertices;
    int mPrevTotalParticleVertices; // so we only recreate frames
	GLfloat *mParticleVerts;
	GLfloat *mParticleTexCoords;
	GLfloat *mParticleColors;
	
	
	std::list<Dust> mDusts;
	int mNumDusts;
	int mTotalDustVertices;
    int mPrevTotalDustVertices; // so we only recreate frames
	GLfloat *mDustVerts;
	GLfloat *mDustColors;
	
	ci::Vec3f mBbRight;
	ci::Vec3f mBbUp;
	
};