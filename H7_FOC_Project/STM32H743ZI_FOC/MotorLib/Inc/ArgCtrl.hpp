/*
 * ArgCtrl.hpp
 *
 *  Created on: Sep 3, 2019
 *      Author: watashi
 */

#ifndef INC_ARGCTRL_HPP_
#define INC_ARGCTRL_HPP_


#include "MotorLibDefPack.hpp"
#include "paramsetting.h"
#include "math.h"
#include "Observer.hpp"

class ArgCtrl {
public://struct
	class ForceCommutation {
		private:
		public:
		fp_rad mFCtargetRPM;
		fp_rad mFCtargetAcc;
		fp_rad mAccelSPD;
	};
private:

	fp_rad mArg;
	fp_rad mArgOld;
	fp_rad mOmega;
	fp_rad mArgErr;

	ForceCommutation ForceCom;

public:
	ArgCtrl();
	virtual ~ArgCtrl();
	void Init(void);
	void increment(fp_rad pArg);
	void decrement(fp_rad pArg);
	fp_rad getArg(void);
	fp_rad getArgErr(void);
	fp_rad getArgOld(void);
	fp_rad getArgOmega(void);

	ForceCom_Status FCacceleration(void);
	ForceCom_Status FCdeceleration(void);

};

#endif /* INC_ARGCTRL_HPP_ */
