#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(PauseLayer) {
	TodoReturn customSetup() {
		PauseLayer::customSetup();

		auto winSize = CCDirector::get()->getWinSize();

		auto level = GameManager::sharedState()->getPlayLayer()->m_level;

		// iron coin: verified
		// bronze coin: pending
		auto levelIDInt =  level->m_levelID.value();
		auto levelID = std::to_string(levelIDInt);
		auto levelIDKey = std::string(level->getCoinKey(levelIDInt));
		auto areCoinsVerified = level->m_coinsVerified.value();
		std::string weeklySuffix = "";
		if (levelIDKey.size() != 2*levelID.size() + 1) weeklySuffix = levelIDKey.substr(2*levelID.size() + 1, 7);
		
		
		log::info("coins: {}", level->m_coins);
		log::info("id: {}", levelID);
		log::info("id key: {}", levelIDKey);
		log::info("suffix: {}", weeklySuffix);
		log::info("are coins verified: {}", areCoinsVerified);

		auto verifiedCoins = GameStatsManager::sharedState()->m_verifiedUserCoins;
		auto pendingCoins = GameStatsManager::sharedState()->m_pendingUserCoins;


		// IDK LOL 
		auto coin1Slot = CCSprite::createWithSpriteFrameName("secretCoin_2_b_01_001.png");
		coin1Slot->setScale(0.6);
		coin1Slot->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(0.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin1Slot->setZOrder(8);

		auto coin2Slot = CCSprite::createWithSpriteFrameName("secretCoin_2_b_01_001.png");
		coin2Slot->setScale(0.6);
		coin2Slot->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(1.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin2Slot->setZOrder(8);

		auto coin3Slot = CCSprite::createWithSpriteFrameName("secretCoin_2_b_01_001.png");
		coin3Slot->setScale(0.6);
		coin3Slot->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(2.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin3Slot->setZOrder(8);

		auto coin1 = CCSprite::createWithSpriteFrameName("secretCoinUI2_001.png");
		coin1->setScale(0.6);
		coin1->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(0.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin1->setZOrder(9);

		auto coin2 = CCSprite::createWithSpriteFrameName("secretCoinUI2_001.png");
		coin2->setScale(0.6);
		coin2->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(1.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin2->setZOrder(9);

		auto coin3 = CCSprite::createWithSpriteFrameName("secretCoinUI2_001.png");
		coin3->setScale(0.6);
		coin3->setPosition({winSize.width/2 + coin1Slot->getContentSize().width*(2.5f - level->m_coins/2.f), winSize.height/11.5f});
		coin3->setZOrder(9);

		// self explanatory
		if (level->m_coins >= 1) this->addChild(coin1Slot);
		if (level->m_coins >= 2) this->addChild(coin2Slot);
		if (level->m_coins >= 3) this->addChild(coin3Slot);

		if (areCoinsVerified) {
			if (verifiedCoins->objectForKey(levelID + "_1" + weeklySuffix)) this->addChild(coin1);
			if (verifiedCoins->objectForKey(levelID + "_2" + weeklySuffix)) this->addChild(coin2);
			if (verifiedCoins->objectForKey(levelID + "_3" + weeklySuffix)) this->addChild(coin3);
		} else if (levelIDInt == 0) {
			if (level->m_firstCoinVerified.value()) this->addChild(coin1);
			if (level->m_secondCoinVerified.value()) this->addChild(coin2);
			if (level->m_thirdCoinVerified.value()) this->addChild(coin3);
		} else {
			if (pendingCoins->objectForKey(levelID + "_1" + weeklySuffix)) this->addChild(coin1);
			if (pendingCoins->objectForKey(levelID + "_2" + weeklySuffix)) this->addChild(coin2);
			if (pendingCoins->objectForKey(levelID + "_3" + weeklySuffix)) this->addChild(coin3);

			coin1Slot->setColor({255, 175, 75});
			coin2Slot->setColor({255, 175, 75});
			coin3Slot->setColor({255, 175, 75});
			coin1->setColor({255, 175, 75});
			coin2->setColor({255, 175, 75});
			coin3->setColor({255, 175, 75});
		}
	}
};