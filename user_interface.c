#include <stdio.h>
#include <string.h>
#include <CSFML/Graphics.h>

#include "user_interface.h"
#include "trees.h"

static sfRenderWindow* window = NULL;
static sfFont* font = NULL;
static sfRectangleShape* yes_rect = NULL;
static sfText* yes_text = NULL;
static sfRectangleShape* no_rect = NULL;
static sfText* no_text = NULL;
static sfRectangleShape* input_rect = NULL;
static sfText* input_prompt = NULL;
static sfText* input_text = NULL;

static void create_buttons_and_input(void)
{
    yes_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(yes_rect, (sfVector2f){BTN_W, BTN_H});
    sfRectangleShape_setPosition(yes_rect, (sfVector2f){120, 420});
    sfRectangleShape_setFillColor(yes_rect, sfColor_fromRGB(80, 180, 80));

    yes_text = sfText_create(font);
    sfText_setCharacterSize(yes_text, 28);
    sfText_setString(yes_text, "YES");
    sfText_setPosition(yes_text, (sfVector2f){120 + 50, 430});

    no_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(no_rect, (sfVector2f){BTN_W, BTN_H});
    sfRectangleShape_setPosition(no_rect, (sfVector2f){520, 420});
    sfRectangleShape_setFillColor(no_rect, sfColor_fromRGB(200, 80, 80));

    no_text = sfText_create(font);
    sfText_setCharacterSize(no_text, 28);
    sfText_setString(no_text, "NO");
    sfText_setPosition(no_text, (sfVector2f){520 + 50, 430});

    input_rect = sfRectangleShape_create();
    sfRectangleShape_setSize(input_rect, (sfVector2f){650, 40});
    sfRectangleShape_setPosition(input_rect, (sfVector2f){20, 520});
    sfRectangleShape_setFillColor(input_rect, sfColor_fromRGB(40, 40, 40));
    sfRectangleShape_setOutlineColor(input_rect, sfColor_fromRGB(180, 180, 180));
    sfRectangleShape_setOutlineThickness(input_rect, 2.f);

    input_prompt = sfText_create(font);
    sfText_setCharacterSize(input_prompt, 20);
    sfText_setPosition(input_prompt, (sfVector2f){26, 526});

    input_text = sfText_create(font);
    sfText_setCharacterSize(input_text, 20);
    sfText_setPosition(input_text, (sfVector2f){300, 526});
}

int ui_init(void)
{
    sfVideoMode mode;
    mode.size.x = WIN_W;
    mode.size.y = WIN_H;
    mode.bitsPerPixel = 32;

    sfContextSettings settings;
    settings.depthBits         = 0;
    settings.stencilBits       = 0;
    settings.antiAliasingLevel = 0;
    settings.majorVersion      = 2;
    settings.minorVersion      = 0;
    settings.attributeFlags    = sfContextDefault;

    window = sfRenderWindow_create(mode,
                                   "Akinator SFML",
                                   sfDefaultStyle,
                                   sfWindowed,
                                   &settings);
    if (!window)
    {
        fprintf(stderr, "UI: cannot create window!\n");
        return 0;
    }

    font = sfFont_createFromFile("/usr/local/share/fonts/moscowsansregular.ttf");
    if (!font)
    {
        printf("Trying to load font from directory...\n");
        font = sfFont_createFromFile("moscowsansregular.ttf");
        if (!font)
            fprintf(stderr, "UI: cannot load font moscowsansregular.ttf\n");
    }

    create_buttons_and_input();
    return 1;
}

void ui_shutdown(void)
{
    if (yes_rect) sfRectangleShape_destroy(yes_rect);
    if (yes_text) sfText_destroy(yes_text);
    if (no_rect) sfRectangleShape_destroy(no_rect);
    if (no_text) sfText_destroy(no_text);
    if (input_rect) sfRectangleShape_destroy(input_rect);
    if (input_prompt) sfText_destroy(input_prompt);
    if (input_text) sfText_destroy(input_text);
    if (font) sfFont_destroy(font);
    if (window) sfRenderWindow_destroy(window);
}

static int point_in_rectshape(sfRectangleShape* rect, int mouse_x, int mouse_y)
{
    if (!rect) return 0;
    sfVector2f pos = sfRectangleShape_getPosition(rect);
    sfVector2f size = sfRectangleShape_getSize(rect);
    return mouse_x >= (int)pos.x && mouse_x <= (int)(pos.x + size.x)
        && mouse_y >= (int)pos.y && mouse_y <= (int)(pos.y + size.y);
}

