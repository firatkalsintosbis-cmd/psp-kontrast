#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspctrl.h>

PSP_MODULE_INFO("MinecraftPE", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

// Grafik listesi için bellek ayırıyoruz
static unsigned int __attribute__((aligned(16))) list[262144];

// Mobil tarzı Hotbar çizimi (Kareleri ekrana basar)
void drawHotbar(int selected) {
    int i;
    for(i = 0; i < 9; i++) {
        int x = 150 + (i * 21); // Hotbar'ı ortalıyoruz
        int y = 240;
        
        unsigned int color = (i == selected) ? 0xFFFFFFFF : 0xFF888888; 
        
        // PSP'nin grafik işlemcisine bir dikdörtgen çiz komutu veriyoruz
        sceGuColor(color);
        // Basit bir kutu çizimi (Gerçek texture gelene kadar yer tutucu)
        struct { float x, y, z; }* vertices = sceGuGetMemory(2 * sizeof(*vertices));
        vertices[0].x = x;     vertices[0].y = y;     vertices[0].z = 0;
        vertices[1].x = x+20;  vertices[1].y = y+20;  vertices[1].z = 0;
        sceGuDrawArray(GU_SPRITES, GU_VERTEX_32BITF|GU_TRANSFORM_2D, 2, 0, vertices);
    }
}

int main() {
    sceGuInit();
    sceGuStart(GU_DIRECT, list);
    sceGuDrawBuffer(GU_PSM_8888, (void*)0, 512);
    sceGuDispBuffer(480, 272, (void*)0x88000, 512);
    sceGuClearColor(0xFFD8A05E); // PE Mavi Gökyüzü
    sceGuFinish();
    sceGuSync(0,0);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_TRUE);

    SceCtrlData pad;
    int selectedSlot = 0;

    while(1) {
        sceCtrlReadBufferPositive(&pad, 1);
        
        // L ve R ile slot değiştirme
        if(pad.Buttons & PSP_CTRL_RTRIGGER) {
            selectedSlot = (selectedSlot + 1) % 9;
            sceKernelDelayThread(200000); 
        }
        if(pad.Buttons & PSP_CTRL_LTRIGGER) {
            selectedSlot = (selectedSlot - 1 + 9) % 9;
            sceKernelDelayThread(200000);
        }

        sceGuStart(GU_DIRECT, list);
        sceGuClear(GU_COLOR_BUFFER_BIT);

        drawHotbar(selectedSlot); // Hotbar'ı her karede çiz

        sceGuFinish();
        sceGuSync(0,0);
        sceDisplayWaitVblankStart();
        sceGuSwapBuffers();
    }
    return 0;
}
