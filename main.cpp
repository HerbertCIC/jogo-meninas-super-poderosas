#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <time.h>

#define GRAVIDADE 9.81f // Aceleração gravitacional
#define PI 3.1416
#define POSX_INICIAL_FLORZINHA 750
#define POSY_INICIAL_FLORZINHA 350
#define NIVEL_2 4
#define NIVEL_3 3
#define POSX_INICIAL_MACACO 100
#define POSY_INICIAL_MACACO 30
#define VEL_INICIAL 200.0f

GLfloat velocidade_inicial_x = VEL_INICIAL; // Velocidade inicial horizontal do projétil
GLfloat velocidade_inicial_y = VEL_INICIAL; // Velocidade inicial vertical do projétil

GLfloat posX_florzinha = POSX_INICIAL_FLORZINHA, posY_florzinha = POSY_INICIAL_FLORZINHA;
GLfloat escala = 1.0;      // Variável de escala inicial
GLfloat escalaNuvem = 1.0; // Variável de escala inicial

GLfloat angOmbro = 0.0;
GLfloat angCotovelo = 0.0;
GLfloat angBanana = 0.0;
GLfloat desloc_x_macaco = 0;
GLfloat desloc_y_macaco = 0;

GLfloat angBracoDFlorzinha = -45.0f;
GLfloat angBracoEFlorzinha = 45.0;

const GLfloat angBracoMinFlorzinha = -45.0f;  // Limite inferior
const GLfloat angBracoMaxFlorzinha = -120.0f; // Limite superior

const GLfloat angOmbroMin = -45.0f; // Limite inferior
const GLfloat angOmbroMax = 0.0f;   // Limite superior

const GLfloat angCotoveloMin = -35.0f; // Limite inferior
const GLfloat angCotoveloMax = 0.0f;   // Limite superior

float posX_AlvoBanana = 0;
float posY_AlvoBanana = 0;

float tempo = 0.0f; // Tempo em segundos
float tempo_banana = 0.0f;
float deslocP_X = 34.0f;
float deslocP_Y = 8.0f;
float posX = posX_florzinha - deslocP_X; // Posição horizontal inicial
float posY = posY_florzinha - deslocP_Y; // Posição vertical inicial
float posicaoX_inicial = 0;
float posicaoY_inicial = 0;
float escalaP = 0.0f; // Escala inicial do projétil
float escalaB = 0.0f; // Escala inicial da banana
bool lancar = false;  // Controle para lançamento
bool lancar_banana = false;
bool animando = true; // Controle para animação inicial
bool animando_banana = true;

float deslocP_X_banana = 220;
float deslocP_Y_banana = 120;
float posX_macaco = POSX_INICIAL_MACACO;
float posY_macaco = POSY_INICIAL_MACACO;
float posX_banana = posX_macaco + deslocP_X_banana; // Posição horizontal inicial
float posX_banana_left = posX_macaco - 200;         // Posição horizontal inicial
float posY_banana = posY_macaco + deslocP_Y_banana; // Posição vertical inicial
float posicaoX_inicial_banana = 0;
float posicaoY_inicial_banana = 0;
bool liberar_lancamento = true;

double tempo_verificacao = 0.0; // Tempo acumulado para verificar a condição

// Variáveis para armazenar a posição inicial da banana ao ser lançada
bool bananaLancada = false;
float posInicialBananaX = 0, posInicialBananaY = 0;

// VARIAVEIS PARA DETECÇÃO DE COLISAO
float macacoLeft = posX_macaco + 100;
float macacoRight = posX_macaco + 200;
float macacoBottom = posY_macaco;
float macacoTop = posY_macaco + 150;

float naveLeft = posX_macaco + 100;
float naveRight = posX_macaco + 250;
float naveBottom = posY_macaco;
float naveTop = posY_macaco + 200;

int vidaNave = 3;
bool lado_projetil = false;

float projLeft = posX - 10;
float projRight = posX + 10;
float projBottom = posY - 10;
float projTop = posY + 10;

float floarzinhaLeft = posX_florzinha - 25;
float floarzinhaRight = posX_florzinha + 25;
float floarzinhaBottom = posY_florzinha - 25;
float floarzinhaTop = posY_florzinha + 100;

float bananaLeft = posX_banana - 14;
float bananaRight = posX_banana + 14;
float bananaBottom = posY_banana - 12;
float bananaTop = posY_banana + 12;

// Explosões

bool explosaoAtiva = false;
float explosaoX = 0, explosaoY = 0;
float raioExplosao = 0.0f;
const float raioMaximoExplosao = 50.0f;
const float raioMaximoExplosaoPersonagem = 120.0f;

// placar
int pontuacao_florzinha = 5;
int pontuacao_macaco = 5;
bool vitoriaFlorzinha = false;
bool vitoriaMacaco = false;
bool exibindoMensagemVitoria = false;

void roadLine_model();
void window_model();
void roadLine(double x, double y);
void window(double x, double y);

static bool condicaoCongelada = false, ladoBanana = false;
static double posXInicialBanana, posYInicialBanana;

bool sentinela_lado_banana_inicial = false;

// PROTOTIPOS-----------------------------------------------------------------------------------
void desenha_banana(float x, float y, bool side);
// void desenhaTexto(float x, float y, const char *texto, void *fonte = GLUT_BITMAP_HELVETICA_18);
void desenhaExplosao(float x, float y, float raio);
void atualizarExplosao(int value);
void atualizarExplosaoPersonagem(int value);
void exibirMensagemVitoria();
void atualizaBoundingBoxeProjetil(float x, float y);
void atualizaBoundingBoxeFlorzinha(float x, float y);
void atualizaBoundingBoxeMacaco(float x, float y);
void atualizaBoundingBoxeNave(float x, float y);
void atualizaBoundingBoxeBanana(float x, float y);
void reseta_pontuacao();
void reseta_projetil();
void reseta_banana();
void resetGeral(int value);
bool decidirLancarBanana();
bool checarColisao();
bool checarColisaoBanana();
bool checarColisaoNave();
void desenhaBoundingBox(float left, float right, float bottom, float top);
void AlteraDeslocamentos(void);
void Animar_macaco(int interacoes);
void circle(GLdouble rad);
void desenhaPlacar();
void desenhaEsferaComBrilho(float x, float y, float escala);
void update(int value);
void circle_with_border(GLdouble rad, GLfloat border_thickness);
void drawEllipse(GLfloat rx, GLfloat ry);
void drawEllipseWithBorder(GLfloat rx, GLfloat ry, GLfloat border_thickness);
void drawSemiCircleWithBorder(GLfloat radius, GLfloat centerX, GLfloat centerY);
void drawSemiEllipseWithBorder(GLfloat radiusX, GLfloat radiusY, GLfloat centerX, GLfloat centerY, GLfloat borderThickness);
void background();
void Sun();
void mountains();
void road();
void sidewalk();
void roadLine_model();
void cloud_model();
void buildin1_model();
void buildin2_model();
void buildin3_model();
void buildin4_model();
void buildin5_model();
void window_model();
void tower_model();
void Tree1_Model();
void Tree2_Model();
void florzinha_model();
void florzinha_queimada_model();
void model_banana(float x, float y, float angle);
void desenha_banana(float x, float y, bool side);
void nave_sobre_macaco();
void macaco_model();
void macaco_queimado_model();

void tower(double x, double y);
void window(double x, double y);
void buildin1(double x, double y);
void buildin2(double x, double y);
void buildin3(double x, double y);
void buildin4(double x, double y);
void buildin5(double x, double y);
void roadLine(double x, double y);
void cloud(double x, double y);
void cloud_Modify(double x, double y, double escalaNuvem);
void Tree1(double x, double y);
void Tree2(double x, double y);
void florzinha(double x, double y, double escala);
void florzinha_queimada(double x, double y, double escala);
void macaco(double x, double y);
void macaco_queimado(double x, double y);
void recalculaAngProjetilBracoD(float ang);
void recalculaAngProjetilBracoE(float ang);
void desenha_macaco();
void Teclado(unsigned char tecla, int x, int y);
void TeclasEspeciais(int tecla, int x, int y);
void display(void);

//----------------------------------------------------------------------------------------------

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1250, 720);
    glutCreateWindow("Townsville");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo preto
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1000.0, 0.0, 500.0); // Define um espaço 2D para projeção

    glutDisplayFunc(display);
    glutKeyboardFunc(Teclado);        // Teclas padrão
    glutSpecialFunc(TeclasEspeciais); // Teclas especiais
    glutTimerFunc(16, update, 0);
    glutTimerFunc(30, Animar_macaco, 0); // Chama a função de call back de animação
    glutMainLoop();
    return 0;
}

//---------------DISPLAY----------------------

