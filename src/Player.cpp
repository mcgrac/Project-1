#include "Player.hpp"
#include <cstdio>
#include<vector>


using namespace std;

Player::Player(float x, float y, float width, float height, int id, int state, float speedX, float speedY, float movementSpeed_, int direction_, int hasPowerUp_, GameCamera* cam_)
    : Entity(x, y, width, height, id, state),
    speed{ speedX, speedY },
    movementSpeed(movementSpeed_),
    isJumping(false),
    colliding(false),
    immunity(false),
    isWalking(false),
    time(0),
    frameCounter(0),
    currentFrame(0),
    timer(0),
    frameSpeed(0.1f),
    direction(direction_),
    hasPowerUp(hasPowerUp_),
    score(0.0f),
    camera(cam_),
    alive(true),
    flagAnimation(false)

{

#pragma region TEXTURES
#pragma region LITTLE MARIO

    walkRight[0] = LoadTexture("resources/textures/mario1.png");
    walkRight[1] = LoadTexture("resources/textures/mario2.png");
    walkRight[2] = LoadTexture("resources/textures/mario3.png");
    walkRight[3] = LoadTexture("resources/textures/mario4.png");

    walkLeft[0] = LoadTexture("resources/textures/Lmario1.png");
    walkLeft[1] = LoadTexture("resources/textures/Lmario2.png");
    walkLeft[2] = LoadTexture("resources/textures/Lmario3.png");
    walkLeft[3] = LoadTexture("resources/textures/Lmario4.png");


    jumplMarioL = LoadTexture("resources/textures/Lmario5.png");
    jumplMarioR = LoadTexture("resources/textures/mario5.png");

    deadMario = LoadTexture("resources/textures/deadMario.png");
#pragma endregion

#pragma region BIG MARIO

    walkRightBig[0] = LoadTexture("resources/textures/bmario1.png");
    walkRightBig[1] = LoadTexture("resources/textures/bmario2.png");
    walkRightBig[2] = LoadTexture("resources/textures/bmario3.png");
    walkRightBig[3] = LoadTexture("resources/textures/bmario4.png");

    walkLeftBig[0] = LoadTexture("resources/textures/Lbmario1.png");
    walkLeftBig[1] = LoadTexture("resources/textures/Lbmario2.png");
    walkLeftBig[2] = LoadTexture("resources/textures/Lbmario3.png");
    walkLeftBig[3] = LoadTexture("resources/textures/Lbmario4.png");

    jumpbMarioL = LoadTexture("resources/textures/bMarioJumpL.png");
    jumpbMarioR = LoadTexture("resources/textures/bMarioJumpR.png");
#pragma endregion

#pragma region STAR MARIO

    walkRightStar[0] = LoadTexture("resources/textures/starMario1.png");
    walkRightStar[1] = LoadTexture("resources/textures/starMario2.png");
    walkRightStar[2] = LoadTexture("resources/textures/starMario3.png");
    walkRightStar[3] = LoadTexture("resources/textures/starMario4.png");

    walkLeftStar[0] = LoadTexture("resources/textures/LstarMario1.png");
    walkLeftStar[1] = LoadTexture("resources/textures/LstarMario2.png");
    walkLeftStar[2] = LoadTexture("resources/textures/LstarMario3.png");
    walkLeftStar[3] = LoadTexture("resources/textures/LstarMario4.png");

    jumpStarLeft = LoadTexture("resources/textures/LstarMarioJump.png");
    jumpStarRight = LoadTexture("resources/textures/starMarioJump.png");

#pragma endregion

#pragma region MARIO FIRE
    walkRightFire[0] = LoadTexture("resources/textures/fmario1.png");
    walkRightFire[1] = LoadTexture("resources/textures/fmario2.png");
    walkRightFire[2] = LoadTexture("resources/textures/fmario3.png");
    walkRightFire[3] = LoadTexture("resources/textures/fmario4.png");

    walkLeftFire[0] = LoadTexture("resources/textures/Lfmario1.png");
    walkLeftFire[1] = LoadTexture("resources/textures/Lfmario2.png");
    walkLeftFire[2] = LoadTexture("resources/textures/Lfmario3.png");
    walkLeftFire[3] = LoadTexture("resources/textures/Lfmario4.png");

    jumpFireLeft = LoadTexture("resources/textures/fMarioJumpL.png");
    jumpFireRight = LoadTexture("resources/textures/fMarioJumpR.png");
#pragma endregion

#pragma region MARIO FLAG

    //star mario
    starMarioFlag[0] = LoadTexture("resources/textures/bsmario_flag1.png");
    starMarioFlag[1] = LoadTexture("resources/textures/bsmario_flag2.png");

    //fire
    fireMarioFlag[0] = LoadTexture("resources/textures/fmario_flag1.png");
    fireMarioFlag[1] = LoadTexture("resources/textures/fmario_flag2.png");

    //big
    bMarioFlag[0] = LoadTexture("resources/textures/bmario_flag1.png");
    bMarioFlag[1] = LoadTexture("resources/textures/bmario_flag2.png");

    //small
    sMarioFlag[0] = LoadTexture("resources/textures/Lmario_flag1.png");
    sMarioFlag[1] = LoadTexture("resources/textures/Lmario_flag2.png");

#pragma endregion

#pragma endregion

#pragma region SOUNDS
    //sounds
    jumpSmallS = LoadSound("resources/audio/JumpSmall.wav"); //
    SetSoundVolume(jumpSmallS, 0.4f);
    marioDieS = LoadSound("resources/audio/MarioDie.wav");
    lostLife = LoadSound("resources/audio/LostLife.wav");
    jumpGoombaS = LoadSound("resources/audio/smb_stomp.wav"); //
    hitBlock = LoadSound("resources/audio/smb_bump.wav"); //

    getPowerUp = LoadSound("resources/audio/smb_vine.wav"); //
    getCoin = LoadSound("resources/audio/smb_coin.wav");//
#pragma endregion

    updateRects();
}

