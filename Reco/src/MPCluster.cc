#include "../interface/MPCluster.h"

#include <cmath>



MPCluster::MPCluster( const std::vector<MPHit>& hits ) {

  hits_ = hits;

}


MPCluster::MPCluster() {

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


float MPCluster::width() const {


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

  float width = std::sqrt( var_x + var_y );
  
  return width;

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
  return clusters;

}

