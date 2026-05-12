#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>

PSP_MODULE_INFO("FatContrast", 0x1000, 1, 1);

int main_thread(SceSize args, void *argp) {
    SceCtrlData pad;
    while(1) {
        sceCtrlReadBufferPositive(&pad, 1);
        
        // Eğer L ve R'ye basılırsa
        if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER)) {
            sceDisplayWaitVblankStart(); 
        }
        
        sceKernelDelayThread(100000);
    }
    return 0;
}

int module_start(SceSize args, void *argp) {
    SceUID thid = sceKernelCreateThread("ContrastThread", main_thread, 0x18, 0x1000, 0, NULL);
    if(thid >= 0) sceKernelStartThread(thid, 0, NULL);
    return 0;
}

int module_stop() { return 0; }

