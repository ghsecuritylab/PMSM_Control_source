/*
 * HFConvolution.hpp
 *
 *  Created on: 2020/01/05
 *      Author: watashi
 */

#ifndef SRC_HFCONVOLUTION_HPP_
#define SRC_HFCONVOLUTION_HPP_

#include <array>
#include "ZIntegrate.hpp"
#include "LPF.hpp"
#include "BPF.hpp"

class HFConvolution {
private:
	std::array<float, 2> mIgd; //単位[A]
	std::array<float, 2> mSinCos;

	LPF mLPFIdc;
	LPF mLPFIqc;
	BPF mBPFIdc;
	BPF mBPFIqc;

	float mKi;
	float mKp;
	float mCycleTime;
	Zintegrate1n mIntegOmega;
	Zintegrate1nMod mIntegTheta;


	float mTheta_c;

public:
	HFConvolution();
	virtual ~HFConvolution();

	void InitCycleTime(float pCycleTime);
	void Init(float pCycleTime, float pKi, float pKp);
	void InitKi(float pKi);
	void InitKp(float pKp);
	void LPFInit(float pGainB0, float pGainB1, float pGainA1);
	void BPFInit(float pGainB0, float pGainB2, float pGainA1, float pGainA2);


	void SetIgdPair(const std::array<float, 2> &pIgd);
	void SetSinCos(const std::array<float, 2> &pSinCos);

	void Calculate();

	float GetTheta_c(void);

};

#endif /* SRC_HFCONVOLUTION_HPP_ */