#include "rtthread.h"
#include "app.h"

extern void ate_app_init(void);
extern void rt_hw_wdg_start(int argc, char **argv);

#if defined(PKG_USING_PLAYER)
    #include "player.h"
    extern int player_system_init(void);
    extern int player_codec_helixmp3_register(void);
    extern int player_codec_beken_aac_register(void);
    extern int player_codec_beken_m4a_register(void);
    extern int player_codec_opencore_amr_register(void);
#endif

int main(int argc, char **argv) {
    ate_app_init();
    app_start();

#if defined(PKG_USING_PLAYER)
    player_codec_helixmp3_register(); 
    player_codec_beken_aac_register(); 
    player_codec_beken_m4a_register(); 
    player_codec_opencore_amr_register(); 
    player_system_init();
#endif

	rt_hw_wdg_start(0,NULL);

    return 0;
}