Player::~Player() { //destructor -> unload everithing from memory

#pragma region TEXTURES

#pragma region SMALL MARIO
    UnloadTexture(walkRight[0]);
    UnloadTexture(walkRight[1]);
    UnloadTexture(walkRight[2]);
    UnloadTexture(walkRight[3]);

    UnloadTexture(walkLeft[0]);
    UnloadTexture(walkLeft[1]);
    UnloadTexture(walkLeft[2]);
    UnloadTexture(walkLeft[3]);

    UnloadTexture(jumplMarioL);
    UnloadTexture(jumplMarioR);
#pragma endregion
#pragma region BIG MARIO
    UnloadTexture(walkRightBig[0]);
    UnloadTexture(walkRightBig[1]);
    UnloadTexture(walkRightBig[2]);
    UnloadTexture(walkRightBig[3]);

    UnloadTexture(walkLeftBig[0]);
    UnloadTexture(walkLeftBig[1]);
    UnloadTexture(walkLeftBig[2]);
    UnloadTexture(walkLeftBig[3]);

    UnloadTexture(jumpbMarioL);
    UnloadTexture(jumpbMarioR);
#pragma endregion

#pragma region STAR
    UnloadTexture(walkRightStar[0]);
    UnloadTexture(walkRightStar[1]);
    UnloadTexture(walkRightStar[2]);
    UnloadTexture(walkRightStar[3]);

    UnloadTexture(walkLeftStar[0]);
    UnloadTexture(walkLeftStar[1]);
    UnloadTexture(walkLeftStar[2]);
    UnloadTexture(walkLeftStar[3]);

    UnloadTexture(jumpStarLeft);
    UnloadTexture(jumpStarRight);
#pragma endregion

#pragma region FIRE MARIO
    UnloadTexture(walkRightFire[0]);
    UnloadTexture(walkRightFire[1]);
    UnloadTexture(walkRightFire[2]);
    UnloadTexture(walkRightFire[3]);

    UnloadTexture(walkLeftFire[0]);
    UnloadTexture(walkLeftFire[1]);
    UnloadTexture(walkLeftFire[2]);
    UnloadTexture(walkLeftFire[3]);

    UnloadTexture(jumpFireLeft);
    UnloadTexture(jumpFireRight);
#pragma endregion

#pragma region FLAG
    UnloadTexture(starMarioFlag[0]);
    UnloadTexture(starMarioFlag[1]);

    UnloadTexture(fireMarioFlag[0]);
    UnloadTexture(fireMarioFlag[1]);

    UnloadTexture(bMarioFlag[0]);
    UnloadTexture(bMarioFlag[1]);

    UnloadTexture(sMarioFlag[0]);
    UnloadTexture(sMarioFlag[1]);
#pragma endregion

#pragma endregion

#pragma region SOUNDS
    UnloadSound(jumpSmallS);
    UnloadSound(hitBlock);
    UnloadSound(marioDieS);
    UnloadSound(lostLife);
    UnloadSound(jumpGoombaS);
    UnloadSound(getPowerUp);
    UnloadSound(getCoin);
#pragma endregion
}

