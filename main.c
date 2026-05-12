#include <pspkernel.h>
#include <pspctrl.h>
// Kernel modunda donanım komutlarını çekmek için özel driver kütüphaneleri kullanılır
#include <pspdisplay_kernel.h> 

// 0x1000 bayrağı en kritik kısımdır! PSP'ye "Ben sıradan bir eklenti değilim, Çekirdek (Kernel) yetkisi istiyorum" der.
PSP_MODULE_INFO("ColorSpaceFat", 0x1000, 1, 1);
PSP_MAIN_THREAD_ATTR(0);

// PSP'nin normalde gizli olan donanımsal parlaklık fonksiyonunu zorla çağırıyoruz
extern int sceDisplaySetBrightness(int level, int unk1);

int main_thread(SceSize args, void *argp) {
    SceCtrlData pad;
    
    while(1) {
        sceCtrlReadBufferPositive(&pad, 1);
        
        // L ve R tuşlarına aynı anda basıldığında...
        if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER)) {
            // Artık Kernel modunda olduğumuz için Sony bizi engelleyemez!
            // Donanımı sınırlarına (100) zorluyoruz.
            sceDisplaySetBrightness(100, 0); 
        }
        
        sceKernelDelayThread(100000); // Sistemin kilitlenmemesi için 100ms döngü gecikmesi
    }
    return 0;
}

int module_start(SceSize args, void *argp) {
    SceUID thid = sceKernelCreateThread("ColorThread", main_thread, 0x18, 0x1000, 0, NULL);
    if(thid >= 0) sceKernelStartThread(thid, 0, NULL);
    return 0;
}

int module_stop() { return 0; }
