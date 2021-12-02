#ifndef LCD_H
#define LCD_H

#include "Arduino.h"


class LCD 
{
    public:
        LCD(int col, int row);
        void lcd_init(void);
        void start_screen(void);  //start screen is on while in idle state before coin detection
        void mode_select_screen(int curr_adc_mode);
        void distance_set_screen(int curr_adc_mode, bool distance_status);
        void game_play_screen(int time_left, int curr_score);
        void end_game_screen(int curr_score);
        void post_game_screen(int curr_score, int curr_adc_mode);
        void clear_screen(void);
        
    private:
        
        int disp_col;
        int disp_row;
        int mode_high_scores[2];
        int mode_last_scores[2];
//        int mode_high_scores[3];
//        int mode_last_scores[3];
};

#endif
