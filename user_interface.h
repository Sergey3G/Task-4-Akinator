#ifndef UI_H
#define UI_H

#define WIN_W 800
#define WIN_H 600
#define BTN_W 160
#define BTN_H 64

int ui_init(void);
void ui_shutdown(void);
int ui_ask_yes_no(const char* question);
int ui_input_text(const char* prompt, char* buffer, int max_len);

#endif
