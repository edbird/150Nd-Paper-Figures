#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include <TH1.h>
//#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
//#include <TGraphErrors.h>

#include "LD_REWEIGHT_DATA_2.h"
//#include "read_data_from_file.h"


#include <string>
#include <map>


TH1D *hSingleEnergy_N0 = nullptr;
TH1D *hSingleEnergy_N2 = nullptr;
TH1D *hSingleEnergy_N22 = nullptr;
TH1D *hSingleEnergy_N4 = nullptr;

TH1D *hTotalEnergy_N0 = nullptr;
TH1D *hTotalEnergy_N2 = nullptr;
TH1D *hTotalEnergy_N22 = nullptr;
TH1D *hTotalEnergy_N4 = nullptr;

TH1D *hSingleEnergy2_N0 = nullptr;
TH1D *hSingleEnergy2_N2 = nullptr;
TH1D *hSingleEnergy2_N22 = nullptr;
TH1D *hSingleEnergy2_N4 = nullptr;
TH1D *hSingleEnergy2_NT = nullptr;

TH1D *hTotalEnergy2_N0 = nullptr;
TH1D *hTotalEnergy2_N2 = nullptr;
TH1D *hTotalEnergy2_N22 = nullptr;
TH1D *hTotalEnergy2_N4 = nullptr;
TH1D *hTotalEnergy2_NT = nullptr;


struct hist_xi_struct
{

    hist_xi_struct(const double xi31, const double xi51, TH1D* histTotal, TH1D *histSingle)
        : xi_31(xi31)
        , xi_51(xi51)
        , hTotalEnergy(histTotal)
        , hSingleEnergy(histSingle)
    {
    }

    double xi_31;
    double xi_51;
    TH1D *hTotalEnergy;
    TH1D *hSingleEnergy;
};

std::map<std::string, std::map<std::string, hist_xi_struct*>> h_xi_map;


