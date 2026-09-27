#include "game.h"

int main() {
    Game game;

	game.Init();

	// w terraria clone
	while (!WindowShouldClose()) {
		game.GeneralUpdate();

		BeginDrawing();

		ClearBackground(Color{ 25, 25, 25, 255 });

		if (game.game_state == TITLE) {

		}
		else if (game.game_state == STARTED) {
			game.StartedUpdate();

			game.StartedDraw();
		}
		else if (game.game_state == END) {

		}
		EndDrawing();
	}

	game.Shutdown();

	return 0;
}