void desenhaTexto(float x, float y, const char *texto, void *fonte = GLUT_BITMAP_HELVETICA_18)
{
    glRasterPos2f(x, y); // Define a posição do texto
    for (const char *c = texto; *c != '\0'; c++)
    {
        glutBitmapCharacter(fonte, *c); // Renderiza cada caractere
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    ///*** Objetos de Layout ***///
    background();

    Sun();
    cloud(600, 190);
    cloud(180, 210);

    cloud_Modify(800, 180, 1);

    mountains();
    buildin2(800, 0);
    buildin2(0, -40);

    buildin1(750, 100);

    buildin3(120, 30);
    buildin3(210, 100);
    buildin3(500, 80);

    buildin1(170, 100);
    tower(400, 50);
    buildin4(280, 100);
    buildin5(555, 100);

    road();
    sidewalk();
    Tree1(50, 30);
    Tree2(560, -10);
    Tree1(660, 30);
    Tree2(235, -10);
    Tree2(850, -10);

    glColor3f(1.0f, 1.0f, 1.0f);
    if (vitoriaMacaco)
    {
        florzinha_queimada(posX_florzinha, posY_florzinha, escala);
    }
    else
    {
        florzinha(posX_florzinha, posY_florzinha, escala);
    }

    desenha_macaco();

    if (lancar)
    {
        glPushMatrix();
        glTranslated(-50, 0, 1);
        desenhaEsferaComBrilho(posX, posY, escalaP);
        glPopMatrix();
    }
    // desenhaBoundingBox(macacoLeft, macacoRight, macacoBottom, macacoTop);
    // desenhaBoundingBox(projLeft, projRight, projBottom, projTop);

    // desenhaBoundingBox(naveLeft, naveRight, naveBottom, naveTop);

    // desenhaBoundingBox(floarzinhaLeft, floarzinhaRight, floarzinhaBottom, floarzinhaTop);
    // desenhaBoundingBox(bananaLeft, bananaRight, bananaBottom, bananaTop);

    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    if (explosaoAtiva)
    {
        if (vitoriaFlorzinha)
        {
            desenhaExplosao(posX_macaco + 150, posY_macaco + 80, raioExplosao);
        }
        else if (vitoriaMacaco)
        {
            desenhaExplosao(posX_florzinha, posY_florzinha, raioExplosao);
        }
        else
        {
            desenhaExplosao(explosaoX, explosaoY, raioExplosao);
        }
    }

    desenhaPlacar();

    char textoNave[20];

    if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
    {
        glColor3ub(128, 0, 128);
        sprintf(textoNave, "Nave:");
        desenhaTexto(200, 445, textoNave);

        for (int i = 0; i < vidaNave; i++)
        {
            float x = 250 + (i * 20);
            float y = 450;
            glPushMatrix();
            glTranslatef(x, y, 0);
            glColor3ub(128, 0, 128);
            circle(6.0);
            glPopMatrix();
        }
    }

    char textoControles[50];

    glColor3ub(255, 255, 255);
    sprintf(textoControles, "w / s: Ajustar ang.    a / d: Alternar lado do disparo");
    desenhaTexto(30, 15, textoControles, GLUT_BITMAP_HELVETICA_12);

    sprintf(textoControles, "espaço: Ataque");
    desenhaTexto(450, 15, textoControles, GLUT_BITMAP_HELVETICA_12);

    sprintf(textoControles, "^");
    desenhaTexto(863, 18, textoControles, GLUT_BITMAP_HELVETICA_18);

    sprintf(textoControles, "<- | -> : Movimentacao");
    desenhaTexto(850, 15, textoControles, GLUT_BITMAP_HELVETICA_12);

    sprintf(textoControles, "v");
    desenhaTexto(863, 6, textoControles, GLUT_BITMAP_HELVETICA_12);

    exibirMensagemVitoria();

    glutSwapBuffers(); // Atualiza tela com buffer duplo
}

// ------------------------------------------  FUNÇÕES ---------------------------------------------------------

void desenhaExplosao(float x, float y, float raio)
{
    // Camada externa - vermelho
    glColor3f(1.0f, 0.2f, 0.0f); // Vermelho brilhante
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++)
    {
        float angle = i * 2.0f * PI / 100;
        float dx = cos(angle) * (raio * 0.8f);
        float dy = sin(angle) * (raio * 0.8f);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Camada intermediária - laranja
    glColor3f(1.0f, 0.5f, 0.0f); // Laranja
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++)
    {
        float angle = i * 2.0f * PI / 100;
        float dx = cos(angle) * (raio * 0.6f); // Reduz o raio da camada intermediária
        float dy = sin(angle) * (raio * 0.6f);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Camada interna - amarelo
    glColor3f(1.0f, 1.0f, 0.0f); // Amarelo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++)
    {
        float angle = i * 2.0f * PI / 100;
        float dx = cos(angle) * (raio * 0.3f); // Reduz ainda mais o raio da camada interna
        float dy = sin(angle) * (raio * 0.3f);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();

    // Fragmentos ao redor
    glColor3f(1.0f, 0.9f, 0.4f); // Fragmentos amarelos
    for (int i = 0; i < 15; i++)
    {                                                     // Menos fragmentos para explosão compacta
        float angle = (rand() % 360) * PI / 180.0f;       // Ângulo aleatório
        float fragmentX = x + cos(angle) * (raio * 0.9f); // Próximos ao centro da explosão
        float fragmentY = y + sin(angle) * (raio * 0.9f);
        glBegin(GL_TRIANGLES);
        glVertex2f(fragmentX, fragmentY);
        glVertex2f(fragmentX + 3.0f, fragmentY + 2.0f); // Fragmentos menores
        glVertex2f(fragmentX - 3.0f, fragmentY + 2.0f);
        glEnd();
    }
}

void atualizarExplosao(int value)
{
    if (explosaoAtiva)
    {
        raioExplosao += 5.0f; // Aumenta o raio da explosão
        if (raioExplosao >= raioMaximoExplosao)
        {
            explosaoAtiva = false; // Finaliza a explosão
            raioExplosao = 0.0f;   // Reseta o raio
        }
        glutPostRedisplay();
        glutTimerFunc(50, atualizarExplosao, 0);
    }
}

void atualizarExplosaoPersonagem(int value)
{
    if (explosaoAtiva)
    {
        raioExplosao += 5.0f; // Aumenta o raio da explosão
        if (raioExplosao >= raioMaximoExplosaoPersonagem)
        {
            explosaoAtiva = false; // Finaliza a explosão
            raioExplosao = 0.0f;   // Reseta o raio
        }
        glutPostRedisplay();
        glutTimerFunc(50, atualizarExplosaoPersonagem, 0);
    }
}

void exibirMensagemVitoria()
{
    if (exibindoMensagemVitoria)
    {
        if (vitoriaFlorzinha)
        {
            glColor3f(0.0f, 0.5f, 0.0f); // Verde
            desenhaTexto(450, 450, "VITORIA!", GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if (vitoriaMacaco)
        {
            glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
            desenhaTexto(450, 450, "DERROTA!", GLUT_BITMAP_TIMES_ROMAN_24);
        }
    }
}

void atualizaBoundingBoxeProjetil(float x, float y)
{
    projLeft = x - 10;
    projRight = x + 10;
    projBottom = y - 10;
    projTop = y + 10;
}

void atualizaBoundingBoxeFlorzinha(float x, float y)
{
    floarzinhaLeft = x - 25;
    floarzinhaRight = x + 25;
    floarzinhaBottom = y - 25;
    floarzinhaTop = y + 100;
}

void atualizaBoundingBoxeMacaco(float x, float y)
{
    macacoLeft = x + 100;
    macacoRight = x + 200;
    macacoBottom = y;
    macacoTop = y + 150;
}

void atualizaBoundingBoxeNave(float x, float y)
{
    naveLeft = x + 60;
    naveRight = x + 240;
    naveBottom = y;
    naveTop = y + 175;
}

void atualizaBoundingBoxeBanana(float x, float y)
{
    bananaLeft = x + 8;
    bananaRight = x + 45;
    bananaBottom = y - 18;
    bananaTop = y + 8;
}

void reseta_pontuacao()
{
    pontuacao_florzinha = 5;
    pontuacao_macaco = 5;
}

void reseta_projetil()
{
    tempo = 0.0f;

    posX = posicaoX_inicial;
    posY = posicaoY_inicial;
    lancar = false;  // Para o lançamento
    animando = true; // Reinicia a animação inicial
    escalaP = 0.0f;  // Reinicia a escala
    atualizaBoundingBoxeProjetil(posX, posY);
}

void reseta_banana()
{
    tempo_banana = 0.0f;
    if (posX_florzinha < posX_macaco)
    {
        posXInicialBanana = posX_macaco + 20;
        posYInicialBanana = posY_macaco + 118;
    }
    else
    {
        posXInicialBanana = posX_macaco + deslocP_X_banana;
        posYInicialBanana = posY_macaco + deslocP_Y_banana;
    }
    atualizaBoundingBoxeBanana(posXInicialBanana, posYInicialBanana);
    sentinela_lado_banana_inicial = false;
    ladoBanana = false;
    liberar_lancamento = true;
    lancar_banana = false;
    animando_banana = true; // Reinicia a animação inicial
    escalaB = 0.0f;         // Reinicia a escala
}

void resetGeral(int value)
{
    reseta_pontuacao();
    exibindoMensagemVitoria = false;
    vitoriaFlorzinha = false;
    vitoriaMacaco = false;
    posX_florzinha = POSX_INICIAL_FLORZINHA;
    posY_florzinha = POSY_INICIAL_FLORZINHA;

    posX_macaco = POSX_INICIAL_MACACO;
    posY_macaco = POSY_INICIAL_MACACO;
    reseta_projetil();
    reseta_banana();

    atualizaBoundingBoxeFlorzinha(posX_florzinha, posY_florzinha);
    atualizaBoundingBoxeMacaco(posX_macaco, posY_macaco);
    vidaNave = 3;

    angBracoDFlorzinha = -45.0f;
    angBracoEFlorzinha = 45.0;

    velocidade_inicial_x = VEL_INICIAL;
    velocidade_inicial_y = VEL_INICIAL;

    lado_projetil = false;
}

// Função para decidir aleatoriamente se a banana será lançada
bool decidirLancarBanana()
{
    return std::rand() % 2 == 0; // Retorna true ou false aleatoriamente
}

bool checarColisao()
{
    if (!(projRight < macacoLeft || // Projetil à esquerda do macaco
          projLeft > macacoRight || // Projetil à direita do macaco
          projTop < macacoBottom || // Projetil abaixo do macaco
          projBottom > macacoTop))
    {
        explosaoAtiva = true;
        explosaoX = posX - 30;
        explosaoY = posY - 20;
        pontuacao_florzinha -= 1;

        if (pontuacao_florzinha == 0 && !exibindoMensagemVitoria)
        {
            exibindoMensagemVitoria = true;                   // Ativa a exibição da mensagem
            vitoriaFlorzinha = true;                          // Define a vitória da florzinha
            glutTimerFunc(0, atualizarExplosaoPersonagem, 0); // Inicia a animação da explosão
            glutTimerFunc(3000, resetGeral, 0);               // Exibe por 3 segundos
        }
        else
        {
            glutTimerFunc(0, atualizarExplosao, 0); // Inicia a animação da explosão
        }
        return true;
    }
    return false;
}

bool checarColisaoBanana()
{
    if (!(bananaRight < floarzinhaLeft ||
          bananaLeft > floarzinhaRight ||
          bananaTop < floarzinhaBottom ||
          bananaBottom > floarzinhaTop))
    {
        explosaoAtiva = true;
        explosaoX = posXInicialBanana + 30;
        explosaoY = posYInicialBanana;
        pontuacao_macaco -= 1;

        if (pontuacao_macaco == 0 && !exibindoMensagemVitoria)
        {
            exibindoMensagemVitoria = true;                   // Ativa a exibição da mensagem
            vitoriaMacaco = true;                             // Define a vitória do macaco
            glutTimerFunc(0, atualizarExplosaoPersonagem, 0); // Inicia a animação da explosão
            glutTimerFunc(3000, resetGeral, 0);               // Exibe por 3 segundos
        }
        else
        {
            glutTimerFunc(0, atualizarExplosao, 0); // Inicia a animação da explosão
        }
        return true;
    };
    return false;
}

bool checarColisaoNave()
{
    if (!(projRight < naveLeft ||
          projLeft > naveRight ||
          projTop < naveBottom ||
          projBottom > naveTop))
    {
        explosaoAtiva = true;
        explosaoX = posX - 30;
        explosaoY = posY - 20;
        vidaNave -= 1;
        glutTimerFunc(0, atualizarExplosao, 0); // Inicia a animação da explosão
        return true;
    }
    return false;
}

void desenhaBoundingBox(float left, float right, float bottom, float top)
{
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho para depuração
    glBegin(GL_LINE_LOOP);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);
    glVertex2f(left, top);
    glEnd();
}

void AlteraDeslocamentos(void)
{
    if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
    {
        int direcao = rand() % 2;
        GLfloat deslocamento = ((rand() % 2 == 0) ? 1 : -1) * ((rand() % 6 + 1) / 10.0f);

        if (direcao == 0)
        {
            desloc_x_macaco = deslocamento;
            desloc_y_macaco = 0.0f;
        }
        else
        {
            desloc_x_macaco = 0.0f;
            desloc_y_macaco = deslocamento;
        }
    }
    else
    {
        GLfloat aux1 = rand();
        GLfloat aux2 = rand();
        if (pontuacao_florzinha < NIVEL_2)
        {
            desloc_x_macaco = (aux1 > aux2) ? 0.6f : -0.6f;
        }
        else if (pontuacao_florzinha < NIVEL_3)
        {
            desloc_x_macaco = (aux1 > aux2) ? 0.7f : -0.7f;
        }
        else
        {
            desloc_x_macaco = (aux1 > aux2) ? 0.5f : -0.5f;
        }
    }
}

void Animar_macaco(int interacoes)
{
    if (!vitoriaFlorzinha)
    {
        // Controla a atualização de deslocamentos
        if (interacoes % 10 == 0)
        {
            AlteraDeslocamentos();
        }

        for (int cont = 0; cont < 17; cont++)
        {
            // Atualiza a posição do macaco
            posX_macaco += desloc_x_macaco;
            if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
            {
                posY_macaco += desloc_y_macaco;
            }
            else if (vidaNave <= 0 && posY_macaco > POSY_INICIAL_MACACO)
            {
                posY_macaco -= 0.2f;
                if (posY_macaco < POSY_INICIAL_MACACO)
                {
                    posY_macaco = POSY_INICIAL_MACACO;
                }
            }

            // Verifica e corrige os limites do macaco
            if (posX_macaco < -100 || posX_macaco > 800)
            {
                desloc_x_macaco = -desloc_x_macaco;              // Inverte direção
                posX_macaco = (posX_macaco < -100) ? -100 : 800; // Corrige posição
                AlteraDeslocamentos();
            }

            if (posY_macaco < 0 || posY_macaco > 450)
            {
                desloc_y_macaco = -desloc_y_macaco;        // Inverte direção
                posY_macaco = (posY_macaco < 0) ? 0 : 450; // Corrige posição
                AlteraDeslocamentos();
            }

            // Atualiza as bounding boxes
            atualizaBoundingBoxeMacaco(posX_macaco, posY_macaco);

            if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
            {
                atualizaBoundingBoxeNave(posX_macaco, posY_macaco);
            }

            // Atualiza a posição da banana se ela não foi lançada
            if (!lancar_banana)
            {
                if (posX_florzinha < posX_macaco)
                {
                    posXInicialBanana = posX_macaco + 20;
                    posYInicialBanana = posY_macaco + 118;
                }
                else
                {
                    posXInicialBanana = posX_macaco + deslocP_X_banana;
                    posYInicialBanana = posY_macaco + deslocP_Y_banana;
                }
                atualizaBoundingBoxeBanana(posXInicialBanana, posYInicialBanana);
            }
        }

        // Incrementa o contador de interações
        interacoes++;
    }

    // Atualiza a exibição e configura o próximo quadro de animação
    glutPostRedisplay();
    glutTimerFunc(30, Animar_macaco, interacoes);
}

void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for (int i = 0; i <= 50; i++, theta += delTheta)
        {
            glVertex2f(rad * cos(theta), rad * sin(theta));
        }
    }
    glEnd();
}

void desenhaPlacar()
{
    // Placar da florzinha (lado direito)
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho //
    char texto[20];
    sprintf(texto, "Florzinha");
    desenhaTexto(900, 445, texto);
    for (int i = 0; i < pontuacao_macaco; i++)
    {
        float x = 880 - (i * 20);
        float y = 450;
        glPushMatrix();
        glTranslatef(x, y, 0);

        circle(6.0);
        glPopMatrix();
    }

    // Placar do macaco (lado esquerdo)
    glColor3f(0.0f, 0.0f, 1.0f); // Azul //
    sprintf(texto, "Macaco");
    desenhaTexto(30, 445, texto);

    for (int i = 0; i < pontuacao_florzinha; i++)
    {
        float x = 100 + (i * 20);
        float y = 450;
        glPushMatrix();
        glTranslatef(x, y, 0);

        circle(6.0);
        glPopMatrix();
    }
}

// DESENHA PROJETIL
void desenhaEsferaComBrilho(float x, float y, float escala)
{
    // Desenhar a esfera principal
    glColor3f(1.0f, 0.41f, 0.71f); // Cor rosa sólida
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(escala, escala, 1.0f);
    circle(10);
    glPopMatrix();
}

// ATUALIZA POSIÇÃO DO PROJETIL
void update(int value)
{
    if (!exibindoMensagemVitoria)
    {
        // PROJETIL
        if (animando)
        {
            escalaP += 0.03f; // Incremento na escala para animação inicial
            if (escalaP >= 1.0f)
            {
                escalaP = 1.0f; // Limita a escala máxima
                animando = false;
            }
        }
        else if (lancar)
        {
            tempo += 0.016f; // Incrementa o tempo (assumindo ~60 FPS)
            float fatorVelocidadeProjetil = 1.5f;
            // Atualiza posições
            if (lado_projetil)
            {

                posX = posicaoX_inicial + (velocidade_inicial_x * tempo * fatorVelocidadeProjetil);                                      // Movimento uniforme na horizontal
                posY = posicaoY_inicial - (velocidade_inicial_y * tempo * fatorVelocidadeProjetil) - (0.5f * GRAVIDADE * tempo * tempo); // Movimento acelerado na vertical
            }
            else
            {
                posX = posicaoX_inicial - (velocidade_inicial_x * tempo * fatorVelocidadeProjetil);                                      // Movimento uniforme na horizontal
                posY = posicaoY_inicial - (velocidade_inicial_y * tempo * fatorVelocidadeProjetil) - (0.5f * GRAVIDADE * tempo * tempo); // Movimento acelerado na vertical
            }

            atualizaBoundingBoxeProjetil(posX, posY);

            if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
            {
                if (checarColisaoNave())
                {
                    reseta_projetil();
                }
            }
            else if (checarColisao())
            {
                reseta_projetil();
            }

            if (posY < 0.0f || posY > 550.0f || posX > 1050.0f || posX < 0.0f)
            {
                reseta_projetil(); // Reinicia caso saia da "tela"
            }
        }

        // BANANA

        const double intervalo_verificacao = 1.0; // Intervalo de 1 segundo para verificar

        // Verifica a condição de lançamento a cada 1 segundo
        tempo_verificacao += 0.016f; // Incrementa o tempo acumulado
        if (tempo_verificacao >= intervalo_verificacao && liberar_lancamento)
        {
            lancar_banana = decidirLancarBanana(); // Define se a banana será lançada
            tempo_verificacao = 0.0;               // Reinicia o temporizador de verificação
            if (lancar_banana)
            {
                posInicialBananaX = posXInicialBanana;
                posInicialBananaY = posYInicialBanana;

                posX_AlvoBanana = posX_florzinha;
                posY_AlvoBanana = posY_florzinha;
            }
        }

        if (animando_banana)
        {
            escalaB += 0.03f; // Incremento na escala para animação inicial
            if (escalaB >= 1.0f)
            {
                escalaB = 1.0f; // Limita a escala máxima
                animando_banana = false;
            }
        }
        else if (lancar_banana)
        {
            tempo_banana += 0.016f; // Incrementa o tempo (assumindo ~60 FPS
            liberar_lancamento = false;
            float fatorVelocidadeBanana;
            if (pontuacao_florzinha < NIVEL_3)
            {
                fatorVelocidadeBanana = 1;
            }
            else
            {
                fatorVelocidadeBanana = 0.8;
            }
            posXInicialBanana = posInicialBananaX + ((posX_AlvoBanana - posInicialBananaX) * tempo_banana * fatorVelocidadeBanana);
            posYInicialBanana = posInicialBananaY + ((posY_AlvoBanana - posInicialBananaY) * tempo_banana * fatorVelocidadeBanana) - (0.5f * GRAVIDADE * tempo_banana * tempo_banana); // Movimento acelerado na vertical
            atualizaBoundingBoxeBanana(posXInicialBanana, posYInicialBanana);

            if (checarColisaoBanana())
            {
                reseta_banana();
            }
            else if (posYInicialBanana < 0.0f || posYInicialBanana > 600.0f || posXInicialBanana > 1200.0f || posXInicialBanana < 0.0f)
            {
                reseta_banana(); // Reinicia caso saia da "tela"
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void circle_with_border(GLdouble rad, GLfloat border_thickness)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    // C�rculo preenchido
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 50; i++, theta += delTheta)
    {
        glVertex2f(rad * cos(theta), rad * sin(theta));
    }
    glEnd();

    // Borda preta
    glLineWidth(border_thickness);
    glColor3f(0, 0, 0);    // Cor preta para a borda
    glBegin(GL_LINE_LOOP); // Desenhar a borda ao redor do c�rculo
    theta = 0.0;
    for (int i = 0; i <= 50; i++, theta += delTheta)
    {
        glVertex2f(rad * cos(theta), rad * sin(theta));
    }
    glEnd();
}

void drawEllipse(GLfloat rx, GLfloat ry)
{
    int num_segments = 100; // N�mero de segmentos para aproximar a elipse
    GLfloat angle;

    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        angle = 2.0f * PI * i / num_segments;         // �ngulo atual
        glVertex2f(rx * cos(angle), ry * sin(angle)); // Coordenadas da elipse
    }
    glEnd();
}

void drawEllipseWithBorder(GLfloat rx, GLfloat ry, GLfloat border_thickness)
{
    int num_segments = 100; // N�mero de segmentos para aproximar a elipse
    GLfloat angle;

    // Desenhar a elipse preenchida
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++)
    {
        angle = 2.0f * PI * i / num_segments;         // �ngulo atual
        glVertex2f(rx * cos(angle), ry * sin(angle)); // Coordenadas da elipse
    }
    glEnd();

    // Desenhar a borda da elipse
    glLineWidth(border_thickness); // Define a espessura da borda
    glColor3f(0.0f, 0.0f, 0.0f);   // Cor da borda (preto)

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)
    {
        angle = 2.0f * PI * i / num_segments;         // �ngulo atual
        glVertex2f(rx * cos(angle), ry * sin(angle)); // Coordenadas da borda
    }
    glEnd();
}

