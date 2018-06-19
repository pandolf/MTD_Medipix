#include "../interface/MPHit.h"

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>



MPHit::MPHit( int x, int y, int c ) {

  x_ = x;
  y_ = y;
  c_ = c;

}


MPHit::MPHit( const MPHit& rhs ) {

  x_ = rhs.x();
  y_ = rhs.y();
  c_ = rhs.c();

}


int MPHit::deltax( const MPHit& otherhit ) const {

  return (this->x_ - otherhit.x());

}

int MPHit::deltay( const MPHit& otherhit ) const {

  return (this->y_ - otherhit.y());

}


bool MPHit::isAdjacent( const MPHit& otherhit ) const {

  return ( (fabs(this->deltax(otherhit))<=1) && (fabs(this->deltay(otherhit))<=1) );

}


float MPHit::deltaR( const MPHit& otherhit ) const {

  return sqrt( (float)this->deltax(otherhit)*this->deltax(otherhit) + (float)this->deltay(otherhit)*this->deltay(otherhit) );

}


std::vector<MPHit> MPHit::readFrameFile( const std::string& frameFile ) {

  std::cout << "[MPHit::readFrameFile] Reading frame file: " << frameFile << std::endl;

  std::vector<MPHit> hits;

  std::ifstream ifs(frameFile);

  while( ifs.good() ) {

    int x, y, c(0);
    ifs >> x >> y >> c;

    if( c>0 ) 
      hits.push_back(MPHit(x,y,c));

  }

  return hits;

}
  
