#include <iostream>
#include <windows.h>
#include <D:/Softwares/Instalan VS/freeglut/include/GL/glut.h> //Ini sesuaikan ya hehe

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

float panjang = 1.0f;
float lebar = 1.0f;
float tinggi = 1.0f;

float rotasiY = 0.0f;
float rotasiX = 0.0f;

float lightPosX = 0.0f, lightPosY = 5.0f, lightPosZ = 0.0f;

float cammanX = -7.75f, cammanY = 0.3f, cammanZ = 4.9f;  // Position de la cammanera
float cammanYaw = 90.0f, cammanPitch = 0.0f;         // That Direcktion
float cammanTargetX = 0.0f, cammanTargetY = 0.0f, cammanTargetZ = 0.0f;  // Targetto

void barrelTank(float radius, float height, int segments) {
    // === SOLID CYLINDER ===
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat cylinder_ambient[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    GLfloat cylinder_diffuse[] = { 0.4f, 0.2f, 0.1f, 1.0f };
    GLfloat cylinder_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, cylinder_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cylinder_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cylinder_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

    glColor3f(0.4, 0.4, 0.4);

    float angleStep = 2.0f * 3.14159f / segments;

    // Sisi samping (solid)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        glVertex3f(x, 0.0f, z);
        glVertex3f(x, height, z);
    }
    glEnd();

    // Tutup bawah (solid)
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius);
    }
    glEnd();

    // Tutup atas (solid)
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, height, sin(angle) * radius);
    }
    glEnd();

    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }

    // === WIREFRAME OVERLAY ===
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.25f, 0.15f);
    glLineWidth(2.5f);

    // Garis vertikal
    glBegin(GL_LINES);
    for (int i = 0; i < segments; i += 2) { // Setiap 2 segmen agar tidak terlalu padat
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;

        glVertex3f(x, 0.0f, z);
        glVertex3f(x, height, z);
    }
    glEnd();

    // Lingkaran bawah (wire)
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, 0.0f, sin(angle) * radius);
    }
    glEnd();

    // Lingkaran atas (wire)
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, height, sin(angle) * radius);
    }
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}
void barrel(void) {
    glColor3f(0.4, 0.4, 0.4);
    barrelTank(0.2f, 3.0f, 32);
}
void tireTank(float radius, float width, int segments) {
    // === SOLID TIRE ===
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat tire_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat tire_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat tire_specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, tire_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, tire_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, tire_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 2.0f);

    glColor3f(0.1f, 0.1f, 0.1f);

    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotasi ke posisi vertikal

    float angleStep = 2.0f * 3.14159f / segments;

    // Sisi samping ban (solid)
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glVertex3f(x, y, -width / 2);
        glVertex3f(x, y, width / 2);
    }
    glEnd();

    // Tutup samping (solid)
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, width / 2);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float angle = i * angleStep;
        glVertex3f(cos(angle) * radius, sin(angle) * radius, -width / 2);
    }
    glEnd();

    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }

    // === WIREFRAME OVERLAY ===
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(2.5f);

    // Garis melingkar (sisi luar)
    for (float w = -width / 2; w <= width / 2; w += width) {
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i += 2) {
            float angle = i * angleStep;
            glVertex3f(cos(angle) * radius, sin(angle) * radius, w);
        }
        glEnd();
    }

    // Garis radial (pola jari-jari)
    glBegin(GL_LINES);
    for (int i = 0; i < segments; i += 4) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        glVertex3f(x, y, -width / 2);
        glVertex3f(x, y, width / 2);
    }
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);

    glPopMatrix();
}
void tire(void) {
    glColor3f(0.2, 0.2, 0.2);

    tireTank(0.5f, 0.2f, 32);
}

void teks(void* font, const char* string, float lineWidth = 3.0f) {
    glPushMatrix();
    glScalef(0.002f, 0.002f, 0.002f);

    glLineWidth(lineWidth);

    for (const char* c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }

    glLineWidth(1.0f);
    glPopMatrix();
}
void teks3D(void) {
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat text_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat text_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat text_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, text_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, text_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, text_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0f);

    glColor3f(0.8f, 0.8f, 0.8f);

    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    teks(GLUT_STROKE_ROMAN, "FISIPOL");

    glPopMatrix();

    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }
}
void bobolaapi(void) {
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 0.0f);

    glPushMatrix();
    glScalef(0.2f, 0.2f, 0.2f);
    glutWireCube(1.0f);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}
void daratan(void) {
    glDisable(GL_LIGHTING);

    glColor3f(0.6f, 0.6f, 0.6f);

    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();

    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for (float z = -10.0f; z <= 10.0f; z += 0.2f) {
        glVertex3f(-10.0f, 0.01f, z);
        glVertex3f(10.0f, 0.01f, z);
    }
    for (float x = -10.0f; x <= 10.0f; x += 0.2f) {
        glVertex3f(x, 0.01f, -10.0f);
        glVertex3f(x, 0.01f, 10.0f);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}
void fisipol(void) {
    glDisable(GL_LIGHTING);

    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glEnd();

    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);
    for (float z = -10.0f; z <= 10.0f; z += 0.2f) {
        glVertex3f(-10.0f, 0.01f, z);
        glVertex3f(10.0f, 0.01f, z);
    }
    for (float x = -10.0f; x <= 10.0f; x += 0.2f) {
        glVertex3f(x, 0.01f, -10.0f);
        glVertex3f(x, 0.01f, 10.0f);
    }
    glEnd();

    glEnable(GL_LIGHTING);
}
void kameraman() {
    // Hitung target berdasarkan yaw dan pitch kamera
    cammanTargetX = cammanX + sin(cammanYaw * 3.14159f / 180.0f) * cos(cammanPitch * 3.14159f / 180.0f);
    cammanTargetY = cammanY + sin(cammanPitch * 3.14159f / 180.0f);
    cammanTargetZ = cammanZ - cos(cammanYaw * 3.14159f / 180.0f) * cos(cammanPitch * 3.14159f / 180.0f);
}
void cream(void) {
    GLfloat prev_specular[4], prev_shininess[1];
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);

    // Set material untuk cream - tidak reflektif
    GLfloat cream_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat cream_shininess[] = { 5.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, cream_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, cream_shininess);

    glColor3f(0.95f, 0.87f, 0.68f);
    glScalef(panjang, tinggi, lebar);
    glutSolidCube(1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);
}
void creamTank(void) {
    glDisable(GL_LIGHTING);

    glColor3f(0.3f, 0.25f, 0.15f);

    glLineWidth(3.0f);

    glScalef(panjang, tinggi, lebar);

    glutWireCube(1.0f);

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}
void cokelat(void) {
    GLfloat prev_specular[4], prev_shininess[1];
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);

    GLfloat brown_diffuse[] = { 0.396f, 0.263f, 0.129f, 1.0f };
    GLfloat brown_specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat brown_shininess[] = { 5.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brown_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brown_shininess);

    glColor3f(0.396f, 0.263f, 0.129f);
    glScalef(panjang, tinggi, lebar);
    glutSolidCube(1);
}
void cokelaterang(void) {
    GLfloat prev_specular[4], prev_shininess[1];
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);

    GLfloat brown_orange_diffuse[] = { 0.648f, 0.3315f, 0.1145f, 1.0f };
    GLfloat brown_orange_specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat brown_orange_shininess[] = { 5.0f };

    glMaterialfv(GL_FRONT, GL_DIFFUSE, brown_orange_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, brown_orange_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, brown_orange_shininess);

    glColor3f(0.648f, 0.3315f, 0.1145f);
    glScalef(panjang, tinggi, lebar);
    glutSolidCube(1);
}
void mesh(void) {
    GLfloat prev_specular[4], prev_shininess[1];
    glGetMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glGetMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);

    GLfloat dark_specular[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat dark_shininess[] = { 2.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, dark_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, dark_shininess);

    glColor3f(0.2f, 0.2f, 0.2f);

    glLineWidth(8.0f);
    glScalef(panjang, tinggi, lebar);

    glutWireCube(1.0f);

    glBegin(GL_LINES);
    for (float y = -0.5f; y <= 0.5f; y += 0.25f) {
        glVertex3f(-0.5f, y, 0.5f);
        glVertex3f(0.5f, y, 0.5f);

        glVertex3f(-0.5f, y, -0.5f);
        glVertex3f(0.5f, y, -0.5f);

        glVertex3f(-0.5f, y, -0.5f);
        glVertex3f(-0.5f, y, 0.5f);

        glVertex3f(0.5f, y, -0.5f);
        glVertex3f(0.5f, y, 0.5f);
    }

    glEnd();

    glLineWidth(1.0f);

    glMaterialfv(GL_FRONT, GL_SPECULAR, prev_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, prev_shininess);
}
void gentengtrapesium(void) {
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat orange_ambient[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_diffuse[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, orange_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

    glBegin(GL_QUADS);
    // Trapesium Kanan-Kiri
    glVertex3f(0.5f, 0.0f, -0.5f); //Kanan
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.3f);
    glVertex3f(0.0f, 1.0f, -0.3f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Kiri
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.3f);
    glVertex3f(0.0f, 1.0f, -0.3f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Bawah
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();

    // Segitiga Depan-Belakang
    glBegin(GL_TRIANGLES); //Depan
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.3f);


    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.0f, 1.0f, -0.3f);
    glEnd();

    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }
}
void garisAtap(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.15f, 0.08f, 0.0f);
    glLineWidth(3.0f);

    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, -0.5f);

    glVertex3f(0.0f, 1.0f, -0.3f);

    glVertex3f(0.0f, 1.0f, 0.3f);

    glVertex3f(-0.5f, 0.0f, 0.5f);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(0.0f, 1.0f, -0.3f);
    glVertex3f(0.5f, 0.0f, -0.5f);

    glVertex3f(0.0f, 1.0f, 0.3f);
    glVertex3f(0.5f, 0.0f, 0.5f);

    glVertex3f(0.0f, 1.0f, 0.3f);
    glVertex3f(0.0f, 1.0f, -0.3f);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}
void gentengKotak(void) {
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat orange_ambient[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_diffuse[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, orange_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

    glBegin(GL_QUADS);
    // Trapesium Kanan-Kiri
    glVertex3f(0.5f, 0.0f, -0.5f); //Kanan
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, -0.4f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Kiri
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(-0.4f, 1.0f, 0.4f);
    glVertex3f(-0.4f, 1.0f, -0.4f);

    glVertex3f(-0.5f, 0.0f, 0.5f); //Depan
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(-0.4f, 1.0f, 0.4f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Belakang
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.4f, 1.0f, -0.4f);
    glVertex3f(-0.4f, 1.0f, -0.4f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Bawah
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);

    glVertex3f(-0.4f, 1.0f, -0.4f); //Atas
    glVertex3f(-0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, -0.4f);
    glEnd();


    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }
}
void garisAtapKotak(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.15f, 0.08f, 0.0f);
    glLineWidth(3.0f);

    //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.5f, 0.0f, -0.5f); 
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, -0.4f);
    glEnd();

    // Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(-0.4f, 1.0f, 0.4f);
    glVertex3f(-0.4f, 1.0f, -0.4f);
    glEnd();

    // Depan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(-0.4f, 1.0f, 0.4f);
    glEnd();

    // Belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.4f, 1.0f, -0.4f);
    glVertex3f(-0.4f, 1.0f, -0.4f);
    glEnd();

    // Bawah
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();

    // Atas
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.4f, 1.0f, -0.4f);
    glVertex3f(-0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, 0.4f);
    glVertex3f(0.4f, 1.0f, -0.4f);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}
void gentengsegitiga(void) {
    GLboolean colorMaterialEnabled;
    glGetBooleanv(GL_COLOR_MATERIAL, &colorMaterialEnabled);
    glDisable(GL_COLOR_MATERIAL);

    GLfloat orange_ambient[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_diffuse[] = { 0.9f, 0.4f, 0.1f, 1.0f };
    GLfloat orange_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, orange_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, orange_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, orange_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 5.0f);

    glBegin(GL_TRIANGLES);
    // Trapesium Kanan-Kiri
    glVertex3f(0.5f, 0.0f, -0.5f); //Kanan
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-0.5f, 0.0f, -0.5f); //Kiri
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
 
    glBegin(GL_TRIANGLES); //Depan
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);


    glVertex3f(-0.5f, 0.0f, -0.5f); //Belakang
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-0.5f, 0.0f, -0.5f); //Bawah
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();

    if (colorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
    }
}
void garisAtapLimas(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.15f, 0.08f, 0.0f);
    glLineWidth(3.0f);

    //Kanan
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Kiri
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Depan
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Belakang
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    // Bawah
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    glEnd();

    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}
