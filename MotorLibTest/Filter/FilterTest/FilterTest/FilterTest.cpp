// FilterTest.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


#include <iostream>
#include <fstream>   // ifstream, ofstream
#include <string>    // useful for reading and writing
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>


#include "paramsetting.h"
#include "LPF.hpp"
#include "BPF.hpp"
#include "HPF.hpp"
#include "WaveGenerator.hpp"

#include "Delay.hpp"

int main()
{

	Delay mDelay;
	mDelay.SetMaxDelaySize(5);
	mDelay.SetNewVal(1);
	mDelay.SetNewVal(2);

	for (int i = 0; i < 10; i++) {
		mDelay.SetNewVal(i);

		std::cout << mDelay.GetOldValue(2) << std::endl;
	}





	//LPF
	LPF lpf;
	lpf.Init(HF_LPF_B0, HF_LPF_B1, HF_LPF_A1);
	
	LPF lpf_bpf;
	HPF hpf_bpf;

	hpf_bpf.Init(HF_HPF_BPF_B0, HF_HPF_BPF_B1, HF_HPF_BPF_A1);
	lpf_bpf.Init(HF_LPF_BPF_B0, HF_LPF_BPF_B1, HF_LPF_BPF_A1);

	BPF bpf;
	bpf.Init(HF_BPF_B0, HF_BPF_B2, HF_BPF_A1, HF_BPF_A2);

	//bpf.Init(HF_BPF_B0, HF_BPF_B2, -1.868f, 0.87f);


	bool bpfcheck = bpf.Check();

	if (bpfcheck == false) {
		return 0;
	}

	WaveGenerator wavegen1;
	//wavegen1.InitFrequency(HF_CONV_FREQ);
	wavegen1.InitFrequency(220);
	WaveGenerator wavegen2;
	wavegen2.InitFrequency(2200);

	WaveGenerator wavegen3;
	wavegen3.InitFrequency(2200);

	std::string filename = "LPFMod.csv";
	std::ofstream writing_file;
	writing_file.open(filename, std::ios::out);

	float UnitDelayB1[2] = { 0 };
	float UnitDelayA1[2] = { 0 };

	float B0 = 0.0334;
	float B1 = 0.0334;
	float A0 = 1;
	float A1 = 0.9331;


	for (int t = 0; t < 1000; t++) {
	
		std::array<float, 2> sincos220 = wavegen1.OutputWaves();
		std::array<float, 2> sincos100 = wavegen2.OutputWaves();
		std::array<float, 2> sincos3 = wavegen3.OutputWaves();
		float sin220 = sincos220.at(0);
		float cos220 = sincos220.at(1);


		float input;
		input = sincos220.at(1) + sincos100.at(1);// +sincos3.at(1); //cos220 + cos 100
		//if (t == 100) {
		//	input = 1;
		//}
		//else {
		//	input = 0;
		//}






		float BPFResult = (	input * B0
							+ UnitDelayB1[0] * B1
							+ UnitDelayA1[0] * A1 ) * A0;

		//UnitDelay更新
		UnitDelayB1[1] = UnitDelayB1[0];
		UnitDelayA1[1] = UnitDelayA1[0];

		UnitDelayB1[0] = input;
		UnitDelayA1[0] = BPFResult;


		double bpfoutputval = bpf.Output(OBSERVER_CYCLE_TIME, input);
		double lpf_bpfoutputval = lpf_bpf.Output(OBSERVER_CYCLE_TIME, input);
		double hpf_bpfoutputval = hpf_bpf.Output(OBSERVER_CYCLE_TIME, lpf_bpfoutputval);

		double bpfOutput = 2 * hpf_bpfoutputval;
		//double bpfOutput = bpfoutputval;
		//float bpfOutput = BPFResult;

		float heterodyne = bpfOutput * sincos220.at(1);

//		float lpfoutputval = lpf.Output(OBSERVER_CYCLE_TIME, heterodyne);
		float lpfoutputval = 0;
		writing_file << "count," << (double)t/(CONTROL_FREQ_HZ) << ", " << "Input, " << input << ", " << "bpfOut," << bpfOutput <<"," <<"hetero," << heterodyne << "," <<"lpfOut," << lpfoutputval << std::endl;
		//writing_file << "count," << t << ", " << "Sin, " << sin220 << ", " << "cos, " << cos220 << ", " <<
		//	"lpf," << lpfoutputval << std::endl;
	}
	lpf.Output(OBSERVER_CYCLE_TIME, 1.0f);

	std::cout << "writing " << filename << "..." << std::endl;
	std::cout << "aiueo" << std::endl;
	system("pause");
    return 0;
}

