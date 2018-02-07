#include "engineStdafx.h"
#include "Random.h"

/*!
* @brief	�R���X�g���N�^�B
*/
Random::Random()
{
}
/*!
* @brief	�f�X�g���N�^�B
*/
Random::~Random()
{
}
/*!
* @brief	�������������B
*@param[in]	seed		�����_���V�[�h�B
*/
void Random::Init(unsigned long seed)
{
	mt[0] = seed & 0xffffffffUL;
	for (mti = 1; mti<N; mti++) {
		mt[mti] =
			(1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
		/* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
		/* In the previous versions, MSBs of the seed affect   */
		/* only MSBs of the array mt[].                        */
		/* 2002/01/09 modified by Makoto Matsumoto             */
		mt[mti] &= 0xffffffffUL;
		/* for >32 bit machines */
	}
}