void drawSemiCircleWithBorder(GLfloat radius, GLfloat centerX, GLfloat centerY)
{
    // Desenha o semi-c�rculo preenchido
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++)
    {
        GLfloat angle = PI * i / 100; // Apenas a metade do c�rculo
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();

    // Desenha a borda do semi-c�rculo
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 100; i++)
    {
        GLfloat angle = PI * i / 100; // Apenas a metade do c�rculo
        glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
    }
    glEnd();
}

void drawSemiEllipseWithBorder(GLfloat radiusX, GLfloat radiusY, GLfloat centerX, GLfloat centerY, GLfloat borderThickness)
{
    // Desenha a semi-elipse preenchida
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++)
    {
        GLfloat angle = PI * i / 100; // Apenas a metade da elipse
        glVertex2f(centerX + radiusX * cos(angle), centerY + radiusY * sin(angle));
    }
    glEnd();

    // Configura a cor da borda
    if (borderThickness)
    {
        glLineWidth(borderThickness); // Define a espessura da borda
        glColor3f(0.0f, 0.0f, 0.0f);  // Cor da borda (preto)

        // Desenha a borda da semi-elipse
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 100; i++)
        {
            GLfloat angle = PI * i / 100; // Apenas a metade da elipse
            glVertex2f(centerX + radiusX * cos(angle), centerY + radiusY * sin(angle));
        }
        glEnd();
    }
}