void plotpaperfig()
{

    gStyle->SetLineStyleString(11, "80 40");
    gStyle->SetLineStyleString(12, "80 40 20 40");
    gStyle->SetLineStyleString(13, "10 20");
    gStyle->SetLineStyleString(14, "40 10");

    std::string file_base = "../gA_theoretical_files/psf-nuclei";


    const std::string isotope = "150Nd";
    //const std::string isotope = "100Mo";


    double Q_bb = 0.0;
    // 150 Nd
    if(isotope == "150Nd")
    {
        Q_bb = 3.37138;
    }
    // 100 Mo
    else if(isotope == "100Mo")
    {
        Q_bb = 3.0344;
    }

    // 150 Nd
    //const Double_t E_min = 0.38;
    // 100 Mo
    const Double_t E_min = 0.4;

    //const Int_t N_BINS_X = std::round((Q_bb) / 1.0e-3);
    const Int_t N_BINS_X = (Int_t)1000.0 * Q_bb;
    std::cout << "N_BINS_X=" << N_BINS_X << std::endl;
    const Double_t X_MIN = 0.0;
    const Double_t X_MAX = std::round(Q_bb * 1000.0) / 1000.0;


    hSingleEnergy_N0 = new TH1D("hSingleEnergy_N0", "hSingleEnergy_N0", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy_N2 = new TH1D("hSingleEnergy_N2", "hSingleEnergy_N2", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy_N22 = new TH1D("hSingleEnergy_N22", "hSingleEnergy_N22", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy_N4 = new TH1D("hSingleEnergy_N4", "hSingleEnergy_N4", N_BINS_X, X_MIN, X_MAX);

    hTotalEnergy_N0 = new TH1D("hTotalEnergy_N0", "hTotalEnergy_N0", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy_N2 = new TH1D("hTotalEnergy_N2", "hTotalEnergy_N2", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy_N22 = new TH1D("hTotalEnergy_N22", "hTotalEnergy_N22", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy_N4 = new TH1D("hTotalEnergy_N4", "hTotalEnergy_N4", N_BINS_X, X_MIN, X_MAX);

    hSingleEnergy2_N0 = new TH1D("hSingleEnergy2_N0", "hSingleEnergy2_N0", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy2_N2 = new TH1D("hSingleEnergy2_N2", "hSingleEnergy2_N2", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy2_N22 = new TH1D("hSingleEnergy2_N22", "hSingleEnergy2_N22", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy2_N4 = new TH1D("hSingleEnergy2_N4", "hSingleEnergy2_N4", N_BINS_X, X_MIN, X_MAX);
    hSingleEnergy2_NT = new TH1D("hSingleEnergy2_N4", "hSingleEnergy2_NT", N_BINS_X, X_MIN, X_MAX);

    hTotalEnergy2_N0 = new TH1D("hTotalEnergy2_N0", "hTotalEnergy2_N0", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy2_N2 = new TH1D("hTotalEnergy2_N2", "hTotalEnergy2_N2", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy2_N22 = new TH1D("hTotalEnergy2_N22", "hTotalEnergy2_N22", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy2_N4 = new TH1D("hTotalEnergy2_N4", "hTotalEnergy2_N4", N_BINS_X, X_MIN, X_MAX);
    hTotalEnergy2_NT = new TH1D("hTotalEnergy2_NT", "hTotalEnergy2_NT", N_BINS_X, X_MIN, X_MAX);



    std::string fname_SingleEnergy_N0 =
        file_base + "/" +
        isotope + "/" +
        "0-N0" + "/" +
        "distSingleElecRad.dat";
    std::string fname_SingleEnergy_N2 =
        file_base + "/" +
        isotope + "/" +
        "1-N2" + "/" +
        "distSingleElecRad.dat";
    std::string fname_SingleEnergy_N22 =
        file_base + "/" +
        isotope + "/" +
        "2-N22" + "/" +
        "distSingleElecRad.dat";
    std::string fname_SingleEnergy_N4 =
        file_base + "/" +
        isotope + "/" +
        "3-N4" + "/" +
        "distSingleElecRad.dat";


    std::string fname_TotalEnergy_N0 =
        file_base + "/" +
        isotope + "/" +
        "0-N0" + "/" +
        "distSumElecRad.dat";
    std::string fname_TotalEnergy_N2 =
        file_base + "/" +
        isotope + "/" +
        "1-N2" + "/" +
        "distSumElecRad.dat";
    std::string fname_TotalEnergy_N22 =
        file_base + "/" +
        isotope + "/" +
        "2-N22" + "/" +
        "distSumElecRad.dat";
    std::string fname_TotalEnergy_N4 =
        file_base + "/" +
        isotope + "/" +
        "3-N4" + "/" +
        "distSumElecRad.dat";

    hSingleEnergy_N0->Sumw2();
    hSingleEnergy_N2->Sumw2();
    hSingleEnergy_N22->Sumw2();
    hSingleEnergy_N4->Sumw2();

    hTotalEnergy_N0->Sumw2();
    hTotalEnergy_N2->Sumw2();
    hTotalEnergy_N22->Sumw2();
    hTotalEnergy_N4->Sumw2();

    hSingleEnergy2_N0->Sumw2();
    hSingleEnergy2_N2->Sumw2();
    hSingleEnergy2_N22->Sumw2();
    hSingleEnergy2_N4->Sumw2();
    hSingleEnergy2_NT->Sumw2();

    hTotalEnergy2_N0->Sumw2();
    hTotalEnergy2_N2->Sumw2();
    hTotalEnergy2_N22->Sumw2();
    hTotalEnergy2_N4->Sumw2();
    hTotalEnergy2_NT->Sumw2();

    hSingleEnergy_N0->SetLineStyle(11);
    hSingleEnergy_N0->SetLineWidth(2);
    hSingleEnergy_N0->SetLineColor(kBlack);

    hSingleEnergy_N2->SetLineStyle(1);
    hSingleEnergy_N2->SetLineWidth(2);
    hSingleEnergy_N2->SetLineColor(kRed);

    hSingleEnergy_N22->SetLineStyle(2);
    hSingleEnergy_N22->SetLineWidth(2);
    hSingleEnergy_N22->SetLineColor(kBlue);

    hSingleEnergy_N4->SetLineStyle(12);
    hSingleEnergy_N4->SetLineWidth(2);
    hSingleEnergy_N4->SetLineColor(kBlue);

    hTotalEnergy_N0->SetLineStyle(11);
    hTotalEnergy_N0->SetLineWidth(2);
    hTotalEnergy_N0->SetLineColor(kBlack);

    hTotalEnergy_N2->SetLineStyle(1);
    hTotalEnergy_N2->SetLineWidth(2);
    hTotalEnergy_N2->SetLineColor(kRed);

    hTotalEnergy_N22->SetLineStyle(2);
    hTotalEnergy_N22->SetLineWidth(2);
    hTotalEnergy_N22->SetLineColor(kBlue);

    hTotalEnergy_N4->SetLineStyle(12);
    hTotalEnergy_N4->SetLineWidth(2);
    hTotalEnergy_N4->SetLineColor(kBlue);

    hSingleEnergy2_N0->SetLineStyle(11);
    hSingleEnergy2_N0->SetLineWidth(2);
    hSingleEnergy2_N0->SetLineColor(kBlue);

    hSingleEnergy2_N2->SetLineStyle(12);
    hSingleEnergy2_N2->SetLineWidth(2);
    hSingleEnergy2_N2->SetLineColor(kRed);

    hSingleEnergy2_N22->SetLineStyle(2);
    hSingleEnergy2_N22->SetLineWidth(2);
    hSingleEnergy2_N22->SetLineColor(kBlue);

    hSingleEnergy2_N4->SetLineStyle(12);
    hSingleEnergy2_N4->SetLineWidth(2);
    hSingleEnergy2_N4->SetLineColor(kBlue);

    hSingleEnergy2_NT->SetLineStyle(1);
    hSingleEnergy2_NT->SetLineWidth(2);
    hSingleEnergy2_NT->SetLineColor(kBlack);

    hTotalEnergy2_N0->SetLineStyle(11);
    hTotalEnergy2_N0->SetLineWidth(2);
    hTotalEnergy2_N0->SetLineColor(kBlue);

    hTotalEnergy2_N2->SetLineStyle(12);
    hTotalEnergy2_N2->SetLineWidth(2);
    hTotalEnergy2_N2->SetLineColor(kRed);

    hTotalEnergy2_N22->SetLineStyle(2);
    hTotalEnergy2_N22->SetLineWidth(2);
    hTotalEnergy2_N22->SetLineColor(kBlue);

    hTotalEnergy2_N4->SetLineStyle(12);
    hTotalEnergy2_N4->SetLineWidth(2);
    hTotalEnergy2_N4->SetLineColor(kBlue);

    hTotalEnergy2_NT->SetLineStyle(1);
    hTotalEnergy2_NT->SetLineWidth(2);
    hTotalEnergy2_NT->SetLineColor(kBlack);

    ifstream if_SingleEnergy_N0(fname_SingleEnergy_N0);
    ifstream if_SingleEnergy_N2(fname_SingleEnergy_N2);
    ifstream if_SingleEnergy_N22(fname_SingleEnergy_N22);
    ifstream if_SingleEnergy_N4(fname_SingleEnergy_N4);

    ifstream if_TotalEnergy_N0(fname_TotalEnergy_N0);
    ifstream if_TotalEnergy_N2(fname_TotalEnergy_N2);
    ifstream if_TotalEnergy_N22(fname_TotalEnergy_N22);
    ifstream if_TotalEnergy_N4(fname_TotalEnergy_N4);


    double e1, prob1;
    unsigned int counts;


    counts = 0;
    while(if_SingleEnergy_N0.good())
    {
        if_SingleEnergy_N0 >> e1 >> prob1;
        hSingleEnergy_N0->Fill(e1, prob1);
        hSingleEnergy2_N0->Fill(e1, prob1);
        hSingleEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_SingleEnergy_N0 << " count: " << counts << std::endl;

    counts = 0;
    while(if_SingleEnergy_N2.good())
    {
        if_SingleEnergy_N2 >> e1 >> prob1;
        hSingleEnergy_N2->Fill(e1, prob1);
        hSingleEnergy2_N2->Fill(e1, prob1);
        hSingleEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_SingleEnergy_N2 << " count: " << counts << std::endl;

    counts = 0;
    while(if_SingleEnergy_N22.good())
    {
        if_SingleEnergy_N22 >> e1 >> prob1;
        hSingleEnergy_N22->Fill(e1, prob1);
        hSingleEnergy2_N22->Fill(e1, prob1);
        hSingleEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_SingleEnergy_N22 << " count: " << counts << std::endl;

    counts = 0;
    while(if_SingleEnergy_N4.good())
    {
        if_SingleEnergy_N4 >> e1 >> prob1;
        hSingleEnergy_N4->Fill(e1, prob1);
        hSingleEnergy2_N4->Fill(e1, prob1);
        hSingleEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_SingleEnergy_N4 << " count: " << counts << std::endl;



    counts = 0;
    while(if_TotalEnergy_N0.good())
    {
        if_TotalEnergy_N0 >> e1 >> prob1;
        hTotalEnergy_N0->Fill(e1, prob1);
        hTotalEnergy2_N0->Fill(e1, prob1);
        hTotalEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_TotalEnergy_N0 << " count: " << counts << std::endl;

    counts = 0;
    while(if_TotalEnergy_N2.good())
    {
        if_TotalEnergy_N2 >> e1 >> prob1;
        hTotalEnergy_N2->Fill(e1, prob1);
        hTotalEnergy2_N2->Fill(e1, prob1);
        hTotalEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_TotalEnergy_N2 << " count: " << counts << std::endl;

    counts = 0;
    while(if_TotalEnergy_N22.good())
    {
        if_TotalEnergy_N22 >> e1 >> prob1;
        hTotalEnergy_N22->Fill(e1, prob1);
        hTotalEnergy2_N22->Fill(e1, prob1);
        hTotalEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_TotalEnergy_N22 << " count: " << counts << std::endl;

    counts = 0;
    while(if_TotalEnergy_N4.good())
    {
        if_TotalEnergy_N4 >> e1 >> prob1;
        hTotalEnergy_N4->Fill(e1, prob1);
        hTotalEnergy2_N4->Fill(e1, prob1);
        hTotalEnergy2_NT->Fill(e1, prob1);
        ++ counts;
    }
    std::cout << fname_TotalEnergy_N4 << " count: " << counts << std::endl;


    hSingleEnergy_N0->Scale(Q_bb * 1.0e+03 / hSingleEnergy_N0->Integral());
    hSingleEnergy_N2->Scale(Q_bb * 1.0e+03 / hSingleEnergy_N2->Integral());
    hSingleEnergy_N22->Scale(Q_bb * 1.0e+03 / hSingleEnergy_N22->Integral());
    hSingleEnergy_N4->Scale(Q_bb * 1.0e+03 / hSingleEnergy_N4->Integral());

//    std::cout << "hTotalEnergy_N0->Integral() => " << hTotalEnergy_N0->Integral() << std::endl;

    hTotalEnergy_N0->Scale(Q_bb * 1.0e+03 / hTotalEnergy_N0->Integral());
    hTotalEnergy_N2->Scale(Q_bb * 1.0e+03 / hTotalEnergy_N2->Integral());
    hTotalEnergy_N22->Scale(Q_bb * 1.0e+03 / hTotalEnergy_N22->Integral());
    hTotalEnergy_N4->Scale(Q_bb * 1.0e+03 / hTotalEnergy_N4->Integral());

    hSingleEnergy2_N0->Scale(Q_bb * 1.0e+03 / hSingleEnergy2_NT->Integral());
    hSingleEnergy2_N2->Scale(Q_bb * 1.0e+03 / hSingleEnergy2_NT->Integral());
    hSingleEnergy2_N22->Scale(Q_bb * 1.0e+03 / hSingleEnergy2_NT->Integral());
    hSingleEnergy2_N4->Scale(Q_bb * 1.0e+03 / hSingleEnergy2_NT->Integral());
    hSingleEnergy2_NT->Scale(Q_bb * 1.0e+03 / hSingleEnergy2_NT->Integral());

    hTotalEnergy2_N0->Scale(Q_bb * 1.0e+03 / hTotalEnergy2_NT->Integral());
    hTotalEnergy2_N2->Scale(Q_bb * 1.0e+03 / hTotalEnergy2_NT->Integral());
    hTotalEnergy2_N22->Scale(Q_bb * 1.0e+03 / hTotalEnergy2_NT->Integral());
    hTotalEnergy2_N4->Scale(Q_bb * 1.0e+03 / hTotalEnergy2_NT->Integral());
    hTotalEnergy2_NT->Scale(Q_bb * 1.0e+03 / hTotalEnergy2_NT->Integral());


    ///////////////////////////////////////////////////////////////////////////
    // Canvas
    ///////////////////////////////////////////////////////////////////////////

    double lposx = 0.48;
    double lposy = 0.65;
    double lsizex = 0.38;
    double lsizey = 0.2;
    double lposy2 = lposy + lsizey / 4.0;
    double lsizey2 = lsizey / 4.0 * 5.0;

    double lposy3 = 0.75;

    TCanvas *canvas = new TCanvas("canvas", "canvas", 600 * 2, 500 * 2);
    canvas->SetFillColor(kWhite);

    canvas->cd();
    TPad *p0 = new TPad("pad0", "pad0", 0.0, 0.5, 0.5, 1.0);
    p0->SetTicks(2, 2);
    p0->SetLeftMargin(0.15);
    p0->SetBottomMargin(0.0);
    p0->SetRightMargin(0.08);
    p0->Draw();

    canvas->cd();
    TPad *p1 = new TPad("pad1", "pad1", 0.5, 0.5, 1.0, 1.0);
    p1->SetTicks(2, 2);
    p1->SetLeftMargin(0.13);
    p1->SetBottomMargin(0.0);
    p1->SetRightMargin(0.1);
    p1->Draw();

    canvas->cd();
    TPad *p2 = new TPad("pad2", "pad2", 0.0, 0.0, 0.5, 0.5);
    p2->SetTicks(2, 2);
    p2->SetLeftMargin(0.15);
    p2->SetTopMargin(0.0);
    p2->SetBottomMargin(0.15);
    p2->SetRightMargin(0.08);
    p2->Draw();

    canvas->cd();
    TPad *p3 = new TPad("pad3", "pad3", 0.5, 0.0, 1.0, 0.5);
    p3->SetTicks(2, 2);
    p3->SetLeftMargin(0.13);
    p3->SetTopMargin(0.0);
    p3->SetBottomMargin(0.15);
    p3->SetRightMargin(0.1);
    p3->Draw();


    p0->cd();
    
    hSingleEnergy_N0->SetTitle(0);
    hSingleEnergy_N0->SetStats(0);
    hSingleEnergy_N0->GetYaxis()->SetRangeUser(0.0, 6.0);
    hSingleEnergy_N0->GetXaxis()->SetLabelSize(20);
    hSingleEnergy_N0->GetYaxis()->SetLabelSize(20);
    hSingleEnergy_N0->GetXaxis()->SetLabelFont(43);
    hSingleEnergy_N0->GetYaxis()->SetLabelFont(43);
    hSingleEnergy_N0->GetXaxis()->SetTitleSize(25);
    hSingleEnergy_N0->GetYaxis()->SetTitleSize(25);
    hSingleEnergy_N0->GetXaxis()->SetTitleFont(43);
    hSingleEnergy_N0->GetYaxis()->SetTitleFont(43);
    hSingleEnergy_N0->GetXaxis()->SetTitle("T_{e} / Q_{#beta#beta}");
    hSingleEnergy_N0->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{e}/Q_{#beta#beta})");
    hSingleEnergy_N0->GetXaxis()->SetTitleOffset(1.5);
    hSingleEnergy_N0->GetYaxis()->SetTitleOffset(2.5);

    hSingleEnergy_N0->Draw("hist");
    hSingleEnergy_N2->Draw("histsame");
    hSingleEnergy_N22->Draw("histsame");
    hSingleEnergy_N4->Draw("histsame");

    hSingleEnergy_N0->GetYaxis()->ChangeLabel(1, 0, 0);
    hSingleEnergy_N0->GetYaxis()->ChangeLabel(-1, 0, 0);
    hSingleEnergy_N0->GetXaxis()->ChangeLabel(1, 0, 0);


    TLegend *leg0 = new TLegend(lposx, lposy, lposx + lsizex, lposy + lsizey);
    leg0->AddEntry(hSingleEnergy_N0, "N = 0", "L");
    leg0->AddEntry(hSingleEnergy_N2, "N = 2", "L");
    leg0->AddEntry(hSingleEnergy_N22, "N = 22", "L");
    leg0->AddEntry(hSingleEnergy_N4, "N = 4", "L");
    leg0->SetBorderSize(0);
    leg0->SetMargin(0.7);
    leg0->SetTextFont(63);
    leg0->SetTextSize(25);

    leg0->Draw();

    p1->cd();

    hTotalEnergy_N0->SetTitle(0);
    hTotalEnergy_N0->SetStats(0);
    hTotalEnergy_N0->GetYaxis()->SetRangeUser(0.0, 2.5);
    hTotalEnergy_N0->GetXaxis()->SetLabelSize(20);
    hTotalEnergy_N0->GetYaxis()->SetLabelSize(20);
    hTotalEnergy_N0->GetXaxis()->SetLabelFont(43);
    hTotalEnergy_N0->GetYaxis()->SetLabelFont(43);
    hTotalEnergy_N0->GetXaxis()->SetTitleSize(25);
    hTotalEnergy_N0->GetYaxis()->SetTitleSize(25);
    hTotalEnergy_N0->GetXaxis()->SetTitleFont(43);
    hTotalEnergy_N0->GetYaxis()->SetTitleFont(43);
    hTotalEnergy_N0->GetXaxis()->SetTitle("T_{ee} / Q_{#beta#beta}");
    hTotalEnergy_N0->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{ee}/Q_{#beta#beta})");
    hTotalEnergy_N0->GetXaxis()->SetTitleOffset(1.5);
    hTotalEnergy_N0->GetYaxis()->SetTitleOffset(2.0);

    hTotalEnergy_N0->Draw("hist");
    hTotalEnergy_N2->Draw("histsame");
    hTotalEnergy_N22->Draw("histsame");
    hTotalEnergy_N4->Draw("histsame");

    hTotalEnergy_N0->GetYaxis()->ChangeLabel(1, 0, 0);
    hTotalEnergy_N0->GetYaxis()->ChangeLabel(-1, 0, 0);
    hTotalEnergy_N0->GetXaxis()->ChangeLabel(1, 0, 0);


    p2->cd();
    
    hSingleEnergy2_NT->SetTitle(0);
    hSingleEnergy2_NT->SetStats(0);
    hSingleEnergy2_NT->GetYaxis()->SetRangeUser(0.0, 4.0);
    hSingleEnergy2_NT->GetXaxis()->SetLabelSize(20);
    hSingleEnergy2_NT->GetYaxis()->SetLabelSize(20);
    hSingleEnergy2_NT->GetXaxis()->SetLabelFont(43);
    hSingleEnergy2_NT->GetYaxis()->SetLabelFont(43);
    hSingleEnergy2_NT->GetXaxis()->SetTitleSize(25);
    hSingleEnergy2_NT->GetYaxis()->SetTitleSize(25);
    hSingleEnergy2_NT->GetXaxis()->SetTitleFont(43);
    hSingleEnergy2_NT->GetYaxis()->SetTitleFont(43);
    hSingleEnergy2_NT->GetXaxis()->SetTitle("T_{e} / Q_{#beta#beta}");
    hSingleEnergy2_NT->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{e}/Q_{#beta#beta})");
    hSingleEnergy2_NT->GetXaxis()->SetTitleOffset(2.5);
    hSingleEnergy2_NT->GetYaxis()->SetTitleOffset(2.5);

    hSingleEnergy2_NT->Draw("hist");
    hSingleEnergy2_N0->Draw("histsame");
    hSingleEnergy2_N2->Draw("histsame");
    hSingleEnergy2_N22->Draw("histsame");
    hSingleEnergy2_N4->Draw("histsame");

    hSingleEnergy2_NT->GetYaxis()->ChangeLabel(1, 0, 0);
    hSingleEnergy2_NT->GetYaxis()->ChangeLabel(-1, 0, 0);


    TLegend *leg2 = new TLegend(lposx, lposy2, lposx + lsizex, lposy2 + lsizey2);
    leg2->AddEntry(hSingleEnergy2_NT, "Total", "L");
    leg2->AddEntry(hSingleEnergy2_N0, "N = 0", "L");
    leg2->AddEntry(hSingleEnergy2_N2, "N = 2", "L");
    leg2->AddEntry(hSingleEnergy2_N22, "N = 22", "L");
    leg2->AddEntry(hSingleEnergy2_N4, "N = 4", "L");
    leg2->SetBorderSize(0);
    leg2->SetMargin(0.7);
    leg2->SetTextFont(63);
    leg2->SetTextSize(25);

    leg2->Draw();

    p3->cd();

    hTotalEnergy2_NT->SetTitle(0);
    hTotalEnergy2_NT->SetStats(0);
    hTotalEnergy2_NT->GetYaxis()->SetRangeUser(0.0, 2.5);
    hTotalEnergy2_NT->GetXaxis()->SetLabelSize(20);
    hTotalEnergy2_NT->GetYaxis()->SetLabelSize(20);
    hTotalEnergy2_NT->GetXaxis()->SetLabelFont(43);
    hTotalEnergy2_NT->GetYaxis()->SetLabelFont(43);
    hTotalEnergy2_NT->GetXaxis()->SetTitleSize(25);
    hTotalEnergy2_NT->GetYaxis()->SetTitleSize(25);
    hTotalEnergy2_NT->GetXaxis()->SetTitleFont(43);
    hTotalEnergy2_NT->GetYaxis()->SetTitleFont(43);
    hTotalEnergy2_NT->GetXaxis()->SetTitle("T_{ee} / Q_{#beta#beta}");
    hTotalEnergy2_NT->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{ee}/Q_{#beta#beta})");
    hTotalEnergy2_NT->GetXaxis()->SetTitleOffset(2.5);
    hTotalEnergy2_NT->GetYaxis()->SetTitleOffset(2.0);

    hTotalEnergy2_NT->Draw("hist");
    hTotalEnergy2_N0->Draw("histsame");
    hTotalEnergy2_N2->Draw("histsame");
    hTotalEnergy2_N22->Draw("histsame");
    hTotalEnergy2_N4->Draw("histsame");

    hTotalEnergy2_NT->GetYaxis()->ChangeLabel(1, 0, 0);
    hTotalEnergy2_NT->GetYaxis()->ChangeLabel(-1, 0, 0);


    p1->cd();
    TLatex latex;
    latex.SetNDC();
    latex.SetTextFont(43);
    latex.SetTextSize(45);
    TString latexstring;
    if(isotope == "150Nd")
    {
        latexstring.Form("^{150}Nd");
    }
    else if(isotope == "100Mo")
    {
        latexstring.Form("^{100}Mo");
    }
    latex.DrawLatex(0.68, 0.75, latexstring);


    canvas->Show();
    canvas->SaveAs("paperfig.pdf");
    canvas->SaveAs("paperfig.eps");
    canvas->SaveAs("paperfig.png");
    canvas->SaveAs("paperfig.C");


    ///////////////////////////////////////////////////////////////////////////
    // Create xi_31, xi_51 dependent plots
    ///////////////////////////////////////////////////////////////////////////


    
    h_xi_map["0.0"]["0.0"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);
    h_xi_map["0.4"]["0.0"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);
    h_xi_map["0.8"]["0.0"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);
    h_xi_map["0.0"]["0.0"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);
    h_xi_map["0.0"]["0.4"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);
    h_xi_map["0.0"]["0.8"] = new hist_xi_struct(0.0, 0.0, nullptr, nullptr);

    for(std::map<std::string, std::map<std::string, hist_xi_struct*>>::iterator it = h_xi_map.begin();
        it != h_xi_map.end(); ++ it)
    {
        for(std::map<std::string, hist_xi_struct*>::iterator jt = it->second.begin();
            jt != it->second.end(); ++ jt)
        {
            const double xi_31_value = std::stod(it->first);
            const double xi_51_value = std::stod(jt->first);
            jt->second->xi_31 = xi_31_value;
            jt->second->xi_51 = xi_51_value;
            TString hname;
            TString xi31s;
            TString xi51s;
            xi31s.Form("%1.1f", xi_31_value);
            xi51s.Form("%1.1f", xi_51_value);
            
            hname.Form("hTotalEnergy_xi31_%s_xi51_%s", xi31s.Data(), xi51s.Data());
            jt->second->hTotalEnergy = new TH1D(hname, hname, N_BINS_X, X_MIN, X_MAX);
            jt->second->hTotalEnergy->SetTitle(0);
            jt->second->hTotalEnergy->SetStats(0);
            jt->second->hTotalEnergy->Sumw2();
            jt->second->hTotalEnergy->SetLineWidth(2);

            jt->second->hTotalEnergy->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{ee}/Q_{#beta#beta})");
            jt->second->hTotalEnergy->GetYaxis()->SetTitleFont(43);
            jt->second->hTotalEnergy->GetYaxis()->SetTitleSize(25);
            jt->second->hTotalEnergy->GetYaxis()->SetLabelFont(43);
            jt->second->hTotalEnergy->GetYaxis()->SetLabelSize(20);

            jt->second->hTotalEnergy->GetXaxis()->SetTitle("T_{ee} / Q_{#beta#beta}");
            jt->second->hTotalEnergy->GetXaxis()->SetTitleFont(43);
            jt->second->hTotalEnergy->GetXaxis()->SetTitleSize(25);
            jt->second->hTotalEnergy->GetXaxis()->SetLabelFont(43);
            jt->second->hTotalEnergy->GetXaxis()->SetLabelSize(20);

            hname.Form("hSingleEnergy_xi31_%s_xi51_%s", xi31s.Data(), xi51s.Data());
            jt->second->hSingleEnergy = new TH1D(hname, hname, N_BINS_X, X_MIN, X_MAX);
            jt->second->hSingleEnergy->SetTitle(0);
            jt->second->hSingleEnergy->SetStats(0);
            jt->second->hSingleEnergy->Sumw2();
            jt->second->hSingleEnergy->SetLineWidth(2);

            jt->second->hSingleEnergy->GetYaxis()->SetTitle("(1/#Gamma)_{N} d#Gamma_{N} / d(T_{e}/Q_{#beta#beta})");
            jt->second->hSingleEnergy->GetYaxis()->SetTitleFont(43);
            jt->second->hSingleEnergy->GetYaxis()->SetTitleSize(25);
            jt->second->hSingleEnergy->GetYaxis()->SetLabelFont(43);
            jt->second->hSingleEnergy->GetYaxis()->SetLabelSize(20);

            jt->second->hSingleEnergy->GetXaxis()->SetTitle("T_{e} / Q_{#beta#beta}");
            jt->second->hSingleEnergy->GetXaxis()->SetTitleFont(43);
            jt->second->hSingleEnergy->GetXaxis()->SetTitleSize(25);
            jt->second->hSingleEnergy->GetXaxis()->SetLabelFont(43);
            jt->second->hSingleEnergy->GetXaxis()->SetLabelSize(20);



        }
    }


    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->SetLineStyle(13);
    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->SetLineColor(kBlack);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->SetLineStyle(1);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->SetLineColor(kBlue);
    h_xi_map.at("0.8").at("0.0")->hTotalEnergy->SetLineStyle(14);
    h_xi_map.at("0.8").at("0.0")->hTotalEnergy->SetLineColor(kRed);

    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->SetLineStyle(13);
    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->SetLineColor(kBlack);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->SetLineStyle(1);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->SetLineColor(kBlue);
    h_xi_map.at("0.8").at("0.0")->hSingleEnergy->SetLineStyle(14);
    h_xi_map.at("0.8").at("0.0")->hSingleEnergy->SetLineColor(kRed);

    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->SetLineStyle(13);
    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->SetLineColor(kBlack);
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->SetLineStyle(1);
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->SetLineColor(kBlue);
    h_xi_map.at("0.0").at("0.8")->hTotalEnergy->SetLineStyle(14);
    h_xi_map.at("0.0").at("0.8")->hTotalEnergy->SetLineColor(kRed);

    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->SetLineStyle(13);
    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->SetLineColor(kBlack);
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->SetLineStyle(1);
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->SetLineColor(kBlue);
    h_xi_map.at("0.0").at("0.8")->hSingleEnergy->SetLineStyle(14);
    h_xi_map.at("0.0").at("0.8")->hSingleEnergy->SetLineColor(kRed);


    for(std::map<std::string, std::map<std::string, hist_xi_struct*>>::iterator it = h_xi_map.begin();
        it != h_xi_map.end(); ++ it)
    {
        for(std::map<std::string, hist_xi_struct*>::iterator jt = it->second.begin();
            jt != it->second.end(); ++ jt)
        {
            const double xi_31_value = std::stod(it->first);
            const double xi_51_value = std::stod(jt->first);

            jt->second->hTotalEnergy->Add(hTotalEnergy_N0);
            jt->second->hTotalEnergy->Add(hTotalEnergy_N2, xi_31_value);
            jt->second->hTotalEnergy->Add(hTotalEnergy_N22, 1.0 / 3.0 * xi_31_value * xi_31_value);
            jt->second->hTotalEnergy->Add(hTotalEnergy_N4, 1.0 / 3.0 * xi_31_value * xi_31_value + xi_51_value);
            jt->second->hTotalEnergy->Scale
            (
                hTotalEnergy_N0->Integral() / 
                (
                    hTotalEnergy_N0->Integral() +
                    xi_31_value * hTotalEnergy_N2->Integral() +
                    1.0 / 3.0 * xi_31_value * xi_31_value * hTotalEnergy_N22->Integral() +
                    (1.0 / 3.0 * xi_31_value * xi_31_value + xi_51_value) * hTotalEnergy_N4->Integral()
                )
            );

            jt->second->hSingleEnergy->Add(hSingleEnergy_N0);
            jt->second->hSingleEnergy->Add(hSingleEnergy_N2, xi_31_value);
            jt->second->hSingleEnergy->Add(hSingleEnergy_N22, 1.0 / 3.0 * xi_31_value * xi_31_value);
            jt->second->hSingleEnergy->Add(hSingleEnergy_N4, 1.0 / 3.0 * xi_31_value * xi_31_value + xi_51_value);
            jt->second->hSingleEnergy->Scale
            (
                hSingleEnergy_N0->Integral() / 
                (
                    hSingleEnergy_N0->Integral() + 
                    xi_31_value * hSingleEnergy_N2->Integral() +
                    1.0 / 3.0 * xi_31_value * xi_31_value * hSingleEnergy_N22->Integral() +
                    (1.0 / 3.0 * xi_31_value * xi_31_value + xi_51_value) * hSingleEnergy_N4->Integral()
                )
            );
        }
    }


    ///////////////////////////////////////////////////////////////////////////
    // Canvas 2
    ///////////////////////////////////////////////////////////////////////////


    TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 600 * 2, 500 * 2);
    canvas2->SetFillColor(kWhite);

    canvas2->cd();
    TPad *pad2_0 = new TPad("pad2_0", "pad2_0", 0.0, 0.5, 0.5, 1.0);
    pad2_0->SetTicks(2, 2);
    pad2_0->SetLeftMargin(0.15);
    pad2_0->SetBottomMargin(0.0);
    pad2_0->SetRightMargin(0.08);
    pad2_0->Draw();

    canvas2->cd();
    TPad *pad2_1 = new TPad("pad2_1", "pad2_1", 0.5, 0.5, 1.0, 1.0);
    pad2_1->SetTicks(2, 2);
    pad2_1->SetLeftMargin(0.13);
    pad2_1->SetBottomMargin(0.0);
    pad2_1->SetRightMargin(0.1);
    pad2_1->Draw();

    canvas2->cd();
    TPad *pad2_2 = new TPad("pad2_2", "pad2_2", 0.0, 0.0, 0.5, 0.5);
    pad2_2->SetTicks(2, 2);
    pad2_2->SetLeftMargin(0.15);
    pad2_2->SetTopMargin(0.0);
    pad2_2->SetBottomMargin(0.15);
    pad2_2->SetRightMargin(0.08);
    pad2_2->Draw();

    canvas2->cd();
    TPad *pad2_3 = new TPad("pad2_3", "pad2_3", 0.5, 0.0, 1.0, 0.5);
    pad2_3->SetTicks(2, 2);
    pad2_3->SetLeftMargin(0.13);
    pad2_3->SetTopMargin(0.0);
    pad2_3->SetBottomMargin(0.15);
    pad2_3->SetRightMargin(0.1);
    pad2_3->Draw();

    pad2_0->cd();
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetXaxis()->SetTitleOffset(1.5);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetYaxis()->SetTitleOffset(2.5);

    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetYaxis()->SetRangeUser(0.0, 4.0);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->Draw("axis");
    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->Draw("histsame");
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->Draw("histsame");
    h_xi_map.at("0.8").at("0.0")->hSingleEnergy->Draw("histsame");

    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetYaxis()->ChangeLabel(1, 0, 0);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetYaxis()->ChangeLabel(-1, 0, 0);
    //h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetXaxis()->ChangeLabel(-1, 0, 0);
    h_xi_map.at("0.4").at("0.0")->hSingleEnergy->GetXaxis()->ChangeLabel(1, 0, 0);


    pad2_1->cd();
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetXaxis()->SetTitleOffset(2.5);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetYaxis()->SetTitleOffset(2.0);

    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetYaxis()->SetRangeUser(0.0, 2.5);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->Draw("axis");
    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->Draw("histsame");
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->Draw("histsame");
    h_xi_map.at("0.8").at("0.0")->hTotalEnergy->Draw("histsame");

    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetYaxis()->ChangeLabel(1, 0, 0);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetYaxis()->ChangeLabel(-1, 0, 0);
    //h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetXaxis()->ChangeLabel(-1, 0, 0);
    h_xi_map.at("0.4").at("0.0")->hTotalEnergy->GetXaxis()->ChangeLabel(1, 0, 0);


    pad2_2->cd();
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetXaxis()->SetTitleOffset(2.5);
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetYaxis()->SetTitleOffset(2.5);

    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetYaxis()->SetRangeUser(0.0, 4.5);
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->Draw("axis");
    h_xi_map.at("0.0").at("0.0")->hSingleEnergy->Draw("histsame");
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->Draw("histsame");
    h_xi_map.at("0.0").at("0.8")->hSingleEnergy->Draw("histsame");

    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetYaxis()->ChangeLabel(1, 0, 0);
    h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetYaxis()->ChangeLabel(-1, 0, 0);
    //h_xi_map.at("0.0").at("0.4")->hSingleEnergy->GetXaxis()->ChangeLabel(-1, 0, 0);


    pad2_3->cd();
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetXaxis()->SetTitleOffset(2.5);
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetYaxis()->SetTitleOffset(2.0);

    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetYaxis()->SetRangeUser(0.0, 2.5);
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->Draw("axis");
    h_xi_map.at("0.0").at("0.0")->hTotalEnergy->Draw("histsame");
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->Draw("histsame");
    h_xi_map.at("0.0").at("0.8")->hTotalEnergy->Draw("histsame");

    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetYaxis()->ChangeLabel(1, 0, 0);
    h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetYaxis()->ChangeLabel(-1, 0, 0);
    //h_xi_map.at("0.0").at("0.4")->hTotalEnergy->GetXaxis()->ChangeLabel(-1, 0, 0);






    pad2_0->cd();

    TLegend *leg2_0 = new TLegend(lposx, lposy, lposx + lsizex, lposy + lsizey);
    leg2_0->AddEntry(h_xi_map.at("0.0").at("0.0")->hSingleEnergy, "#xi_{31} = 0.0", "L");
    leg2_0->AddEntry(h_xi_map.at("0.4").at("0.0")->hSingleEnergy, "#xi_{31} = 0.4", "L");
    leg2_0->AddEntry(h_xi_map.at("0.8").at("0.0")->hSingleEnergy, "#xi_{31} = 0.8", "L");
    //leg2_0->SetHeader("#xi_{51} = 0.0", "C");
    leg2_0->SetBorderSize(0);
    leg2_0->SetMargin(0.6);
    leg2_0->SetTextFont(63);
    leg2_0->SetTextSize(25);

    leg2_0->Draw();



    pad2_2->cd();

    TLegend *leg2_2 = new TLegend(lposx, lposy3, lposx + lsizex, lposy3 + lsizey);
    //leg2_2->SetHeader("#xi_{31} = 0.0", "C");
    leg2_2->AddEntry(h_xi_map.at("0.0").at("0.0")->hSingleEnergy, "#xi_{51} = 0.0", "L");
    leg2_2->AddEntry(h_xi_map.at("0.0").at("0.4")->hSingleEnergy, "#xi_{51} = 0.4", "L");
    leg2_2->AddEntry(h_xi_map.at("0.0").at("0.8")->hSingleEnergy, "#xi_{51} = 0.8", "L");
    leg2_2->SetBorderSize(0);
    leg2_2->SetMargin(0.6);
    leg2_2->SetTextFont(63);
    leg2_2->SetTextSize(25);

    leg2_2->Draw();



    pad2_1->cd();

    TLatex latex2;
    latex2.SetNDC();
    latex2.SetTextFont(43);
    latex2.SetTextSize(45);
    TString latexstring2;
    if(isotope == "150Nd")
    {
        latexstring2.Form("^{150}Nd");
    }
    else if(isotope == "100Mo")
    {
        latexstring2.Form("^{100}Mo");
    }
    latex2.DrawLatex(0.68, 0.75, latexstring2);



    canvas2->Show();
    canvas2->SaveAs("paperfig2.pdf");
    canvas2->SaveAs("paperfig2.eps");
    canvas2->SaveAs("paperfig2.png");
    canvas2->SaveAs("paperfig2.C");

}