static void draw_question(const char* question)
{
    if (!window) return;
    sfText* q = sfText_create(font);
    sfText_setCharacterSize(q, 24);
    sfText_setString(q, question ? question : "");
    sfText_setPosition(q, (sfVector2f){20, 40});
    sfRenderWindow_drawText(window, q, NULL);
    sfText_destroy(q);
}

int ui_ask_yes_no(const char* question)
{
    if (!window)
    {
        fprintf(stderr, "UI: ui_ask_yes_no called before ui_init\n");
        return 0;
    }

    int answer = -1;
    while (sfRenderWindow_isOpen(window) && answer == -1)
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
                return 0;
            }

            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft)
            {
                int mouse_x = event.mouseButton.position.x;
                int mouse_y = event.mouseButton.position.y;
                if (point_in_rectshape(yes_rect, mouse_x, mouse_y))
                    answer = 1;
                else if (point_in_rectshape(no_rect, mouse_x, mouse_y))
                    answer = 0;
            }

            if (event.type == sfEvtKeyPressed)
            {
                if (event.key.code == sfKeyY) answer = 1;
                if (event.key.code == sfKeyN) answer = 0;
            }
        }

        sfRenderWindow_clear(window, sfColor_fromRGB(18, 18, 18));

        draw_question(question);

        if (yes_rect) sfRenderWindow_drawRectangleShape(window, yes_rect, NULL);
        if (yes_text) sfRenderWindow_drawText(window, yes_text, NULL);

        if (no_rect) sfRenderWindow_drawRectangleShape(window, no_rect, NULL);
        if (no_text) sfRenderWindow_drawText(window, no_text, NULL);

        if (input_rect) sfRenderWindow_drawRectangleShape(window, input_rect, NULL);
        if (input_prompt) sfRenderWindow_drawText(window, input_prompt, NULL);
        if (input_text) sfRenderWindow_drawText(window, input_text, NULL);

        sfRenderWindow_display(window);
    }

    return (answer == 1) ? 1 : 0;
}

int ui_input_text(const char* prompt, char* buffer, int max_len)
{
    if (!buffer || max_len <= 0) return 0;
    if (!window)
    {
        fprintf(stderr, "UI: ui_input_text called before ui_init\n");
        return 0;
    }

    buffer[0] = '\0';
    int pos = 0;
    int submitted = 0;

    while (sfRenderWindow_isOpen(window) && !submitted)
    {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
                return 0;
            }

            if (event.type == sfEvtTextEntered)
            {
                uint32_t unicode = event.text.unicode;
                if (unicode == '\r' || unicode == '\n')
                {
                    submitted = 1;
                    break;
                }

                if (unicode == 8)
                {
                    if (pos > 0) { pos--; buffer[pos] = '\0'; }
                }
                else if (unicode >= 32 && unicode < 127)
                {
                    if (pos < max_len - 1)
                    {
                        buffer[pos++] = (char)unicode;
                        buffer[pos] = '\0';
                    }
                }
            }

            if (event.type == sfEvtMouseButtonPressed && event.mouseButton.button == sfMouseLeft)
            {
                int mouse_x = event.mouseButton.position.x;
                int mouse_y = event.mouseButton.position.y;
                if (point_in_rectshape(yes_rect, mouse_x, mouse_y))
                {
                    strncpy(buffer, "YES", (size_t)(max_len - 1));
                    buffer[max_len - 1] = '\0';
                    submitted = 1;
                }
                else if (point_in_rectshape(no_rect, mouse_x, mouse_y))
                {
                    strncpy(buffer, "NO", (size_t)(max_len - 1));
                    buffer[max_len - 1] = '\0';
                    submitted = 1;
                }
            }
        }

        if (input_text)
            sfText_setString(input_text, buffer);

        sfRenderWindow_clear(window, sfColor_fromRGB(18, 18, 18));

        sfText* title = sfText_create(font);
        sfText_setCharacterSize(title, 20);
        sfText_setString(title, prompt);
        sfText_setPosition(title, (sfVector2f){20, 10});
        sfRenderWindow_drawText(window, title, NULL);
        sfText_destroy(title);

        if (yes_rect) sfRenderWindow_drawRectangleShape(window, yes_rect, NULL);
        if (yes_text) sfRenderWindow_drawText(window, yes_text, NULL);
        if (no_rect) sfRenderWindow_drawRectangleShape(window, no_rect, NULL);
        if (no_text) sfRenderWindow_drawText(window, no_text, NULL);

        if (input_rect) sfRenderWindow_drawRectangleShape(window, input_rect, NULL);
        if (input_prompt) sfRenderWindow_drawText(window, input_prompt, NULL);
        if (input_text) sfRenderWindow_drawText(window, input_text, NULL);

        sfRenderWindow_display(window);
    }

    return submitted;
}