void Player::modifyHitbox() { //this is used for mofifyng the hitbox when mario goes from big to little

    switch (state) {

    case 1: //little mario

        hitbox.width = walkLeft[0].width;
        hitbox.height = walkLeft[0].height;
        break;

    case 2: //big mario

        hitbox.width = walkLeftBig[0].width;
        hitbox.height = walkLeftBig[0].height;
        break;

    case 3: //power mario

        hitbox.width = walkLeftBig[0].width;
        hitbox.height = walkLeftBig[0].height;
        break;

    default:
        break;
    }

    //printf("MarioState after modifyng= %d\n", state);
}

void Player::isWalkingTrue() { //called while the key arrows are pressed
    isWalking = true;
}
void Player::isWalkingFalse() { //called when the move keys are unpressed
    isWalking = false;
}

bool Player::shouldDrawMario(bool immunity) {
    if (!immunity) return true; //if immunity is false it will return true -> it should draw mario
    return ((int)(GetTime() * 10) % 2) == 0;//return true and false continiouslt for making the blinking effect
}

float Player::getTime() { //get the time in game
    return time;
}

bool Player::shouldUseStarSprite() {
    return ((int)(GetTime() * 10) % 2) == 0;
}

void Player::draw() {

    if (isWalking) { //only run timer if mario is walking
        timer += GetFrameTime();
    }

    if (timer >= frameSpeed) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 4; // between 0 and 3
    }

    Vector2 position = { hitbox.x, hitbox.y }; //get the position of mario


    switch (state) {
    case 0: //dead
        DrawTexture(deadMario, position.x, position.y, WHITE);
        break;
    case 1: // small mario
        if (!isJumping && !flagAnimation) {
            if (direction == 1) { // right
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRight[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRight[0], position.x, position.y, WHITE);
                    }
                }
            }
            else { // left
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeft[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeft[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else if (isJumping && !flagAnimation) { // jumping
            if (direction == 1) {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioR, position.x, position.y, WHITE);
                }
            }
            else {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumplMarioL, position.x, position.y, WHITE);
                }
            }
        }
        else { //mario is going down the flag

            if (shouldUseStarSprite()) {
                DrawTexture(sMarioFlag[0], position.x, position.y, WHITE);
            }
            else {
                DrawTexture(sMarioFlag[1], position.x, position.y, WHITE);
            }
        }
        break;

    case 2: // Big mario
        if (!isJumping && !flagAnimation) {
            if (direction == 1) {
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRightBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkRightBig[0], position.x, position.y, WHITE);
                    }
                }
            }
            else {
                if (isWalking) {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeftBig[currentFrame], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (shouldDrawMario(immunity)) {
                        DrawTexture(walkLeftBig[0], position.x, position.y, WHITE);
                    }
                }
            }
        }
        else if (isJumping && !flagAnimation){ // jumping
            if (direction == 1) {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumpbMarioR, position.x, position.y, WHITE);
                }
            }
            else {
                if (shouldDrawMario(immunity)) {
                    DrawTexture(jumpbMarioL, position.x, position.y, WHITE);
                }
            }
        }
        else { //mario is going down the flag

            if (shouldUseStarSprite()) {
                DrawTexture(bMarioFlag[0], position.x, position.y, WHITE);
            }
            else {
                DrawTexture(bMarioFlag[1], position.x, position.y, WHITE);
            }
        }
        break;

    case 3: //powerUp
    {
        bool useStarSprite = shouldUseStarSprite();

        switch (hasPowerUp)
        {
        case 1: //drawFlower Mario

            if (!isJumping && !flagAnimation) {
                if (direction == 1) {
                    if (isWalking) {

                        DrawTexture(walkRightFire[currentFrame], position.x, position.y, WHITE);
                    }
                    else {

                        DrawTexture(walkRightFire[0], position.x, position.y, WHITE);
                    }
                }
                else {
                    if (isWalking) {

                        DrawTexture(walkLeftFire[currentFrame], position.x, position.y, WHITE);
                    }
                    else {
                        DrawTexture(walkLeftFire[0], position.x, position.y, WHITE);
                    }
                }
            }
            else if (isJumping && !flagAnimation) { // jumping
                if (direction == 1) {
                    DrawTexture(jumpFireRight, position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(jumpFireLeft, position.x, position.y, WHITE);
                }
            }
            else { //mario is going down the flag

                if (shouldUseStarSprite()) {
                    DrawTexture(fireMarioFlag[0], position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(fireMarioFlag[1], position.x, position.y, WHITE);
                }
            }

            break;

        case 2: //draw star mario
            starPowerUpTimer();

            if (!isJumping && !flagAnimation) {
                if (direction == 1) {
                    if (isWalking) {
                        if (useStarSprite) {
                            DrawTexture(walkRightStar[currentFrame], position.x, position.y, WHITE);
                        }
                        else {
                            DrawTexture(walkRightBig[currentFrame], position.x, position.y, WHITE);
                        }
                    }
                    else {
                        if (useStarSprite) {
                            DrawTexture(walkRightStar[0], position.x, position.y, WHITE);
                        }
                        else {
                            DrawTexture(walkRightBig[0], position.x, position.y, WHITE);
                        }
                    }
                }
                else {
                    if (isWalking) {
                        if (useStarSprite) {
                            DrawTexture(walkLeftStar[currentFrame], position.x, position.y, WHITE);
                        }
                        else {
                            DrawTexture(walkLeftBig[currentFrame], position.x, position.y, WHITE);
                        }
                    }
                    else {
                        if (useStarSprite) {
                            DrawTexture(walkLeftStar[0], position.x, position.y, WHITE);
                        }
                        else {
                            DrawTexture(walkLeftBig[0], position.x, position.y, WHITE);
                        }
                    }
                }
            }
            else if (isJumping && !flagAnimation) { // jumping
                if (direction == 1) {
                    if (useStarSprite) {
                        DrawTexture(jumpStarRight, position.x, position.y, WHITE);
                    }
                    else {
                        DrawTexture(jumplMarioR, position.x, position.y, WHITE);
                    }
                }
                else {
                    if (useStarSprite) {
                        DrawTexture(jumpStarLeft, position.x, position.y, WHITE);
                    }
                    else {
                        DrawTexture(jumplMarioL, position.x, position.y, WHITE);
                    }
                }
            }
            else { //mario is going down the flag

                if (shouldUseStarSprite()) {
                    DrawTexture(starMarioFlag[0], position.x, position.y, WHITE);
                }
                else {
                    DrawTexture(starMarioFlag[1], position.x, position.y, WHITE);
                }
            }
            break;

        default:
            break;
        }

        break;
    }

    default:
        break;
    }
}

