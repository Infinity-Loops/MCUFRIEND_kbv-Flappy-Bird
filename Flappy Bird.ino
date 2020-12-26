#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
const int XP=6,XM=A2,YP=A1,YM=7; //240x320 ID=0x9325
#define TS_MINX 213
#define TS_MINY 913
#define TS_MAXX 920
#define TS_MAXY 199
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
MCUFRIEND_kbv tft;
#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor, sc, v = 0, pv = 0, i = 0, j = 0;
float a = 0.5;
#define MINPRESSURE 1
#define MAXPRESSURE 1000
TSPoint waitOneTouch()
{
    TSPoint p;
    do
    {
        p = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

    } while ((p.z < MINPRESSURE) || (p.z > MAXPRESSURE));
    return p;
}
void bird(int n)
{
    tft.fillCircle(tft.width() / 3, tft.height() / 2 - 45 + v, 18, YELLOW);
    tft.drawCircle(tft.width() / 3, tft.height() / 2 - 45 + v, 18, BLACK);
    tft.fillRect(tft.width() / 3, tft.height() / 2 - 40 + v, 20, 7, RED);
    tft.drawRect(tft.width() / 3, tft.height() / 2 - 40 + v, 20, 7, BLACK);
    tft.fillRect(tft.width() / 3, tft.height() / 2 - 37 + v, 20, 1, BLACK);
    tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 7, WHITE);
    tft.drawCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 7, BLACK);
    tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 2, BLACK);
    tft.fillRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + v, 18, 7, WHITE);
    tft.drawRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + v, 18, 7, BLACK);
}
void birdcyan(int pv)
{
    tft.fillCircle(tft.width() / 3, tft.height() / 2 - 45 + pv, 18, CYAN);
    tft.drawCircle(tft.width() / 3, tft.height() / 2 - 45 + pv, 18, CYAN);
    tft.fillRect(tft.width() / 3, tft.height() / 2 - 40 + pv, 20, 7, CYAN);
    tft.drawRect(tft.width() / 3, tft.height() / 2 - 40 + pv, 20, 7, CYAN);
    tft.fillRect(tft.width() / 3, tft.height() / 2 - 37 + pv, 20, 1, CYAN);
    tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 7, CYAN);
    tft.drawCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 7, CYAN);
    tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 2, CYAN);
    tft.fillRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + pv, 18, 7, CYAN);
    tft.drawRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + pv, 18, 7, CYAN);
}
void setup(void)
{
    uint16_t ID = tft.readID();
    tft.reset();
    tft.begin(ID); //0x9325
    tft.setRotation(1);
    tft.fillScreen(CYAN);
    bird(0);
    tft.fillRect(0, 20, tft.width(), 3, BLACK);
    tft.fillRect(0, 0, tft.width(), 20, 0xD78A);
    tft.setTextSize(2);
    tft.setCursor(tft.width() / 3 - 10, 2);
    tft.setTextColor(RED);
    tft.print("Placar :");
    tft.print(sc);
    tft.fillRect(0, tft.height() - 33, tft.width(), 8, 0x3F30);
    tft.fillRect(0, tft.height() - 25, tft.width(), 25, 0xD78A);
    tft.setCursor(60, tft.height() - 20);
    tft.setTextColor(BLUE);
    tft.print("FLAPPY BIRD");
    tft.setCursor(tft.height() / 2, tft.height() / 2);
    tft.setTextColor(0xF080);
    tft.setTextSize(4);
    tft.print("Jogar");
    waitOneTouch();
    tft.fillScreen(CYAN);
    tft.fillRect(0, 0, tft.width(), 20, 0xD78A);
    tft.fillRect(0, tft.height() - 25, tft.width(), 25, 0xD78A);
    bird(0);
    pinMode(13, OUTPUT);
}
void loop()
{
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
        p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
        p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
        ;
        if (p.x > 0 && p.x < 320 && p.y > 0 && p.y < 240)
        {
            j = -8;
        }
    }
    tft.fillRect(tft.width() - 40 - (i * 2), 20, 20, 50, 0xD78A);
    tft.fillRect(tft.width() - 40 - (i * 2), 165, 20, 50, 0xD78A);
    tft.fillRect(tft.width() - 20 - (i * 2), 20, 20, 50, CYAN);
    tft.fillRect(tft.width() - 20 - (i * 2), 165, 20, 50, CYAN);
    tft.fillRect(0, 0, 20, tft.height(), 0xD78A);
    pv = v;
    v = v + (4 * a * j);
    birdcyan(pv);
    bird(v);
    j++;
    i++;
    if (i == 141 && (v <= 120 || v > -34 || (280 - (2 * i) < 106 && 280 - (2 * i) > 70 && 57 + v > 73 && 93 + v < 165)))
        i = 0;
    else if ((v >= 122 || v < (-34) || (280 - (2 * i) < 106 && 280 - (2 * i) > 70 && (57 + v < 73 || 93 + v > 165)) && i < 143))
    {
        tft.fillScreen(CYAN);
        tft.setCursor(tft.height() / 2, tft.height() / 2);
        tft.setTextSize(3);
        tft.println("Perdeu!");
        i = 500;
        delay(5000);
        setup();
    }
}