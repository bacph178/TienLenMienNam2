//  Created by Black3rry on 11/3/16.
//  Copyright (c) 2015 Black3rry. All rights reserved.

#ifndef Vina_GameConfig_h
#define Vina_GameConfig_h

#define XXX 400

enum {
    kCardLayer1 = 1,
    kCardLayer2 = 1,
    kCardLayer3 = 3,
    kCardLayer4 = 4,
    kCardLayer5 = 5,
    kCardlayer6 = 6
};

enum {
    kGameIntro,
    kGamePlay,
    kGameOver
};

enum CardState {
    Idle,
    OnHand,
    Putted,
    Fold,
    Destroy
};

enum PlayerState{
    Idle_Player,
    Play,
    Pass,
    Win,
    Lose,
    Pre
};

enum CardType {
    Hearts = 0,
    Diamonds,
    Clubs,
    Spade,
    OTHER
};

#define PROMOTE_GAME_URL "market://search?q=pub:XXX"

#define GAME_STATUS_PLAYING 1
#define GAME_STATUS_PAUSE   2
#define GAME_STATUS_OVER    3

//define game notifications
#define NOTIFICATION_GRAVITY_SWITCH "gravity switch"
#define NOTIFICATION_LEVEL_COMPLETED "level completed"

//==========================================================

//== Login screen
#define BTN_LOGIN_FACEBOOK "btn_login_facebook.png"
#define BTN_LOGIN "btn_login.png"
#define BTN_REGISTER "btn_register.png"
#define BTN_PLAY_NOW "btn_play_now.png"
#define BKG_INPUT_LOGIN "bkg_input_login.png"

#define SPRITE_GIRL_LOGIN "girl_login.png"
#define BKG_LOGIN "bkg_login.jpg"

//== Register screen
#define BTN_REGISTER_REGISTER "btn_register_register.png"
#define BKG_INPUT_SDT "bkg_input_sdt.png"
#define BKG_INPUT_PASSWORD "bkg_input_password.png"
#define BKG_INPUT_REPASSWORD "bkg_input_repassword.png"
#define SPRITE_BIGKEN_ONLINE "txt_bigken_online.png"
#define SPRITE_GIRL_REGISTER "girl_register.png"
#define BKG_REGISTER "bkg_register.png"

//== List Game Screen
#define BTN_ITEM_GAME "btn_item_game.png"
#define BTN_BACK "btn_back.png"
#define BTN_MENU "btn_menu.png"
#define BTN_SETTING "btn_setting"
#define BTN_HELPER "btn_helper.png"
#define BTN_CENTS "btn_load_cents.png"
#define BTN_DOI_THUONG "btn_doi_thuong.png"
#define BKG_AVATAR "bkg_avatar.png"
#define SPRITE_COINS "image_coins.png"
#define SPRITE_KENS "image_kens.png"
#define SPRITE_LIST_GAME "girl_list_game.png"
#define BKF_LIST_GAME "bkg_list_game.jpg"

// TLMN
#define BTN_MESSAGE "btn_messange.png"
#define BTN_SOUND_ON "btn_sound_on.png"
#define BTN_SOUND_OFF "btn_sound_off.png"
#define BTN_PURCHASE "btn_purchase.png"
#define BTN_BUTTON "ic_button_primary.png"
#define BKG_CHAT_BOX "bkg_charbox.9.png"
#define BKG_TABLE "bkg_table.jpg"

#endif