void Player::update(vector<Entity*>& entity, float gravity) {

    if (hitbox.y >= 448.0f) { alive = false; }//if it has fallen in a hole

    float delta = GetFrameTime();

    if ((state == 1 ||state ==2 ||state == 3) && !flagAnimation) { //if mario alive
        applyGravity(gravity, delta);
        updateRects();
        if (IsKeyDown(KEY_RIGHT)) {

            if (direction == -1) {

                printf("chage direction to right");

                changeDirection();
            }

            if (direction == 1) { // if I am going right

                move(1, camera->getRawCamera().target.x, delta); //move to the right
            }
            isWalking = true;
        }
        if (IsKeyDown(KEY_LEFT)) {

            if (direction == 1) {

                printf("chage direction to left");

                changeDirection();
            }

            if (direction == -1) { // if I am going left

                move(-1, camera->getRawCamera().target.x, delta); //move to the left
            }
            isWalking = true;
        }
        if (IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT)) {
            printf("key released");

            isWalking = false;
        }
        colisionsPlayer(entity);
        if (immunity) {

            immunityVoid(delta);
        }
        if (IsKeyPressed(KEY_SPACE) && !isJumping) {

            printf("JUMPING\n");
            jump(390.0f);
        }
        if (state == 3 && hasPowerUp == 1 && IsKeyPressed(KEY_F)) {

            printf("FireballCasted\n");
            castFireball(entity);
        }
    }
    else if (state == 0 && !flagAnimation){
        die(gravity, delta);
    }
    else {
        win(delta);
    }

}

