/**
 * @file graphics.h
 *
 * @brief Header file for graphics-related functionality.
 *
 * This file contains declarations for functions and constants related to graphics
 * in the application. It includes definitions for screen dimensions, textures,
 * and other graphical elements.
 */

#ifndef GRAPHICS_HEADER
#define GRAPHICS_HEADER

#include "game.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_ttf.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief Default screen width.
 */
#define DEFAULT_SCREEN_WIDTH 1280

/**
 * @brief Default screen height.
 */
#define DEFAULT_SCREEN_HEIGHT 720

/**
 * @brief Width in fullscreen mode.
 */
#define FULLSCREEN_WIDTH 1920

/**
 * @brief Height in fullscreen mode.
 */
#define FULLSCREEN_HEIGHT 1080

/**
 * @brief Minimum width of blocks.
 */
#define MIN_BLOCKS_WIDTH 16

/**
 * @brief Minimum height of blocks.
 */
#define MIN_BLOCKS_HEIGHT 8

/**
 * @brief Width of the texture.
 */
#define TEXTURE_WIDTH 128

/**
 * @brief Height of the texture.
 */
#define TEXTURE_HEIGHT 128

/**
 * @brief Frames per second.
 */
#define FPS 60

/**
 * @brief Movement speed.
 */
#define SPEED 691.891

/**
 * @brief Character size of the targets.
 */
#define TARGETS_CHAR_SIZE 16

/**
 * @brief Function pointer type for the display function.
 *
 * This function pointer type is used to define a display function that takes
 * a pointer to a GameState structure as a parameter.
 */
typedef void (*DisplayFunction)(struct GameState *game);

/**
 * @brief Structure representing a text with texture and destination rectangle.
 */
typedef struct Text {
    SDL_Texture *texture; /**< Texture for the text. */
    SDL_Rect destination; /**< Destination rectangle for rendering the text. */
} Text;

/**
 * @brief Structure representing various texts used in the application.
 */
typedef struct Texts {
    Text victory; /**< Text for victory. */
    Text restart; /**< Text for restart. */
    Text targets; /**< Text for targets. */
    Text quit; /**< Text for quit. */
    Text name; /**< Text for name. */
    Text fullscreen; /**< Text for fullscreen. */
} Texts;

/**
 * @brief Structure representing an entity with sprite information and rendering properties.
 */
typedef struct Entity {
    int isMoving; /**< Flag indicating if the entity is moving. */
    enum Direction direction; /**< Direction of the entity's movement. */
    int frameClip; /**< Index of the current frame clip. */
    SDL_Rect sourceSprite; /**< Source rectangle for sprite clipping. */
    SDL_Rect destinationRender; /**< Destination rectangle for rendering the entity. */
    Location spriteUpClips[4]; /**< Sprite clips for upward movement. */
    Location spriteDownClips[4]; /**< Sprite clips for downward movement. */
    Location spriteRightClips[4]; /**< Sprite clips for rightward movement. */
    Location spriteLeftClips[4]; /**< Sprite clips for leftward movement. */
} Entity;

/**
 * @brief Structure representing the graphics context of the application.
 */
typedef struct GraphicsContext {
    SDL_Window *window; /**< SDL window for the application. */
    SDL_Renderer *renderer; /**< SDL renderer for rendering graphics. */
    SDL_Texture *gameTexture; /**< Texture for the game graphics. */
    TTF_Font *font; /**< TrueType font for text rendering. */
    int width; /**< Width of the graphics context. */
    int height; /**< Height of the graphics context. */
    Entity player; /**< Player entity in the game. */
    Entity box; /**< Box entity in the game. */
    Texts *texts; /**< Texts used in the application. */
} GraphicsContext;

/**
 * @brief External declaration of the global graphics context.
 *
 * This external declaration is used to access the global graphics context
 * from other parts of the application.
 */
extern GraphicsContext graphicsContext;

/**
 * @brief Displays an SDL error message and exits the program.
 *
 * @param section The section or context where the error occurred.
 * @param error The error message to display.
 */
void SDL_ErrorExit(const char *section, const char *error);

/**
 * @brief Initializes sprite-related resources.
 */
void initializeSprites();

/**
 * @brief Initializes the SDL library.
 */
void initializeSDL();

/**
 * @brief Destroys textures associated with texts.
 *
 * @param texts The Texts structure containing textures to destroy.
 */
void destroysTextsTextures(Texts *texts);

/**
 * @brief Finalizes and cleans up the SDL library.
 */
void finalizeSDL();

/**
 * @brief Loads an SDL texture from a file.
 *
 * @param renderer The SDL renderer to associate the texture with.
 * @param filePath The file path of the image.
 *
 * @return The loaded SDL texture.
 */
SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *filePath);

/**
 * @brief Creates a Text structure for rendering text at a specific position.
 *
 * @param text The text content.
 * @param x The x-coordinate of the text.
 *
 * @return The Text structure.
 */
Text makeText(const char *text, int x);

/**
 * @brief Creates a victory Text structure for rendering victory messages.
 *
 * @param text The victory text content.
 *
 * @return The Text structure.
 */
Text makeVictoryText(const char *text);

/**
 * @brief Updates the rendering of text elements based on the game state.
 *
 * @param game The current game state.
 */
void updateRenderTexts(struct GameState *game);

/**
 * @brief Initializes text-related resources.
 */
void initializeTexts();

/**
 * @brief Renders the map based on the current game state.
 *
 * @param game The current game state.
 */
void renderMap(struct GameState *game);

/**
 * @brief Renders entities (such as player and boxes) based on the current game state.
 *
 * @param game The current game state.
 */
void renderEntities(struct GameState *game);

/**
 * @brief Displays the game using SDL.
 *
 * @param game The current game state.
 */
void displaySDL(struct GameState *game);

/**
 * @brief Initializes the NCurses library.
 */
void initializeNCurses();


/**
 * @brief Displays the game in the console using NCurses.
 *
 * @param game The current game state.
 */
void displayConsole(struct GameState *game);


#endif