void jendela(void) {
    glColor4f(0.7f, 0.8f, 0.9f, 1.0f);
    glScalef(panjang, tinggi, lebar);
    glutSolidCube(1.0f);
}
void frame(void) {
    glDisable(GL_LIGHTING);
    glColor3f(0.3f, 0.2f, 0.1f);
    glLineWidth(2.5f);
    glScalef(panjang, tinggi, lebar);
    glutWireCube(1.0f);
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat LightPosition[] = { lightPosX, lightPosY, lightPosZ, 1.0f };

    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
    glPopMatrix();

    // Kamera
    kameraman();
    gluLookAt
        (cammanX, cammanY, cammanZ,           // Posisi
        cammanTargetX, cammanTargetY, cammanTargetZ, 0.0f, 1.0f, 0.0f);  // Arah

    //Disini bang
    
    glPushMatrix();
    glScalef(16.5, 0.05, 2);
    glTranslatef(0.07f, -6.5f, 2.5f);
    cream();
        glPushMatrix();
            glScalef(0.125, 1, 6.25);
            glTranslatef(3.5f, 0.0f, 0.5f);
            cream();
        glPopMatrix();
        glPushMatrix();
            glScalef(0.25, 1, 1);
            glTranslatef(2.5f, 0.0f, 2.5f);
            cream();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(2, 0.05, 1);
    glTranslatef(-1.25, -6, 2);
    cream();
        glPushMatrix();
            glScalef(0.75, 10, 0.2);
            glTranslatef(0,0,0);
            cokelat();
            glPushMatrix();
            glScalef(1,1,1);
            glRotatef(-90, 1, 0, 0);
            glRotatef(180, 0, 0, 1);
            glTranslatef(0.45, -1.4, 0.15);
            teks3D();
            glPopMatrix();
        glPopMatrix();
        
    glPopMatrix();

    

    glPushMatrix();
    glScalef(2, 1.1, 2);
    glTranslatef(0.0f, -0.3f, 0.0f);
    daratan();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.15, 1.1, 0.1);
    glTranslatef(29.5f, -0.29f, -46.0f);
    daratan();
    glPopMatrix();

    glPushMatrix();
    glScalef(1, 1.1, 0.5);
    glTranslatef(3.0f, -0.295f, -2.0f);
    fisipol();
    glPopMatrix();

    glPushMatrix();
    glScalef(14, 0.125, 0.75);
    glTranslatef(0.335, -3, -4.25);
    cokelat(); //Jalan Gedung E Kekanan
    glPopMatrix();

    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glTranslatef(5, 0.375, 7.5);
        glScalef(2, 2, 2);
            glPushMatrix(); //Tank I
                glPushMatrix(); //Body
                glScalef(0.25, 0.1, 0.5);
                glTranslatef(0, -2.05, 0.125);
                cream();
                creamTank();
                    glPushMatrix(); //Smoke;
                        glScalef(0.4, 0.25, 0.2);
                        glTranslatef(0.45, -1, 2.75);
                        barrel();
                        glPushMatrix(); //Smoke;
                            glScalef(0.5, 0.5, 0.5);
                            glTranslatef(0,5 , 0);
                            barrel();
                        glPopMatrix();
                    glPopMatrix();

                    glPushMatrix(); //Smoke;
                        glScalef(0.4, 0.25, 0.2);
                        glTranslatef(-0.45, -1, 2.75);
                        barrel();
                        glPushMatrix(); //Smoke;
                            glScalef(0.5, 0.5, 0.5);
                            glTranslatef(0, 5, 0);
                            barrel();
                        glPopMatrix();
                    glPopMatrix();

                    glPushMatrix(); //Driver View Port
                    glScalef(0.25, 0.4, 0.1);
                    glTranslatef(-0.8, 0.3, -4.75);
                    cream();
                    creamTank();
                        glPushMatrix(); //Driver View Port
                            glScalef(0.8, 0.04, 0.3);
                            glTranslatef(0,2,-1.5);
                            cokelat();
                            creamTank();
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                glRotatef(5, 1, 0, 0);
                    glPushMatrix(); //Slanted SidePlate
                    glRotatef(-30, 0, 0, 1);
                    glScalef(0.05, 0.001, 0.5);
                    glTranslatef(4.75, -110, 0.15);
                
                    cream();
                    creamTank();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-0.2, 0, 0);
                glRotatef(5, 1, 0, 0);
                    glPushMatrix(); //Slanted SidePlate
                    glRotatef(30, 0, 0, 1);
                    glScalef(0.05, 0.001, 0.5);
                    glTranslatef(-1.25, -210, 0.15);
                
                    cream();
                    creamTank();
                    glPopMatrix();
                glPopMatrix();
                
                glPushMatrix(); //Lower Glacis
                glScalef(0.25, 0.0625, 0.1);
                    glPushMatrix();
                        glScalef(1, 1, 1);
                        glTranslatef(0, -3.65, -2);
                        glRotatef(-15, 1, 0, 0);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix();
                        glScalef(1, 1, 1);
                        glTranslatef(0, -3.8, -2.2);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix();
                        glScalef(1, 1, 1);
                        glTranslatef(0, -4, -2);
                        cream();
                        creamTank();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix(); //Turret
                glScalef(0.15, 0.125, 0.2);
                glTranslatef(0, -1.2, 0.2);
                cream();
                creamTank();
                    glPushMatrix();
                        glScalef(1, 0.2, 1);
                        glTranslatef(-0.4, 0.2, 0.2);
                        barrel(); //Cupola
                    glPopMatrix();
                    glPushMatrix(); //Front
                        glScalef(1, 0.5, 0.75);
                        glTranslatef(0, 0.5, -0.35);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix(); //Front
                        glScalef(0.8, 0.4, 0.25);
                        glTranslatef(0, 0.6, -2.25);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix(); //Side-Left
                        glRotatef(-10, 0, 1, 0);
                        glScalef(0.5, 1, 1);
                        glTranslatef(-0.75, 0, 0);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix(); //Side-Right
                        glRotatef(10, 0, 1, 0);
                        glScalef(0.5, 1, 1);
                        glTranslatef(0.75, 0, 0);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix(); //Back
                        glScalef(0.75, 0.45, 0.45);
                        glTranslatef(0, 0.5, 1.35);
                        cream();
                        creamTank();
                    glPopMatrix();

                    glPushMatrix();
                        glScalef(0.5, 0.5, 0.5);
                        glRotatef(270, 1, 0, 0);
                        glTranslatef(0, -0.5, 0.5);
                        barrel();
                        glPushMatrix();
                            glScalef(0.5, 1.25, 0.5);
                            glTranslatef(0, 2,0);
                            barrel();
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(0.9, 0.25, 0.9);
                            glTranslatef(0,24,0);
                            barrel(); //Muzzle Brake
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
                
                glPushMatrix();
                
                glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21,-7);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25,-0.5);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5,10);
                cream();
                creamTank();
                glPopMatrix();

                glPopMatrix();
                glPushMatrix();
                glTranslatef(-0.275, 0, 0);
                glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21,-7);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25,-0.5);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
                glPopMatrix();

                glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5,10);
                cream();
                creamTank();
                glPopMatrix();

                glPopMatrix();
                    glPushMatrix(); //Tire - L
                    glRotatef(90, 0, 0, 1);
                    glScalef(0.1,0.1,0.1);
                    glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                    tire(); //Drive Wheel
                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5,0,0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire I
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5, -0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire I - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5,0,2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire II
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5, -0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire II - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5,0,3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire III
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5, -0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire III - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1,1,1);
                            glTranslatef(-0.5,0,4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire IV
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0.275, 0, 0);
                    glPushMatrix(); //Tire - L
                        glRotatef(90, 0, 0, 1);
                        glScalef(0.1, 0.1, 0.1);
                        glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                        tire(); //Drive Wheel
                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire I
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire I - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire II
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire II - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire III
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire III - R
                        glPopMatrix();

                        glPushMatrix();
                            glColor3f(0.4, 0.4, 0.4);
                            glScalef(1, 1, 1);
                            glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                            tire(); //Tire IV
                        glPopMatrix();
                    glPopMatrix();
                glPopMatrix();
            glPopMatrix();

    glPopMatrix();

    glPushMatrix(); //Tank 2
        glRotatef(270, 0, 1, 0);
        glTranslatef(5, 0.375, 3);
        glScalef(2, 2, 2);
        glPushMatrix(); //Tank
            glPushMatrix(); //Body
                glScalef(0.25, 0.1, 0.5);
                glTranslatef(0, -2.05, 0.125);
                cream();
                creamTank();
                glPushMatrix(); //Smoke;
                    glScalef(0.4, 0.25, 0.2);
                    glTranslatef(0.45, -1, 2.75);
                    barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix(); //Smoke;
                glScalef(0.4, 0.25, 0.2);
                glTranslatef(-0.45, -1, 2.75);
                barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

            glPushMatrix(); //Driver View Port
                glScalef(0.25, 0.4, 0.1);
                glTranslatef(-0.8, 0.3, -4.75);
                cream();
                creamTank();
                glPushMatrix(); //Driver View Port
                    glScalef(0.8, 0.04, 0.3);
                    glTranslatef(0, 2, -1.5);
                    cokelat();
                    creamTank();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(-30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(4.75, -110, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-0.2, 0, 0);
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(-1.25, -210, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix(); //Lower Glacis
            glScalef(0.25, 0.0625, 0.1);
            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.65, -2);
                glRotatef(-15, 1, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.8, -2.2);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -4, -2);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Lower Glacis End

         glPushMatrix(); //Turret
            glScalef(0.15, 0.125, 0.2);
            glTranslatef(0, -1.2, 0.2);
            cream();
            creamTank();
            glPushMatrix();
                glScalef(1, 0.2, 1);
                glTranslatef(-0.4, 0.2, 0.2);
                barrel(); //Cupola
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(1, 0.5, 0.75);
                glTranslatef(0, 0.5, -0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(0.8, 0.4, 0.25);
                glTranslatef(0, 0.6, -2.25);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Left
                glRotatef(-10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(-0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Right
                glRotatef(10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Back
                glScalef(0.75, 0.45, 0.45);
                glTranslatef(0, 0.5, 1.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(0.5, 0.5, 0.5);
                glRotatef(270, 1, 0, 0);
                glTranslatef(0, -0.5, 0.5);
                barrel();
                glPushMatrix();
                    glScalef(0.5, 1.25, 0.5);
                    glTranslatef(0, 2, 0);
                    barrel();
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.9, 0.25, 0.9);
                    glTranslatef(0, 24, 0);
                    barrel(); //Muzzle Brake
                glPopMatrix();
            glPopMatrix();
         glPopMatrix(); //Turret End

         glPushMatrix();//Track Seq

            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq End

         glPushMatrix();
            glTranslatef(-0.275, 0, 0);
            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq II End

         glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.275, 0, 0);
            glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        glPopMatrix(); 
    glPopMatrix();//Tank 2

    glPushMatrix(); //Tank 3
        glRotatef(180, 0, 1, 0);
        glTranslatef(-3.3, 0.375, 4.8);
        glScalef(2, 2, 2);
        glPushMatrix(); //Tank
            glPushMatrix(); //Body
                glScalef(0.25, 0.1, 0.5);
                glTranslatef(0, -2.05, 0.125);
                cream();
                creamTank();
                glPushMatrix(); //Smoke;
                    glScalef(0.4, 0.25, 0.2);
                    glTranslatef(0.45, -1, 2.75);
                    barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix(); //Smoke;
                glScalef(0.4, 0.25, 0.2);
                glTranslatef(-0.45, -1, 2.75);
                barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

            glPushMatrix(); //Driver View Port
                glScalef(0.25, 0.4, 0.1);
                glTranslatef(-0.8, 0.3, -4.75);
                cream();
                creamTank();
                glPushMatrix(); //Driver View Port
                    glScalef(0.8, 0.04, 0.3);
                    glTranslatef(0, 2, -1.5);
                    cokelat();
                    creamTank();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(-30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(4.75, -110, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-0.2, 0, 0);
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(-1.25, -210, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix(); //Lower Glacis
            glScalef(0.25, 0.0625, 0.1);
            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.65, -2);
                glRotatef(-15, 1, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.8, -2.2);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -4, -2);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Lower Glacis End

         glPushMatrix(); //Turret
            glScalef(0.15, 0.125, 0.2);
            glTranslatef(0, -1.2, 0.2);
            cream();
            creamTank();
            glPushMatrix();
                glScalef(1, 0.2, 1);
                glTranslatef(-0.4, 0.2, 0.2);
                barrel(); //Cupola
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(1, 0.5, 0.75);
                glTranslatef(0, 0.5, -0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(0.8, 0.4, 0.25);
                glTranslatef(0, 0.6, -2.25);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Left
                glRotatef(-10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(-0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Right
                glRotatef(10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Back
                glScalef(0.75, 0.45, 0.45);
                glTranslatef(0, 0.5, 1.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(0.5, 0.5, 0.5);
                glRotatef(270, 1, 0, 0);
                glTranslatef(0, -0.5, 0.5);
                barrel();
                glPushMatrix();
                    glScalef(0.5, 1.25, 0.5);
                    glTranslatef(0, 2, 0);
                    barrel();
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.9, 0.25, 0.9);
                    glTranslatef(0, 24, 0);
                    barrel(); //Muzzle Brake
                glPopMatrix();
            glPopMatrix();
         glPopMatrix(); //Turret End

         glPushMatrix();//Track Seq

            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq End

         glPushMatrix();
            glTranslatef(-0.275, 0, 0);
            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq II End

         glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.275, 0, 0);
            glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        glPopMatrix(); 
    glPopMatrix();//Tank 2

    glPushMatrix(); //Tank 4
        glRotatef(180, 0, 1, 0);
        glTranslatef(-4.3, 0.375, 4.8);
        glScalef(2, 2, 2);
        glPushMatrix(); //Tank
            glPushMatrix(); //Body
                glScalef(0.25, 0.1, 0.5);
                glTranslatef(0, -2.05, 0.125);
                cream();
                creamTank();
                glPushMatrix(); //Smoke;
                    glScalef(0.4, 0.25, 0.2);
                    glTranslatef(0.45, -1, 2.75);
                    barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix(); //Smoke;
                glScalef(0.4, 0.25, 0.2);
                glTranslatef(-0.45, -1, 2.75);
                barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

            glPushMatrix(); //Driver View Port
                glScalef(0.25, 0.4, 0.1);
                glTranslatef(-0.8, 0.3, -4.75);
                cream();
                creamTank();
                glPushMatrix(); //Driver View Port
                    glScalef(0.8, 0.04, 0.3);
                    glTranslatef(0, 2, -1.5);
                    cokelat();
                    creamTank();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(-30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(4.75, -110, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-0.2, 0, 0);
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(-1.25, -210, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix(); //Lower Glacis
            glScalef(0.25, 0.0625, 0.1);
            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.65, -2);
                glRotatef(-15, 1, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.8, -2.2);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -4, -2);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Lower Glacis End

         glPushMatrix(); //Turret
            glScalef(0.15, 0.125, 0.2);
            glTranslatef(0, -1.2, 0.2);
            cream();
            creamTank();
            glPushMatrix();
                glScalef(1, 0.2, 1);
                glTranslatef(-0.4, 0.2, 0.2);
                barrel(); //Cupola
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(1, 0.5, 0.75);
                glTranslatef(0, 0.5, -0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(0.8, 0.4, 0.25);
                glTranslatef(0, 0.6, -2.25);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Left
                glRotatef(-10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(-0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Right
                glRotatef(10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Back
                glScalef(0.75, 0.45, 0.45);
                glTranslatef(0, 0.5, 1.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(0.5, 0.5, 0.5);
                glRotatef(270, 1, 0, 0);
                glTranslatef(0, -0.5, 0.5);
                barrel();
                glPushMatrix();
                    glScalef(0.5, 1.25, 0.5);
                    glTranslatef(0, 2, 0);
                    barrel();
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.9, 0.25, 0.9);
                    glTranslatef(0, 24, 0);
                    barrel(); //Muzzle Brake
                glPopMatrix();
            glPopMatrix();
         glPopMatrix(); //Turret End

         glPushMatrix();//Track Seq

            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq End

         glPushMatrix();
            glTranslatef(-0.275, 0, 0);
            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq II End

         glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.275, 0, 0);
            glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        glPopMatrix(); 
    glPopMatrix();//Tank 4

    glPushMatrix(); //Tank 5
        glRotatef(180, 0, 1, 0);
        glTranslatef(-5.3, 0.375, 4.8);
        glScalef(2, 2, 2);
        glPushMatrix(); //Tank
            glPushMatrix(); //Body
                glScalef(0.25, 0.1, 0.5);
                glTranslatef(0, -2.05, 0.125);
                cream();
                creamTank();
                glPushMatrix(); //Smoke;
                    glScalef(0.4, 0.25, 0.2);
                    glTranslatef(0.45, -1, 2.75);
                    barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix(); //Smoke;
                glScalef(0.4, 0.25, 0.2);
                glTranslatef(-0.45, -1, 2.75);
                barrel();
                    glPushMatrix(); //Smoke;
                        glScalef(0.5, 0.5, 0.5);
                        glTranslatef(0, 5, 0);
                        barrel();
                    glPopMatrix();
                glPopMatrix();

            glPushMatrix(); //Driver View Port
                glScalef(0.25, 0.4, 0.1);
                glTranslatef(-0.8, 0.3, -4.75);
                cream();
                creamTank();
                glPushMatrix(); //Driver View Port
                    glScalef(0.8, 0.04, 0.3);
                    glTranslatef(0, 2, -1.5);
                    cokelat();
                    creamTank();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(-30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(4.75, -110, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix();
            glTranslatef(-0.2, 0, 0);
            glRotatef(5, 1, 0, 0);
            glPushMatrix(); //Slanted SidePlate
                glRotatef(30, 0, 0, 1);
                glScalef(0.05, 0.001, 0.5);
                glTranslatef(-1.25, -210, 0.15);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix();

         glPushMatrix(); //Lower Glacis
            glScalef(0.25, 0.0625, 0.1);
            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.65, -2);
                glRotatef(-15, 1, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -3.8, -2.2);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(1, 1, 1);
                glTranslatef(0, -4, -2);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Lower Glacis End

         glPushMatrix(); //Turret
            glScalef(0.15, 0.125, 0.2);
            glTranslatef(0, -1.2, 0.2);
            cream();
            creamTank();
            glPushMatrix();
                glScalef(1, 0.2, 1);
                glTranslatef(-0.4, 0.2, 0.2);
                barrel(); //Cupola
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(1, 0.5, 0.75);
                glTranslatef(0, 0.5, -0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Front
                glScalef(0.8, 0.4, 0.25);
                glTranslatef(0, 0.6, -2.25);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Left
                glRotatef(-10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(-0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Side-Right
                glRotatef(10, 0, 1, 0);
                glScalef(0.5, 1, 1);
                glTranslatef(0.75, 0, 0);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //Back
                glScalef(0.75, 0.45, 0.45);
                glTranslatef(0, 0.5, 1.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix();
                glScalef(0.5, 0.5, 0.5);
                glRotatef(270, 1, 0, 0);
                glTranslatef(0, -0.5, 0.5);
                barrel();
                glPushMatrix();
                    glScalef(0.5, 1.25, 0.5);
                    glTranslatef(0, 2, 0);
                    barrel();
                glPopMatrix();

                glPushMatrix();
                    glScalef(0.9, 0.25, 0.9);
                    glTranslatef(0, 24, 0);
                    barrel(); //Muzzle Brake
                glPopMatrix();
            glPopMatrix();
         glPopMatrix(); //Turret End

         glPushMatrix();//Track Seq

            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq End

         glPushMatrix();
            glTranslatef(-0.275, 0, 0);
            glPushMatrix(); //Track
                glScalef(0.05, 0.01, 0.5);
                glTranslatef(2.75, -34, 0.065);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomDiagTrack
                glRotatef(-45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -44, -0.6);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //BottomFrtDiagTrack
                glRotatef(60, 1, 0, 0);
                glScalef(0.05, 0.01, 0.1);
                glTranslatef(2.75, -35.5, 1.4);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopFrtDiagTrack
                glRotatef(-30, 1, 0, 0);
                glScalef(0.05, 0.01, 0.06);
                glTranslatef(2.75, -6.8, -5.1);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidBackTrack
                glRotatef(-90, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, -31, -7.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidFrtTrack
                glRotatef(-80, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 21, -7);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(15, 1, 0, 0);
                glScalef(0.05, 0.01, 0.15);
                glTranslatef(2.75, -25, -0.5);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); // MidTopTrack
                glRotatef(2, 1, 0, 0);
                glScalef(0.05, 0.01, 0.35);
                glTranslatef(2.75, -24.5, 0.35);
                cream();
                creamTank();
            glPopMatrix();

            glPushMatrix(); //TopDiagTrack
                glRotatef(45, 1, 0, 0);
                glScalef(0.05, 0.01, 0.04);
                glTranslatef(2.75, 2.5, 10);
                cream();
                creamTank();
            glPopMatrix();
         glPopMatrix(); //Track Seq II End

         glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, -0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
                glColor3f(0.4, 0.4, 0.4);
                glScalef(1, 1, 1);
                glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
                tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.275, 0, 0);
            glPushMatrix(); //Tire - L
            glRotatef(90, 0, 0, 1);
            glScalef(0.1, 0.1, 0.1);
            glTranslatef(-2.5, 1.35, -2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Drive Wheel
            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 0.75); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 1.375); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire I - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 2); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 2.625); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire II - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 3.25); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0.1, 3.875); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire III - R
            glPopMatrix();

            glPushMatrix();
            glColor3f(0.4, 0.4, 0.4);
            glScalef(1, 1, 1);
            glTranslatef(-0.5, 0, 4.5); //X naik = Keatas, Y naik = Kekiri, Z Naik = Kebelakang
            tire(); //Tire IV
            glPopMatrix();
            glPopMatrix();
            glPopMatrix();
        glPopMatrix(); 
    glPopMatrix();//Tank 5

    glPushMatrix(); //Atap Jalan Gedung E Kekanan
    glRotatef(90, 0, 1, 0);
    glScalef(0.75, 0.125, 2);
    glTranslatef(4.25, 0, 0);
    gentengtrapesium(); 
    garisAtap();
        glPushMatrix(); //Pillar
        glScalef(0.33, 2, 0.125);
            glPushMatrix(); // PK 1
                glScalef(0.25, 2, 0.25);
                glTranslatef(-5, -0.5, -10);
                cokelat();

                glPushMatrix(); // PK 2
                    glScalef(1,1,1); 
                    glTranslatef(0,0,7);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 3
                    glScalef(1,1,1);
                    glTranslatef(0,0,14);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 4
                    glScalef(1,1,1);
                    glTranslatef(0,0,20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 5
                    glScalef(1,1,1); 
                    glTranslatef(10,0,7);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 6
                    glScalef(1,1,1);
                    glTranslatef(10,0,14);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 7
                    glScalef(1,1,1);
                    glTranslatef(10,0,20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); // PK 7
                    glScalef(1,1,1);
                    glTranslatef(10,0,0);
                    cokelat();
                glPopMatrix();

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.45, 0, 0);
    glScalef(1.6, 1, 1);
        glPushMatrix(); //Atap Jalan Gedung E Kekanan III
        glRotatef(90, 0, 1, 0);
        glScalef(0.75, 0.125, 2);
        glTranslatef(4.25, 0, 0);
        gentengtrapesium(); 
        garisAtap();
            glPushMatrix(); //Pillar
            glScalef(0.33, 2, 0.125);
                glPushMatrix(); // PK 1
                    glScalef(0.25, 2, 0.25);
                    glTranslatef(-5, -0.5, -10);
                    cokelat();

                    glPushMatrix(); // PK 2
                        glScalef(1,1,1); 
                        glTranslatef(0,0,7);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 3
                        glScalef(1,1,1);
                        glTranslatef(0,0,14);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 4
                        glScalef(1,1,1);
                        glTranslatef(0,0,20);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 5
                        glScalef(1,1,1); 
                        glTranslatef(10,0,7);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 6
                        glScalef(1,1,1);
                        glTranslatef(10,0,14);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 7
                        glScalef(1,1,1);
                        glTranslatef(10,0,20);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 7
                        glScalef(1,1,1);
                        glTranslatef(10,0,0);
                        cokelat();
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.45, 0, 0);
    glScalef(1.6, 1, 1);
        glPushMatrix(); //Atap Jalan Gedung E Kekanan III
        glRotatef(90, 0, 1, 0);
        glScalef(0.75, 0.125, 2);
        glTranslatef(4.25, 0, 0);
        gentengtrapesium(); 
        garisAtap();
            glPushMatrix(); //Pillar
            glScalef(0.33, 2, 0.125);
                glPushMatrix(); // PK 1
                    glScalef(0.25, 2, 0.25);
                    glTranslatef(-5, -0.5, -10);
                    cokelat();

                    glPushMatrix(); // PK 2
                        glScalef(1,1,1); 
                        glTranslatef(0,0,7);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 3
                        glScalef(1,1,1);
                        glTranslatef(0,0,14);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 4
                        glScalef(1,1,1);
                        glTranslatef(0,0,20);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 5
                        glScalef(1,1,1); 
                        glTranslatef(10,0,7);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 6
                        glScalef(1,1,1);
                        glTranslatef(10,0,14);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 7
                        glScalef(1,1,1);
                        glTranslatef(10,0,20);
                        cokelat();
                    glPopMatrix();

                    glPushMatrix(); // PK 7
                        glScalef(1,1,1);
                        glTranslatef(10,0,0);
                        cokelat();
                    glPopMatrix();

                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.25, 0.25, 0.25);

        glPushMatrix(); //Gedung Srikandi
            glScalef(6, 2, 5);
            glTranslatef(-0.1, -0.375, -3.5);
            cream();
                glPushMatrix();
                glScalef(1.1, 0.5, 1.1);
                glTranslatef(0, 1, 0);
                gentengsegitiga();
                garisAtapLimas();
                glPopMatrix();
        glPopMatrix();

        glPushMatrix(); //Gedung Perpus Start
        glScalef(9, 2, 4);
        glTranslatef(4.25, -0.375, -4.25);
        cream();
            glPushMatrix(); //Lantai Gedung Perpus
                glScalef(1.2, 0.02, 1.2);
                glTranslatef(0, -13, 0);
                cokelat();
            glPopMatrix(); //Lantai Gedung Perpus
            glPushMatrix(); //Pintu
                glScalef(0.1, 0.5, 0.01);
                glTranslatef(-1.25, 0.15, 50);
                jendela();
                frame();
            glPopMatrix(); //Pintu

            glPushMatrix(); //Tapak
                glScalef(0.2, 0.2, 0.25);
                glTranslatef(-0.625, -1.4, 2.25);
                cokelat();
            glPopMatrix(); //Tapak

            glPushMatrix(); // Pillar
            glScalef(0.025, 1, 0.025);
            glTranslatef(-20, 0, 20);
            cokelat();
                glPushMatrix(); //Jendela I Lt. I
                glScalef(5, 0.25, 0.05);
                glTranslatef(1, 0.8, 5);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix(); //Jendela II Lt. I - Depan
                glScalef(5, 0.25, 0.05);
                glTranslatef(5, 0.8, 5);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix(); //Jendela III Lt. I - Depan
                glScalef(5, 0.25, 0.05);
                glTranslatef(7, 0.8, 5);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix(); //Pillar II
                    glScalef(1, 2, 1);
                    glTranslatef(10, 0.25, 0);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar III
                    glScalef(1, 2, 1);
                    glTranslatef(20, 0.25, 0);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar IV
                    glScalef(1, 2, 1);
                    glTranslatef(30, 0.25, 0);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar V
                    glScalef(1, 2, 1);
                    glTranslatef(40, 0.25, 0);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar VI
                    glScalef(1, 2, 1);
                    glTranslatef(10, 0.25, -20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar VII
                    glScalef(1, 2, 1);
                    glTranslatef(20, 0.25, -20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar VIII
                    glScalef(1, 2, 1);
                    glTranslatef(30, 0.25, -20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar IX
                    glScalef(1, 2, 1);
                    glTranslatef(40, 0.25, -20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar X
                    glScalef(1, 2, 1);
                    glTranslatef(10, 0.25, -40);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar XI
                    glScalef(1, 2, 1);
                    glTranslatef(20, 0.25, -40);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar XII
                    glScalef(1, 2, 1);
                    glTranslatef(30, 0.25, -40);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar XIII
                    glScalef(1, 2, 1);
                    glTranslatef(40, 0.25, -40);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar XIV
                    glScalef(1, 1, 1);
                    glTranslatef(0, 0, -20);
                    cokelat();
                glPopMatrix();

                glPushMatrix(); //Pillar XV
                    glScalef(1, 1, 1);
                    glTranslatef(0, 0, -40);
                    cokelat();
                glPopMatrix();
            glPopMatrix(); // Pillar

            glPushMatrix(); // Atap Tengah
                glScalef(1.25, 0.25, 1.25);
                glTranslatef(0, 2, 0);
                gentengKotak();
                garisAtapKotak();
            glPopMatrix(); // Atap Tengah

            glPushMatrix(); //Lantai 2
                glScalef(0.75, 1, 1);
                glTranslatef(0.16625, 1, 0);
                cream();
                glPushMatrix(); //Atap Lt. II
                    glRotatef(90, 0, 1, 0);
                    glScalef(1.25, 0.25, 1.25);
                    glTranslatef(0, 2, 0);
                    gentengtrapesium();
                    garisAtap();
                glPopMatrix();

                glPushMatrix(); //Jendela I Lt. I - Depan
                    glScalef(0.15, 0.25, 0.005);
                    glTranslatef(-2.2, 0.8, 100);
                    jendela();
                    frame();
                glPopMatrix();

                glPushMatrix(); //Jendela II Lt. I - Depan
                    glScalef(0.15, 0.25, 0.005);
                    glTranslatef(0, 0.8, 100);
                    jendela();
                    frame();
                glPopMatrix();

                glPushMatrix(); //Jendela III Lt. II - Depan
                    glScalef(0.15, 0.25, 0.005);
                    glTranslatef(2.2, 0.8, 100);
                    jendela();
                    frame();
                glPopMatrix();
            
            glPopMatrix();
        glPopMatrix(); //Gedung Perpus End

        glPushMatrix(); //Gedung Radio Start
            glPushMatrix(); //Gedung A
                glScalef(6, 2, 6);
                glTranslatef(8, -0.375, -2);
                cream();
                    glPushMatrix(); //Lantai Gedung A
                        glScalef(1.2, 0.02, 1.2);
                        glTranslatef(0, -13, 0);
                        cokelat();
                    glPopMatrix(); //Lantai Gedung  A

                    glPushMatrix(); //Atap Gedung A
                        glScalef(1.2, 1.2, 1.2);
                        glTranslatef(0, 0.4065, 0);
                        gentengsegitiga();
                        garisAtapLimas(); 
                    glPopMatrix(); //Atap Gedung A
            glPopMatrix(); // Gedung A

            glPushMatrix(); //Gedung B
                glScalef(4, 2, 5);
                glTranslatef(12, -0.375, -1.15);
                cream();
                glPushMatrix(); //Lantai Gedung B
                    glScalef(1.2, 0.02, 1.2);
                    glTranslatef(0, -13, 0);
                    cokelat();
                glPopMatrix(); //Lantai Gedung  B
                glPushMatrix(); //Atap Gedung B
                    glScalef(1.2, 0.75, 2);
                    glTranslatef(0, 0.65, -0.2);
                    gentengtrapesium();
                    garisAtap();
                glPopMatrix(); //Atap Gedung B
            glPopMatrix(); // Gedung B
        glPopMatrix(); //Gedung Radio End

        glPushMatrix(); //Gedung E Start
        glTranslatef(-14, 0, -0.75);
            glPushMatrix(); //Gedung E (Atap Coklat)
                glPushMatrix();
                    glScalef(19, 2.5, 5);
                    glTranslatef(0, 0, -2.7);
                    cream(); //Gedung E Lt. I
                glPopMatrix();

                glPushMatrix();
                    glScalef(19.5, 6, 5.5);
                    glTranslatef(0, 0.6, -2.45);
                    cream(); //Gedung E Lt. II
                glPopMatrix();

                glPushMatrix();
                    glScalef(21, 0.5, 7);
                    glTranslatef(0, 1.6, -1.925);
                    cream(); //Outer Case Bawah Lt. II
                glPopMatrix();

                glPushMatrix();
                    glScalef(21, 0.25, 7);
                    glTranslatef(0, -5.5, -1.925);
                    cokelat(); //Lantai Bawah Lt. I
                glPopMatrix();

                glPushMatrix();
                glScalef(2, 0.25, 4);
                glTranslatef(3, -5.5, -2.25);
                cokelat(); //Lantai Pintu Masuk Lt. I
                glPopMatrix();

                glPushMatrix();
                    glScalef(2, 0.5, 4);
                    glTranslatef(3, 1.6, -2.25);
                    cream(); //Pintu Masuk Lt. I                    
                    glPushMatrix(); //Pillar Lt I Lobby
                        glScalef(0.125, 4.125, 0.0625);
                        glTranslatef(2.5, -0.5, -4);
                        cokelat();
                            glPushMatrix(); //Pillar Lt I Lobby II
                                glScalef(1, 1, 1);
                                glTranslatef(-5, 0, 0);
                                cokelat();
                            glPopMatrix();

                            glPushMatrix(); //Pillar Lt I Lobby II
                                glScalef(1, 1, 1);
                                glTranslatef(0, 0, 10);
                                cokelat();
                            glPopMatrix();

                            glPushMatrix(); //Pillar Lt I Lobby III
                                glScalef(1, 1, 1);
                                glTranslatef(-5, 0, 10);
                                cokelat();
                            glPopMatrix();

                            glPushMatrix(); //Pillar Lt I Lobby IV
                                glScalef(1, 1, 1);
                                glTranslatef(12, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Lobby Belakang IV
                                glScalef(1, 1, 1);
                                glTranslatef(12, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I I
                                glScalef(1, 1, 1);
                                glTranslatef(-12, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I II
                                glScalef(1, 1, 1);
                                glTranslatef(-18.5, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I III
                                glScalef(1, 1, 1);
                                glTranslatef(-30.5, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I IV
                                glScalef(1, 1, 1);
                                glTranslatef(-42.5, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I V
                                glScalef(1, 1, 1);
                                glTranslatef(-54.5, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I VI
                                glScalef(1, 1, 1);
                                glTranslatef(-66.5, 0, -1);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang I
                                glScalef(1, 1, 1);
                                glTranslatef(-12, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang II
                                glScalef(1, 1, 1);
                                glTranslatef(-18.5, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang III
                                glScalef(1, 1, 1);
                                glTranslatef(-30.5, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang IV
                                glScalef(1, 1, 1);
                                glTranslatef(-42.5, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang V
                                glScalef(1, 1, 1);
                                glTranslatef(-54.5, 0, -26);
                                cokelat();
                            glPopMatrix();
                            glPushMatrix(); //Pillar Lt I Belakang VI
                                glScalef(1, 1, 1);
                                glTranslatef(-66.5, 0, -26);
                                cokelat();
                            glPopMatrix();
                    glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                    glScalef(2, 4.5, 6.6);
                    glTranslatef(2, 0.62, -2.05);
                    cream(); //Pillar Kompartemen Kiri Lt. II
                glPopMatrix();

                glPushMatrix();
                glScalef(14, 4.5, 6.3);
                glTranslatef(-0.2, 0.62, -2.15);
                cream(); //Ruang Kompartemen Kiri Lt. II
                glPopMatrix();

                glPushMatrix();
                glScalef(13.5, 0.25, 6.5);
                glTranslatef(-0.25, 11, -2.075);
                cream(); //Pembatas Kompartemen Kiri Lt. II
                glPopMatrix();

                glPushMatrix();
                    glScalef(21, 0.5, 7);
                    glTranslatef(0, 9.6, -1.925);
                    cream(); //Outer Case Atas Lt. II
                glPopMatrix();
                
                glPushMatrix(); //Pillar Orange Lt II Start
                    glScalef(0.25, 4, 0.25);
                    glTranslatef(8, 0.65, -41.5);
                    cokelaterang(); //Pilar Orange Lt II Paling Kanan (Acuan)
                        glPushMatrix(); 
                            glScalef(1, 1, 1);
                            glTranslatef(-6, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II I
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-12, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II II
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-18, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II III
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-24, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II IV
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-30, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II V
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-36, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VI
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-42, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VII
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-48, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VIII
                        glPopMatrix();
                glPopMatrix(); //Pillar Orange Lt II End

                glPushMatrix(); //Pillar Orange Lt II Belakang Start
                    glScalef(0.25, 4, 0.25);
                    glTranslatef(8, 0.65, -67);
                    cokelaterang(); //Pilar Orange Lt II Paling Kanan (Acuan)
                        glPushMatrix(); 
                            glScalef(1, 1, 1);
                            glTranslatef(-6, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II I
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-12, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II II
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-18, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II III
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-24, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II IV
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-30, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II V
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-36, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VI
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-42, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VII
                        glPopMatrix();
                        glPushMatrix();
                            glScalef(1, 1, 1);
                            glTranslatef(-48, 0, 0);
                            cokelaterang(); //Pilar Orange Lt II VIII
                        glPopMatrix();
                glPopMatrix(); //Pillar Orange Lt II Belakang End

                glPushMatrix(); //Jendela Lt II Kiri Start
                    glScalef(1, 0.75, 0.25);
                    glTranslatef(2.5, 2.3, -42);
                    jendela(); //Jendela Paling Kanan (Acuan)
                    frame();
                    glPushMatrix(); //Jendela Atas 0
                        glScalef(1.1, 1, 1);
                        glTranslatef(0, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah I
                        glScalef(1.1, 1, 1);
                        glTranslatef(-1.13, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas I
                        glScalef(1.1, 1, 1);
                        glTranslatef(-1.13, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah II
                        glScalef(1.1, 1, 1);
                        glTranslatef(-2.51, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas II
                        glScalef(1.1, 1, 1);
                        glTranslatef(-2.51, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah III
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas III
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah V
                        glScalef(1.1, 1, 1);
                        glTranslatef(-5.23, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas V
                        glScalef(1.1, 1, 1);
                        glTranslatef(-5.23, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VI
                        glScalef(1.1, 1, 1);
                        glTranslatef(-6.6, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VI
                        glScalef(1.1, 1, 1);
                        glTranslatef(-6.6, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-7.96, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-7.96, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VIII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-9.32, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VIII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-9.32, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IX
                        glScalef(1.1, 1, 1);
                        glTranslatef(-10.65, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas IX
                        glScalef(1.1, 1, 1);
                        glTranslatef(-10.65, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                glPopMatrix(); //Jendela Lt II Kiri End

                glPushMatrix(); //Jendela Lt II Kiri Belakang Start
                    glScalef(1, 0.75, 0.25);
                    glTranslatef(2.5, 2.3, -66.5);
                    jendela(); //Jendela Paling Kanan (Acuan)
                    frame();
                    glPushMatrix(); //Jendela Atas 0
                        glScalef(1.1, 1, 1);
                        glTranslatef(0, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah I
                        glScalef(1.1, 1, 1);
                        glTranslatef(-1.13, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas I
                        glScalef(1.1, 1, 1);
                        glTranslatef(-1.13, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah II
                        glScalef(1.1, 1, 1);
                        glTranslatef(-2.51, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas II
                        glScalef(1.1, 1, 1);
                        glTranslatef(-2.51, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah III
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas III
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas IV
                        glScalef(1.1, 1, 1);
                        glTranslatef(-3.85, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah V
                        glScalef(1.1, 1, 1);
                        glTranslatef(-5.23, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas V
                        glScalef(1.1, 1, 1);
                        glTranslatef(-5.23, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VI
                        glScalef(1.1, 1, 1);
                        glTranslatef(-6.6, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VI
                        glScalef(1.1, 1, 1);
                        glTranslatef(-6.6, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-7.96, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-7.96, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah VIII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-9.32, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas VIII
                        glScalef(1.1, 1, 1);
                        glTranslatef(-9.32, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Bawah IX
                        glScalef(1.1, 1, 1);
                        glTranslatef(-10.65, 0, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                    glPushMatrix(); //Jendela Atas IX
                        glScalef(1.1, 1, 1);
                        glTranslatef(-10.65, 2.5, 0);
                        jendela(); //Jendela Paling Kanan (Acuan)
                        frame();
                    glPopMatrix();
                glPopMatrix(); //Jendela Lt II Kiri Belakang End
                glPushMatrix(); //Pembatas Kaca Kanan Start
                    glScalef(5, 1.9, 6);
                    glTranslatef(1.5, 0.9, -2.25);
                    cokelaterang();
                        glPushMatrix(); //Jendela Kanan Start
                            glPushMatrix();
                                glScalef(0.2, 0.8, 0.05);
                                glTranslatef(-1.75, 1.15, 9);
                                jendela();
                                frame(); //Jendela Kanan - Kiri Acuan
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(1, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan I
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(2, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan II
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(3, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan III
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(0.5, 1, 1);
                                    glTranslatef(4, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan IV
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix(); //Jendela Kanan End
                        glPushMatrix(); //Jendela Kanan Belakang Start
                            glPushMatrix();
                                glScalef(0.2, 0.8, 0.05);
                                glTranslatef(-1.75, 1.15, -9);
                                jendela();
                                frame(); //Jendela Kanan - Kiri Acuan
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(1, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan I
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(2, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan II
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(1, 1, 1);
                                    glTranslatef(3, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan III
                                glPopMatrix();
                                glPushMatrix();
                                    glScalef(0.5, 1, 1);
                                    glTranslatef(4, 0, 0);
                                    jendela();
                                    frame(); //Jendela Kanan IV
                                glPopMatrix();
                            glPopMatrix();
                        glPopMatrix(); //Jendela Kanan Belakang End
                glPopMatrix(); //Pembatas Kaca Kanan End
                glPushMatrix(); //Atap Gedung E Start
                glScalef(22, 3, 9);
                glRotatef(90, 0, 1, 0);
                glTranslatef(1.5, 1.92, 0);
                gentengtrapesium();
                garisAtap();
                glPopMatrix(); //Atap Gedung E End
            glPopMatrix();
        glPopMatrix(); //Gedung E End

        glPushMatrix(); //Gedung F Start
        glTranslatef(0, 0, -6.75);
            glPushMatrix();
                glPushMatrix(); // Atap
                    glScalef(7, 0.75, 12);
                    glTranslatef(1.1225, 0.4, -0.5);
                    gentengtrapesium();
                    garisAtap();
                glPopMatrix(); // Atap
                glPushMatrix(); //Atas
                glScalef(6, 0.1, 8);
                glTranslatef(1.3, 2.5, -0.875);
                cream();
                glPopMatrix(); //Atas

                glPushMatrix(); //Bawah
                glScalef(6, 0.1, 8);
                glTranslatef(1.3, -12, -0.875);
                cream();
                glPopMatrix(); //Bawah

                glPushMatrix(); //Pintu Kaca Kiri
                    glPushMatrix(); //Kaca Kiri
                    glScalef(0.1, 1.4, 1);
                    glTranslatef(50, -0.365, -6.5);
                    jendela();
                    frame();
                    glPopMatrix(); //Kaca Kiri

                    glPushMatrix(); //Kaca Kanan
                    glScalef(0.1, 1.4, 1);
                    glTranslatef(50, -0.365, -5.5);
                    jendela();
                    frame();
                    glPopMatrix(); //Kaca Kanan
                glPopMatrix(); //Pintu Kaca Kiri

                glPushMatrix(); //Pintu Kaca Kanan
                    glPushMatrix(); //Kaca Kiri
                    glScalef(0.1, 1.4, 1);
                    glTranslatef(106, -0.365, -6.5);
                    jendela();
                    frame();
                    glPopMatrix(); //Kaca Kiri

                    glPushMatrix(); //Kaca Kanan
                    glScalef(0.1, 1.4, 1);
                    glTranslatef(106, -0.365, -5.5);
                    jendela();
                    frame();
                    glPopMatrix(); //Kaca Kanan
                glPopMatrix(); //Pintu Kaca Kanan

                glPushMatrix(); //Depan
                glScalef(6, 2, 2);
                glTranslatef(1.3, -0.35, -2);
                cream();
                    glPushMatrix(); //Lantai Gedung F - Depan
                        glScalef(1.2, 0.02, 1.2);
                        glTranslatef(0, -14.5, 0);
                        cokelat();
                    glPopMatrix(); //Lantai Gedung  F - Depan
                    glPushMatrix(); //Pintu Luar - Kiri
                    glScalef(0.2, 0.6, 0.01);
                    glTranslatef(-0.5, 0.2, 50);
                    jendela();
                    frame();
                    glPopMatrix(); //Pintu Luar - Kiri

                    glPushMatrix(); //Pintu Luar - Kanan
                    glScalef(0.2, 0.6, 0.01);
                    glTranslatef(0.5, 0.2, 50);
                    jendela();
                    frame();
                    glPopMatrix(); //Pintu Luar - Kanan

                    glPushMatrix(); //Pintu Dalam - Kanan
                    glScalef(0.2, 0.6, 0.01);
                    glTranslatef(-0.5, 0.2, -50);
                    jendela();
                    frame();
                    glPopMatrix(); //Pintu Dalam - Kanan

                    glPushMatrix(); //Pintu Dalam - Kanan
                    glScalef(0.2, 0.6, 0.01);
                    glTranslatef(0.5, 0.2, -50);
                    jendela();
                    frame();
                    glPopMatrix(); //Pintu Dalam - Kanan

                    glPushMatrix(); //Lobby Depan - Bawah
                    glScalef(0.6, 0.1, 1);
                    glTranslatef(0, -2.75, 1);
                    cream();
                    glPopMatrix(); // Lobby Depan - Bawah

                    glPushMatrix(); //Lobby Depan - Kiri
                    glScalef(0.05, 0.5, 1);
                    glTranslatef(-6, -0.375, 1);
                    cream();
                    glPopMatrix(); // Lobby Depan - Kiri

                    glPushMatrix(); //Lobby Depan - Kanan
                    glScalef(0.05, 0.5, 1);
                    glTranslatef(6, -0.375, 1);
                    cream();
                    glPopMatrix(); // Lobby Depan - Kanan

                    glPushMatrix(); //Lobby Depan - Atas
                    glScalef(0.6, 0.1, 1);
                    glTranslatef(0, 4.5, 1);
                    cream();
                    glPopMatrix(); // Lobby Depan - Atas
                glPopMatrix(); //Depan

                glPushMatrix(); //Belakang
                glScalef(6, 2, 4);
                glTranslatef(1.3, -0.35, -2.25);
                cream();
                    glPushMatrix(); //Lantai Gedung F - Belakang
                        glScalef(1.2, 0.02, 1.2);
                        glTranslatef(0, -14.5, 0);
                        cokelat();
                    glPopMatrix(); //Lantai Gedung  F - Belakang
                    glPushMatrix(); //Kaca Gedung Belakang - Kiri
                    glScalef(0.01, 0.4, 0.15);
                    glTranslatef(-50, 0.4, 2);
                    jendela(); //Kaca I - Acuan
                    frame();
                        glPushMatrix(); //Kaca II
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -1);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca II
                        glPushMatrix(); //Kaca III
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -2);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca III
                        glPushMatrix(); //Kaca IV
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -3);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca IV
                    glPopMatrix(); //Kaca Gedung Belakang - Kiri

                    glPushMatrix(); //Kaca Gedung Belakang - Kanan
                    glScalef(0.01, 0.4, 0.15);
                    glTranslatef(50, 0.4, 2);
                    jendela(); //Kaca I
                    frame();
                        glPushMatrix(); //Kaca II
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -1);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca II
                        glPushMatrix(); //Kaca III
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -2);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca III
                        glPushMatrix(); //Kaca IV
                        glScalef(1, 1, 1);
                        glTranslatef(0, 0, -3);
                        jendela();
                        frame();
                        glPopMatrix(); //Kaca IV
                    glPopMatrix(); //Kaca Gedung Belakang - Kiri

                    glPushMatrix(); //Pintu Dalam - Kanan
                        glScalef(0.2, 0.6, 0.01);
                        glTranslatef(0.5, 0.2, 50);
                        jendela();
                        frame();
                    glPopMatrix(); //Pintu Dalam - Kanan

                    glPushMatrix(); //Pintu Dalam - Kiri
                        glScalef(0.2, 0.6, 0.01);
                        glTranslatef(-0.5, 0.2, 50);
                        jendela();
                        frame();
                    glPopMatrix(); //Pintu Dalam - Kiri
                glPopMatrix(); //Belakang
            glPopMatrix();
        glPopMatrix(); //Gedung F End

        glPushMatrix(); //Bangunan Kelas - Start
            glPushMatrix();
            glScalef(5, 1.5, 19);
            glTranslatef(0, -0.35, 0);
            cream(); //Gedung Tengah Lt. I
            glPushMatrix(); //Lantai Gedung Kelas
            glScalef(1.4, 0.05, 1.1);
            glTranslatef(0, -10, 0);
            cokelat();
            glPopMatrix(); //Lantai Gedung  Kelas
            glPopMatrix();

            glPushMatrix();
            glScalef(4.5, 1.2, 18.5);
            glTranslatef(0, 0.5, 0);
            cream(); //Gedung Tengah - Tengah
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 2.5, 20);
            glTranslatef(0, 1, 0);
            cream(); //Gedung Tengah Lt. II
            glPopMatrix();

            glPushMatrix(); //Atap Start
                glPushMatrix(); //Atap Persegi Start
                    glPushMatrix(); //Atap Persegi Core Start
                    glScalef(7, 0.25, 22);
                    glTranslatef(0, 14.5, 0);
                    cream();
                        glPushMatrix(); //Atap Persegi Top Start
                        glScalef(1.01, 0.25, 1.01);
                        glTranslatef(0, 1.5, 0);
                        cream();
                        glPopMatrix(); //Atap Persegi Top End
                        glPushMatrix(); //Atap Persegi Bot Start
                        glScalef(1.01, 0.25, 1.01);
                        glTranslatef(0, -1.5, 0);
                        cream();
                        glPopMatrix(); //Atap Persegi Bot End
                    glPopMatrix(); //Atap Persegi Core End
                glPopMatrix(); //Atap Persegi End

                glPushMatrix(); //Atap Persegi Connector Start
                glScalef(6.5, 0.25, 21);
                glTranslatef(0, 15, 0);
                cream();
                glPopMatrix(); //Atap Persegi Connector End

                glPushMatrix(); //Genteng Start
                glScalef(7,2,22);
                glTranslatef(0, 1.9, 0);
                gentengtrapesium();
                garisAtap();
                glPopMatrix(); //Genteng End

            glPopMatrix(); //Atap End

            glPushMatrix(); //Jendela Start
                glPushMatrix(); //Jendela Lt II Start

                        glPushMatrix();
                        glScalef(0.1, 0.7, 1.1); // Jendela Kanan Ujung
                        glTranslatef(30, 3.8, 7.75);
                        jendela();
                        frame();
                        glPopMatrix();

                        glPushMatrix();
                        glScalef(0.1, 0.7, 1.1); // Jendela I
                        glTranslatef(30, 3.8, 6.3);
                        jendela();
                        frame(); 
                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela II
                            glTranslatef(0, 0, -1.45);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela III
                            glTranslatef(0, 0, -2.85);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela IV
                            glTranslatef(0, 0, -4.25);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela V
                            glTranslatef(0, 0, -5.65);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VI
                            glTranslatef(0, 0, -7.05);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VII
                            glTranslatef(0, 0, -8.45);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VII
                            glTranslatef(0, 0, -9.85);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VIII
                            glTranslatef(0, 0, -11.25);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela IX
                            glTranslatef(0, 0, -12.65);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela X
                            glTranslatef(0, 0, -14.05);
                            jendela();
                            frame();
                            glPopMatrix();
                        glPopMatrix();

                        glPushMatrix();
                        glScalef(0.1, 0.7, 1.1); // Jendela Kiri Ujung
                        glTranslatef(-30, 3.8, 7.75);
                        jendela();
                        frame();
                        glPopMatrix();

                        glPushMatrix();
                        glScalef(0.1, 0.7, 1.1); // Jendela I
                        glTranslatef(-30, 3.8, 6.3);
                        jendela();
                        frame(); 
                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela II
                            glTranslatef(0, 0, -1.45);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela III
                            glTranslatef(0, 0, -2.85);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela IV
                            glTranslatef(0, 0, -4.25);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela V
                            glTranslatef(0, 0, -5.65);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VI
                            glTranslatef(0, 0, -7.05);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VII
                            glTranslatef(0, 0, -8.45);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VII
                            glTranslatef(0, 0, -9.85);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela VIII
                            glTranslatef(0, 0, -11.25);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela IX
                            glTranslatef(0, 0, -12.65);
                            jendela();
                            frame();
                            glPopMatrix();

                            glPushMatrix();
                            glScalef(1, 1, 1); // Jendela X
                            glTranslatef(0, 0, -14.05);
                            jendela();
                            frame();
                            glPopMatrix();
                        glPopMatrix();

                glPopMatrix(); //Jendela Lt II End
            glPopMatrix(); //Jendela End

            glPushMatrix(); //Bungkusan Pillar - Start
                glPushMatrix();
                    glScalef(0.25, 5, 0.25);
                    glTranslatef(12, 0.25, 40);
                    cokelat(); //Pillar Lt. I Depan

                        glPushMatrix();
                        glTranslatef(-10, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(-14, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(-24, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                glPopMatrix();

                glPushMatrix();
                    glScalef(0.25, 5, 0.25);
                    glTranslatef(12, 0.25, -40);
                    cokelat(); //Pillar Lt. I Belakang

                        glPushMatrix();
                        glTranslatef(-10, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(-14, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(-24, 0, 0);
                        cokelat(); //Pillar Lt. I
                        glPopMatrix();

                glPopMatrix();

                glPushMatrix(); //Pillar Samping Kanan
                    glScalef(0.25, 5, 0.25);
                    glTranslatef(12, 0.25, 40);

                        glPushMatrix();
                        glTranslatef(0, 0, -9.2);
                        cokelat(); //Pillar I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -15.4);
                        cokelat(); //Pillar II
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -21.6);
                        cokelat(); //Pillar III
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -27.8);
                        cokelat(); //Pillar IV
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -34);
                        cokelat(); //Pillar V
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -40.2);
                        cokelat(); //Pillar VI
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -46.4);
                        cokelat(); //Pillar VII
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -52.6);
                        cokelat(); //Pillar VIII
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -58.8);
                        cokelat(); //Pillar IX
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -65);
                        cokelat(); //Pillar X
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -71);
                        cokelat(); //Pillar XI
                        glPopMatrix();

                glPopMatrix();

                glPushMatrix(); //Pillar Samping Kiri
                    glScalef(0.25, 5, 0.25);
                    glTranslatef(-12, 0.25, 40);

                        glPushMatrix();
                        glTranslatef(0, 0, -9.2);
                        cokelat(); //Pillar I
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -15.4);
                        cokelat(); //Pillar II
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -21.6);
                        cokelat(); //Pillar III
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -27.8);
                        cokelat(); //Pillar IV
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -34);
                        cokelat(); //Pillar V
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -40.2);
                        cokelat(); //Pillar VI
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -46.4);
                        cokelat(); //Pillar VII
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -52.6);
                        cokelat(); //Pillar VIII
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -58.8);
                        cokelat(); //Pillar IX
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -65);
                        cokelat(); //Pillar X
                        glPopMatrix();

                        glPushMatrix();
                        glTranslatef(0, 0, -71);
                        cokelat(); //Pillar XI
                        glPopMatrix();

                glPopMatrix();

                    glPushMatrix();
                    glScalef(0.05, 1, 20);
                    glTranslatef(60, 0.75, 0);
                    mesh(); //Mesh Kanan
                    glPopMatrix();

                    glPushMatrix();
                    glScalef(0.05, 1, 20);
                    glTranslatef(-60, 0.75, 0);
                    mesh(); //Mesh Kiri
                    glPopMatrix();

                    glPushMatrix();
                    glScalef(6, 1, 0.05);
                    glTranslatef(0, 0.75, 200);
                    mesh(); //Mesh Depan
                    glPopMatrix();

                    glPushMatrix();
                    glScalef(6, 1, 0.05);
                    glTranslatef(0, 0.75, -200);
                    mesh(); //Mesh Belakang
                    glPopMatrix();

            glPopMatrix(); //Bungkusan Pillar - End

        glPopMatrix(); //Bangunan Kelas - End

        glTranslatef(-20, 0, 0); //Copy-Pindah Kiri

            glPushMatrix(); //Bangunan Kelas - Start
            glPushMatrix();
            glScalef(5, 1.5, 19);
            glTranslatef(0, -0.35, 0);
            cream(); //Gedung Tengah Lt. I
            glPushMatrix(); //Lantai Gedung Kelas
            glScalef(1.4, 0.05, 1.1);
            glTranslatef(0, -10, 0);
            cokelat();
            glPopMatrix(); //Lantai Gedung  Kelas
            glPopMatrix();

            glPushMatrix();
            glScalef(4.5, 1.2, 18.5);
            glTranslatef(0, 0.5, 0);
            cream(); //Gedung Tengah - Tengah
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 2.5, 20);
            glTranslatef(0, 1, 0);
            cream(); //Gedung Tengah Lt. II
            glPopMatrix();

            glPushMatrix(); //Atap Start
            glPushMatrix(); //Atap Persegi Start
            glPushMatrix(); //Atap Persegi Core Start
            glScalef(7, 0.25, 22);
            glTranslatef(0, 14.5, 0);
            cream();
            glPushMatrix(); //Atap Persegi Top Start
            glScalef(1.01, 0.25, 1.01);
            glTranslatef(0, 1.5, 0);
            cream();
            glPopMatrix(); //Atap Persegi Top End
            glPushMatrix(); //Atap Persegi Bot Start
            glScalef(1.01, 0.25, 1.01);
            glTranslatef(0, -1.5, 0);
            cream();
            glPopMatrix(); //Atap Persegi Bot End
            glPopMatrix(); //Atap Persegi Core End
            glPopMatrix(); //Atap Persegi End

            glPushMatrix(); //Atap Persegi Connector Start
            glScalef(6.5, 0.25, 21);
            glTranslatef(0, 15, 0);
            cream();
            glPopMatrix(); //Atap Persegi Connector End

            glPushMatrix(); //Genteng Start
            glScalef(7, 2, 22);
            glTranslatef(0, 1.9, 0);
            gentengtrapesium();
            garisAtap();
            glPopMatrix(); //Genteng End

            glPopMatrix(); //Atap End

            glPushMatrix(); //Jendela Start
            glPushMatrix(); //Jendela Lt II Start

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela Kanan Ujung
            glTranslatef(30, 3.8, 7.75);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela I
            glTranslatef(30, 3.8, 6.3);
            jendela();
            frame();
            glPushMatrix();
            glScalef(1, 1, 1); // Jendela II
            glTranslatef(0, 0, -1.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela III
            glTranslatef(0, 0, -2.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IV
            glTranslatef(0, 0, -4.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela V
            glTranslatef(0, 0, -5.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VI
            glTranslatef(0, 0, -7.05);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -8.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -9.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VIII
            glTranslatef(0, 0, -11.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IX
            glTranslatef(0, 0, -12.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela X
            glTranslatef(0, 0, -14.05);
            jendela();
            frame();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela Kiri Ujung
            glTranslatef(-30, 3.8, 7.75);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela I
            glTranslatef(-30, 3.8, 6.3);
            jendela();
            frame();
            glPushMatrix();
            glScalef(1, 1, 1); // Jendela II
            glTranslatef(0, 0, -1.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela III
            glTranslatef(0, 0, -2.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IV
            glTranslatef(0, 0, -4.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela V
            glTranslatef(0, 0, -5.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VI
            glTranslatef(0, 0, -7.05);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -8.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -9.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VIII
            glTranslatef(0, 0, -11.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IX
            glTranslatef(0, 0, -12.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela X
            glTranslatef(0, 0, -14.05);
            jendela();
            frame();
            glPopMatrix();
            glPopMatrix();

            glPopMatrix(); //Jendela Lt II End
            glPopMatrix(); //Jendela End

            glPushMatrix(); //Bungkusan Pillar - Start
            glPushMatrix();
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, 40);
            cokelat(); //Pillar Lt. I Depan

            glPushMatrix();
            glTranslatef(-10, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-14, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-24, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPopMatrix();

            glPushMatrix();
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, -40);
            cokelat(); //Pillar Lt. I Belakang

            glPushMatrix();
            glTranslatef(-10, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-14, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-24, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPopMatrix();

            glPushMatrix(); //Pillar Samping Kanan
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, 40);

            glPushMatrix();
            glTranslatef(0, 0, -9.2);
            cokelat(); //Pillar I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -15.4);
            cokelat(); //Pillar II
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -21.6);
            cokelat(); //Pillar III
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -27.8);
            cokelat(); //Pillar IV
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -34);
            cokelat(); //Pillar V
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -40.2);
            cokelat(); //Pillar VI
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -46.4);
            cokelat(); //Pillar VII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -52.6);
            cokelat(); //Pillar VIII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -58.8);
            cokelat(); //Pillar IX
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -65);
            cokelat(); //Pillar X
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -71);
            cokelat(); //Pillar XI
            glPopMatrix();

            glPopMatrix();

            glPushMatrix(); //Pillar Samping Kiri
            glScalef(0.25, 5, 0.25);
            glTranslatef(-12, 0.25, 40);

            glPushMatrix();
            glTranslatef(0, 0, -9.2);
            cokelat(); //Pillar I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -15.4);
            cokelat(); //Pillar II
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -21.6);
            cokelat(); //Pillar III
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -27.8);
            cokelat(); //Pillar IV
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -34);
            cokelat(); //Pillar V
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -40.2);
            cokelat(); //Pillar VI
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -46.4);
            cokelat(); //Pillar VII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -52.6);
            cokelat(); //Pillar VIII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -58.8);
            cokelat(); //Pillar IX
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -65);
            cokelat(); //Pillar X
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -71);
            cokelat(); //Pillar XI
            glPopMatrix();

            glPopMatrix();

            glPushMatrix();
            glScalef(0.05, 1, 20);
            glTranslatef(60, 0.75, 0);
            mesh(); //Mesh Kanan
            glPopMatrix();

            glPushMatrix();
            glScalef(0.05, 1, 20);
            glTranslatef(-60, 0.75, 0);
            mesh(); //Mesh Kiri
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 1, 0.05);
            glTranslatef(0, 0.75, 200);
            mesh(); //Mesh Depan
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 1, 0.05);
            glTranslatef(0, 0.75, -200);
            mesh(); //Mesh Belakang
            glPopMatrix();

            glPopMatrix(); //Bungkusan Pillar - End

            glPopMatrix(); //Bangunan Kelas - End

        glTranslatef(40, 0, 0); //Copy - Kanan I

            glPushMatrix(); //Gedung F Start
            glTranslatef(0, 0, -6.75);
            glPushMatrix();
            glPushMatrix(); // Atap
            glScalef(7, 0.75, 12);
            glTranslatef(1.1225, 0.4, -0.5);
            gentengtrapesium();
            garisAtap();
            glPopMatrix(); // Atap

            glPushMatrix(); //Atas
            glScalef(6, 0.1, 8);
            glTranslatef(1.3, 2.5, -0.875);
            cream();
            glPopMatrix(); //Atas

            glPushMatrix(); //Bawah
            glScalef(6, 0.1, 8);
            glTranslatef(1.3, -12, -0.875);
            cream();
            glPopMatrix(); //Bawah

            glPushMatrix(); //Pintu Kaca Kiri
            glPushMatrix(); //Kaca Kiri
            glScalef(0.1, 1.4, 1);
            glTranslatef(50, -0.365, -6.5);
            jendela();
            frame();
            glPopMatrix(); //Kaca Kiri

            glPushMatrix(); //Kaca Kanan
            glScalef(0.1, 1.4, 1);
            glTranslatef(50, -0.365, -5.5);
            jendela();
            frame();
            glPopMatrix(); //Kaca Kanan
            glPopMatrix(); //Pintu Kaca Kiri

            glPushMatrix(); //Pintu Kaca Kanan
            glPushMatrix(); //Kaca Kiri
            glScalef(0.1, 1.4, 1);
            glTranslatef(106, -0.365, -6.5);
            jendela();
            frame();
            glPopMatrix(); //Kaca Kiri

            glPushMatrix(); //Kaca Kanan
            glScalef(0.1, 1.4, 1);
            glTranslatef(106, -0.365, -5.5);
            jendela();
            frame();
            glPopMatrix(); //Kaca Kanan
            glPopMatrix(); //Pintu Kaca Kanan

            glPushMatrix(); //Depan
            glScalef(6, 2, 2);
            glTranslatef(1.3, -0.35, -2);
            cream();
            glPushMatrix(); //Lantai Gedung F - Depan
            glScalef(1.2, 0.02, 1.2);
            glTranslatef(0, -14.5, 0);
            cokelat();
            glPopMatrix(); //Lantai Gedung  F - Depan
            glPushMatrix(); //Pintu Luar - Kiri
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(-0.5, 0.2, 50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Luar - Kiri

            glPushMatrix(); //Pintu Luar - Kanan
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(0.5, 0.2, 50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Luar - Kanan

            glPushMatrix(); //Pintu Dalam - Kanan
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(-0.5, 0.2, -50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Dalam - Kanan

            glPushMatrix(); //Pintu Dalam - Kanan
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(0.5, 0.2, -50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Dalam - Kanan

            glPushMatrix(); //Lobby Depan - Bawah
            glScalef(0.6, 0.1, 1);
            glTranslatef(0, -2.75, 1);
            cream();
            glPopMatrix(); // Lobby Depan - Bawah

            glPushMatrix(); //Lobby Depan - Kiri
            glScalef(0.05, 0.5, 1);
            glTranslatef(-6, -0.375, 1);
            cream();
            glPopMatrix(); // Lobby Depan - Kiri

            glPushMatrix(); //Lobby Depan - Kanan
            glScalef(0.05, 0.5, 1);
            glTranslatef(6, -0.375, 1);
            cream();
            glPopMatrix(); // Lobby Depan - Kanan

            glPushMatrix(); //Lobby Depan - Atas
            glScalef(0.6, 0.1, 1);
            glTranslatef(0, 4.5, 1);
            cream();
            glPopMatrix(); // Lobby Depan - Atas
            glPopMatrix(); //Depan

            glPushMatrix(); //Belakang
            glScalef(6, 2, 4);
            glTranslatef(1.3, -0.35, -2.25);
            cream();
            glPushMatrix(); //Lantai Gedung F - Belakang
            glScalef(1.2, 0.02, 1.2);
            glTranslatef(0, -14.5, 0);
            cokelat();
            glPopMatrix(); //Lantai Gedung  F - Belakang
            glPushMatrix(); //Kaca Gedung Belakang - Kiri
            glScalef(0.01, 0.4, 0.15);
            glTranslatef(-50, 0.4, 2);
            jendela(); //Kaca I - Acuan
            frame();
            glPushMatrix(); //Kaca II
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -1);
            jendela();
            frame();
            glPopMatrix(); //Kaca II
            glPushMatrix(); //Kaca III
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -2);
            jendela();
            frame();
            glPopMatrix(); //Kaca III
            glPushMatrix(); //Kaca IV
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -3);
            jendela();
            frame();
            glPopMatrix(); //Kaca IV
            glPopMatrix(); //Kaca Gedung Belakang - Kiri

            glPushMatrix(); //Kaca Gedung Belakang - Kanan
            glScalef(0.01, 0.4, 0.15);
            glTranslatef(50, 0.4, 2);
            jendela(); //Kaca I
            frame();
            glPushMatrix(); //Kaca II
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -1);
            jendela();
            frame();
            glPopMatrix(); //Kaca II
            glPushMatrix(); //Kaca III
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -2);
            jendela();
            frame();
            glPopMatrix(); //Kaca III
            glPushMatrix(); //Kaca IV
            glScalef(1, 1, 1);
            glTranslatef(0, 0, -3);
            jendela();
            frame();
            glPopMatrix(); //Kaca IV
            glPopMatrix(); //Kaca Gedung Belakang - Kiri

            glPushMatrix(); //Pintu Dalam - Kanan
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(0.5, 0.2, 50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Dalam - Kanan

            glPushMatrix(); //Pintu Dalam - Kiri
            glScalef(0.2, 0.6, 0.01);
            glTranslatef(-0.5, 0.2, 50);
            jendela();
            frame();
            glPopMatrix(); //Pintu Dalam - Kiri
            glPopMatrix(); //Belakang
            glPopMatrix();
            glPopMatrix(); //Gedung F End

            glPushMatrix(); //Bangunan Kelas - Start
            glPushMatrix();
            glScalef(5, 1.5, 19);
            glTranslatef(0, -0.35, 0);
            cream(); //Gedung Tengah Lt. I
            glPushMatrix(); //Lantai Gedung Kelas
            glScalef(1.4, 0.05, 1.1);
            glTranslatef(0, -10, 0);
            cokelat();
            glPopMatrix(); //Lantai Gedung  Kelas
            glPopMatrix();

            glPushMatrix();
            glScalef(4.5, 1.2, 18.5);
            glTranslatef(0, 0.5, 0);
            cream(); //Gedung Tengah - Tengah
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 2.5, 20);
            glTranslatef(0, 1, 0);
            cream(); //Gedung Tengah Lt. II
            glPopMatrix();

            glPushMatrix(); //Atap Start
            glPushMatrix(); //Atap Persegi Start
            glPushMatrix(); //Atap Persegi Core Start
            glScalef(7, 0.25, 22);
            glTranslatef(0, 14.5, 0);
            cream();
            glPushMatrix(); //Atap Persegi Top Start
            glScalef(1.01, 0.25, 1.01);
            glTranslatef(0, 1.5, 0);
            cream();
            glPopMatrix(); //Atap Persegi Top End
            glPushMatrix(); //Atap Persegi Bot Start
            glScalef(1.01, 0.25, 1.01);
            glTranslatef(0, -1.5, 0);
            cream();
            glPopMatrix(); //Atap Persegi Bot End
            glPopMatrix(); //Atap Persegi Core End
            glPopMatrix(); //Atap Persegi End

            glPushMatrix(); //Atap Persegi Connector Start
            glScalef(6.5, 0.25, 21);
            glTranslatef(0, 15, 0);
            cream();
            glPopMatrix(); //Atap Persegi Connector End

            glPushMatrix(); //Genteng Start
            glScalef(7, 2, 22);
            glTranslatef(0, 1.9, 0);
            gentengtrapesium();
            garisAtap();
            glPopMatrix(); //Genteng End

            glPopMatrix(); //Atap End

            glPushMatrix(); //Jendela Start
            glPushMatrix(); //Jendela Lt II Start

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela Kanan Ujung
            glTranslatef(30, 3.8, 7.75);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela I
            glTranslatef(30, 3.8, 6.3);
            jendela();
            frame();
            glPushMatrix();
            glScalef(1, 1, 1); // Jendela II
            glTranslatef(0, 0, -1.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela III
            glTranslatef(0, 0, -2.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IV
            glTranslatef(0, 0, -4.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela V
            glTranslatef(0, 0, -5.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VI
            glTranslatef(0, 0, -7.05);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -8.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -9.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VIII
            glTranslatef(0, 0, -11.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IX
            glTranslatef(0, 0, -12.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela X
            glTranslatef(0, 0, -14.05);
            jendela();
            frame();
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela Kiri Ujung
            glTranslatef(-30, 3.8, 7.75);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(0.1, 0.7, 1.1); // Jendela I
            glTranslatef(-30, 3.8, 6.3);
            jendela();
            frame();
            glPushMatrix();
            glScalef(1, 1, 1); // Jendela II
            glTranslatef(0, 0, -1.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela III
            glTranslatef(0, 0, -2.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IV
            glTranslatef(0, 0, -4.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela V
            glTranslatef(0, 0, -5.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VI
            glTranslatef(0, 0, -7.05);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -8.45);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VII
            glTranslatef(0, 0, -9.85);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela VIII
            glTranslatef(0, 0, -11.25);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela IX
            glTranslatef(0, 0, -12.65);
            jendela();
            frame();
            glPopMatrix();

            glPushMatrix();
            glScalef(1, 1, 1); // Jendela X
            glTranslatef(0, 0, -14.05);
            jendela();
            frame();
            glPopMatrix();
            glPopMatrix();

            glPopMatrix(); //Jendela Lt II End
            glPopMatrix(); //Jendela End

            glPushMatrix(); //Bungkusan Pillar - Start
            glPushMatrix();
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, 40);
            cokelat(); //Pillar Lt. I Depan

            glPushMatrix();
            glTranslatef(-10, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-14, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-24, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPopMatrix();

            glPushMatrix();
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, -40);
            cokelat(); //Pillar Lt. I Belakang

            glPushMatrix();
            glTranslatef(-10, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-14, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-24, 0, 0);
            cokelat(); //Pillar Lt. I
            glPopMatrix();

            glPopMatrix();

            glPushMatrix(); //Pillar Samping Kanan
            glScalef(0.25, 5, 0.25);
            glTranslatef(12, 0.25, 40);

            glPushMatrix();
            glTranslatef(0, 0, -9.2);
            cokelat(); //Pillar I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -15.4);
            cokelat(); //Pillar II
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -21.6);
            cokelat(); //Pillar III
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -27.8);
            cokelat(); //Pillar IV
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -34);
            cokelat(); //Pillar V
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -40.2);
            cokelat(); //Pillar VI
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -46.4);
            cokelat(); //Pillar VII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -52.6);
            cokelat(); //Pillar VIII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -58.8);
            cokelat(); //Pillar IX
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -65);
            cokelat(); //Pillar X
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -71);
            cokelat(); //Pillar XI
            glPopMatrix();

            glPopMatrix();

            glPushMatrix(); //Pillar Samping Kiri
            glScalef(0.25, 5, 0.25);
            glTranslatef(-12, 0.25, 40);

            glPushMatrix();
            glTranslatef(0, 0, -9.2);
            cokelat(); //Pillar I
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -15.4);
            cokelat(); //Pillar II
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -21.6);
            cokelat(); //Pillar III
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -27.8);
            cokelat(); //Pillar IV
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -34);
            cokelat(); //Pillar V
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -40.2);
            cokelat(); //Pillar VI
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -46.4);
            cokelat(); //Pillar VII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -52.6);
            cokelat(); //Pillar VIII
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -58.8);
            cokelat(); //Pillar IX
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -65);
            cokelat(); //Pillar X
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0, 0, -71);
            cokelat(); //Pillar XI
            glPopMatrix();

            glPopMatrix();

            glPushMatrix();
            glScalef(0.05, 1, 20);
            glTranslatef(60, 0.75, 0);
            mesh(); //Mesh Kanan
            glPopMatrix();

            glPushMatrix();
            glScalef(0.05, 1, 20);
            glTranslatef(-60, 0.75, 0);
            mesh(); //Mesh Kiri
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 1, 0.05);
            glTranslatef(0, 0.75, 200);
            mesh(); //Mesh Depan
            glPopMatrix();

            glPushMatrix();
            glScalef(6, 1, 0.05);
            glTranslatef(0, 0.75, -200);
            mesh(); //Mesh Belakang
            glPopMatrix();

            glPopMatrix(); //Bungkusan Pillar - End

            glPopMatrix(); //Bangunan Kelas - End

            glTranslatef(20, 0, 0); //Copy Kanan II

                glPushMatrix(); //Bangunan Kelas - Start
                glPushMatrix();
                glScalef(5, 1.5, 19);
                glTranslatef(0, -0.35, 0);
                cream(); //Gedung Tengah Lt. I
                glPushMatrix(); //Lantai Gedung Kelas
                glScalef(1.4, 0.05, 1.1);
                glTranslatef(0, -10, 0);
                cokelat();
                glPopMatrix(); //Lantai Gedung  Kelas
                glPopMatrix();

                glPushMatrix();
                glScalef(4.5, 1.2, 18.5);
                glTranslatef(0, 0.5, 0);
                cream(); //Gedung Tengah - Tengah
                glPopMatrix();

                glPushMatrix();
                glScalef(6, 2.5, 20);
                glTranslatef(0, 1, 0);
                cream(); //Gedung Tengah Lt. II
                glPopMatrix();

                glPushMatrix(); //Atap Start
                glPushMatrix(); //Atap Persegi Start
                glPushMatrix(); //Atap Persegi Core Start
                glScalef(7, 0.25, 22);
                glTranslatef(0, 14.5, 0);
                cream();
                glPushMatrix(); //Atap Persegi Top Start
                glScalef(1.01, 0.25, 1.01);
                glTranslatef(0, 1.5, 0);
                cream();
                glPopMatrix(); //Atap Persegi Top End
                glPushMatrix(); //Atap Persegi Bot Start
                glScalef(1.01, 0.25, 1.01);
                glTranslatef(0, -1.5, 0);
                cream();
                glPopMatrix(); //Atap Persegi Bot End
                glPopMatrix(); //Atap Persegi Core End
                glPopMatrix(); //Atap Persegi End

                glPushMatrix(); //Atap Persegi Connector Start
                glScalef(6.5, 0.25, 21);
                glTranslatef(0, 15, 0);
                cream();
                glPopMatrix(); //Atap Persegi Connector End

                glPushMatrix(); //Genteng Start
                glScalef(7, 2, 22);
                glTranslatef(0, 1.9, 0);
                gentengtrapesium();
                garisAtap();
                glPopMatrix(); //Genteng End

                glPopMatrix(); //Atap End

                glPushMatrix(); //Jendela Start
                glPushMatrix(); //Jendela Lt II Start

                glPushMatrix();
                glScalef(0.1, 0.7, 1.1); // Jendela Kanan Ujung
                glTranslatef(30, 3.8, 7.75);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(0.1, 0.7, 1.1); // Jendela I
                glTranslatef(30, 3.8, 6.3);
                jendela();
                frame();
                glPushMatrix();
                glScalef(1, 1, 1); // Jendela II
                glTranslatef(0, 0, -1.45);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela III
                glTranslatef(0, 0, -2.85);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela IV
                glTranslatef(0, 0, -4.25);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela V
                glTranslatef(0, 0, -5.65);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VI
                glTranslatef(0, 0, -7.05);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VII
                glTranslatef(0, 0, -8.45);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VII
                glTranslatef(0, 0, -9.85);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VIII
                glTranslatef(0, 0, -11.25);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela IX
                glTranslatef(0, 0, -12.65);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela X
                glTranslatef(0, 0, -14.05);
                jendela();
                frame();
                glPopMatrix();
                glPopMatrix();

                glPushMatrix();
                glScalef(0.1, 0.7, 1.1); // Jendela Kiri Ujung
                glTranslatef(-30, 3.8, 7.75);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(0.1, 0.7, 1.1); // Jendela I
                glTranslatef(-30, 3.8, 6.3);
                jendela();
                frame();
                glPushMatrix();
                glScalef(1, 1, 1); // Jendela II
                glTranslatef(0, 0, -1.45);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela III
                glTranslatef(0, 0, -2.85);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela IV
                glTranslatef(0, 0, -4.25);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela V
                glTranslatef(0, 0, -5.65);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VI
                glTranslatef(0, 0, -7.05);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VII
                glTranslatef(0, 0, -8.45);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VII
                glTranslatef(0, 0, -9.85);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela VIII
                glTranslatef(0, 0, -11.25);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela IX
                glTranslatef(0, 0, -12.65);
                jendela();
                frame();
                glPopMatrix();

                glPushMatrix();
                glScalef(1, 1, 1); // Jendela X
                glTranslatef(0, 0, -14.05);
                jendela();
                frame();
                glPopMatrix();
                glPopMatrix();

                glPopMatrix(); //Jendela Lt II End
                glPopMatrix(); //Jendela End

                glPushMatrix(); //Bungkusan Pillar - Start
                glPushMatrix();
                glScalef(0.25, 5, 0.25);
                glTranslatef(12, 0.25, 40);
                cokelat(); //Pillar Lt. I Depan

                glPushMatrix();
                glTranslatef(-10, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-14, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-24, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPopMatrix();

                glPushMatrix();
                glScalef(0.25, 5, 0.25);
                glTranslatef(12, 0.25, -40);
                cokelat(); //Pillar Lt. I Belakang

                glPushMatrix();
                glTranslatef(-10, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-14, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(-24, 0, 0);
                cokelat(); //Pillar Lt. I
                glPopMatrix();

                glPopMatrix();

                glPushMatrix(); //Pillar Samping Kanan
                glScalef(0.25, 5, 0.25);
                glTranslatef(12, 0.25, 40);

                glPushMatrix();
                glTranslatef(0, 0, -9.2);
                cokelat(); //Pillar I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -15.4);
                cokelat(); //Pillar II
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -21.6);
                cokelat(); //Pillar III
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -27.8);
                cokelat(); //Pillar IV
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -34);
                cokelat(); //Pillar V
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -40.2);
                cokelat(); //Pillar VI
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -46.4);
                cokelat(); //Pillar VII
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -52.6);
                cokelat(); //Pillar VIII
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -58.8);
                cokelat(); //Pillar IX
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -65);
                cokelat(); //Pillar X
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -71);
                cokelat(); //Pillar XI
                glPopMatrix();

                glPopMatrix();

                glPushMatrix(); //Pillar Samping Kiri
                glScalef(0.25, 5, 0.25);
                glTranslatef(-12, 0.25, 40);

                glPushMatrix();
                glTranslatef(0, 0, -9.2);
                cokelat(); //Pillar I
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -15.4);
                cokelat(); //Pillar II
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -21.6);
                cokelat(); //Pillar III
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -27.8);
                cokelat(); //Pillar IV
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -34);
                cokelat(); //Pillar V
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -40.2);
                cokelat(); //Pillar VI
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -46.4);
                cokelat(); //Pillar VII
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -52.6);
                cokelat(); //Pillar VIII
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -58.8);
                cokelat(); //Pillar IX
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -65);
                cokelat(); //Pillar X
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, 0, -71);
                cokelat(); //Pillar XI
                glPopMatrix();

                glPopMatrix();

                glPushMatrix();
                glScalef(0.05, 1, 20);
                glTranslatef(60, 0.75, 0);
                mesh(); //Mesh Kanan
                glPopMatrix();

                glPushMatrix();
                glScalef(0.05, 1, 20);
                glTranslatef(-60, 0.75, 0);
                mesh(); //Mesh Kiri
                glPopMatrix();

                glPushMatrix();
                glScalef(6, 1, 0.05);
                glTranslatef(0, 0.75, 200);
                mesh(); //Mesh Depan
                glPopMatrix();

                glPushMatrix();
                glScalef(6, 1, 0.05);
                glTranslatef(0, 0.75, -200);
                mesh(); //Mesh Belakang
                glPopMatrix();

                glPopMatrix(); //Bungkusan Pillar - End

                glPopMatrix(); //Bangunan Kelas - End
                // Copy Kanan II End Here
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(lightPosX, lightPosY, lightPosZ);
    bobolaapi();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboardcontrol(unsigned char key, int x, int y) {
    float moveSpeed = 0.1f;
    float rotateSpeed = 3.0f;

    switch (key) {
        // GERAKAN KAMERA
    case 'w': // Maju
        cammanX += sin(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        cammanZ -= cos(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        break;
    case 's': // Mundur
        cammanX -= sin(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        cammanZ += cos(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        break;
    case 'a': // Kiri
        cammanX -= cos(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        cammanZ -= sin(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        break;
    case 'd': // Kanan
        cammanX += cos(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        cammanZ += sin(cammanYaw * 3.14159f / 180.0f) * moveSpeed;
        break;
    case 'q': // Naik
        cammanY += moveSpeed;
        break;
    case 'e': // Turun
        cammanY -= moveSpeed;
        break;

        // ROTASI KAMERA
    case 'j': // Putar kiri
        cammanYaw -= rotateSpeed;
        break;
    case 'l': // Putar kanan
        cammanYaw += rotateSpeed;
        break;
    case 'i': // Lihat atas
        cammanPitch -= rotateSpeed;
        break;
    case 'k': // Lihat bawah
        cammanPitch += rotateSpeed;
        break;

        // RESET KAMERA
    case 'r':
        cammanX = -7.75f, cammanY = 0.3f, cammanZ = 4.9f;
        cammanYaw = 90.0f, cammanPitch = 0.0f;
        break; 
    case 't': // Light naik
        lightPosY += moveSpeed;
        break;
    case 'g': // Light turun
        lightPosY -= moveSpeed;
        break;
    case 'f': // Light kiri
        lightPosX -= moveSpeed;
        break;
    case 'h': // Light kanan
        lightPosX += moveSpeed;
        break;
    case 'v': // Light maju
        lightPosZ -= moveSpeed;
        break;
    case 'b': // Light mundur
        lightPosZ += moveSpeed;
        break;
    case 'o': // Reset 
        lightPosX = 0.0f;
        lightPosY = 10.0f;
        lightPosZ = 0.0f;
        break;
    }

    // Limit anti kebalik
    if (cammanPitch > 89.0f) cammanPitch = 89.0f;
    if (cammanPitch < -89.0f) cammanPitch = -89.0f;
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    
    GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; 
    GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
    GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_NORMALIZE);

    glShadeModel(GL_SMOOTH);
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat default_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat default_shininess[] = { 10.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, default_shininess);

    glutKeyboardFunc(keyboardcontrol);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Project Fisipol");

    HWND hwnd = FindWindowA(NULL, "Project Fisipol");

    ShowWindow(hwnd, SW_RESTORE);

    SetWindowPos(hwnd, HWND_TOP, 0, 0, 1366, 768, SWP_SHOWWINDOW);
    ShowWindow(hwnd, SW_MAXIMIZE);
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
