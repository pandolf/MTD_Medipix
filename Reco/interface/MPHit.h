#ifndef MPHIT_H
#define MPHIT_H

#include <vector>


class MPHit {

 public:

  MPHit( int x, int y, int c=1 );
  MPHit( const MPHit& rhs );

  ~MPHit() {};

  int x() const { return x_; };
  int y() const { return y_; };
  int c() const { return c_; };

  void set_x( int x ) { x_ = x; };
  void set_y( int y ) { y_ = y; };
  void set_c( int c ) { c_ = c; };

  int deltax( const MPHit& otherhit ) const;
  int deltay( const MPHit& otherhit ) const;

  bool isAdjacent( const MPHit& otherhit ) const;

  float deltaR( const MPHit& otherhit ) const;

  static std::vector<MPHit> readFrameFile( const std::string& frameFile );

 private:

  int x_;
  int y_;
  int c_;


};

#endif