//--------------------------------------CENARIO BACKGROUND PRINCIPAL----------------------------

void background()
{
    glBegin(GL_QUADS);

    // Cor da parte inferior (clara)
    glColor3ub(255, 255, 255);
    glVertex2f(0, 100);
    glVertex2f(1000, 100);

    // Cor da parte superior (escura)
    glColor3ub(121, 224, 237);
    glVertex2f(1000, 500);
    glVertex2f(0, 500);

    glEnd();
}

void Sun()
{
    glColor3ub(252, 255, 179);
    glPushMatrix();
    glTranslatef(425, 425, 0);
    circle(30);
    glPopMatrix();
}

void mountains()
{
    glPushMatrix();
    glTranslatef(0, -150, 0);
    glBegin(GL_POLYGON);

    glColor3ub(213, 221, 232);
    glVertex2f(0, 100);
    glVertex2f(1000, 100);
    glVertex2f(1000, 171);
    glVertex2f(950, 171);
    glVertex2f(939, 340);
    glVertex2f(887, 340);
    glVertex2f(758, 351);
    glVertex2f(767, 351);
    glVertex2f(682, 187);
    glVertex2f(700, 187);
    glVertex2f(654, 447);
    glVertex2f(651, 447);
    glVertex2f(629, 370);
    glVertex2f(629, 370);
    glVertex2f(601, 265);
    glVertex2f(603, 265);
    glVertex2f(567, 377);
    glVertex2f(566, 377);
    glVertex2f(420, 300);
    glVertex2f(420, 300);
    glVertex2f(400, 200);
    glVertex2f(400, 200);
    glVertex2f(362, 467);
    glVertex2f(364, 467);
    glVertex2f(317, 200);
    glVertex2f(315, 200);
    glVertex2f(295, 410);
    glVertex2f(297, 410);
    glVertex2f(200, 280);
    glVertex2f(200, 280);
    glVertex2f(100, 370);
    glVertex2f(100, 370);
    glVertex2f(30, 200);
    glVertex2f(30, 200);
    glVertex2f(0, 300);
    glEnd();
    glPopMatrix();
}

void road()
{
    glBegin(GL_QUADS);

    glColor3ub(75, 98, 106);
    glVertex2f(0, 0);
    glVertex2f(1000, 0);
    glVertex2f(1000, 100);
    glVertex2f(0, 100);

    glEnd();

    int initial_space = 20;

    for (int cont = 0; cont < 18; cont++)
    {
        roadLine(initial_space, 50);
        initial_space += 60;
    }
}

