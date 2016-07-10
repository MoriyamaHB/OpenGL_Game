/*
 * bgm.h
 *
 *  Created on: 2016/07/10
 *      Author: mhrbykm
 */

#ifndef SOUND_BGM_H_
#define SOUND_BGM_H_

class Bgm{
public:
	enum BgmStruct {
		kGameBgm = 0, BgmStructNum
	};
	void Play(BgmStruct sound);
	void Update();
	void Stop();
	~Bgm();
private:
	Sound *pbgm_[BgmStructNum]; //Bgm
};

#endif /* SOUND_BGM_H_ */
