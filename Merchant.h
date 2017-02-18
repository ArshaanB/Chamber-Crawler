#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "NonPlayable.h"

class Merchant final: public NonPlayable {
	public:
    Merchant(int x, int y);
	SubjectType getSubject() override;
};
#endif
