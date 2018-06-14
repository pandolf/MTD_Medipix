#include "../interface/MPHit.h"
#include "../interface/MPCluster.h"
#include "../interface/MPDrawStuff.h"

#include <iostream>
#include <fstream>
#include <string>

#include "TCanvas.h"
#include "TH2D.h"
#include "TColor.h"
#include "TStyle.h"
#include "TEllipse.h"



std::vector<MPHit> readFrame( const std::string& frameFile );



int main( int argc, char* argv[] ) {


  if( argc != 2 ) {
    std::cout << "./drawFrame [frameFile]" << std::endl;
    exit(1);
  }

  system( "mkdir -p frames" );

  MPDrawStuff::setStyle();
  gStyle->SetPadTopMargin(0.);
  gStyle->SetPadBottomMargin(0.);//0.13);
  gStyle->SetPadLeftMargin(0.);//0.16);
  gStyle->SetPadRightMargin(0.);//0.02);

  std::string frameFile_full(argv[1]);
  std::string frameFile = frameFile_full.substr(0, frameFile_full.find("."));

  std::vector<MPHit> hits = readFrame(frameFile_full);

  TCanvas* c1 = new TCanvas( "c1", "", 600, 600 );
  c1->cd();

  TH2D* h2_frame = new TH2D( "frame", "", 256, 1, 257, 256, 1, 257 );
  h2_frame->GetXaxis()->SetNdivisions(0);
  h2_frame->GetYaxis()->SetNdivisions(0);
  h2_frame->GetZaxis()->SetRangeUser(0., 2.);
  h2_frame->SetXTitle("X");
  h2_frame->SetYTitle("Y");

  for( unsigned ix=1; ix<257; ++ix )
    for( unsigned iy=1; iy<257; ++iy )
      h2_frame->SetBinContent( ix, iy, 0.01 );

  for( unsigned i=0; i<hits.size(); ++i )
    h2_frame->SetBinContent( hits[i].x(), hits[i].y(), hits[i].c() );

  h2_frame->Draw("col");

  c1->SaveAs( Form("frames/%s.pdf", frameFile.c_str()) );
  c1->SaveAs( Form("frames/%s.eps", frameFile.c_str()) );


  std::vector<MPCluster> clusters = MPCluster::makeClustersNN(hits);

  for( unsigned i=0; i<clusters.size(); ++i ) {
    TEllipse* ell = new TEllipse( clusters[i].x(), clusters[i].y(), clusters[i].width(), clusters[i].width() );
    ell->SetLineColor(kRed);
    ell->SetLineWidth(2);
    ell->Draw("same");
  }

  c1->SaveAs( Form("frames/%s_withClust.pdf", frameFile.c_str()) );
  c1->SaveAs( Form("frames/%s_withClust.eps", frameFile.c_str()) );


  return 0;

}



std::vector<MPHit> readFrame( const std::string& frameFile ) {

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
