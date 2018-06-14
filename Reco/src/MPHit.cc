#include "../interface/MPHit.h"

#include <cmath>



MPHit::MPHit( int x, int y, int c ) {

  x_ = x;
  y_ = y;
  c_ = c;

}


int MPHit::deltax( const MPHit& otherhit ) const {

  return (this->x_ - otherhit.x());

}

int MPHit::deltay( const MPHit& otherhit ) const {

  return (this->y_ - otherhit.y());

}


bool MPHit::isAdjacent( const MPHit& otherhit ) const {

  return ( (fabs(this->deltax(otherhit))<=1) || (fabs(this->deltay(otherhit))<=1) );

}


float MPHit::deltaR( const MPHit& otherhit ) const {

  return sqrt( (float)this->deltax(otherhit)*this->deltax(otherhit) + (float)this->deltay(otherhit)*this->deltay(otherhit) );

}