void sidewalk()
{
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 230);
    glVertex2f(0, 90);
    glVertex2f(1000, 90);
    glVertex2f(1000, 100);
    glVertex2f(0, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(148, 166, 189);
    glVertex2f(0, 90);
    glVertex2f(1000, 90);
    glVertex2f(1000, 92);
    glVertex2f(0, 93);
    glEnd();
}

//--------------------------MODELS---------------------------------

void roadLine_model()
{
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 230);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 4);
    glVertex2f(0, 4);
    glEnd();
}

void cloud_model()
{

    glColor3f(1.25, 0.924, 0.930);

    /// Top_Left

    glPushMatrix();
    glTranslatef(20, 210, 0);
    circle(15);
    glPopMatrix();

    /// Top

    glPushMatrix();
    glTranslatef(40, 225, 0);
    circle(16);
    glPopMatrix();

    /// Right

    glPushMatrix();
    glTranslatef(60, 210, 0);
    circle(16);
    glPopMatrix();

    /// middle_Fill
    glPushMatrix();
    glTranslatef(55, 210, 0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(50, 210, 0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(45, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 204, 0);
    circle(10);
    glPopMatrix();
}

void buildin1_model()
{

    glBegin(GL_POLYGON);
    glColor3ub(164, 192, 232);
    glVertex2i(0, 0);
    glVertex2i(50, 0);
    glVertex2i(50, 200);
    glVertex2i(0, 200);
    glEnd();

    glLineWidth(3);
    glColor3ub(117, 145, 185);

    glBegin(GL_LINES);
    glVertex2f(10, 10);
    glVertex2f(10, 190);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(20, 10);
    glVertex2f(20, 190);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(30, 10);
    glVertex2f(30, 190);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(40, 10);
    glVertex2f(40, 190);
    glEnd();
}

void buildin2_model()
{
    // Desenhar o pol�gono
    glBegin(GL_POLYGON);
    glColor3ub(131, 157, 192); // Cor do pol�gono
    glVertex2f(0, 0);          // Ponto 1: (0,0)
    glVertex2f(200, 0);        // Ponto 2: (200,0)
    glVertex2f(200, 200);      // Ponto 3: (200,200)
    glVertex2f(100, 200);      // Ponto 4: (100,200)
    glVertex2f(100, 366);      // Ponto 5: (100,366)
    glVertex2f(54, 357);       // Ponto 6: (54,357)
    glVertex2f(54, 140);       // Ponto 7: (54,140)
    glVertex2f(0, 200);        // Ponto 8: (0,200)
    glEnd();
}

void buildin3_model()
{

    glBegin(GL_POLYGON);
    glColor3ub(100, 130, 168);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 250);
    glVertex2f(0, 250);
    glEnd();
}

void buildin4_model()
{
    glBegin(GL_POLYGON);
    glColor3ub(119, 147, 186);

    glVertex2f(0, 0);
    glVertex2f(40, 0);
    glVertex2f(40, 100);
    glVertex2f(0, 115);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(163, 191, 231);

    glVertex2f(40, 0);
    glVertex2f(100, 0);
    glVertex2f(100, 100);
    glVertex2f(40, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(190, 207, 230);

    glVertex2f(40, 100);
    glVertex2f(100, 100);
    glVertex2f(62, 115);
    glVertex2f(0, 115);

    glEnd();
}

void buildin5_model()
{
    glBegin(GL_POLYGON);
    glColor3ub(163, 191, 231);

    glVertex2f(0, 0);
    glVertex2f(150, 0);
    glVertex2f(150, 100);
    glVertex2f(0, 100);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(119, 147, 186);

    glVertex2f(150, 0);
    glVertex2f(190, 0);
    glVertex2f(190, 115);
    glVertex2f(150, 100);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(190, 207, 230);

    glVertex2f(0, 100);
    glVertex2f(150, 100);
    glVertex2f(190, 115);
    glVertex2f(60, 115);

    glEnd();
}

void window_model()
{
    glBegin(GL_QUADS);
    glColor3ub(117, 145, 185);
    glVertex2f(0, 0);
    glVertex2f(5, 0);
    glVertex2f(5, 5);
    glVertex2f(0, 5);
    glEnd();
}

void tower_model()
{
    // tower
    glColor3ub(179, 198, 223);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(30, 0);
    glVertex2f(30, 200);
    glVertex2f(0, 200);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(30, 0);
    glVertex2f(60, 0);
    glVertex2f(60, 250);
    glVertex2f(30, 250);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(60, 0);
    glVertex2f(90, 0);
    glVertex2f(90, 320);
    glVertex2f(60, 320);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(70, 0);
    glVertex2f(80, 0);
    glVertex2f(80, 400);
    glVertex2f(70, 400);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 0);
    glVertex2f(120, 0);
    glVertex2f(120, 250);
    glVertex2f(90, 250);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(120, 0);
    glVertex2f(150, 0);
    glVertex2f(150, 200);
    glVertex2f(120, 200);
    glEnd();

    // windows
    int x_start = 10;
    int y_start = 25;
    int y_increment = 20;
    int num_windows = 9;

    // Loop para criar as janelas em diferentes alturas
    for (int row = 0; row < 9; row++)
    {
        int y = y_start + row * y_increment;
        int x = x_start;

        for (int cont = 0; cont < num_windows; cont++)
        {
            window(x, y);
            x += 15;
        }
    }

    x_start = 40;
    y_start = 210;
    y_increment = 20;
    num_windows = 5;

    for (int row = 0; row < 2; row++)
    {
        int y = y_start + row * y_increment;
        int x = x_start;

        for (int cont = 0; cont < num_windows; cont++)
        {
            window(x, y);
            x += 15;
        }
    }
    window(75, 260);
    window(75, 280);
    window(75, 300);
}

void Tree1_Model()
{
    glPushMatrix();
    glTranslatef(10, 110, 0);
    circle(15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 100, 0);
    circle(15);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex2f(9, 70);
    glVertex2f(9, 90);
    glVertex2f(11, 90);
    glVertex2f(11, 70);
    glEnd();
}

void Tree2_Model()
{

    glPushMatrix();
    glTranslatef(30, 130, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(25, 126, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(35, 126, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30, 125, 0);
    circle(5);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex2f(29, 110);
    glVertex2f(29, 124);
    glVertex2f(31, 124);
    glVertex2f(31, 110);

    glEnd();
}

void florzinha_model()
{
    glPushMatrix();
    // LAÇO
    glColor3ub(230, 63, 34);
    glPushMatrix();
    glTranslatef(-10, 80, 0);
    glRotatef(10.0, 0.0, 0.0, 1.0);
    drawEllipseWithBorder(8, 25, 0.7);
    glPopMatrix();

    glColor3ub(230, 63, 34);
    glPushMatrix();
    glTranslatef(10, 80, 0);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    drawEllipseWithBorder(8, 25, 0.7);
    glPopMatrix();

    glColor3ub(230, 63, 34);
    glPushMatrix();
    glTranslatef(0, 68, 0);
    circle_with_border(5, 0.7);
    glPopMatrix();

    // CABELO ATRÁS
    glColor3ub(243, 105, 28);
    glPushMatrix();
    glTranslatef(0, -2, 0);
    circle_with_border(18, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(243, 105, 28);
    glVertex2f(-18, -2);
    glVertex2f(18, -2);
    glVertex2f(18, 28);
    glVertex2f(-18, 28);
    glEnd();

    // BRAÇOS
    glColor3ub(247, 206, 176);
    glPushMatrix();
    glTranslatef(-10, 12, 0);
    glRotatef(angBracoDFlorzinha, 0.0, 0.0, 1.0);
    glTranslatef(0, -10, 0);
    drawEllipseWithBorder(5, 10, 0.7);
    if (!lancar && !lado_projetil)
        desenhaEsferaComBrilho(-3, -22, escalaP);
    glPopMatrix();

    glColor3ub(247, 206, 176);
    glPushMatrix();
    glTranslatef(10, 12, 0);
    glRotatef(angBracoEFlorzinha, 0.0, 0.0, 1.0);
    glTranslatef(0, -10, 0);
    drawEllipseWithBorder(5, 10, 0.7);

    if (!lancar && lado_projetil)
        desenhaEsferaComBrilho(-0, -22, escalaP);
    glPopMatrix();

    // PERNAS
    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(-5, -24, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(-10, -22);
    glVertex2f(0, -22);
    glVertex2f(0, -12);
    glVertex2f(-10, -12);
    glEnd();

    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(6, -24, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(1, -22);
    glVertex2f(11, -22);
    glVertex2f(11, -12);
    glVertex2f(1, -12);
    glEnd();

    // TRONCO
    glBegin(GL_POLYGON);
    glColor3ub(238, 100, 166);
    glVertex2f(-15, -12);
    glVertex2f(15, -12);
    glVertex2f(10, 16);
    glVertex2f(-10, 16);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex2f(-15, -12);
    glVertex2f(15, -12);
    glVertex2f(10, 16);
    glVertex2f(-10, 16);
    glEnd();

    // CINTO
    glBegin(GL_POLYGON);
    glColor3ub(1, 1, 1);
    glVertex2f(-14, -2);
    glVertex2f(14, -2);
    glVertex2f(11, 8);
    glVertex2f(-11, 8);
    glEnd();

    // ROSTO
    glColor3ub(247, 206, 176);
    glPushMatrix();
    glTranslatef(0, 38, 0);
    circle_with_border(27, 0.7);
    glPopMatrix();

    // OLHOS
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-15, 38, 0);
    circle_with_border(12, 0.7);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(15, 38, 0);
    circle_with_border(12, 0.7);
    glPopMatrix();

    glColor3ub(238, 100, 166);
    glPushMatrix();
    glTranslatef(-13, 38, 0);
    circle_with_border(10, 0.7);
    glPopMatrix();

    glColor3ub(238, 100, 166);
    glPushMatrix();
    glTranslatef(13, 38, 0);
    circle_with_border(10, 0.7);
    glPopMatrix();

    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(-11, 38, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(11, 38, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(-8, 38, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(8, 38, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    // CABELO FRENTE
    glColor3ub(243, 105, 28);
    glPushMatrix();
    glTranslatef(-8, 38, 0);
    drawSemiEllipseWithBorder(25, 18, 8, 12, 1.0);
    glPopMatrix();

    // BOCA
    glBegin(GL_POLYGON);
    glColor3ub(1, 1, 1);
    glVertex2f(-3, 21);
    glVertex2f(3, 21);
    glVertex2f(3, 22);
    glVertex2f(-3, 22);
    glEnd();

    glPopMatrix();
}

void florzinha_queimada_model()
{
    // LAÇO
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-10, 80, 0);
    glRotatef(10.0, 0.0, 0.0, 1.0);
    drawEllipseWithBorder(8, 25, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(10, 80, 0);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    drawEllipseWithBorder(8, 25, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(0, 68, 0);
    circle_with_border(5, 0.7);
    glPopMatrix();

    // CABELO ATRÁS
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(0, -2, 0);
    circle_with_border(18, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-18, -2);
    glVertex2f(18, -2);
    glVertex2f(18, 28);
    glVertex2f(-18, 28);
    glEnd();

    // BRAÇOS
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-10, 12, 0);
    glRotatef(angBracoDFlorzinha, 0.0, 0.0, 1.0);
    glTranslatef(0, -10, 0);
    drawEllipseWithBorder(5, 10, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(18, 6, 0);
    glRotatef(angBracoEFlorzinha, 0.0, 0.0, 1.0);
    drawEllipseWithBorder(5, 10, 0.7);
    glPopMatrix();

    // PERNAS
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-5, -24, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-10, -22);
    glVertex2f(0, -22);
    glVertex2f(0, -12);
    glVertex2f(-10, -12);
    glEnd();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(6, -24, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(1, -22);
    glVertex2f(11, -22);
    glVertex2f(11, -12);
    glVertex2f(1, -12);
    glEnd();

    // TRONCO
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-15, -12);
    glVertex2f(15, -12);
    glVertex2f(10, 16);
    glVertex2f(-10, 16);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3ub(0, 0, 0);
    glVertex2f(-15, -12);
    glVertex2f(15, -12);
    glVertex2f(10, 16);
    glVertex2f(-10, 16);
    glEnd();

    // CINTO
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-14, -2);
    glVertex2f(14, -2);
    glVertex2f(11, 8);
    glVertex2f(-11, 8);
    glEnd();

    // ROSTO
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(0, 38, 0);
    circle_with_border(27, 0.7);
    glPopMatrix();

    // OLHOS
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-15, 38, 0);
    circle_with_border(12, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(15, 38, 0);
    circle_with_border(12, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-13, 38, 0);
    circle_with_border(10, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(13, 38, 0);
    circle_with_border(10, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-11, 38, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(11, 38, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-8, 38, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(8, 38, 0);
    circle_with_border(4, 0.7);
    glPopMatrix();

    // CABELO FRENTE
    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(-8, 38, 0);
    drawSemiEllipseWithBorder(25, 18, 8, 12, 1.0);
    glPopMatrix();

    // BOCA
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(-3, 21);
    glVertex2f(3, 21);
    glVertex2f(3, 22);
    glVertex2f(-3, 22);
    glEnd();
}

void model_banana(float x, float y, float angle)
{
    glColor3ub(255, 221, 51); // Amarelo
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(angle, 0, 0, 1);
    drawSemiEllipseWithBorder(20.0f, 10.0f, 100.0f, 100.0f, 1.0f);
    glPopMatrix();
}

void desenha_banana(float x, float y, bool side)
{
    if (lancar_banana && !sentinela_lado_banana_inicial)
    {
        sentinela_lado_banana_inicial = true;
        ladoBanana = side;
    }
    if (lancar_banana)
    {
        if (!ladoBanana)
        {
            glPushMatrix();
            glTranslatef(x, y, 0);
            glScalef(escalaB, escalaB, 1.0f);
            model_banana(-110, -45, -30);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(x + 50, y, 0);
            glScalef(escalaB, escalaB, 1.0f);
            glScalef(-1.0f, 1.0f, 1.0f);
            model_banana(-110, -45, -30);
            glPopMatrix();
        }
    }
    else
    {
        if (!side)
        {
            glPushMatrix();
            glTranslatef(x, y, 0);
            glScalef(escalaB, escalaB, 1.0f);
            model_banana(-110, -45, -30);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(x + 50, y, 0);
            glScalef(escalaB, escalaB, 1.0f);
            glScalef(-1.0f, 1.0f, 1.0f);
            model_banana(-110, -45, -30);
            glPopMatrix();
        }
    }
}

void nave_sobre_macaco()
{
    // Ativar transparência para o vidro
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Vidro da nave (translúcido)
    glPushMatrix();
    glColor4f(0.4f, 0.8f, 1.0f, 0.5f); // Azul claro translúcido
    glTranslatef(155, 80, 0);          // Posição sobre o macaco
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0); // Centro do vidro
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 85.0f; // Raio horizontal
        float y = sin(angle) * 95.0f; // Raio vertical
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // Borda destacada do vidro
    glPushMatrix();
    glColor3ub(180, 240, 255); // Azul mais claro para o contorno
    glTranslatef(155, 80, 0);  // Mesma posição do vidro
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 87.0f; // Raio ligeiramente maior para a borda
        float y = sin(angle) * 97.0f;
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // Desabilitar transparência após desenhar o vidro
    glDisable(GL_BLEND);

    // Base da nave
    glPushMatrix();
    glTranslatef(155, 20, 0); // Posição abaixo do vidro
    glColor3ub(128, 0, 128);  // Roxo para a base
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 85.0f; // Raio da base (oval horizontal)
        float y = sin(angle) * 20.0f; // Altura menor
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // Suporte inferior da nave
    glPushMatrix();
    glTranslatef(155, 10, 0); // Posição mais abaixo para o suporte
    glColor3ub(100, 0, 100);  // Tom mais escuro de roxo
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 65.0f; // Raio um pouco menor
        float y = sin(angle) * 12.0f; // Altura menor
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // Luzes decorativas na base da nave
    glPushMatrix();
    glTranslatef(155, 20, 0); // Posição das luzes
    for (int i = 0; i < 360; i += 30)
    { // Mais luzes, espaçadas uniformemente
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 75.0f; // Raio das luzes
        float y = sin(angle) * 20.0f;
        glColor3ub(0, 255, 255); // Azul claro para as luzes
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 30)
        { // Cada luz é um pequeno círculo
            float light_angle = j * M_PI / 180.0f;
            float lx = cos(light_angle) * 5.0f; // Tamanho do círculo
            float ly = sin(light_angle) * 5.0f;
            glVertex2f(x + lx, y + ly);
        }
        glEnd();
    }
    glPopMatrix();

    // Topo decorativo da base (anel brilhante)
    glPushMatrix();
    glTranslatef(155, 30, 0); // Posição acima da base principal
    glColor3ub(180, 0, 180);  // Roxo claro
    glBegin(GL_LINE_LOOP);    // Contorno fino
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0f;
        float x = cos(angle) * 90.0f; // Maior que a base principal
        float y = sin(angle) * 22.0f; // Contorno oval
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    // Detalhe central (suporte em forma de cone)
    glPushMatrix();
    glTranslatef(155, 0, 0); // Posição no centro da base
    glColor3ub(50, 0, 50);   // Tom escuro de roxo para o cone
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 20);    // Ponta superior do cone
    glVertex2f(-30, -20); // Base esquerda do cone
    glVertex2f(30, -20);  // Base direita do cone
    glEnd();
    glPopMatrix();
}

void macaco_model()
{
    // Capa
    glPushMatrix();
    glTranslatef(93, 0, 0);
    glBegin(GL_POLYGON);
    glColor3ub(146, 70, 113);
    glVertex2f(0, 20);
    glVertex2f(105, 20);
    glVertex2f(105, 90);
    glVertex2f(0, 90);
    glEnd();
    glPopMatrix();

    // Braço esquerdo
    glPushMatrix();
    glTranslatef(41, -30, 0);
    glBegin(GL_POLYGON);
    glColor3ub(1, 1, 1);
    glVertex2f(40, 100);
    glVertex2f(67, 100);
    glVertex2f(50, 120);
    glEnd();

    // Luva esquerda
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(40, 100);
    glVertex2f(60, 75);
    glVertex2f(67, 100);
    glEnd();
    glPopMatrix();
    // Botas
    glPushMatrix();
    glTranslatef(40, -28, 0);
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(80, 40);
    glVertex2f(100, 40);
    glVertex2f(100, 60);
    glVertex2f(90, 60);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(110, 40);
    glVertex2f(130, 40);
    glVertex2f(120, 60);
    glVertex2f(110, 60);
    glEnd();
    glPopMatrix();

    // Braço direito com hierarquia de transformações
    glPushMatrix();
    glTranslatef(170, 70, 0);           // Posição inicial do ombro
    glRotatef(angOmbro, 0.0, 0.0, 1.0); // Rotação do ombro
    glTranslatef(10, 0, 0);             // Ajuste do braço após rotação

    // Desenho do braço
    glBegin(GL_POLYGON);
    glColor3ub(1, 1, 1);
    glVertex2f(-5, 0);
    glVertex2f(30, 0);
    glVertex2f(38, 0);
    glVertex2f(30, 20);
    glVertex2f(-10, 20);
    glEnd();

    // Luva com hierarquia de transformações
    glPushMatrix();
    glTranslatef(25, 20, 0);           // Mover para o final do braço
    glRotatef(angCotovelo, 0, 0, 1.0); // Rotação do cotovelo

    // Desenho da luva
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 255);
    glVertex2f(0, 0);
    glVertex2f(15, -22);
    glVertex2f(35, 20);
    glEnd();

    glPopMatrix();
    glPopMatrix();

    // Tronco
    glPushMatrix();
    glTranslatef(39, -30, 0);
    glBegin(GL_POLYGON);
    glColor3ub(46, 24, 217);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(160, 120);
    glVertex2f(50, 120);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 255);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(120, 80);
    glVertex2f(90, 80);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(46, 24, 217);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(130, 60);
    glVertex2f(80, 60);
    glEnd();
    glPopMatrix(); // Fim da luva

    // Rosto
    glPushMatrix();
    glColor3ub(1, 1, 1);
    glTranslatef(50, -10, 0);

    glPushMatrix();
    glTranslatef(95, 110, 0);
    circle_with_border(35, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, -20, 0);
    glBegin(GL_POLYGON);
    glColor3ub(161, 189, 64);
    glVertex2f(80, 120);
    glVertex2f(135, 120);
    glVertex2f(135, 135);
    glVertex2f(115, 127);
    glVertex2f(80, 135);
    glEnd();
    glPopMatrix();

    glColor3ub(161, 189, 64);
    glTranslatef(95, 82, 0);
    drawSemiEllipseWithBorder(15, 28, 0, 0, 0.0);
    glPopMatrix();

    // Boca
    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(147, 80, 0);
    drawSemiEllipseWithBorder(8, 10, 0, 0, 0);
    glPopMatrix();

    // Olhos
    glColor3ub(220, 170, 196);
    glPushMatrix();
    glTranslatef(135, 98, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(220, 168, 196);
    glPushMatrix();
    glTranslatef(163, 98, 0);
    circle_with_border(8, 0.7);
    glPopMatrix();

    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(137, 99, 0);
    circle_with_border(5, 0.7);
    glPopMatrix();

    glColor3ub(1, 1, 1);
    glPushMatrix();
    glTranslatef(164, 99, 0);
    circle_with_border(5, 0.7);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(138, 100, 0);
    circle_with_border(3, 0.7);
    glPopMatrix();

    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(165, 101, 0);
    circle_with_border(3, 0.7);
    glPopMatrix();

    // Chapéu
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(145, 107, 0);
    drawSemiEllipseWithBorder(35, 60, 0, 0, 1.0);
    glPopMatrix();

    glColor3ub(146, 70, 113);
    glPushMatrix();
    glTranslatef(164, 117, 0);
    circle_with_border(2, 0.7);
    glPopMatrix();

    glColor3ub(146, 70, 113);
    glPushMatrix();
    glTranslatef(140, 117, 0);
    circle_with_border(2, 0.7);
    glPopMatrix();

    glColor3ub(146, 70, 113);
    glPushMatrix();
    glTranslatef(152, 127, 0);
    circle_with_border(3, 0.7);
    glPopMatrix();

    if (pontuacao_florzinha < NIVEL_2 && vidaNave > 0)
    {
        nave_sobre_macaco();
    }
}

void macaco_queimado_model()
{

    glColor3ub(0, 0, 0);
    // Capa
    glPushMatrix();
    glTranslatef(93, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 20);
    glVertex2f(105, 20);
    glVertex2f(105, 90);
    glVertex2f(0, 90);
    glEnd();
    glPopMatrix();

    // Braço esquerdo
    glPushMatrix();
    glTranslatef(41, -30, 0);
    glBegin(GL_POLYGON);
    glVertex2f(40, 100);
    glVertex2f(67, 100);
    glVertex2f(50, 120);
    glEnd();

    // Luva esquerda
    glBegin(GL_POLYGON);
    glVertex2f(40, 100);
    glVertex2f(60, 75);
    glVertex2f(67, 100);
    glEnd();
    glPopMatrix();
    // Botas
    glPushMatrix();
    glTranslatef(40, -28, 0);
    glBegin(GL_POLYGON);
    glVertex2f(80, 40);
    glVertex2f(100, 40);
    glVertex2f(100, 60);
    glVertex2f(90, 60);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(110, 40);
    glVertex2f(130, 40);
    glVertex2f(120, 60);
    glVertex2f(110, 60);
    glEnd();
    glPopMatrix();

    // Braço direito com hierarquia de transformações
    glPushMatrix();
    glTranslatef(170, 70, 0);           // Posição inicial do ombro
    glRotatef(angOmbro, 0.0, 0.0, 1.0); // Rotação do ombro
    glTranslatef(10, 0, 0);             // Ajuste do braço após rotação

    // Desenho do braço
    glBegin(GL_POLYGON);
    glVertex2f(-5, 0);
    glVertex2f(30, 0);
    glVertex2f(38, 0);
    glVertex2f(30, 20);
    glVertex2f(-10, 20);
    glEnd();

    // Luva com hierarquia de transformações
    glPushMatrix();
    glTranslatef(25, 20, 0);           // Mover para o final do braço
    glRotatef(angCotovelo, 0, 0, 1.0); // Rotação do cotovelo

    // Desenho da luva
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0);
    glVertex2f(15, -22);
    glVertex2f(35, 20);
    glEnd();

    glPopMatrix();
    glPopMatrix();

    // Tronco
    glPushMatrix();
    glTranslatef(39, -30, 0);
    glBegin(GL_POLYGON);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(160, 120);
    glVertex2f(50, 120);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(120, 80);
    glVertex2f(90, 80);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(90, 75);
    glVertex2f(120, 75);
    glVertex2f(130, 60);
    glVertex2f(80, 60);
    glEnd();
    glPopMatrix(); // Fim da luva

    // Rosto
    glPushMatrix();
    glTranslatef(50, -10, 0);

    glPushMatrix();
    glTranslatef(95, 110, 0);
    circle_with_border(35, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10, -20, 0);
    glBegin(GL_POLYGON);
    glVertex2f(80, 120);
    glVertex2f(135, 120);
    glVertex2f(135, 135);
    glVertex2f(115, 127);
    glVertex2f(80, 135);
    glEnd();
    glPopMatrix();

    glTranslatef(95, 82, 0);
    drawSemiEllipseWithBorder(15, 28, 0, 0, 0.0);
    glPopMatrix();

    // Chapéu
    glPushMatrix();
    glTranslatef(145, 107, 0);
    drawSemiEllipseWithBorder(35, 60, 0, 0, 1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(164, 117, 0);
    circle_with_border(2, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(140, 117, 0);
    circle_with_border(2, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(152, 127, 0);
    circle_with_border(3, 0.7);
    glPopMatrix();
}

//----------------------------FUNCOES DE TRANSLAÇÃO---------------------------

void tower(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    tower_model();
    glPopMatrix();
}

void window(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    window_model();
    glPopMatrix();
}

void buildin1(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    buildin1_model();
    glPopMatrix();
}

void buildin2(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    buildin2_model();
    glPopMatrix();
}
void buildin3(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    buildin3_model();
    glPopMatrix();
}

void buildin4(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    buildin4_model();
    glPopMatrix();
}

void buildin5(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    buildin5_model();
    glPopMatrix();
}

void roadLine(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    roadLine_model();
    glPopMatrix();
}

void cloud(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    cloud_model();
    glPopMatrix();
}

void cloud_Modify(double x, double y, double escalaNuvem)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(escalaNuvem, escalaNuvem, 1);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    cloud_model();
    glPopMatrix();
}

void Tree1(double x, double y)
{
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(x, y, 0);
    Tree1_Model();
    glPopMatrix();
}

void Tree2(double x, double y)
{
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(x, y, 0);
    Tree2_Model();
    glPopMatrix();
}

void florzinha(double x, double y, double escala)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(escala, escala, 1); // Aplica escala
    florzinha_model();

    glPopMatrix();
}

void florzinha_queimada(double x, double y, double escala)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(escala, escala, 1); // Aplica escala
    florzinha_queimada_model();
    glPopMatrix();
}

void macaco(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    macaco_model();
    glPopMatrix();
}

void macaco_queimado(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    macaco_queimado_model();
    glPopMatrix();
}

void recalculaAngProjetilBracoD(float ang)
{
    float angRad = -ang * (M_PI / 180.0f); // Converte o ângulo para radianos

    // Define o comprimento do braço
    float comprimentoBraco = 22.0f; // Ajuste conforme necessário

    // Calcula a posição inicial do projétil com base na rotação e posição do braço direito
    posicaoX_inicial = posX_florzinha - 10 + comprimentoBraco * sin(angRad);
    posicaoY_inicial = posY_florzinha + 10 - comprimentoBraco * cos(angRad);

    // Calcula as velocidades iniciais do projétil
    float velocidade_inicial = 200.0f;
    velocidade_inicial_x = velocidade_inicial * sin(angRad);
    velocidade_inicial_y = velocidade_inicial * cos(angRad);
}

void recalculaAngProjetilBracoE(float ang)
{
    float angRad = ang * (M_PI / 180.0f); // Converte o ângulo para radianos

    // Define o comprimento do braço
    float comprimentoBraco = 22.0f; // Ajuste conforme necessário

    // Calcula a posição inicial do projétil com base na rotação e posição do braço esquerdo
    posicaoX_inicial = posX_florzinha + 50 + comprimentoBraco * sin(angRad);
    posicaoY_inicial = posY_florzinha + 10 - comprimentoBraco * cos(angRad);

    // Calcula as velocidades iniciais do projétil
    float velocidade_inicial = 200.0f;
    velocidade_inicial_x = velocidade_inicial * sin(angRad);
    velocidade_inicial_y = velocidade_inicial * cos(angRad);
}

void desenha_macaco()
{
    if (!vitoriaFlorzinha)
    {
        if (posX_florzinha < posX_macaco)
        {
            glPushMatrix();
            glTranslatef(posX_macaco + 300, posY_macaco, 0);
            glScalef(-1.0f, 1.0f, 1.0f); // Espelha horizontalmente
            macaco_model();
            glPopMatrix();
            desenha_banana(posXInicialBanana, posYInicialBanana, true);
        }
        else
        {
            macaco(posX_macaco, posY_macaco);
            desenha_banana(posXInicialBanana, posYInicialBanana, false);
        }
    }
    else
    {
        if (posX_florzinha < posX_macaco)
        {
            glPushMatrix();
            glTranslatef(posX_macaco + 300, posY_macaco, 0);
            glScalef(-1.0f, 1.0f, 1.0f); // Espelha horizontalmente
            macaco_queimado_model();
            glPopMatrix();
            desenha_banana(posXInicialBanana, posYInicialBanana, true);
        }
        else
        {
            macaco_queimado(posX_macaco, posY_macaco);
            desenha_banana(posXInicialBanana, posYInicialBanana, false);
        }
    }
}

//----------- Funções de tratamento de eventos do teclado
void Teclado(unsigned char tecla, int x, int y)
{
    if (!exibindoMensagemVitoria)
    {
        if (tecla == 32 && !lancar && !animando)
        {

            lancar = true;
            tempo = 0.0f;
            if (!lado_projetil)
            {
                recalculaAngProjetilBracoD(angBracoDFlorzinha);
            }
            else
            {
                recalculaAngProjetilBracoE(angBracoEFlorzinha);
            }
        }
        switch (tecla)
        {        // quando a tecla ESC (keycode=27) for pressionada
        case 27: // o programa deverá ser finalizado
            exit(0);
            break;
        case 'W':
        case 'w':
            if (!lado_projetil)
            {
                angBracoDFlorzinha = fmax(angBracoDFlorzinha - 10, angBracoMaxFlorzinha);
            }
            else
            {
                angBracoEFlorzinha = fmin(angBracoEFlorzinha + 10, -angBracoMaxFlorzinha);
            }
            break;
        case 'S':
        case 's':
            if (!lado_projetil)
            {
                angBracoDFlorzinha = fmin(angBracoDFlorzinha + 10, angBracoMinFlorzinha);
            }
            else
            {
                angBracoEFlorzinha = fmax(angBracoEFlorzinha - 10, -angBracoMinFlorzinha);
            }
            break;
        case 'd':
        case 'D':
            if (!lancar)
            {
                lado_projetil = true;
                angBracoDFlorzinha = -45.0f;
                velocidade_inicial_x = VEL_INICIAL;
                velocidade_inicial_y = VEL_INICIAL;
                reseta_projetil();
            }
            break;
        case 'a':
        case 'A':
            if (!lancar)
            {
                lado_projetil = false;
                angBracoEFlorzinha = 45.0f;
                velocidade_inicial_x = VEL_INICIAL;
                velocidade_inicial_y = VEL_INICIAL;
                reseta_projetil();
            }
            break;
        }
    }
}

void TeclasEspeciais(int tecla, int x, int y)
{
    GLfloat desloc = 7;
    GLfloat incrementoEscala = 0.1; // Quantidade para aumentar/diminuir a escala

    if (!exibindoMensagemVitoria)
    {

        switch (tecla)
        {                    // Verifica se alguma tecla é pressionada
        case GLUT_KEY_RIGHT: // Seta direcional direita
            posX_florzinha += desloc;
            atualizaBoundingBoxeProjetil(posX, posY);
            atualizaBoundingBoxeFlorzinha(posX_florzinha, posY_florzinha);
            if (!lancar)
                posX += desloc; // Move o projétil se não estiver sendo lançado
            break;
        case GLUT_KEY_LEFT: // Seta direcional esquerda
            posX_florzinha -= desloc;
            atualizaBoundingBoxeProjetil(posX, posY);
            atualizaBoundingBoxeFlorzinha(posX_florzinha, posY_florzinha);
            if (!lancar)
                posX -= desloc; // Move o projétil se não estiver sendo lançado
            break;
        case GLUT_KEY_UP: // Seta direcional cima
            posY_florzinha += desloc;
            atualizaBoundingBoxeProjetil(posX, posY);
            atualizaBoundingBoxeFlorzinha(posX_florzinha, posY_florzinha);
            if (!lancar)
                posY += desloc; // Move o projétil se não estiver sendo lançado
            break;
        case GLUT_KEY_DOWN: // Seta direcional baixo
            posY_florzinha = fmax(posY_florzinha - desloc, 70);
            if (posY_florzinha != 70)
            {
                atualizaBoundingBoxeProjetil(posX, posY);
                atualizaBoundingBoxeFlorzinha(posX_florzinha, posY_florzinha);
                if (!lancar)
                    posY -= desloc; // Move o projétil se não estiver sendo lançado
            }

            break;
        case GLUT_KEY_PAGE_UP: // PgUp para aumentar a escala
            escala += incrementoEscala;
            break;
        case GLUT_KEY_PAGE_DOWN:                                                           // PgDown para diminuir a escala
            escala = (escala - incrementoEscala > 0) ? escala - incrementoEscala : escala; // Evita escala negativa
            break;
        case GLUT_KEY_F1: // Aumentar o ângulo do
            angOmbro = fmax(angOmbro - 5, angOmbroMin);
            if (!lancar_banana)
            {
                deslocP_Y_banana = deslocP_Y_banana - 5;
                angBanana = angBanana - 5;
            }
            break;
        case GLUT_KEY_F2: // Diminuir o ângulo do ombro
            angOmbro = fmin(angOmbro + 5, angOmbroMax);
            if (!lancar_banana)
            {
                deslocP_Y_banana = deslocP_Y_banana + 5;
                angBanana = angBanana + 5;
            }

            break;
        case GLUT_KEY_F3: // Aumentar o ângulo do cotovelo
            angCotovelo = fmax(angCotovelo - 5, angCotoveloMin);
            break;
        case GLUT_KEY_F4: // Diminuir o ângulo do cotovelo
            angCotovelo = fmin(angCotovelo + 5, angCotoveloMax);
            break;
        case GLUT_KEY_F5: // Aumentar o ângulo do cotovelo
            angBanana = angBanana - 5;
            break;
        case GLUT_KEY_F6: // Diminuir o ângulo do cotovelo
            angBanana = angBanana + 5;
            break;
        }
    }

    glutPostRedisplay(); // Chama a função display novamente, fazendo com
                         // que a janela corrente seja redesenhada
}
