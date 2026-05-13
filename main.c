#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>

PSP_MODULE_INFO("MinecraftPE", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

// Mobil tarzdaki o geniş görüş açısını ayarlıyoruz (FOV)
float fov = 75.0f; 

void setupGu() {
    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, (void*)0, 512);
    sceGuDispBuffer(480, 272, (void*)0x88000, 512);
    sceGuClearColor(0xFFD8A05E); // Mobil Minecraft gökyüzü rengi (Açık Mavi)
    sceGuFinish();
    sceGuDisplay(GU_TRUE);
}

int main() {
    setupGu();
    SceCtrlData pad;

    while(1) {
        sceCtrlReadBufferPositive(&pad, 1);
        
        sceGuStart(GU_DIRECT, list);
        sceGuClear(GU_COLOR_BUFFER_BIT);
        
        // Buraya blok çizim kodları gelecek
        
        sceGuFinish();
        sceGuSync(0,0);
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
        
        if(pad.Buttons & PSP_CTRL_HOME) break;
    }

    sceKernelExitGame();
    return 0;
}

