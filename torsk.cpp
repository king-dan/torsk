#include <iostream>
#include <cstdlib>
#include <stdio.h>

int g_spr = 10;
int g_peng = 500;
int g_pl = 1;
int g_godis = 0;
float g_skam = 12.5f;
int g_torsk = 0;

void p()
{
    const char *m[2] = {"Södermalm", "Hasseludden"};
    printf("\nDu befinner dig nu vid %s\n", m[g_pl]);
}

void s()
{
    printf("Du har: %d cl sprit, %d kr, %d kg godis, %.2f%% skam i kroppen\n", g_spr, g_peng, g_godis, g_skam);
    if (g_torsk)
        printf("Du är taxi-torsk\n");
    printf("Vad vill du göra?\n");
}

void alt()
{
    int sm=0,beer=0,corr=0,candy=0,talk=0,hu=0,sova=0;
    int idx = 0;
    
    if (g_peng >= 350)
    {
        if (g_pl == 1)
            sm = ++idx;
        candy = ++idx;
        if (g_pl == 0)
            hu = ++idx;
    }
    
    if (g_peng >= 0)
        talk = ++idx;
        
    if (g_pl == 1)
    {
        beer = ++idx;
        corr = ++idx;

        if (g_torsk || g_peng < 10.0f)
            sova = ++idx;
    }
    
    
    if (sm) printf("%d. Beställa taxi till Södermalm\n", sm);
    if (candy) printf("%d. Köp flera kilo godis (350 kr)\n", candy);
    if (hu) printf("%d. Beställa taxi tillbaka till Yasuragi\n", hu);
    if (talk) printf("%d. Hitta folk att prata med\n", talk);
    if (beer) printf("%d. Köpa öl i baren\n", beer);
    if (corr) printf("%d. Gå ett varv längs korriderna\n", corr);
    if (sova) printf("%d. Gå till rummet och sova.\n", sova);
    
    if (idx == 0)
    {
        printf("\nUtmattad och pank lägger du dig i rännstenen och sover.\n");
        printf("Du är en rännstenstorsk. Här slutar äventyret\n");
        exit(1);
    }
    
    printf("Ange alternativ: ");
    int v;
    scanf("%d", &v);
    
    if (v < 0)
    {
        printf("Felaktigt val\n");
        alt();
        return;
    }
    
    printf("\n");

    if (v == candy) {
        printf("==> Du köper 5 kilo godis.\n");
        g_peng -= 350;
        g_godis = 5.0f;
    } else if (v == sm) {
        printf("==> Du tar en taxi till Södermalm tillsammans med övriga ölsugna. Du har tur och slipper betala.\n");
        g_pl = 0;
    } else if (v == hu) {
        printf("==> Du tar en taxi tillbaka, det kostar dig 350 kronor\n");
        g_pl = 1;
        g_peng -= 350;
        g_skam += (100-g_skam)*0.80f;
        g_torsk = 1;
    } else if (v == corr) {
        printf("==> Du spatserar i de omåttligt långa korridorerna tills det värker i fötterna. Skammen ökar en smula\n");
        g_skam += (100-g_skam)*.24f;
    } else if (v == talk) {
        printf("==> Du möter en oerhört berusad finländare som pratar om Korva Penttinen i flera timmar.\n");
        int kost = 50 + rand()%100;
        printf("==> Du bjuder honom på en öl för %d kr\n", kost);
        g_peng -= kost;
        if (g_peng < 0)
        {
            printf("==> Du har nu övertrasserat ditt konto.\n");
            printf("==> Skammen är nu maximal\n");
            g_skam = 100.0f;
        }
    } else if (v == beer) {
        int kost = 50 + rand()%100;
        printf("==> Du prasslar med stålarna och får köpa en öl för %d kr.\n", kost);
        g_peng -= kost;
        if (g_peng < 0)
        {
            printf("==> Du har nu övertrasserat ditt konto.\n");
            printf("==> Skammen är nu maximal\n");
            g_skam = 100.0f;
        }
        else
        {
            printf("==> Skammen avtar något.\n");
            g_skam = g_skam * 0.90f;
        }
        
    } else if (v == sova) {
        printf("==> Äventyret slutar här nu.\n");
        if (g_torsk)
            printf("*** Du är en riktig Taxi-Torsk\n");
        if (!g_godis)
            printf("*** Du fick inte tag i något godis\n");
        if (g_peng <= 0)
            printf("*** Du är en penga-torsk\n");
        exit(0);
    } else {
        printf("Fel!");
    }
}


int main()
{
    printf("Välkommen till Taxitorsk 0.1.1-godistorsk\n");
    srand(time(0));
    while (true)
    {
        p();
        s();
        alt();
    }
    return 0;
}
