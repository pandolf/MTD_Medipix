#include "../interface/MPCluster.h"

#include <cmath>



MPCluster::MPCluster( const std::vector<MPHit>& hits ) {

  hits_ = hits;

}


MPCluster::MPCluster() {

}


void MPCluster::add_hit( const MPHit& hit ) {

  MPHit newhit(hit);
  this->hits_.push_back(newhit);

}


float MPCluster::x() const {

  float num(0.), denom(0.);

  for( unsigned i=0; i<hits_.size(); ++i ) {

    num   += hits_[i].c() * hits_[i].x();
    denom += hits_[i].c();

  }

  return num/denom;

}


float MPCluster::y() const {

  float num(0.), denom(0.);

  for( unsigned i=0; i<hits_.size(); ++i ) {

    num   += hits_[i].c() * hits_[i].y();
    denom += hits_[i].c();

  }

  return num/denom;

}


bool MPCluster::isAdjacent( const MPHit& hit ) const {

  bool isAdj = false;

  for( unsigned i=0; i<this->hits_.size(); ++i ) {

    if( hit.isAdjacent( this->hits_[i] ) ) {
  
      isAdj = true;
      break;

    } // if

  } // for 

  return isAdj;

}


float MPCluster::rms() const {


  float xm = this->x();
  float ym = this->y();

  float var_x(0.);
  float var_y(0.);

  float sumW(0.);

  for( unsigned i=0; i<hits_.size(); ++i ) {

    sumW += hits_[i].c();

    var_x += ( hits_[i].x() - xm )*( hits_[i].x() - xm )*hits_[i].c(); 
    var_y += ( hits_[i].y() - ym )*( hits_[i].y() - ym )*hits_[i].c(); 

  }

  var_x /= sumW;
  var_y /= sumW;

  float rms = std::sqrt( var_x + var_y );
  
  return rms;

}


int MPCluster::widthx() const {

  int max_x = -1;
  int min_x = 9999;

  for( unsigned i=0; i<this->hits().size(); ++i ) {

    if( hits()[i].x() > max_x ) max_x = hits()[i].x();
    if( hits()[i].x() < min_x ) min_x = hits()[i].x();

  }

  return (max_x-min_x);

}


int MPCluster::widthy() const {

  int max_y = -1;
  int min_y = 9999;

  for( unsigned i=0; i<this->hits().size(); ++i ) {

    if( hits()[i].y() > max_y ) max_y = hits()[i].y();
    if( hits()[i].y() < min_y ) min_y = hits()[i].y();

  }

  return (max_y-min_y);

}


int MPCluster::width() const {

  return std::max( this->widthx(), this->widthy() );

}


bool MPCluster::isGood() const {

  return ( this->width()<=2 );

}



float MPCluster::dist( const MPCluster& other_cluster ) const {

  float x1 = this->x();
  float y1 = this->y();

  float x2 = other_cluster.x();
  float y2 = other_cluster.y();

  return std::sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );

}




std::vector<MPCluster> MPCluster::makeClustersNN( const std::vector<MPHit>& hits ) {

  std::vector<MPCluster> clusters;

  std::vector<MPHit> hits_copy(hits);

  
  std::vector<MPHit>::iterator i_hit = hits_copy.begin();

  while( hits_copy.size()>0 ) {

    MPCluster this_cluster;

    this_cluster.add_hit( *i_hit ); // the seed
    hits_copy.erase( i_hit ); // erase takes care of moving the pointer fwd so no need for ++

    std::vector<MPHit>::iterator j_hit = hits_copy.begin();

    while( j_hit != hits_copy.end() ) { // add all adjacent hits to the cluster

      if( this_cluster.isAdjacent(*j_hit) ) {
    
        this_cluster.add_hit(*j_hit);
        hits_copy.erase(j_hit); // erase takes care of moving the pointer fwd so no need for ++

      } else {

        j_hit++;
    
      }

    } // while

    clusters.push_back(this_cluster);

  }  // while i

  return clusters;

}