void Player::castFireball(vector<Entity*>& entity) {

    entity.push_back(new Fireball(hitbox.x + 16, hitbox.y, 16, 16, direction));
}
void Player::jump(float jumpForce) {
    if (!isJumping || !colliding) { //jump if it's not jumping or it has hitted a goomba(colliding will only be true when colliding blocks)
        speed.y = -jumpForce;
        isJumping = true; //avoids jumping continiously
    }

    if (!IsSoundPlaying(jumpSmallS) && !IsSoundPlaying(jumpGoombaS)) { // do the normal jump sound

        PlaySound(jumpSmallS);
    }

}

void Player::changeDirection() {

    if (direction == 1) { 
        
        direction = -1; 
    }
    else if (direction == -1) {

        direction = 1;
    }
}

void Player::applyGravity(float gravity, float delta) {

    //Apply gravity
    speed.y += gravity * delta;
    hitbox.y += speed.y * delta;
}
void Player::move(int direction, float cameraX, float delta) {

    float nextX = hitbox.x;

    if (direction == 1) {
        nextX += movementSpeed * delta;
    }
    else {
        nextX -= movementSpeed * delta;
    }

    float leftLimit = cameraX - 512.0f / 2.0f; // left side visible of the screen

    if (nextX >= leftLimit) {
        hitbox.x = nextX;
    }
    else {
        hitbox.x = leftLimit; // blocks mario from going ouside this limit
    }
}

void Player::immunityVoid(float delta) {
    if (immunity) {
        time += delta; //counts back from 3 to 0
        if (time >= 3) { //counts until three, which is the time of immunity
            immunity = false;
            time = 0;
        }
    }
}

