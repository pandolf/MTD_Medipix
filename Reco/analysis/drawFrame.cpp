#include "../interface/MPHit.h"
#include "../interface/MPCluster.h"
#include "../interface/MPDrawStuff.h"

#include <iostream>
#include <string>

#include "TCanvas.h"
#include "TH2D.h"
#include "TColor.h"
#include "TStyle.h"
#include "TEllipse.h"





int main( int argc, char* argv[] ) {


  if( argc != 2 ) {
    std::cout << "./drawFrame [frameFile]" << std::endl;
    exit(1);
  }

  system( "mkdir -p frames" );

  MPDrawStuff::setStyle();
  gStyle->SetPadTopMargin(0.);
  gStyle->SetPadBottomMargin(0.);
  gStyle->SetPadLeftMargin(0.);
  gStyle->SetPadRightMargin(0.);


  MPDrawStuff::setPalette( "pixelman" );
  MPDrawStuff::setPalette( "clusterStandard" );

  std::string frameFile_full(argv[1]);
  std::string frameFile = frameFile_full.substr(0, frameFile_full.find("."));
  if( frameFile.size()==frameFile_full.size() ) {
    frameFile_full += ".txt";
  }

  std::vector<MPHit> hits = MPHit::readFrameFile(frameFile_full);

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

  std::cout << "found these clusters:" << std::endl;
  for( unsigned i=0; i<clusters.size(); ++i ) {

    std::cout << "cluster " << i << "    width=" << clusters[i].width() << std::endl;

    for( unsigned ihit=0; ihit<clusters[i].hits().size(); ++ihit ) 

      std::cout << "  hit " << ihit << "  x: " << clusters[i].hits()[ihit].x() << "  y: " << clusters[i].hits()[ihit].y() << std::endl;

  }



  for( unsigned i=0; i<clusters.size(); ++i ) {

    float ell_r = clusters[i].width()+1;
    //ell_r *= 5.; // for visibility

    TEllipse* ell = new TEllipse( clusters[i].x(), clusters[i].y(), ell_r, ell_r );
    if( clusters[i].isGood() ) {
      ell->SetLineColor(kGreen);
      ell->SetLineWidth(2);
    } else {
      ell->SetLineColor(kRed);
      ell->SetLineWidth(1);
    }
    ell->SetFillStyle(0);
    ell->Draw("same");

  }

  c1->SaveAs( Form("frames/%s_withClust.pdf", frameFile.c_str()) );
  c1->SaveAs( Form("frames/%s_withClust.eps", frameFile.c_str()) );


  return 0;

}


