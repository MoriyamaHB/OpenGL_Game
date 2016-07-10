/*
 * bgm.cpp
 *
 *  Created on: 2016/07/10
 *      Author: mhrbykm
 */

#include "../declaration/GV.h"

//Bgmを鳴らす
void Bgm::Play(Bgm::BgmStruct sound) {
	delete pbgm_[sound];
	if (sound == Bgm::kGameBgm) {
		pbgm_[sound] = new Sound("sound/111.wav");	//Bgm
	}
}

//Bgmを更新
void Bgm::Update() {
	for (int i = 0; i < Bgm::BgmStructNum; i++) {
		if (pbgm_[i] == NULL)
			break;
		pbgm_[i]->Stream();
	}
}

//Bgmを止める
void Bgm::Stop() {
	for (int i = 0; i < Bgm::BgmStructNum; i++) {
		delete pbgm_[i];
		pbgm_[i] = NULL;
	}
}

Bgm::~Bgm(){
	Stop();
}