void Player::colisionsPlayer(vector<Entity*>& e) {

    //we use an itarator here because we don't want to make acces to deleted memory
    //we traverse the vector of entities until the end of the list, not having in account the size, because it might change when deleting something

    for (auto it = e.begin(); it != e.end(); ) { 
        Entity* ent = *it;

        if (flag == nullptr && ent->getId() == 6) {
            flag = dynamic_cast<Flag*>(ent);
        }

        // Collision with blocks (id == 2)
        if (ent->getId() == 2 && CheckCollisionRecs(hitbox, ent->getHitbox())) {

            if (!ent) { //if the pointer is null
                ++it; //next iteration
                continue;
            }

            //for checking collisions we use the middle pints of each side and define a different behaviour for each one of them
            if (CheckCollisionPointRec(bottom, ent->getHitbox())) { //collision bottom (floor)
                speed.y = 0;
                hitbox.y = ent->getHitbox().y - hitbox.height;
                isJumping = false;
            }

            if (CheckCollisionPointRec(top, ent->getHitbox())) { //collision above (head)
                hitbox.y = ent->getHitbox().y + ent->getHitbox().height;
                speed.y = 1.0f;

                if (SurpriseBlock* surprise = dynamic_cast<SurpriseBlock*>(ent)) { //do a dynamyc cast to know if that pointer has a surpirseBlock element to acces to it

                    if (surprise->getState() == 1) { //only create the power up and interact with the block if it has not been hitted (state 1)

                        surprise->retPowerUp()->throwPower(); //throw the power of the corresponding powerUp (NOW)
                        printf("Star created: positionX: %f position Y:%f State: %d Id %d\n", surprise->retPowerUp()->getHitbox().x, surprise->retPowerUp()->getHitbox().y, surprise->retPowerUp()->getState(), surprise->retPowerUp()->getId());

                        surprise->decreaseState();
                    }

                }

                if (BreakBlock* breakBlock = dynamic_cast<BreakBlock*>(ent)) { //do a dynamic cast to make sure that's a break block

                    if (state != 1) { // if mario is not little
                        breakBlock->changeBreakBlock(); //start breking animation
                    }
                    else {
                        PlaySound(hitBlock);
                    }
                }
            }

            if (CheckCollisionPointRec(left, ent->getHitbox())) { //collision left side
                printf("collision left");
                hitbox.x = ent->getHitbox().x + ent->getHitbox().width;
            }

            if (CheckCollisionPointRec(right, ent->getHitbox())) { //collision right side
                printf("collision right");
                hitbox.x = ent->getHitbox().x - hitbox.width;
            }

            colliding = true;

            ++it; //next iteration
            continue; //use continuo for going outside and to the next iteration
        }
        else {

            colliding = false;
        }

        // Collisions with enemy (id == 1)
        //if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->getId() == 1) {

        //    Enemy* enemy = dynamic_cast<Enemy*>(ent);

        //    if (enemy->getTypeEnemy() == 'g' && CheckCollisionPointRec(bottom, ent->getHitbox())) {//if the enemy is a goomba and collision with feet

        //        if (!ent) {
        //            ++it; //next iteration
        //            continue; //use continuo for going outside and to the next iteration
        //        }

        //        printf("COLLISION GOOMBA CON LOS PIES\n");
        //        PlaySound(jumpGoombaS);

        //        ent->decreaseState();

        //        if (hasPowerUp != 2) {
        //            jump(350.0f);
        //        }

        //        addScore(200);

        //        hitbox.y -= 5.0f; //for avoiding continious collision
        //        continue; //use continuo for going outside and to the next iteration
        //    
        //    }
        //    else if (hasPowerUp == 2) {
        //        if (!ent) {
        //            ++it; //next iteration
        //            continue; //use continuo for going outside and to the next iteration
        //        }

        //        ent->markForDelation();
        //    }
        //    else {
        //        state--;
        //        if (state != 0) {
        //            modifyHitbox(); //modify its hitbox when its hitted
        //            immunity = true;
        //        }
        //        continue;
        //    }
        //}
        //else{
        //    colliding = false;
        //}

        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->getId() == 1 && ent->getState() == 1) {

            if (ent == nullptr) { //if the pointer is null, continue

                continue;
            }

            if (Piranha* piranha = dynamic_cast<Piranha*>(ent)) { //if colliding with piranha

                if (hasPowerUp != 2) { //if has not the star power up
                    state--; //decrese state mario
                    if (state != 0) {
                        PlaySound(lostLife);
                        modifyHitbox(); //modify its hitbox when its hitted
                        immunity = true;
                    }
                    else {
                        //PlaySound(marioDieS);
                    }
                }
                else { //if has the star power up

                    delete piranha;
                    it = e.erase(it);
                    
                }

                continue;
            }

            if (CheckCollisionPointRec(bottom, ent->getHitbox()) && ent->getState() == 1 || hasPowerUp == 2) { //collision with mario's feet or mario has a star powerUp

                if (!ent) {
                    ++it; //next iteration
                    continue; //use continuo for going outside and to the next iteration
                }

                PlaySound(jumpGoombaS);

                ent->decreaseState();

                if (hasPowerUp != 2) {
                    jump(350.0f);
                }

                hitbox.y -= 5.0f; //for avoiding continious collision
                continue; //use continuo for going outside and to the next iteration
            }
            else { //collision with the rest of the body

                state--;
                if (state != 0) {
                    PlaySound(lostLife);
                    modifyHitbox(); //modify its hitbox when its hitted
                    immunity = true;
                }
                else {
                    //PlaySound(marioDieS);
                }
            }
        }
        else {

            colliding = false;
        }

        // Collisions with powerUp (id == 3)
        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && !immunity && ent->getId() == 3) {

            BaseObject* base = dynamic_cast<BaseObject*>(ent);

            printf("getPowerUp\n");

            if (base->getTouched()) {
                switch (base->getTypePowerUp())
                {
                case 1: //mushroom

                    if (state == 1) {
                        hitbox.y -= 16; //elevate mario before its hitbox change
                    }
                    if (state == 1) { //change from small mario to big mario
                        state = 2; 
                        PlaySound(getPowerUp);
                    } 

                    ent->markForDelation();

                    break;

                case 2: //flower

                    if (state == 1) {
                        hitbox.y -= 16; //elevate mario before its hitbox change
                    }

                    if (hasPowerUp != 1) {
                        PlaySound(getPowerUp);
                    }

                    state = 3;
                    hasPowerUp = 1;

                    ent->markForDelation();
                    break;


                case 3: //star
                    if (state == 1) {
                        hitbox.y -= 16; //elevate mario before its hitbox change
                    }

                    PlaySound(getPowerUp);

                    state = 3;
                    hasPowerUp = 2; //has a star powerUp

                    ent->markForDelation();
                    break;

                case 4: //coin

                    printf("coin getter\n");
                    PlaySound(getCoin);
                    addScore(100);

                    ent->markForDelation();
                    break;
                default:
                    break;
                }
            }

            modifyHitbox(); //modify hitbox in case mario gets the power up when he is little


        }
        else {

            colliding = false;
        }

        if (CheckCollisionRecs(hitbox, ent->getHitbox()) && ent->getId() == 5) { //colliding with the pole
            flagAnimation = true;
        }
        ++it; //next iteration
    }
}

void Player::increaseState() {

    state++;
}

void Player::starPowerUpTimer() {

    if (hasPowerUp == 2) {
        time += GetFrameTime(); //counts back from 10 to 0
        if(time >= 10.0f){
            hasPowerUp = 0; //eliminate PowerUp
            state = 2; //change to normal big mario
            time = 0;
        }
    }
}

void Player::addScore(int scoreToAdd) { //uses for adding a certain score

    score += scoreToAdd;

}

void Player::die(float gravity, float delta) {

    printf("MARIO DEAD\n");

    time += GetFrameTime(); //use variable time for doing the animation

    if (time >= 0.0f && time <= 1.5f) { //move up for 3 seconds

        applyGravity(gravity, delta);

        if (time >= 0.0f && time <= 0.1f){
            jump(300.0f);
        }
    }
    else { //set alive to false for ending the level and the animation
        time = 0.0f;
        alive = false;
    }
}

void Player::win(float delta) {
    printf("Winning flag\n");

    flag->move(80, delta);
    //flagAnimation = true;
    hitbox.y += 80 * delta;


}
