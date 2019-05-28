#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "CEvent.h"
#include "GameOfLife.h"

using namespace std;

class Game : public CEvent {
public:
	Game(int scnwidth, int scnheight);
	~Game();

	bool onInit();
	void onEvent(SDL_Event * event);
	void OnExit();
	void OnLButtonUp(int mx, int my);
	void OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode);
	void onLoop();
	void onRender();
	int onExecute();
	void onCleanup();

private:
	bool running, skipNextGen;
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Rect arenaViewport, menuViewport;
	int screenWidth = 800, screenHeight = 600, rectSize = 3, timeStep = 0;
	TTF_Font * font;
	GameOfLife GoL;
};

/*
 * CLASS IMPLEMENTATIONS
 */
Game::Game(int scnwidth, int scnheight) {
	this->running = true;
	this->skipNextGen = false;
	this->window = NULL;
	this->renderer = NULL;
	this->screenWidth = scnwidth;
	this->screenHeight = scnheight;
	// Set viewports initials
	this->arenaViewport.x = 0;
	this->arenaViewport.y = 0;
	this->arenaViewport.w = int(this->screenWidth * 0.75);
	this->arenaViewport.h = this->screenHeight;
	this->menuViewport.x = int(this->screenWidth * 0.75);
	this->menuViewport.y = 0;
	this->menuViewport.w = int(this->screenWidth * 0.25);
	this->menuViewport.h = this->screenHeight;
}

Game::~Game() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool Game::onInit() {
	SDL_Log("Initializing SDL systems...\n");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL initialization failed. SDL Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_Log("Creating window...\n");
	if ((this->window = SDL_CreateWindow("Life like cellular automata simulation", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL)) == NULL) {
		SDL_Log("Creating window failed. SDL Error: %s\n", SDL_GetError());
		return false;
	}
	SDL_Log("Creating renderer...\n");
	if ((this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED)) == NULL) {
		SDL_Log("Creating renderer failed. SDL Error: %s\n", SDL_GetError());
	}
	SDL_Log("Initializing TTF library...\n");
	if (TTF_Init() < 0) {
		SDL_Log("TTF initialization failed. TTF Error: %\n", TTF_GetError());
		return false;
	}
	SDL_Log("Loading font...\n");
	if ((this->font = TTF_OpenFont("digital-7.ttf", 11)) == NULL) {
		SDL_Log("Loading font failed. TTF Error: %s\n", TTF_GetError());
		return false;
	}
	Rules rles;
	rles.birth = { 3, 4 };
	rles.survive = { 2, 3, 4 };
	GoL.initGameOfLife(int(this->arenaViewport.w / this->rectSize), int(this->arenaViewport.h / this->rectSize), rles);
	GoL.fillMapRandomly();
	// set menuviewport
	SDL_SetRenderDrawColor(this->renderer, 180, 180, 180, 255);
	SDL_RenderFillRect(this->renderer, &this->menuViewport);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(this->renderer, &this->arenaViewport);
	SDL_RenderPresent(this->renderer);
	SDL_Log("Initialization completed!\n");
	return true;
}

void Game::onEvent(SDL_Event * event) {
	CEvent::OnEvent(event);
}

void Game::OnExit() {
	this->running = false;
}

void Game::OnLButtonUp(int mx, int my) {
	if (mx < this->arenaViewport.w) {
		if (this->GoL.getCellByRef(mx / this->rectSize, my / this->rectSize) == '1') this->GoL.getCellByRef(mx / this->rectSize, my / this->rectSize) = '0';
		else if (this->GoL.getCellByRef(mx / this->rectSize, my / this->rectSize) == '0') this->GoL.getCellByRef(mx / this->rectSize, my / this->rectSize) = '1';
	}
}

void Game::OnKeyDown(SDL_Keycode sym, Uint16 mod, Uint16 scancode) {
	if (sym == SDLK_p && this->skipNextGen) this->skipNextGen = false;
	else if (sym == SDLK_p && !this->skipNextGen) this->skipNextGen = true;
	if (sym == SDLK_c) this->GoL.clearMap();
}

void Game::onLoop() {
	if (!this->skipNextGen) GoL.nextGeneration();
}

void Game::onRender() {
	SDL_Rect rect;
	SDL_RenderSetViewport(this->renderer, &this->arenaViewport);
	rect.h = this->rectSize;
	rect.w = this->rectSize;
	for (int i = 0; i < this->arenaViewport.w / this->rectSize; i++) {
		for (int j = 0; j < this->arenaViewport.h / this->rectSize; j++) {
			rect.x = i * this->rectSize;
			rect.y = j * this->rectSize;
			if (GoL.getCellValue(i, j) == '1') SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
			if (GoL.getCellValue(i, j) == '0') SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(this->renderer, &rect);
		}
	}
	SDL_RenderPresent(this->renderer);
}

int Game::onExecute() {
	SDL_Event Event;
	while (this->running) {
		while (SDL_PollEvent(&Event)) {
			this->onEvent(&Event);
		}
		this->onLoop();
		this->onRender();
		SDL_Delay(this->timeStep);
	}
	this->onCleanup();
	return 0;
}

void Game::onCleanup() {
	TTF_CloseFont(this->font);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}