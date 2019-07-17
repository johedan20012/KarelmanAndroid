#include "Level.h"

Level::Level(Player* player) {

	mTimer = Timer::Instance();

	mPlayer = player;
	mPlayerHit = false;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 64, { 255,255,255 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.5f));

    mScore = new Scoreboard({255,255,255});
    mScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH-200,50));
    mScore->Score(0);

    mMonsters = new Scoreboard({255,255,255});
    mMonsters->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH-800,50));
    mMonsters->Score(0);

    mStage = new Scoreboard({255,255,255});
    mStage->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH-1000,50));
    mStage->Score(1000);

	mGameOver = false;
	mGameOverDelay = 3.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

    mFondo = new Texture("fondo.png",Graphics::Instance()->SCREEN_WIDTH,Graphics::Instance()->SCREEN_HEIGHT);
    mFondo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH/2,Graphics::Instance()->SCREEN_HEIGHT/2));

    mCurrentState = running;

	Enemy::CurrentPlayer(mPlayer);

	int aux = rand() % 3;
    for(int i = 0; i < MAX_SPAWNS; i++){
        aux = rand() % 3;
        mSpawns[i] = new Spawner((Spawner::TYPE) aux);
    }

	mSpawns[0]->Pos(Vector2(50,50));
	mSpawns[1]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH - 50,50));
	mSpawns[2]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH - 50,Graphics::Instance()->SCREEN_HEIGHT - 50));
	mSpawns[3]->Pos(Vector2(50,Graphics::Instance()->SCREEN_HEIGHT - 50));

	mATopeDelay = (rand()%10);

	mATopeText = new AnimatedTexture("atope.png",0,0,200,100,4,0.5f,AnimatedTexture::vertical);
	mATopeText->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH-210,Graphics::Instance()->SCREEN_HEIGHT-70));
}

Level::~Level() {

	mTimer = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

    delete mFondo;
    mFondo = NULL;

    delete mScore;
    mScore = NULL;

    delete mStage;
    mStage = NULL;

    delete mMonsters;
    mMonsters = NULL;
	
	for (int i = 0; i < mEnemies.size(); i++) {

		delete mEnemies[i];
		mEnemies[i] = NULL;
	}

	for(int i = 0; i < MAX_SPAWNS; i++){
		delete mSpawns[i];
		mSpawns[i] = NULL;
	}

	delete mATopeText;
	mATopeText = NULL;
}

void Level::HandleCollisions() {

	if (!mPlayerHit ) {
		if (mPlayer->WasHit()) {
			mPlayerHit = true;
			mPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath() {

		//if (mPlayer->Lives() > 0) {

		//} else {

			//if (mGameOverTimer == 0.0f) {

			//}
            mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = gameover;
			}
		//}

}

void Level::HandleEnemySpawning() {
	for(int i  = 0; i < MAX_SPAWNS; i++){
		mSpawns[i]->Update(&mEnemies,mCurrentStage);
	}

	/*
	mSpawnTimer += mTimer->DeltaTime();
	if (mSpawnTimer >= mSpawnDelay) {
        if(rand()%3 == 0) {
            mEnemies.push_back(new Blenster());
        }else if(rand()%2){
            mEnemies.push_back(new Clumster());
        }else{
			mEnemies.push_back(new Monster());
		}
		mSpawnTimer = 0.0f;
	}*/
}

Level::LEVEL_STATES Level::State() {

	return mCurrentState;
}

void Level::Update() {
	mCurrentStage += (float)(mTimer->DeltaTime()/100);
	if(mCurrentStage > 50) mCurrentStage = 50; //Stage maximo de 100

	if(!mATopeActivado){
        mATopeTimer += mTimer->DeltaTime();
        if(mATopeTimer >= mATopeDelay){ //Aparece el boton atope
            mATopeActivado = true;
        }
	}
	if(mATopeActivado)  mATopeText->Update();


	if(mCurrentState == running) {
		HandleEnemySpawning();

		for (int i = 0; i < mEnemies.size(); i++) {

			mEnemies[i]->Update();

			if (mEnemies[i]->WasHit()) {
                if(mEnemies[i]->IsEspecial()) {
                    mPlayer->AddScore(mEnemies.size()*20);
                    for(int a=0; a<mEnemies.size(); a++){
                        delete mEnemies[a];
                        mEnemies[a] = NULL;
                    }
                    mEnemies.clear(); //Si el mounstro era especial mata a todos al morir
                }else {
                    mEnemies.erase(mEnemies.begin() + i);
                }
			}
		}

        mPlayer->Update();

		HandleCollisions();

		mScore->Score(mPlayer->Score());

		mMonsters->Score(mEnemies.size());

		mStage->Score(mCurrentStage*1000);

        if (mPlayerHit) {
            mCurrentState = terminated;
        }
	}
	if(mCurrentState == terminated){
        HandlePlayerDeath();
	}
}

void Level::Render() {
    mFondo->Render();

	for(int i  = 0; i < MAX_SPAWNS; i++){
		mSpawns[i]->Render();
	}

    for (int i = 0; i < mEnemies.size(); i++) {

        mEnemies[i]->Render();
    }

    if (mPlayerHit) {
        /*if (mGameOverTimer >= mGameOverLabelOnScreen) {

            mGameOverLabel->Render();
        }*/
    }

    mPlayer->Render();

    mScore->Render();

    mMonsters->Render();

    mStage->Render();

    if(mATopeActivado) mATopeText->Render();

    if(mCurrentState == terminated){
        mGameOverLabel->Render();
    }
}