#ifndef MPCLUSTER_H
#define MPCLUSTER_H

#include <iostream>
#include <vector>

#include "../interface/MPHit.h"



class MPCluster {

 public:

  MPCluster( const std::vector<MPHit>& hits );
  MPCluster();
  ~MPCluster() {};

  void add_hit( const MPHit& hit );

  float x() const;
  float y() const;

  bool isAdjacent( const MPHit& hit ) const;

  int nhits() const { return hits_.size(); };

  int width() const;
  int widthx() const;
  int widthy() const;

  float rms() const;

  bool isGood() const;

  float dist( const MPCluster& other_cluster ) const;

  std::vector<MPHit> hits() const { return hits_; };

  void set_hits( const std::vector<MPHit>& hits ) { hits_ = hits;};

  static std::vector<MPCluster> makeClustersNN( const std::vector<MPHit>& hits );

 private:

  std::vector<MPHit> hits_;

};


#endif
