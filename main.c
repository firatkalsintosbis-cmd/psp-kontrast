#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdisplay_kernel.h> 

// Kernel yetkisi devrede
PSP_MODULE_INFO("ColorSpaceFat", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

int main_thread(SceSize args, void *argp) {
    SceCtrlData pad;
    
    while(1) {
        sceCtrlReadBufferPositive(&pad, 1);
        
        // L ve R tuşlarına aynı anda basıldığında...
        if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER)) {
            // Kernel kütüphanesinin resmi donanım komutu çalışır!
            sceDisplaySetBrightness(100, 0); 
        }
        
        sceKernelDelayThread(100000); // Sistemin kilitlenmemesi için döngü gecikmesi
    }
    return 0;
}

int module_start(SceSize args, void *argp) {
    SceUID thid = sceKernelCreateThread("ColorThread", main_thread, 0x18, 0x1000, 0, NULL);
    if(thid >= 0) sceKernelStartThread(thid, 0, NULL);
    return 0;
}

int module_stop() { return 0; }
