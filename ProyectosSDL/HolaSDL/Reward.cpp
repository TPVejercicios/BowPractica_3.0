#include "Reward.h"
#include "GameState.h"
#include "Texture.h"
#include "PlayState.h"

Reward::Reward(Point2D _pos, Vector2D _dir, int _h, int _w, Texture* _bubleTex, GameState* _owner, int _id, int _speed, Texture* reward_tex)
	:SDLGameObject(_pos, _dir, _h, _w, _bubleTex, _owner, _id, _speed)
{
	bubleTex = _bubleTex;
	rewardsTex = reward_tex;
	collisionable = false;
	startTicks = SDL_GetTicks();
}

Reward::~Reward() {
	bubleTex = nullptr;
	rewardsTex = nullptr;
}

void Reward::handleEvent(const SDL_Event event) {
	if (currState == OUTSIDE && event.type == SDL_MOUSEBUTTONDOWN /*&& event.button.button == SDL_BUTTON_LEFT*/) {
		SDL_Point p = { event.button.x, event.button.y };
		SDL_Rect* r = new SDL_Rect();
		if (currState == INSIDE) {
			r->x = this->pos.getX();
			r->y = this->pos.getY();
			r->h = BUBBLE_Y_SIZE;
			r->w = BUBBLE_X_SIZE;
		}
		else if (currState == OUTSIDE) {
			r->x = REWARD_GAP_X + this->pos.getX();
			r->y = REWARD_GAP_Y + this->pos.getY();
			r->h = this->height;
			r->w = this->width;
		}
		if (SDL_PointInRect(&p, r) == SDL_TRUE) {
			if (currState == INSIDE) currState = OUTSIDE;
			else if (currState == OUTSIDE) {
				action();
				currState = PICKED;
			}
		}
		delete r;
		r = nullptr;
	}
}

void Reward::update() {
	pos.setY(pos.getY() + dir.getY() * MAX_SPEED_REW);
	currCol++;
	currRateFrame = SDL_GetTicks() - startTicks;
	if (currRateFrame >= timeToExploit) collisionable = true;
	if (currCol >= MAX_COLS) currCol = 0;
	if (pos.getY() > MAX_Y_POS || currState == PICKED) {
		dynamic_cast<GameState*>(ownerState)->killObject(this);
	}
}

void Reward::render() {
	rewardsTex->renderFrame(SDL_Rect({ (int)pos.getX() + REWARD_GAP_X,(int)pos.getY() + REWARD_GAP_Y,(int)width,(int)height }), currRow, currCol, 0, SDL_FLIP_NONE);
	if (currState == INSIDE) {
		bubleTex->render(SDL_Rect({ (int)pos.getX(),(int)pos.getY(),BUBBLE_Y_SIZE,BUBBLE_X_SIZE }), SDL_FLIP_NONE);
	}
}

void Reward::setState(int state) {
	switch (state) {
	case INSIDE:
		currState = INSIDE;
		break;
	case OUTSIDE:
		currState = OUTSIDE;
		break;
	case PICKED:
		currState = PICKED;
		break;
	default:
		break;
	}
}

void AddArrows::action() {
	static_cast<PlayState*>(ownerState)->addArrows(ARROWS_TO_ADD);
};

void RemoveArrows::action() {
	static_cast<PlayState*>(ownerState)->addArrows(ARROWS_TO_REMOVE);
};

void ReviveButterflies::action() {
	static_cast<PlayState*>(ownerState)->addButterflies(BUTTERFLIES_TO_ADD);
};

void BigBallons::action() {
	static_cast<PlayState*>(ownerState)->setBallonScale(BALLON_BIG_SCALE);
};